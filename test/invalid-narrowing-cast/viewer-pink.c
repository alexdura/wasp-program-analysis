#include <glib.h>
#include <glib-object.h>
#include "viewer-pink.h"

// The last argument is the type of the PARENT
// If you put the same type here, the program
// just loops, lol.
G_DEFINE_TYPE(AnimalCat, animal_cat, ANIMAL_FELID_TYPE)

static void
animal_cat_make_it_pink_impl(void) {
  g_print("CAT: made it pink\n");
}

static void
animal_cat_open_impl(AnimalFelid *self, GError **error) {
  g_print("CAT: Pink viewer opened\n");
}

static void
animal_cat_class_init(AnimalCatClass *klass) {
  klass->meow = animal_cat_make_it_pink_impl;
  klass->open = animal_cat_open_impl;
  g_print("CAT INITIALIZED \n");
}

static void
animal_cat_init (AnimalCat *self) {
  g_print("CAT INITIALIZED \n");
}

void animal_cat_meow(AnimalCat *self) {
  AnimalCatClass *klass = ANIMAL_CAT_GET_CLASS (self);
  klass->meow();
}
