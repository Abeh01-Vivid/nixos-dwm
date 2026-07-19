void
agent(Client *c, const Arg *arg)
{
	const char *s;
	WebKitSettings *settings;

	s = getatom(c, AtomAgent);
	settings = webkit_web_view_get_settings(c->view);
	g_object_set(G_OBJECT(settings), "user-agent", s, NULL);
}
