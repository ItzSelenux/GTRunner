#include <gtk/gtk.h>
#include <libayatana-appindicator/app-indicator.h>

#define ML 256

GtkWidget *window, *dialog;
GKeyFile *key_file;
GtkTreeStore *tree_store;

guint cfg;
gchar *config_file_path;

#include "events.h"
#include "settings.h"
#include "cfgmgr.h"
#include "mainwindow.h"
