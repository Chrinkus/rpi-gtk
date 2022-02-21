#include <gtk/gtk.h>

void end_program(GtkWidget* wid, gpointer ptr)
{
	gtk_main_quit();
}

static void file_selected(GtkFileChooserButton* btn, gpointer ptr)
{
	printf("%s selected\n",
			gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(btn)));
}

static void save_file(GtkWidget* btn, gpointer ptr)
{
	GtkWidget* sch = gtk_file_chooser_dialog_new("Save file",
			GTK_WINDOW(ptr), GTK_FILE_CHOOSER_ACTION_SAVE,
			"Cancel", 0, "OK", 1, NULL);
	if (gtk_dialog_run(GTK_DIALOG(sch)) == 1) {
		printf("%s selected\n", gtk_file_chooser_get_filename(
					GTK_FILE_CHOOSER(sch)));
	}
	gtk_widget_destroy(sch);
}

static void col_selected(GtkColorButton* btn, gpointer ptr)
{
	GdkColor col;
	gtk_color_button_get_color(btn, &col);
	printf("red = %d, green = %d, blue = %d\n", col.red, col.green,
			col.blue);
}

static void fnt_selected(GtkFontButton* btn, gpointer ptr)
{
	printf("font = %s\n", gtk_font_button_get_font_name(btn));
}

int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);

	GtkWidget* win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget* btn = gtk_button_new_with_label("Close window");
	g_signal_connect(win, "delete-event", G_CALLBACK(end_program), NULL);
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program), win);

	GtkWidget* vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_add(GTK_CONTAINER(win), vbox);

	GtkWidget* fc_btn = gtk_file_chooser_button_new("Select file",
			GTK_FILE_CHOOSER_ACTION_OPEN);
	g_signal_connect(fc_btn, "file-set", G_CALLBACK(file_selected), NULL);

	GtkWidget* sv_btn = gtk_button_new_with_label("Select file");
	g_signal_connect(sv_btn, "clicked", G_CALLBACK(save_file), win);

	GtkWidget* col_btn = gtk_color_button_new();
	g_signal_connect(col_btn, "color-set", G_CALLBACK(col_selected), NULL);

	GtkWidget* fnt_btn = gtk_font_button_new();
	g_signal_connect(fnt_btn, "font-set", G_CALLBACK(fnt_selected), NULL);

	gtk_box_pack_start(GTK_BOX(vbox), fc_btn, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), sv_btn, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), col_btn, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), fnt_btn, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn, TRUE, TRUE, 0);

	gtk_widget_show_all(win);
	gtk_main();
	return 0;
}

