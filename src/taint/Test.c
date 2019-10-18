// A C-file for testing my taint analysis.
// Creates a taint function that creates a
// tainted value. This value should not be
// printable.

int taint() { return 13; }

void print(int x) { /* sink */ }

void foo(int x) {
  print(x);
}

int bar() {
  return taint();
}

int main() {
  int i = 0;
  int j = taint();
  foo(j);
  foo(i);
  print(i);
  print(j); // Should not be allowed.
  print(bar());
}
