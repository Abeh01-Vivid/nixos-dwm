/* download-console */

void
downloadstarted(WebKitWebContext *wc, WebKitDownload *d, Client *c)
{
	webkit_download_set_allow_overwrite(d, TRUE);
	g_signal_connect(G_OBJECT(d), "decide-destination",
	                 G_CALLBACK(decidedestination), NULL);
	g_signal_connect(G_OBJECT(d), "notify::estimated-progress",
	                 G_CALLBACK(printprogress), NULL);
	g_signal_connect(G_OBJECT(d), "failed",
	                 G_CALLBACK(downloadfailed), NULL);
	g_signal_connect(G_OBJECT(d), "finished",
	                 G_CALLBACK(downloadfinished), NULL);
}

void
downloadfailed(WebKitDownload *d, GParamSpec *ps, void *arg)
{
	logdownload(d, " -- FAILED");
}

void
downloadfinished(WebKitDownload *d, GParamSpec *ps, void *arg)
{
	logdownload(d, " -- COMPLETED");

	#if AUTO_OPEN_PATCH
	Arg a = (Arg)AUTOOPEN(webkit_download_get_destination(d));
	spawn(NULL, &a);
	#endif // AUTO_OPEN_PATCH
}

gboolean
decidedestination(WebKitDownload *d, gchar *suggested_filename, void *arg)
{
	gchar *dest;
	dest = g_strdup_printf("file://%s/%s", downloaddir, suggested_filename);
	webkit_download_set_destination(d, dest);
	return TRUE;
}

void
printprogress(WebKitDownload *d, GParamSpec *ps, void *arg)
{
	logdownload(d, "");
}

void
logdownload(WebKitDownload *d, gchar *tail)
{
	gchar *filename, *statfile;
	FILE *stat;

	filename = g_path_get_basename(webkit_download_get_destination(d));
	statfile = g_strdup_printf("%s/%s", dlstatusdir, filename);

	if ((stat = fopen(statfile, "w")) == NULL) {
		perror("dlstatus");
	} else {
		fprintf(stat, "%s: %d%% (%d.%ds)%s\n",
		        filename,
		        (int)(webkit_download_get_estimated_progress(d) * 100),
		        (int) webkit_download_get_elapsed_time(d),
		        (int)(webkit_download_get_elapsed_time(d) * 100),
		        tail);
		fclose(stat);
	}

	g_free(statfile);
	g_free(filename);
}

void
spawndls(Client *c, const Arg *a)
{
	Arg arg = (Arg)DLSTATUS;
	spawn(c, &arg);
}
