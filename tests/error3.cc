#include "ppl.hh"
#include <stdexcept>

using namespace std;
using namespace Parma_Polyhedra_Library;

#define NOISY 0

int main() {
  Variable x(0);
  Variable y(1);
  Polyhedron p1;
  Polyhedron p2;
  p2.insert(x + y /= 1);
  try {
    p2.convex_hull_assign(p1);
  }
  catch (std::invalid_argument& e) {
    cout << "invalid_argument: " << e.what() << endl;
    exit(0);
  }
  catch (...) {
    exit(1);
  }

  // Should not get here.
  return 1;
}

