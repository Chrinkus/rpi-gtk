#include <gtk/gtk.h>

enum province { MB, AB, SK, ON, QC, BC, NB, PE, NS, NL, NU, N_PROVINCES };
const char* const province[N_PROVINCES] = {
	[BC] = "British Columbia",
	[AB] = "Alberta",
	[SK] = "Saskatchewan",
	[MB] = "Manitoba",
	[ON] = "Ontario",
	[QC] = "Quebec",
	[NB] = "New Brunswick",
	[PE] = "Prince Edward Island",
	[NS] = "Nova Scotia",
	[NL] = "Newfoundland",
	[NU] = "Nunavut",
};

void end_program(GtkWidget* wid, gpointer ptr)
{
	gtk_main_quit();
}

void row_selected(GtkWidget* wid, gpointer ptr)
{
	GtkTreeSelection* sel;
	GtkTreeModel* model;
	GtkTreeIter iter;
	char* option;

	sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(wid));
	if (gtk_tree_selection_get_selected(sel, &model, &iter)) {
		gtk_tree_model_get(model, &iter, 0, &option, -1);
		printf("The selected row contains the text %s\n", option);
	}
}

int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);

	GtkWidget* win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget* btn = gtk_button_new_with_label("Close window");
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
	g_signal_connect(win, "delete-event", G_CALLBACK(end_program), NULL);

	GtkListStore* ls = gtk_list_store_new(2,
			G_TYPE_STRING,
			GDK_TYPE_PIXBUF);
	GdkPixbuf* icon = gtk_icon_theme_load_icon(
			gtk_icon_theme_get_default(),
			"dialog-ok-apply",
			32, 0, NULL);
	for (int i = 0; i < N_PROVINCES; ++i)
		gtk_list_store_insert_with_values(ls, NULL, i,
				0, province[i],	// col 0 string
				1, icon,	// col 1 pixbuf
				-1);		// terminator

	GtkWidget* tv = gtk_tree_view_new_with_model(GTK_TREE_MODEL(ls));
	g_signal_connect(tv, "cursor-changed", G_CALLBACK(row_selected), NULL);

	GtkCellRenderer* prend = gtk_cell_renderer_pixbuf_new();
	GtkCellRenderer* trend = gtk_cell_renderer_text_new();

	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tv),
			-1, "Icon", prend, "pixbuf", 1, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tv),
			-1, "Option", trend, "text", 0, NULL);

	GtkWidget* tbl = gtk_table_new(2, 2, FALSE);
	gtk_table_attach_defaults(GTK_TABLE(tbl), tv, 0, 2, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(tbl), btn, 0, 1, 1, 2);
	gtk_container_add(GTK_CONTAINER(win), tbl);
	gtk_widget_show_all(win);
	gtk_main();
	return 0;
}

