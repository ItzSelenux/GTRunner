void on_menu_item_activate(GtkWidget *item, gpointer command)
{
	gchar *toexec = g_strdup(gtk_widget_get_name(item));
	g_info("Running command: %s\n", toexec);

	GError *error = NULL;
	GPid pid;
	gboolean success = g_spawn_async_with_pipes(NULL, (gchar *[]){"/bin/sh", "-c", toexec, NULL},
		NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, &pid, NULL, NULL, NULL, &error);

	if (!success)
	{
		g_warning("Error running command: %s", error->message);
		g_error_free(error);
	}
	else
	{
		g_spawn_close_pid(pid);
	}

	g_free(toexec);
}
