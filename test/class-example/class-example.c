#include <glib.h>
#include <glib-object.h>

#include "viewer-file.h"
#include "viewer-pink.h"

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

  GObject *pink = g_object_new(VIEWER_TYPE_PINK, NULL);
  viewer_file_open(pink, NULL);
  viewer_make_it_pink(pink);
  g_object_unref(G_OBJECT (pink));

  GObject *otherobj = g_object_new(VIEWER_TYPE_FILE, NULL);
  ViewerFile *vf = VIEWER_FILE(otherobj); // cast to viewer file type
  viewer_file_open(vf, NULL); // this is correct
  ViewerPink *not_pink = VIEWER_PINK(vf); // this is not correct
  viewer_make_it_pink(not_pink); // this should fail
  g_object_unref(G_OBJECT (otherobj));
}


int main() {
  test_object();
}
