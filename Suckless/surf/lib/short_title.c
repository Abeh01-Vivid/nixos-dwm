void
toggletitle(Client *c, const Arg *a)
{
	extendedtitle = !extendedtitle;
	updatetitle(c);
}
