#include<config.h>
#include<stdio.h>
#include<gtk/gtk.h>
void static call(GtkWidget *widget,gpointer data)
{
g_print("%s \n",(gchar*) data);
}
int main(int agrc, char *agrv[])
{
gtk_init(&agrc,&agrv);
GtkWidget *window,*button;
window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
gtk_window_set_title(GTK_WINDOW(window),"one button");
button=gtk_button_new_with_label("hello world");
g_signal_connect(button,"clicked",G_CALLBACK(call),(gpointer) "hello world");
gtk_container_set_border_width(GTK_CONTAINER(window),10);
gtk_container_add(GTK_CONTAINER(window),button);
gtk_widget_show_all(window);
gtk_main();
return (0);
}