// This is a file to show how to use GObject
// In this file, we use it to create two int64
// and copy one into another
#include <glib.h>
#include <glib-object.h>

static void test_int (void)
{
  // We initialize to "values"
  // in the GObject type system.
  GValue a_value = G_VALUE_INIT;
  GValue b_value = G_VALUE_INIT;
  // This is also a type from the GLib type system.
  guint64 a, b;

  a = 0xdeadbeef;

  // We initialize the value a_value
  g_value_init (&a_value, G_TYPE_UINT64);
  // The value is set equals to a: 0xdeadbeef
  g_value_set_uint64 (&a_value, a);

  // Same for the value b.
  g_value_init (&b_value, G_TYPE_UINT64);
  // We copy from a_value to b_value
  g_value_copy (&a_value, &b_value);

  // This extracts the uint64 from the value.
  b = g_value_get_uint64 (&b_value);

  if (a == b) {
    g_print ("Yay !! 10 lines of code to copy around a uint64.\n");
  } else {
    g_print ("Are you sure this is not a Z80 ?\n");
  }
}

int main() {
  test_int();
}
