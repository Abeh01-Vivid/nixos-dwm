void
playexternal(Client *c, const Arg *a)
{
	Arg arg;

	arg = (Arg)VIDEOPLAY(geturi(c));
	spawn(c, &arg);
}
