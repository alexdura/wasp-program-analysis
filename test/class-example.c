#include <glib.h>
#include <glib-object.h>
#include "viewer-file.h"

/// Viewer file stuff


// This type has to be defined by the user, its purpose is to hold private data
// for the class.
typedef struct {
  int x;
} ViewerFilePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (ViewerFile, viewer_file, G_TYPE_OBJECT)

static void
viewer_file_class_init (ViewerFileClass *klass)
{
  g_print("Viewer file class initialized\n");
}

static void
viewer_file_init (ViewerFile *self)
{
  ViewerFilePrivate *priv = viewer_file_get_instance_private (self);

  /* initialize all public and private members to reasonable default values.
   * They are all automatically initialized to 0 to begin with. */
  g_print("Viewer file object initialized\n");
}

/// End of Viewer file stuff
static void test_object (void)
{
  GObject *obj;
  GValue obj_vala = G_VALUE_INIT;
  GValue obj_valb = G_VALUE_INIT;
  obj = g_object_new (VIEWER_TYPE_FILE, NULL);

  g_value_init (&obj_vala, VIEWER_TYPE_FILE);
  g_value_set_object (&obj_vala, obj);

  g_value_init (&obj_valb, G_TYPE_OBJECT);

  /* g_value_copy's semantics for G_TYPE_OBJECT types is to copy the reference.
   * This function thus calls g_object_ref.
   * It is interesting to note that the assignment works here because
   * VIEWER_TYPE_FILE is a G_TYPE_OBJECT.
   */
  g_value_copy (&obj_vala, &obj_valb);

  g_object_unref (G_OBJECT (obj));
  g_object_unref (G_OBJECT (obj));

  GObject *otherobj = g_object_new(VIEWER_TYPE_FILE, NULL);
  g_object_unref(G_OBJECT (otherobj));

}


int main() {
  test_object();
}
