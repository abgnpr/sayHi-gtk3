#include <gtk/gtk.h>

static void
print_entry(GtkWidget* widget, gpointer data)
{
    gchar* text = gtk_entry_get_text(GTK_ENTRY(data));
    g_print("Hi %s\n", text);
}

int main(int argc, char* argv[])
{
    GtkBuilder* builder;
    GObject* window;
    GObject* entry;
    GObject* button;
    GError* error = NULL;

    gtk_init(&argc, &argv);

    /* Construct a GtkBuilder instance and load our UI description */
    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "builder.ui", &error) == 0) {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    /* Connect signal handlers to the constructed widgets. */
    window = gtk_builder_get_object(builder, "window");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    entry = gtk_builder_get_object(builder, "entry");

    button = gtk_builder_get_object(builder, "say_hi");
    g_signal_connect(button, "clicked", G_CALLBACK(print_entry), entry);

    gtk_main();

    return 0;
}

// gcc `pkg-config --cflags gtk+-3.0` -o test hello.c `pkg-config --libs gtk+-3.0`