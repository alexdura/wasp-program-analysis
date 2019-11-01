/* This file is an example using GObject 
   inheritance mechanism
*/
#include <glib.h>
#include <glib-object.h>

#include "viewer-file.h"
#include "viewer-pink.h"

static void test_object (void)
{
  GObject *obj;
  // We create two values
  GValue obj_vala = G_VALUE_INIT;
  GValue obj_valb = G_VALUE_INIT;
  // This creates a new instance 
  // of the type VIEWER_TYPE_FILE
  // The function accepts key / value pairs
  // for setting properties, terminated by NULL.
  obj = g_object_new (VIEWER_TYPE_FILE, NULL);

  // Initialize obj_vala to its default value
  g_value_init (&obj_vala, VIEWER_TYPE_FILE);
  // I think this is the same thing, with a pointer to the type instead.
  // This means that obj_vala points to obj
  g_value_set_object (&obj_vala, obj);

  // We do the same for the b object...
  g_value_init (&obj_valb, G_TYPE_OBJECT);

  /* g_value_copy's semantics for G_TYPE_OBJECT types is to copy the reference.
   * This function thus calls g_object_ref.
   * It is interesting to note that the assignment works here because
   * VIEWER_TYPE_FILE is a G_TYPE_OBJECT.
   */
  // This copies obj_vala into obj_valb
  // (Just copies the reference)
  g_value_copy (&obj_vala, &obj_valb);

  // We decrease the reference pointer to those objects
  // (Does it destroy the objects, though?)
  // obj_vala and obj_valb both point to an object which
  // does not exist anymore.
  g_object_unref (G_OBJECT (obj));
  g_object_unref (G_OBJECT (obj));

  // This is another part,
  // We create two objects, one from parent class,
  // One from daughter class, and we look at what they do.
  GObject *pink = g_object_new(VIEWER_TYPE_PINK, NULL);
  // This is how you "call a method" in GObject
  viewer_file_open(pink, NULL);
  viewer_make_it_pink(pink);
  // Here we free the pink object.
  g_object_unref(G_OBJECT (pink));

  // Here we create an object of the parent class
  GObject *otherobj = g_object_new(VIEWER_TYPE_FILE, NULL);
  // We have a macro for casting.
  ViewerFile *vf = VIEWER_FILE(otherobj); // cast to viewer file type
  viewer_file_open(vf, NULL); // this is correct
  // Free as well.
  g_object_unref(G_OBJECT (otherobj));
}


int main() {
  test_object();
}
