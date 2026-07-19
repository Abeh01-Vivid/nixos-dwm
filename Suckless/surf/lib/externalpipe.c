static void
externalpipe_execute(char* buffer, Arg *arg) {
	int to[2];
	void (*oldsigpipe)(int);
	if (pipe(to) == -1)
		return;
	switch (fork()) {
	case -1:
		close(to[0]);
		close(to[1]);
		return;
	case 0:
		dup2(to[0], STDIN_FILENO); close(to[0]); close(to[1]);
		execvp(((char **)arg->v)[0], (char **)arg->v);
		fprintf(stderr, "st: execvp %s\n", ((char **)arg->v)[0]);
		perror("failed");
		exit(0);
	}
	close(to[0]);
	oldsigpipe = signal(SIGPIPE, SIG_IGN);
	write(to[1], buffer, strlen(buffer));
	close(to[1]);
	signal(SIGPIPE, oldsigpipe);
}

static void
externalpipe_resource_done(GObject *obj, GAsyncResult *s, gpointer data)
{
	WebKitWebResource *r = WEBKIT_WEB_RESOURCE(obj);
	Arg *arg = (Arg *)data;
	GError *gerr = NULL;
	guchar *buffer = webkit_web_resource_get_data_finish(r, s, NULL, &gerr);
	if (gerr == NULL) {
		externalpipe_execute((char *) buffer, arg);
	} else {
		g_error_free(gerr);
	}
	g_free(buffer);
}

static void
externalpipe_js_done(GObject *obj, GAsyncResult *s, gpointer data)
{
	WebKitWebView *wv = WEBKIT_WEB_VIEW(obj);
	Arg *arg = (Arg *)data;
	GError *gerr = NULL;
	JSCValue *v = webkit_web_view_evaluate_javascript_finish(wv, s, &gerr);
	if (!v) {
		if (gerr)
			g_error_free(gerr);
		return;
	}
	if (jsc_value_is_string(v)) {
		char *buffer = jsc_value_to_string(v);
		externalpipe_execute(buffer, arg);
		g_free(buffer);
	}
	g_object_unref(v);
}

void
externalpipe(Client *c, const Arg *arg)
{
	if (curconfig[JavaScript].val.i) {
		webkit_web_view_evaluate_javascript(
			c->view, "window.document.documentElement.outerHTML", -1,
			NULL, NULL, NULL, externalpipe_js_done, (gpointer)arg);
	} else {
		WebKitWebResource *resource = webkit_web_view_get_main_resource(c->view);
		if (resource != NULL) {
			webkit_web_resource_get_data(
				resource, NULL, externalpipe_resource_done, (gpointer)arg);
		}
	}
}

#if EXTERNALPIPE_SIGNAL_PATCH
void
sigusr1(int unused)
{
	static Arg a = {.v = externalpipe_sigusr1};
	Client *c;
	for (c = clients; c; c = c->next)
		externalpipe(c, &a);
}
#endif // EXTERNALPIPE_SIGNAL_PATCH
