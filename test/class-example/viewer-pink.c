// This is a file for the class ViewerPink which
// is used in class-example.c
#include <glib.h>
#include <glib-object.h>
#include "viewer-pink.h"

// We define the type with three args:
// - Name of the type in camelcase (for values with that type)
// - Name of the type in lower_case (I think, for generating some functions with the type name)
// - The parent type.
G_DEFINE_TYPE(ViewerPink, viewer_pink, VIEWER_TYPE_FILE)

// We declare the function make_it_pink
// for the CLASS object for ViewerPinks
static void
viewer_pink_make_it_pink_impl(void) {
  g_print("VIEWER_PINK: made it pink\n");
}

// We declare the function open
// for the CLASS object for ViewerPinks
static void
viewer_pink_open_impl(ViewerFile *self, GError **error) {
  g_print("VIEWER_PINK: Pink viewer opened\n");
}

// Constructor for the class object.
static void
viewer_pink_class_init(ViewerPinkClass *klass) {
  klass->make_it_pink = viewer_pink_make_it_pink_impl;
  klass->open = viewer_pink_open_impl;
  g_print("Viewer pink class initialized\n");
}

// Constructor for the ViewerPink objects
static void
viewer_pink_init (ViewerPink *self) {
  g_print("Viewer pink object initialized\n");
}

// make_it_pink method for ViewerPink objects.
void viewer_make_it_pink(ViewerPink *self) {
  ViewerPinkClass *klass = VIEWER_PINK_GET_CLASS (self);
  klass->make_it_pink();
}
