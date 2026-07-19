gboolean
scrollmultiply(GtkWidget *w, GdkEvent *e, Client *c)
{
	e->scroll.delta_y *= scroll_multiplier;
	return FALSE;
}
