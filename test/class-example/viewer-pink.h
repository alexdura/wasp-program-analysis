
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

// This is a macro for encapsulating declaring things
G_BEGIN_DECLS

/*
 * Type declaration.
 */
#define VIEWER_TYPE_PINK viewer_pink_get_type() /* defined by the G_DECLARE... macro below */
/*
  Declares a derivable type (kind of like DEFINE_TYPE in the '.c' file)
*/
G_DECLARE_DERIVABLE_TYPE (ViewerPink, viewer_pink, VIEWER, PINK, ViewerFile)

// The struct of class object for the class viewer pink
struct _ViewerPinkClass
{
  GObjectClass parent_class;


  void (* open) (ViewerFile  *file,
                 GError     **error);
  void (* make_it_pink) (void);


  /* Padding to allow adding up to 12 new virtual functions without
   * breaking ABI. */
  gpointer padding[12];
};

/*
 * Method definitions.
 */
ViewerPink *viewer_pink_new (void);

// Inherit from ViewerFile
// void viewer_file_open(ViewerPink *self, GError **error);
void viewer_make_it_pink(ViewerPink *self);

G_END_DECLS

#endif /* __VIEWER_FILE_H__ */
