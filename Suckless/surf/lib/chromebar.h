#include <ctype.h>

typedef struct {
	char *token;
	char *uri;
	int nr;
} SearchEngine;

#define SCHEME_CHAR(ch) (isalnum (ch) || (ch) == '-' || (ch) == '+')
#define DOMAIN_CHAR(ch) (isalnum (ch) || (ch) == '-' || (ch) == '.')

static const gchar *parseuri(const gchar *uri, char **parsed_uri);
static char **parse_address(const char *url);
static char **parse_url(char *str);
static int url_has_domain(char *url, char **parsed_uri);
