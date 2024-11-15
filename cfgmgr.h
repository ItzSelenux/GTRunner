void on_cell_edited(GtkCellRendererText *renderer, gchar *path, gchar *new_text, gpointer user_data)
{
	GtkTreeIter iter;
	GtkTreeModel *model = GTK_TREE_MODEL(tree_store);

	if (gtk_tree_model_get_iter_from_string(model, &iter, path))
	{
		gchar *section, *param;
		gtk_tree_model_get(model, &iter, 0, &section, 1, &param, -1);

		if (section && param)
		{
			g_key_file_set_string(key_file, section, param, new_text);
		}

		gtk_tree_store_set(tree_store, &iter, 2, new_text, -1);
		g_free(section);
		g_free(param);
	}
}

void create_cfg_widgets(void)
{
	tree_store = gtk_tree_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	gsize num_sections;
	gchar **sections = g_key_file_get_groups(key_file, &num_sections);

	for (gsize i = 0; i < num_sections; i++)
	{
		GtkTreeIter section_iter;
		gchar *mainicon = g_key_file_get_string(key_file, sections[i], "mainicon", NULL);
		gchar *elements = g_key_file_get_string(key_file, sections[i], "elements", NULL);
		gchar *commands = g_key_file_get_string(key_file, sections[i], "commands", NULL);

		gtk_tree_store_append(tree_store, &section_iter, NULL);
		gtk_tree_store_set(tree_store, &section_iter, 0, sections[i], 1, NULL, 2, NULL, -1);

		GtkTreeIter child_iter;
		gtk_tree_store_append(tree_store, &child_iter, &section_iter);
		gtk_tree_store_set(tree_store, &child_iter, 0, sections[i], 1, "mainicon", 2, mainicon ? mainicon : "", -1);

		gtk_tree_store_append(tree_store, &child_iter, &section_iter);
		gtk_tree_store_set(tree_store, &child_iter, 0, sections[i], 1, "elements", 2, elements ? elements : "", -1);

		gtk_tree_store_append(tree_store, &child_iter, &section_iter);
		gtk_tree_store_set(tree_store, &child_iter, 0, sections[i], 1, "commands", 2, commands ? commands : "", -1);

		g_free(mainicon);
		g_free(elements);
		g_free(commands);
	}

	g_strfreev(sections);

	GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(tree_store));
	g_object_unref(tree_store);

	GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
	GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("Section", renderer, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree_view), FALSE);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Parameter", renderer, "text", 1, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

	renderer = gtk_cell_renderer_text_new();
	g_object_set(renderer, "editable", TRUE, NULL);
	g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_edited), NULL);

	column = gtk_tree_view_column_new_with_attributes("Value", renderer, "text", 2, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

	GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);
	gtk_widget_set_size_request(scrolled_window, 600, 400);

	gtk_container_add(GTK_CONTAINER(window), scrolled_window);
}

void on_cfg(GtkWidget *button, gpointer data)
{
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(window), "GTRunner Settings");
		//gtk_window_set_icon(GTK_WINDOW(window));
		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
		gtk_container_set_border_width(GTK_CONTAINER(window), 1);
		g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

		create_cfg_widgets();

	gtk_widget_show_all(window);
}
