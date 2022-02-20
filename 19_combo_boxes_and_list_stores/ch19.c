#include <gtk/gtk.h>

GtkWidget* txt;

void end_program(GtkWidget* wid, gpointer ptr)
{
	gtk_main_quit();
}

void copy_text(GtkWidget* wid, gpointer ptr)
{
	const char* input = gtk_entry_get_text(GTK_ENTRY(txt));
	gtk_label_set_text(GTK_LABEL(ptr), input);
}

void check_toggle(GtkWidget* wid, gpointer ptr)
{
	printf("The state of the button is %d\n",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid)));
}

void combo_changed(GtkWidget* wid, gpointer ptr)
{
	int sel = gtk_combo_box_get_active(GTK_COMBO_BOX(wid));
	char* selected = gtk_combo_box_text_get_active_text(
			GTK_COMBO_BOX_TEXT(wid));
	printf("The value of the combo is %d %s\n", sel, selected);
	gtk_label_set_text(GTK_LABEL(ptr), selected);
}

int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget* win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget* quit = gtk_button_new_with_label("Close window");
	g_signal_connect(quit, "clicked", G_CALLBACK(end_program), NULL);
	g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

	GtkWidget* lbl = gtk_label_new("My label");
	GtkWidget* copy = gtk_button_new_with_label("Copy button");
	g_signal_connect(copy, "clicked", G_CALLBACK(copy_text), lbl);

	GtkWidget* chk = gtk_check_button_new_with_label("My check");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(chk), TRUE);
	g_signal_connect(chk, "toggled", G_CALLBACK(check_toggle), NULL);

	GtkObject* adj = gtk_adjustment_new(0, -10, 10, 1, 0, 0);
	txt = gtk_spin_button_new(GTK_ADJUSTMENT(adj), 0, 0);

	GtkWidget* rad1 = gtk_radio_button_new_with_label(NULL, "Button 1");
	GSList* group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rad1));
	GtkWidget* rad2 = gtk_radio_button_new_with_label(group, "Button 2");

	// Chapter 19
	GtkWidget* comb = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comb), "Option 1");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comb), "Option 2");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comb), "Option 3");
	gtk_combo_box_set_active(GTK_COMBO_BOX(comb), 0);

	GtkWidget* lbl2 = gtk_label_new("Combo label");
	g_signal_connect(comb, "changed", G_CALLBACK(combo_changed), lbl2);

	int pos = 0;
	GtkListStore* ls = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_list_store_insert_with_values(ls, NULL, pos++, 0, "Ontario", -1);
	gtk_list_store_insert_with_values(ls, NULL, pos++, 0, "Manitoba", -1);
	gtk_list_store_insert_with_values(ls, NULL, pos++, 0, "Alberta", -1);
	gtk_list_store_insert_with_values(ls, NULL, pos++, 0, "Quebec", -1);

	//GtkWidget* comb2 = gtk_combo_box_new_with_model(GTK_TREE_MODEL(ls));
	GtkTreeModelSort* sorted = GTK_TREE_MODEL_SORT(
			gtk_tree_model_sort_new_with_model(
				GTK_TREE_MODEL(ls)));
	gtk_tree_sortable_set_sort_column_id(
			GTK_TREE_SORTABLE(sorted), 0, GTK_SORT_ASCENDING);
	GtkWidget* comb2 = gtk_combo_box_new_with_model(
			GTK_TREE_MODEL(sorted));
	GtkCellRenderer* rend = gtk_cell_renderer_text_new();

	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(comb2), rend, FALSE);
	gtk_cell_layout_add_attribute(GTK_CELL_LAYOUT(comb2), rend, "text", 0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(comb2), 0);

	GtkWidget* lbl3 = gtk_label_new("List combo");

	int rows = 6;
	GtkWidget* tbl = gtk_table_new(rows, 2, TRUE);
	// Table cell edge coords: left, right, top, bottom
	gtk_table_attach_defaults(GTK_TABLE(tbl), lbl, 0, 2, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(tbl), copy, 0, 1, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(tbl), txt, 1, 2, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(tbl), rad1, 0, 1, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(tbl), rad2, 1, 2, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(tbl), lbl2, 0, 1, 3, 4);
	gtk_table_attach_defaults(GTK_TABLE(tbl), comb, 1, 2, 3, 4);
	gtk_table_attach_defaults(GTK_TABLE(tbl), lbl3, 0, 1, 4, 5);
	gtk_table_attach_defaults(GTK_TABLE(tbl), comb2, 1, 2, 4, 5);
	gtk_table_attach_defaults(GTK_TABLE(tbl), chk, 0, 1, rows-1, rows);
	gtk_table_attach_defaults(GTK_TABLE(tbl), quit, 1, 2, rows-1, rows);

	gtk_container_add(GTK_CONTAINER(win), tbl);
	gtk_widget_show_all(win);
	gtk_main();
	return 0;
}

