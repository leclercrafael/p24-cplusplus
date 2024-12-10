#include < iostream>
#include <limits>
void swap(int* a, int* b) {
   int t {*a};
   *a = *b;
   *b = t;
}
int main() {
   int x {0};
   int y {83};
   swap(&x, &y);
return 0;
}