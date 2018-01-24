#include <gdk/gdk.h>
#include <gtk/gtk.h>
#define CLOG_MAIN
#include "clog.h"

enum { MY_LOGGER };
#define FILE_NAME "clipboard.log"

int usage(char *name)
{
  fprintf(stdout, "Usage: %s filename\nEx: clipboard.log\n", name);
  return (EXIT_FAILURE);
}

void handle_owner_change (
  GtkClipboard *clipboard,
  GdkEvent *event,
  gpointer data
) {
  (void)event, (void)data;

  char *text;

  if (gtk_clipboard_wait_is_text_available(clipboard)
    && (text = gtk_clipboard_wait_for_text(clipboard)))
    clog_info(CLOG(MY_LOGGER), "%s", text);
}

int main(int ac, char **av)
{
  GtkClipboard* clipboard;

  if (ac != 2)
    return (usage(*av));

  if (clog_init_path(MY_LOGGER, FILE_NAME))
  {
    fprintf(stderr, "Logger initialization failed.\n");
    return (EXIT_FAILURE);
  }

  gtk_init_check(NULL, NULL);
  clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

  g_signal_connect(
    clipboard,
    "owner-change",
    G_CALLBACK(handle_owner_change),
    NULL
  );

  gtk_main();

  clog_free(MY_LOGGER);
  return (EXIT_SUCCESS);
}