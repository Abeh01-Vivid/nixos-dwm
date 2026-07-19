static void externalpipe(Client *c, const Arg *a);

#if EXTERNALPIPE_SIGNAL_PATCH
static void sigusr1(int unused);
#endif // EXTERNALPIPE_SIGNAL_PATCH
