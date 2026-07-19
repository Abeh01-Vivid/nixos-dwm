void
clickplumb(Client *c, const Arg *a, WebKitHitTestResult *h)
{
	Arg arg;

	const char *s;
	WebKitHitTestResultContext e = webkit_hit_test_result_get_context(h);
	if (OnSel & e)
		s = gtk_clipboard_wait_for_text(gtk_clipboard_get(GDK_SELECTION_PRIMARY));
	else if ((OnLink|OnMedia|OnImg) & e)
		s = webkit_hit_test_result_get_link_uri(h);
	arg = (Arg)PLUMB(s);
	spawn(c, &arg);
}
