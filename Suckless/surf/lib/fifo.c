static GFile *fifof;

static ParamMap paramnames[] = {
	{ "autoplay",     MediaManualPlay  },
	{ "caret",        CaretBrowsing    },
	{ "geolocation",  Geolocation      },
	{ "hidebg",       HideBackground   },
	{ "images",       LoadImages       },
	{ "indicators",   ShowIndicators   },
	{ "js",           JavaScript       },
	{ "kiosk",        KioskMode        },
	{ "microphone",   AccessMicrophone },
	{ "scrollbars",   ScrollBars       },
	{ "smoothscroll", SmoothScrolling  },
	{ "spellcheck",   SpellChecking    },
	{ "stricttls",    StrictTLS        },
	{ "style",        Style            },
	{ "webcam",       AccessWebcam     },
	{ "webgl",        WebGL            },
};

static Cmd commands[] = {
	{ "clipboard",        clipboard,          ARGTYPE_INT },
	{ "find",             find,               ARGTYPE_INT },
	{ "inject",           injectjs,           ARGTYPE_STR },
	{ "loaduri",          loaduri,            ARGTYPE_STR },
	{ "reload",           reload,             ARGTYPE_INT },
	{ "scrollh",          scrollh,            ARGTYPE_INT },
	{ "scrollv",          scrollv,            ARGTYPE_INT },
	{ "showcert",         showcert,           ARGTYPE_NIL },
	{ "spawn",            spawn,              ARGTYPE_STR },
	{ "stop",             stop,               ARGTYPE_NIL },
	{ "toggle",           togglewrapper,      ARGTYPE_STR },
	{ "togglecookies",    togglecookiepolicy, ARGTYPE_NIL },
	{ "togglefullscreen", togglefullscreen,   ARGTYPE_NIL },
	{ "toggleinspector",  toggleinspector,    ARGTYPE_NIL },
	{ "zoom",             zoom,               ARGTYPE_INT },
};

void
cleanup_fifo(void)
{
	GError *error = NULL;

	if (fifof != NULL)
		if (!g_file_delete(fifof, NULL, &error))
			g_warning("cleanup: couldn't delete fifo: %s\n", error->message);
}

gboolean
init_fifo(Client *c)
{
	gboolean r = FALSE;
	char *path = g_strconcat(fifodir, "/", winid, NULL);

	if (path) {
		if (g_file_test(path, G_FILE_TEST_EXISTS) && unlink(path))
			fprintf(stderr, "surf: couldn't unlink old fifo: %s\n", path);

		if (!mkfifo(path, 0600)) {
			r = start_fifo(c, path);
		} else {
			fprintf(stderr, "init_fifo: couldn't create fifo: %s\n", path);
			r = FALSE;
		}
	}


	// fifo info no longer needed
	g_free(fifodir);
	if (path)
		g_free(path);

	return r;
}

gboolean
start_fifo(Client *c, char *path)
{
	GError *error = NULL;
	GFileIOStream *fs;
	GOutputStream *os;
	GDataInputStream *is;
	fifof = g_file_new_for_path (path);

	/* open in read/write so no blocking occurs */
	fs = g_file_open_readwrite(fifof, NULL, &error);
	if (!fs) {
		fprintf(stderr, "surf: can't open: %s\n", error->message);
		g_error_free(error);
		return FALSE;
	}

	os = g_io_stream_get_output_stream(G_IO_STREAM(fs));
	if (!g_output_stream_close(os, NULL, &error)) {
		fprintf(stderr, "start_fifo: failed to close write end: %s\n",
		          error->message);
		g_error_free(error);
		return FALSE;
	}

	is = g_data_input_stream_new(g_io_stream_get_input_stream(G_IO_STREAM(fs)));

	g_data_input_stream_read_line_async(is, G_PRIORITY_DEFAULT, NULL,
	                                    &fifo_read_cb, c);

	g_setenv("SURF_FIFO", path, TRUE);

	return TRUE;
}

void
fifo_read_cb(GObject *f, GAsyncResult *r, gpointer d)
{
	Client *c = (Client *)d;
	GDataInputStream *s = (GDataInputStream *)f;
	GError *error = NULL;
	gsize length;
	gchar *rest;

	gchar *line = g_data_input_stream_read_line_finish(s, r, &length, &error);
	if (error) {
		fprintf(stderr, "fifo_read_cb: error reading: %s\n", error->message);
		return;
	}

	if (!line)
		return;

	line = strtok_r(line, " ", &rest);

	dispatchcmd(c, line, rest);

	g_data_input_stream_read_line_async(s, G_PRIORITY_DEFAULT, NULL,
	                                    &fifo_read_cb, c);
}

void
dispatchcmd(Client *c, char *cmd, char *a)
{
	Arg arg;
	int i;

	for (i = 0; i < LENGTH(commands); i++) {
		if (strcmp(cmd, commands[i].cmd) == 0) {
			switch (commands[i].t) {
			case ARGTYPE_STR: arg = (Arg)(const void *)a; break;
			case ARGTYPE_INT: arg = (Arg)atoi(a);         break;
			case ARGTYPE_FLT: arg = (Arg)(float)atof(a);  break;
			case ARGTYPE_NIL: arg = (Arg)0;               break;
			}

			if (commands[i].t == ARGTYPE_INT) {
				printf("%i\n", arg.i);
			}
			commands[i].func(c, (const Arg *)&arg);
			return;
		}
	}

	fprintf(stderr, "%s: no such command\n", cmd);
}

void
injectjs(Client *c, const Arg *a)
{
	evalscript(c, "%s", (char *)a->v);
}

void
togglewrapper(Client *c, const Arg *a)
{
	int i;

	for (i = 0; i < LENGTH(paramnames); i++) {
		if (strcmp(paramnames[i].p, (char *)a->v) == 0) {
			Arg targ = (Arg)(const void *)paramnames[i].pv;
			return toggle(c, &targ);
		}
	}

	fprintf(stderr, "toggle: no such setting '%s'", (char *)a->v);
}
