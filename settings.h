void create_indicator_for_section(const gchar *section);

void readconf(void)
{
	config_file_path = g_strdup_printf("%s/.config/gtrunner.conf", g_get_home_dir());
	key_file = g_key_file_new();
	GError *error = NULL;

	if (!g_key_file_load_from_file(key_file, config_file_path, G_KEY_FILE_NONE, &error))
	{
		g_warning("Error opening file: %s", error->message);
		g_error_free(error);
		g_key_file_free(key_file);
		g_free(config_file_path);
		return;
	}

	if (!cfg)
	{
		gsize num_sections;
		gchar **sections = g_key_file_get_groups(key_file, &num_sections);

		for (gsize i = 0; i < num_sections; i++)
		{
			create_indicator_for_section(sections[i]);
		}

		g_strfreev(sections);
		g_key_file_free(key_file);
	}
	g_free(config_file_path);
}

void saveconfig(void)
{
}
