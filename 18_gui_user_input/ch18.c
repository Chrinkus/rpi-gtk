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

	GtkWidget* tbl = gtk_table_new(4, 2, TRUE);
	// Table cell edge coords: left, right, top, bottom
	gtk_table_attach_defaults(GTK_TABLE(tbl), lbl, 0, 2, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(tbl), copy, 0, 1, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(tbl), txt, 1, 2, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(tbl), rad1, 0, 1, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(tbl), rad2, 1, 2, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(tbl), chk, 0, 1, 3, 4);
	gtk_table_attach_defaults(GTK_TABLE(tbl), quit, 1, 2, 3, 4);

	gtk_container_add(GTK_CONTAINER(win), tbl);
	gtk_widget_show_all(win);
	gtk_main();
	return 0;
}

