static void
loaduri(Client *c, const Arg *arg)
{
	const gchar *u;
	char *rp, *pt;
	const gchar *uri = arg->v;
	char **parsed_uri;
	char *home;
	char *path;
	int i;
	FILE *f;
	Arg a = { .i = 0 };

	if (*uri == '\0')
		return;

	pt=malloc(strlen(uri)+1);
	pt=strdup((char *)uri);
	parsed_uri = parse_url(pt);

	/* In case it's a file path. */
	if (strncmp(parsed_uri[0], "file://", 6) == 0 ||
		(strlen(parsed_uri[0]) == 0 && strlen(parsed_uri[1]) == 0)) {
		path=malloc(strlen(parsed_uri[1])+strlen(parsed_uri[2])+strlen(parsed_uri[3])+1);
		path=strcpy(path, parsed_uri[1]);
		path=strcat(path, parsed_uri[2]);
		path=strcat(path, parsed_uri[3]);

		if (path[0] == '~')	{
			home = getenv("HOME");
			home = realloc(home, strlen(path)+strlen(home));
			home = strcat(home, path+1);
			free(path);
			path = home;
		}
		rp = realpath(path, NULL);
		u = g_strdup_printf("file://%s", rp);
		free(path);
		free(rp);
	} else {
		u = parseuri(pt,parsed_uri);
	}

	free(pt);
	for (i = 0; i < 4; i++)
		free(parsed_uri[i]);
	free(parsed_uri);

	/* prevents endless loop */
	if (c->targeturi && strcmp(u, c->targeturi) == 0) {
		reload(c, &a);
		return;
	}

	webkit_web_view_load_uri(c->view, u);
	f = fopen(historyfile, "a+");
	fprintf(f, "%s", u);
	fclose(f);
	c->progress = 0;
	c->title = strdup(u);
	g_free((gpointer )u);
	updatetitle(c);
}

/* This function takes an url and chop it into three part: scheme, domain, the
 * rest, e.g. http://www.google.co.uk/search?q=hello will produce a triple
 * ('http://', 'www.google.co.uk', '/search?q=hello')
 */
static char **
parse_url(char *str)
{
	/* Return the position of ':' - last element of a scheme, or 0 if there
	 * is no scheme. */
	char *sch="";
	char *pt;
	char **ret;
	char **dret;
	int k,i = 0;

	pt=malloc(strlen(str)+1);
	pt=strcpy(pt, str);

	while (*pt == ' ')
		pt+=1;
	ret=malloc(4*sizeof(char *));

	/* The first char must be a scheme char. */
	if (!*pt || !SCHEME_CHAR (*pt)) {
		ret[0]=malloc(1);
		ret[0][0]='\0';
		dret=parse_address(pt);
		for (k=0;k<3;k++)
			ret[k+1]=dret[k];
		return ret;
	}
	++i;
	/* Followed by 0 or more scheme chars. */
	while (*(pt+i) && SCHEME_CHAR (*(pt+i))) {
		++i;
	}
	sch=malloc(i+4);
	sch=strncpy(sch, pt, i);
	sch[i]='\0';
	if (strlen(sch)) {
		sch=strcat(sch, "://");
	}

	/* Terminated by "://". */
	if (strncmp(sch, pt, strlen(sch)) == 0) {
		ret[0]=sch;
		/* dret=malloc(strlen(str)); */
		dret=parse_address(pt+i+3);
		for (k=0;k<3;k++)
			ret[k+1]=dret[k];
		return ret;
	}
	ret[0]=malloc(1);
	ret[0][0]='\0';
	dret=parse_address(str);
	for (k=0;k<3;k++)
		ret[k+1]=dret[k];
	return ret;
}

/*
 * This function takes an url without a scheme and outputs a pair: domain and
 * the rest.
 */
static char **
parse_address(const char *url)
{
	int n;
	size_t i=0;
	size_t u=strlen(url);
	char *domain;
	char *port;
	char **res=malloc(3*sizeof (char *));

	if (isalnum(*url)) {
		++i;
		while (*(url+i) && DOMAIN_CHAR (*(url+i)))
			++i;
	}
	domain=malloc(i+1);
	domain=strncpy(domain, url, i);
	domain[i]='\0';

	/* Check for a port number */
	if ( (u > i) && *(url+i) == ':' ) {
		n=i+1;
		while ( (n<=u) && (n<i+1+5) && isdigit(*(url+n)) ) {
			n++;
		}

		if (n > i + 1) {
			port=malloc(n-i+1);
			port=strncpy(port, (url+i), n-i);
			port[n-i+1]='\0';
		} else {
			port=malloc(1);
			port[0]='\0';
		}
	} else {
		n=i;
		port=malloc(1);
		port[0] = '\0';
	}

	res[0]=domain;
	res[1]=port;
	res[2]=malloc(strlen(url+n)+1);
	res[2]=strcpy(res[2], (url+n));
	return res;
}

/*
 * This function tests if the url has a qualified domain name.
 */
static int
url_has_domain(char *url, char **parsed_uri)
{
	char *domain=parsed_uri[1];
	char *rest=parsed_uri[3];

	if (strstr(domain, " ") != NULL)
		return false;

	if (! *domain || (*rest && rest[0] != '/'))
		return false;

	/* The domain name should contain at least one '.',
	 * unless it is "localhost" */
	if (strcmp(domain, "localhost") == 0)
		return true;

	if (strstr(domain, ".") != NULL)
		return true;

	return false;
}

static const gchar *
parseuri(const gchar *uri, char **parsed_uri)
{
	guint i;
	gchar *pt = g_strdup(uri);

	while (*pt == ' ')
		pt+=1;

	bool hdm = url_has_domain((char *) pt, parsed_uri);

	if (hdm)
		return g_strrstr(pt, "://") ? g_strdup(pt) : g_strdup_printf("http://%s", pt);

	for (i = 0; i < LENGTH(searchengines); i++) {
		if (searchengines[i].token == NULL || searchengines[i].uri == NULL)
			continue;

		if ((*(pt + strlen(searchengines[i].token)) == ' ' && g_str_has_prefix(pt, searchengines[i].token)))
		{
			switch (searchengines[i].nr) {
			case 0:
				return g_strdup_printf("%s", searchengines[i].uri);
				break;
			case 2:
				return g_strdup_printf(searchengines[i].uri, pt + strlen(searchengines[i].token) + 1, pt + strlen(searchengines[i].token) + 1);
				break;
			default:
				return g_strdup_printf(searchengines[i].uri, pt + strlen(searchengines[i].token) + 1);
				break;
			}
		}

		if (strcmp(pt, searchengines[i].token) == 0 && strstr(searchengines[i].token, "%s") == NULL) {
			return g_strdup_printf(searchengines[i].uri, "");
		}
	}
	return g_strdup_printf(searchengine, pt); // default search engine
}
