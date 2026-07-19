/* download-console */
static void downloadstarted(WebKitWebContext *wc, WebKitDownload *d,
                            Client *c);
static void downloadfailed(WebKitDownload *d, GParamSpec *ps, void *arg);
static void downloadfinished(WebKitDownload *d, GParamSpec *ps, void *arg);
static gboolean decidedestination(WebKitDownload *d,
                                  gchar *suggested_filename, void *arg);
static void printprogress(WebKitDownload *d, GParamSpec *ps, void *arg);
static void logdownload(WebKitDownload *d, gchar *tail);
static void spawndls(Client *c, const Arg *a);
