// A C-file for testing my taint analysis.
// Creates a taint function that creates a
// tainted value. This value should not be
// printable.

int taint() { return 13; }

void print(int x) { /* sink */ }

int main() {
  int i = 0;
  int j = taint();
  print(i);
  print(j); // Should not be allowed.
}
