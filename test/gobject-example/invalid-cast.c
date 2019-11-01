#include <glib-object.h>
#include "invalid-cast.h"

// This is needed because the class was declared using
// G_DECLARE_FINAL_TYPE in the header file.
struct _MyDog {
    /* FUN FACT:
    if you forget to add this, it will still compile!
    however, the function g_object_new() will return
    zero, and the MY_DOG_TYPE function will also return zero.
    Thankfully, when you run the program, you get very helpful
    error messages of this kind:
    - specified instance size of type "MyDog" is smaller than 'GTypeInstance' size
    - g_once_init_leave: assertion 'result != 0' failed
    - assertion G_TYPE_IS_OBJECT(object_type) failed
    Most interestingly, if you have a class which you can inherit
    from, you don't need to add this!

    */
    GObject parent_instance;
    /* SECOND FUN FACT:
    If you do not set the field above as the FIRST field 
    of your struct, the object will not know what it's
    class is!
    Therefore, when you will call unref() on your object,
    it will print the following:
    - g_object_unref: assertion 'G_IS_OBJECT (object)' failed

    Isn't programming *fun*?
    */

    int weight;
} ;

G_DEFINE_TYPE(MyDog, my_dog, G_TYPE_OBJECT)

// These functions have been created by the 
// Macro G_DECLARE_FINAL_TYPE in the header file
// You need to define them as well.
static void my_dog_init(MyDog* self) {
    self->weight = 0;
    g_print("Initialized dog\n");
}

static void my_dog_class_init(MyDogClass* klass) {
    g_print("Initialized dog class\n");
}

// Method for a dog barking (not to be inherited)
void my_dog_bark(MyDog* self) {
    g_print("WAF!");
}

static void create_dog_normally() {
    // First we create a dog
    GObject *doggo = g_object_new(MY_DOG_TYPE, NULL);
    // We make it bark
    my_dog_bark(doggo);
    // And we destroy the dog.
    g_object_unref(doggo);
}


int main(int argc, char const *argv[])
{
    create_dog_normally();
    return 0;
}
