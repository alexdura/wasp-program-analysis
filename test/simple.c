#include <glib.h>
#include <glib-object.h>

static void test_int (void)
{
  GValue a_value = G_VALUE_INIT;
  GValue b_value = G_VALUE_INIT;
  guint64 a, b;

  a = 0xdeadbeef;

  g_value_init (&a_value, G_TYPE_UINT64);
  g_value_set_uint64 (&a_value, a);

  g_value_init (&b_value, G_TYPE_UINT64);
  g_value_copy (&a_value, &b_value);

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
