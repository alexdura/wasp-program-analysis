// This file is where we define the viewer-file class 
// used in class-example.c
#include <glib.h>
#include <glib-object.h>
#include "viewer-file.h"

/// Viewer file stuff
// This type has to be defined by the user, its purpose is to hold private data
// for the class.
typedef struct {
  int x;
} ViewerFilePrivate;

// We create a type, where we give:
// - the name we want to give it 
// - the name we want to give it (again) but in lowecase with '_' (???!?)
// - The GType of parent type
// I suspect the second argument is for generating function names
// talking about the type you are defining.
G_DEFINE_TYPE_WITH_PRIVATE (ViewerFile, viewer_file, G_TYPE_OBJECT)

// We declare one method here
static void
viewer_file_open_impl(ViewerFile *self, GError **error) {
  g_print("VIEWER_FILE: Print file opened\n");
}

// We declare a contructor here
// This constructor is for the CLASS object
static void
viewer_file_class_init (ViewerFileClass *klass)
{
  // Assign viewer_file_open_impl
  // to "open" in the class object 
  klass->open = viewer_file_open_impl;
  g_print("Viewer file class initialized\n");
}

// This is a constructor for OBJECTS of the type ViewerFile
static void
viewer_file_init (ViewerFile *self)
{
  ViewerFilePrivate *priv = viewer_file_get_instance_private (self);

  /* initialize all public and private members to reasonable default values.
   * They are all automatically initialized to 0 to begin with. */
  g_print("Viewer file object initialized\n");
}

// Re-implementation of the method, which will call the 
// class version. 
// Each object asks their class what to do.
void viewer_file_open(ViewerFile *self, GError **error) {
  ViewerFileClass *klass;
  klass = VIEWER_FILE_GET_CLASS (self);
  klass->open(self, error);
}
