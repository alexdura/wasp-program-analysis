/*
 * Copyright/Licensing information.
 */

/* inclusion guard */
#ifndef __VIEWER_PINK_H__
#define __VIEWER_PINK_H__

#include "viewer-file.h"
#include <glib-object.h>
/*
 * Potentially, include other headers on which this header depends.
 */

G_BEGIN_DECLS

/*
 * Type declaration.
 */
#define ANIMAL_CAT_TYPE animal_cat_get_type() /* defined by the G_DECLARE... macro below */
/*
   viewer - module
   pink - class

   the name viewer_pink_get_type is generated by the macro G_DECLARE.. by concaten
*/
G_DECLARE_DERIVABLE_TYPE (AnimalCat, animal_cat, ANIMAL, CAT, AnimalFelid);

struct _AnimalCatClass
{
  GObjectClass parent_class;


  void (* jump) (AnimalFelid *opponent,
		  GError     **error);
  void (* meow) (void);


  /* Padding to allow adding up to 12 new virtual functions without
   * breaking ABI. */
  gpointer padding[12];
};

/*
 * Method definitions.
 */
AnimalCat * animal_cat_new (void);

// Inherit from ViewerFile
// void viewer_file_open(AnimalCat *self, GError **error);
void animal_cat_meow(AnimalCat *self);

G_END_DECLS

#endif /* __VIEWER_FILE_H__ */
