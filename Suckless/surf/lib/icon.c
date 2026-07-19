void
setup_default_icons(void)
{
	GdkPixbuf *gpix;
	GList *icons = NULL;
	int i;

	/* set icons */
	for (i = 0; i < IconLast; i++) {
		G_GNUC_BEGIN_IGNORE_DEPRECATIONS
		gpix = gdk_pixbuf_new_from_xpm_data(surf_xpm[i]);
		G_GNUC_END_IGNORE_DEPRECATIONS
		icons = g_list_prepend(icons, gpix);
	}
	gtk_window_set_default_icon_list(icons);
	for (i = 0; icons != NULL && i < IconLast; i++) {
		g_object_unref(icons->data);
		icons = g_list_remove_link(icons, icons);
	}
}
