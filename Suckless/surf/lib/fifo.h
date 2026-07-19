#include <sys/types.h>
#include <sys/stat.h>

typedef enum {
	ARGTYPE_INT,
	ARGTYPE_FLT,
	ARGTYPE_STR,
	ARGTYPE_NIL,
} ArgType;

typedef struct {
	char *cmd;
	void (*func)(Client *c, const Arg *a);
	ArgType t;
} Cmd;

typedef struct {
	char *p;
	ParamName pv;
} ParamMap;

static void cleanup_fifo(void);
static gboolean init_fifo(Client *c);
static gboolean start_fifo(Client *c, char *path);
static void fifo_read_cb(GObject *f, GAsyncResult *r, gpointer d);
static void dispatchcmd(Client *c, char *cmd, char *a);
static void injectjs(Client *c, const Arg *a);
static void togglewrapper(Client *c, const Arg *a);
