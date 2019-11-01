// This is a test file for casting incorrectly a value in gObject

#ifndef __INVALID_CAST_H__
#define __INVALID_CAST_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define MY_DOG_TYPE my_dog_get_type()
G_DECLARE_FINAL_TYPE(MyDog, my_dog, MY, DOG, GObject)

struct _MyDogClass {
    GObjectClass parent_class;

    // We need to store the methods here
    void (* bark) (MyDog*);
};

// We declare a method for this type.
void my_dog_bark(MyDog* self);

// Constructor
MyDog* my_dog_new(void);

// Destructor
void my_dog_dispose(MyDog* d);

G_END_DECLS

#endif 