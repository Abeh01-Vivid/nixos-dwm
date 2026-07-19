static void
selhist(Client *c, const Arg *arg)
{
	WebKitBackForwardList *lst;
	WebKitBackForwardListItem *cur;
	gint i;
	gchar *out;
	gchar *tmp;
	gchar *line;

	out = g_strdup("");

	if (!(lst = webkit_web_view_get_back_forward_list(c->view)))
		return;

	GList *backlist = webkit_back_forward_list_get_back_list(lst);
	GList *fwdlist  = webkit_back_forward_list_get_forward_list(lst);

	for (i = g_list_length(backlist); i > 0; i--) {
		if (!(cur = webkit_back_forward_list_get_nth_item(lst, -i)))
			break;
		line = g_strdup_printf("%d: %s\n", -i,
		                       webkit_back_forward_list_item_get_original_uri(cur));
		tmp = g_strconcat(out, line, NULL);
		g_free(out);
		g_free(line);
		out = tmp;
	}
	if ((cur = webkit_back_forward_list_get_nth_item(lst, 0))) {
		line = g_strdup_printf("%d: %s", 0,
		                       webkit_back_forward_list_item_get_original_uri(cur));
		tmp = g_strconcat(out, line, NULL);
		g_free(out);
		g_free(line);
		out = tmp;
	}
	for (i = 1; i <= (gint)g_list_length(fwdlist); i++) {
		if (!(cur = webkit_back_forward_list_get_nth_item(lst, i)))
			break;
		line = g_strdup_printf("\n%d: %s", i,
		                       webkit_back_forward_list_item_get_original_uri(cur));
		tmp = g_strconcat(out, line, NULL);
		g_free(out);
		g_free(line);
		out = tmp;
	}
	setatom(c, AtomHist, out);
	g_list_free(backlist);
	g_list_free(fwdlist);
	g_free(out);
	spawn(c, arg);
}

static void
navhist(Client *c, const Arg *arg)
{
	Arg a = { .i = atoi(arg->v) };
	navigate(c, &a);
}