static char **filter_patterns = NULL;
static regex_t *filter_expressions = NULL;
static size_t filter_count = 0;

static int
filter_init(const char *path)
{
	FILE *f;
	char line[BUFSIZ];
	char *errorbuf;
	int errors = 0;
	size_t capacity = 16;

	f = fopen(path, "r");
	if (!f) {
		fprintf(stderr, "surf: could not open filter file: %s\n", path);
		return 0;
	}

	filter_patterns = malloc(sizeof(char *) * capacity);
	filter_count = 0;

	while (fgets(line, sizeof(line), f)) {
		/* strip trailing newline */
		line[strcspn(line, "\n")] = '\0';
		/* skip empty lines and comments */
		if (line[0] == '\0' || line[0] == '#')
			continue;
		if (filter_count >= capacity) {
			capacity *= 2;
			filter_patterns = realloc(filter_patterns, sizeof(char *) * capacity);
		}
		filter_patterns[filter_count++] = strdup(line);
	}
	fclose(f);

	filter_expressions = malloc(sizeof(regex_t) * filter_count);
	errorbuf = malloc(sizeof(char) * BUFSIZ);

	for (size_t idx = 0; idx < filter_count; idx++) {
		int err = regcomp(&filter_expressions[idx], filter_patterns[idx],
		                  REG_EXTENDED | REG_ICASE | REG_NOSUB);
		if (err != 0) {
			regerror(err, &filter_expressions[idx], errorbuf, BUFSIZ);
			fprintf(stderr, "surf: failed to compile \"%s\": %s\n",
			        filter_patterns[idx], errorbuf);
			errors = 1;
		}
	}

	free(errorbuf);
	return !errors;
}

static void
filter_cleanup(void)
{
	for (size_t idx = 0; idx < filter_count; idx++) {
		regfree(&filter_expressions[idx]);
		free(filter_patterns[idx]);
	}
	free(filter_expressions);
	free(filter_patterns);
	filter_count = 0;
}

static int
filter_request(const gchar *uri)
{
	if (!strcmp(uri, "about:blank"))
		return 0;
	for (size_t idx = 0; idx < filter_count; idx++) {
		if (regexec(&filter_expressions[idx], uri, 0, NULL, 0) != REG_NOMATCH) {
			#if URL_FILTERING_VERBOSE_PATCH
			fprintf(stderr, "surf: filtering \"%s\"\n", uri);
			#endif
			return 1;
		}
	}
	#if URL_FILTERING_VERBOSE_PATCH
	fprintf(stderr, "surf: not filtering \"%s\"\n", uri);
	#endif
	return 0;
}
