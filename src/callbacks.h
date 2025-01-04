/*
 * Copyright (C) 2003-2025 Jason Woodward <woodwardj at jaos dot org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <config.h>
#include <gtk/gtk.h>
#include <slapt.h>
#define RC_LOCATION "/etc/slapt-get/slapt-getrc"


/*
 * Standard gettext macros.
 */
#include <libintl.h>
#undef _
#define _(String) dgettext(PACKAGE, String)
#define P_(String, String_p, n) ngettext(String, String_p, n)
#ifdef gettext_noop
#define N_(String) gettext_noop(String)
#else
#define N_(String) (String)
#endif

enum {
    STATUS_ICON_COLUMN,
    NAME_COLUMN,
    VERSION_COLUMN,
    LOCATION_COLUMN,
    SERIES_COLUMN,
    DESC_COLUMN,
    SIZE_COLUMN,
    STATUS_COLUMN,
    VISIBLE_COLUMN,
    INST_COLUMN,
    MARKED_COLUMN,
    UPGRADEABLE_COLUMN,
    NUMBER_OF_COLUMNS
};

gboolean gslapt_window_resized(GtkWindow *window, GdkEvent *event, gpointer data);
void on_gslapt_destroy(GObject *object, gpointer user_data);
void update_callback(GObject *object, gpointer user_data);
void upgrade_callback(GObject *object, gpointer user_data);
void execute_callback(GObject *object, gpointer user_data);
void search_activated(GtkWidget *gslapt, gpointer user_data);
void add_pkg_for_install(GtkWidget *gslapt, gpointer user_data);
void add_pkg_for_reinstall(GtkWidget *gslapt, gpointer user_data);
void add_pkg_for_removal(GtkWidget *gslapt, gpointer user_data);
void build_installed_treeviewlist(GtkWidget *);
void build_available_treeviewlist(GtkWidget *);
void build_searched_treeviewlist(GtkWidget *, gchar *pattern);
void open_about(GObject *object, gpointer user_data);

void show_pkg_details(GtkTreeSelection *selection, gpointer data);

void preferences_sources_add(GtkWidget *w, gpointer user_data);
void preferences_sources_remove(GtkWidget *w, gpointer user_data);
void preferences_sources_edit(GtkWidget *w, gpointer user_data);
void preferences_sources_modify(GtkWidget *w, gpointer user_data);
void preferences_on_ok_clicked(GtkWidget *w, gpointer user_data);

void transaction_okbutton_clicked(GtkWidget *w, gpointer user_data);
void preferences_exclude_add(GtkWidget *w, gpointer user_data);
void preferences_exclude_remove(GtkWidget *w, gpointer user_data);

int gtk_progress_callback(void *data, off_t dltotal, off_t dlnow, off_t ultotal, off_t ulnow);
void build_package_treeviewlist(GtkWidget *treeview);

void cancel_preferences(GtkWidget *w, gpointer user_data);
void cancel_transaction(GtkWidget *w, gpointer user_data);

void unmark_package(GtkWidget *gslapt, gpointer user_data);

void build_treeview_columns(GtkWidget *treeview);

void on_button_cancel_clicked(GtkButton *button, gpointer user_data);

GtkEntryCompletion *build_search_completions(void);

void repositories_changed_callback(GtkWidget *repositories_changed, gpointer user_data);

/* menu callbacks */
void clean_callback(GtkWidget *widget, gpointer user_data);
void open_preferences(GtkMenuItem *menuitem, gpointer user_data);
void open_icon_legend(GObject *object, gpointer user_data);
void unmark_all_activate(GtkMenuItem *menuitem, gpointer user_data);
void update_activate(GtkMenuItem *menuitem, gpointer user_data);
void mark_all_upgrades_activate(GtkMenuItem *menuitem, gpointer user_data);
void execute_activate(GtkMenuItem *menuitem, gpointer user_data);

slapt_vector_t *parse_disabled_package_sources(const char *file_name);

void view_all_packages(GtkMenuItem *menuitem, gpointer user_data);
void view_available_packages(GtkMenuItem *menuitem, gpointer user_data);
void view_installed_packages(GtkMenuItem *menuitem, gpointer user_data);

void view_marked_packages(GtkMenuItem *menuitem, gpointer user_data);

void mark_obsolete_packages(GtkMenuItem *menuitem, gpointer user_data);

#ifdef SLAPT_HAS_GPGME
void preferences_sources_add_key(GtkWidget *w, gpointer user_data);
#endif

void view_upgradeable_packages(GtkMenuItem *menuitem, gpointer user_data);
void view_changelogs(GtkMenuItem *menuitem, gpointer user_data);

void cancel_source_edit(GtkWidget *w, gpointer user_data);
void source_edit_ok(GtkWidget *w, gpointer user_data);

GdkPixbuf *gslapt_img(const char *img);
void gslapt_load_ui(GtkBuilder *b, const char *f);
