gchar *
parseuri(const gchar *uri)
{
	guint i;

	for (i = 0; i < LENGTH(searchengines); i++) {
		if (g_str_has_prefix(uri, searchengines[i].token)) {
			return g_strdup_printf(searchengines[i].uri,
				uri + strlen(searchengines[i].token));
		}
	}

	return g_strdup_printf("http://%s", uri);
}
