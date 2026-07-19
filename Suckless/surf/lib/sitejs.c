void
runsitescripts(Client *c, const char *uri)
{
	gchar *script;
	gsize l;
	int i;

	for (i = 0; i < LENGTH(scripts); ++i) {
		if (scripts[i].regex && !regexec(&(scripts[i].re), uri, 0, NULL, 0)) {
			runscript(c, scripts[i].file);
		}
	}

	#if MULTIJS_PATCH
	for (i = 0; i < LENGTH(scriptfiles); i++) {
		runscript(c, scriptfiles[i]);
	}
	#else
	runscript(c, scriptfile);
	#endif // MULTIJS_PATCH
}

void
runscript(Client *c, const char *file)
{
	gchar *script;
	gsize l;

	if (g_file_get_contents(file, &script, &l, NULL) && l)
 		evalscript(c, "%s", script);
	g_free(script);
}
