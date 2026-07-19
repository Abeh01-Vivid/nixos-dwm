void
handle_zoommtg(WebKitURISchemeRequest *request)
{
	const char* uri = webkit_uri_scheme_request_get_uri (request);
	Arg a = (Arg)PLUMB(uri);
	printf("handleplumb: %s",(char*)a.v);
	if (fork() == 0) {
		if (dpy)
			close(ConnectionNumber(dpy));
		close(spair[0]);
		close(spair[1]);
		setsid();
		execvp(((char **)a.v)[0], (char **)a.v);
		fprintf(stderr, "%s: execvp %s", argv0, ((char **)a.v)[0]);
		perror(" failed");
		exit(1);
	}
}
