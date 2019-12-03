#include <glib.h>
#include <glib-object.h>

#include "viewer-file.h"
#include "viewer-pink.h"

static void test_object (void)
{
  // Build a VIEWER_FILE object, but cast it to a subtype
  GObject *otherobj = g_object_new(ANIMAL_FELID_TYPE, NULL);
  AnimalFelid *fa = ANIMAL_FELID(otherobj); // cast to viewer file type
  animal_felid_open(fa, NULL); // this is correct
  AnimalCat *not_cat = ANIMAL_CAT(fa); // this is not correct
  animal_cat_meow(not_cat); // this should fail
  g_object_unref(G_OBJECT (otherobj));
}


int main() {
  test_object();
}
