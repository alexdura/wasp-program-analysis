#include <glib.h>
#include <glib-object.h>
#include "viewer-file.h"

/// Viewer file stuff
// This type has to be defined by the user, its purpose is to hold private data
// for the class.
typedef struct {
  int x;
} AnimalFelidPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (AnimalFelid, animal_felid, G_TYPE_OBJECT)

static void
animal_felid_open_impl(AnimalFelid *self, GError **error) {
  g_print("ANIMAL_FELID: Print file opened\n");
}

static void
animal_felid_class_init (AnimalFelidClass *klass)
{
  klass->open = animal_felid_open_impl;
  g_print("Viewer file class initialized\n");
}

static void
animal_felid_init (AnimalFelid *self)
{
  AnimalFelidPrivate *priv = animal_felid_get_instance_private (self);

  /* initialize all public and private members to reasonable default values.
   * They are all automatically initialized to 0 to begin with. */
  g_print("Felid object initialized\n");
}

void animal_felid_open(AnimalFelid *self, GError **error) {
  AnimalFelidClass *klass;
  klass = ANIMAL_FELID_GET_CLASS (self);
  klass->open(self, error);
}
