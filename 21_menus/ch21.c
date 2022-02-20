#include <gtk/gtk.h>

void end_program(GtkWidget* wid, gpointer ptr)
{
	gtk_main_quit();
}

void print_label(GtkWidget* wid, gpointer ptr)
{
	const char* lbl = gtk_menu_item_get_label(GTK_MENU_ITEM(wid));
	printf("%s callback activated\n", lbl);
}

void button_popup(GtkWidget* wid, gpointer ptr)
{
	GtkWidget* f_menu = gtk_menu_new();
	GtkWidget* quit_mi = gtk_menu_item_new_with_label("Quit");
	gtk_menu_shell_append(GTK_MENU_SHELL(f_menu), quit_mi);
	g_signal_connect(quit_mi, "activate", G_CALLBACK(end_program), NULL);

	gtk_widget_show_all(f_menu);
	gtk_menu_popup(GTK_MENU(f_menu), NULL, NULL, NULL, NULL, 1,
			gtk_get_current_event_time());
}

int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);

	GtkWidget* win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget* btn = gtk_button_new_with_label("Close window");
	g_signal_connect(btn, "clicked", G_CALLBACK(button_popup), NULL);
	g_signal_connect(win, "delete-event", G_CALLBACK(end_program), NULL);

	GtkWidget* mbar = gtk_menu_bar_new();

	GtkWidget* file_mi = gtk_menu_item_new_with_label("File");
	gtk_menu_shell_append(GTK_MENU_SHELL(mbar), file_mi);

	GtkWidget* f_menu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_mi), f_menu);

	GtkWidget* quit_mi = gtk_menu_item_new_with_label("Quit");
	gtk_menu_shell_append(GTK_MENU_SHELL(f_menu), quit_mi);
	g_signal_connect(quit_mi, "activate", G_CALLBACK(end_program), NULL);

	GtkWidget* edit_mi = gtk_menu_item_new_with_label("Edit");
	gtk_menu_shell_append(GTK_MENU_SHELL(mbar), edit_mi);

	GtkWidget* e_menu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit_mi), e_menu);

	GtkWidget* cut_mi = gtk_menu_item_new_with_label("Cut");
	gtk_menu_shell_append(GTK_MENU_SHELL(e_menu), cut_mi);
	g_signal_connect(cut_mi, "activate", G_CALLBACK(print_label), NULL);

	GtkWidget* copy_mi = gtk_menu_item_new_with_label("Copy");
	gtk_menu_shell_append(GTK_MENU_SHELL(e_menu), copy_mi);
	g_signal_connect(copy_mi, "activate", G_CALLBACK(print_label), NULL);

	GtkWidget* paste_mi = gtk_menu_item_new_with_label("Paste");
	gtk_menu_shell_append(GTK_MENU_SHELL(e_menu), paste_mi);
	g_signal_connect(paste_mi, "activate", G_CALLBACK(print_label), NULL);

	GtkWidget* vbox = gtk_vbox_new(FALSE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), mbar, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn, TRUE, TRUE, 0);

	gtk_container_add(GTK_CONTAINER(win), vbox);
	gtk_widget_show_all(win);
	gtk_main();
	return 0;
}

