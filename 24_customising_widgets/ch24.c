#include <gtk/gtk.h>

void end_program(GtkWidget* wid, gpointer ptr)
{
	gtk_main_quit();
}

int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);

	GtkWidget* win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget* btn = gtk_button_new_with_label("Close window");
	g_signal_connect(win, "delete-event", G_CALLBACK(end_program), NULL);
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program), win);

	GtkWidget* btn1 = gtk_button_new_with_label("Naked button");
	g_object_set(G_OBJECT(btn1), "relief", GTK_RELIEF_NONE, NULL);

	GtkWidget* btn2 = gtk_button_new_with_label("Alt _button");
	g_object_set(G_OBJECT(btn2), "use-underline", TRUE, NULL);

	GtkWidget* lbl = gtk_label_new("My label");
	g_object_set(G_OBJECT(lbl), "angle", 45.0, NULL);

	GtkWidget* vbox = gtk_vbox_new(FALSE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), btn1, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn2, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), lbl, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn, TRUE, TRUE, 0);

	gtk_container_add(GTK_CONTAINER(win), vbox);
	gtk_widget_show_all(win);
	gtk_main();
	return 0;
}

