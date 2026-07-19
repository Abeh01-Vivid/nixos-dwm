void
search(Client *c, const Arg *a)
{
	Arg arg;
	char *url;

	url = g_strdup_printf(searchengine, a->v);
	arg.v = url;
	loaduri(c, &arg);

	g_free(url);
}
