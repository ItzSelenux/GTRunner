void on_about(GtkMenuItem *menuitem, gpointer userdata)
{
	dialog = gtk_about_dialog_new();
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "GTRunner");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "Copyright © 2024 ItsZariep");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "Run commands from tray");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), pver);
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "https://codeberg.org/itszariep/gtrunner");
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(dialog), "Project WebSite");
	gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(dialog),GTK_LICENSE_GPL_3_0);
	gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(dialog),"info");

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

void create_indicator_for_section(const gchar *section)
{
	gchar *mainicon = g_key_file_get_string(key_file, section, "mainicon", NULL),
	*elements = g_key_file_get_string(key_file, section, "elements", NULL),
	*commands = g_key_file_get_string(key_file, section, "commands", NULL),
	*icons = g_key_file_get_string(key_file, section, "icons", NULL);

	AppIndicator *indicator = app_indicator_new(
		section,
		mainicon ? mainicon : "default-icon",
		APP_INDICATOR_CATEGORY_APPLICATION_STATUS);

	GtkWidget *menu = gtk_menu_new();

	if (elements && commands)
	{
		gchar **element_list = g_strsplit(elements, ",", -1),
		**command_list = g_strsplit(commands, ",", -1),
		**icons_list = g_strsplit(icons, ",", -1);

		for (int i = 0; element_list[i] != NULL && command_list[i] != NULL; i++)
		{
			GtkWidget *menu_item = gtk_menu_item_new(),
				*box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6),
					*image = gtk_image_new_from_icon_name(icons_list[i], GTK_ICON_SIZE_MENU),
					*label = gtk_label_new(element_list[i]);

				gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 0);
				gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

			gtk_container_add(GTK_CONTAINER(menu_item), box);
			gtk_widget_set_name(menu_item, command_list[i]);
			g_signal_connect(menu_item, "activate", G_CALLBACK(on_menu_item_activate), command_list[i]);
			gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);
		}
		g_strfreev(element_list);
		g_strfreev(command_list);
	}

	gtk_widget_show_all(menu);
	app_indicator_set_menu(indicator, GTK_MENU(menu));

	app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);

	g_free(mainicon);
	g_free(elements);
	g_free(commands);
}

void create_window(void)
{
	readconf();

	if (cfg)
	{
		on_cfg(window, NULL);
	}

	gtk_main();
}
