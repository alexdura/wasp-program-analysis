/*
 * Copyright/Licensing information.
 */

/* inclusion guard */
#ifndef __FELID_H__
#define __FELID_H__

#include <glib-object.h>
/*
 * Potentially, include other headers on which this header depends.
 */

G_BEGIN_DECLS

/*
 * Type declaration.
 */
#define ANIMAL_FELID_TYPE animal_felid_get_type ()
G_DECLARE_DERIVABLE_TYPE (AnimalFelid, animal_felid, ANIMAL, FELID, GObject)

struct _AnimalFelidClass
{
  GObjectClass parent_class;

  /* Class virtual function fields. */
  void (* open) (AnimalFelid *file,
		 GError     **error);

  /* Padding to allow adding up to 12 new virtual functions without
   * breaking ABI. */
  gpointer padding[12];
};

/*
 * Method definitions.
 */
AnimalFelid *animal_felid_new (void);
void animal_felid_open(AnimalFelid *self, GError **error);

G_END_DECLS

#endif /* __FELID_H__ */
