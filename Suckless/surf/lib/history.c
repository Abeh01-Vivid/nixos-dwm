void
updatehistory(const char *url)
{
	FILE *f;
	f = fopen(historyfile, "a+");

	char timestamp[20];
	time_t now = time (0);
	strftime (timestamp, 20, "%Y-%m-%dT%H:%M:%S", localtime (&now));

	fprintf(f, "%s %s\n", timestamp, url);
	fclose(f);
}
