#include <glib.h>
#include <glib-object.h>
#include "animal-felid.h"

/// Viewer file stuff
// This type has to be defined by the user, its purpose is to hold private data
// for the class.
typedef struct {
  int x;
} AnimalFelidPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (AnimalFelid, animal_felid, G_TYPE_OBJECT)

static void
animal_felid_jump_impl(AnimalFelid *self, GError **error) {
  g_print("ANIMAL_FELID: Boing! \n");
}

static void
animal_felid_class_init (AnimalFelidClass *klass)
{
  klass->jump = animal_felid_jump_impl;
  g_print("FELID INITIALIZED \n");
}

static void
animal_felid_init (AnimalFelid *self)
{
  AnimalFelidPrivate *priv = animal_felid_get_instance_private (self);

  /* initialize all public and private members to reasonable default values.
   * They are all automatically initialized to 0 to begin with. */
  g_print("Felid object initialized\n");
}

void animal_felid_jump(AnimalFelid *self, GError **error) {
  AnimalFelidClass *klass;
  klass = ANIMAL_FELID_GET_CLASS (self);
  klass->jump(self, error);
}
