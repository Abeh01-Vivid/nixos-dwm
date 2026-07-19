static int insertmode = 0;

void
insert(Client *c, const Arg *a)
{
	insertmode = (a->i);
}
