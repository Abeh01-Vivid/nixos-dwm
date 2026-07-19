#include <regex.h>

static int filter_init(const char *path);
static void filter_cleanup(void);
static int filter_request(const gchar *uri);
