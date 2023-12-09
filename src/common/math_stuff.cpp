#include "common/math_stuff.hpp"

std::vector<Scalar> position2Unity(const Vector<3>& pos_rh) {
  std::vector<Scalar> unity_position{-pos_rh(1), pos_rh(2), pos_rh(0)};
  return unity_position;
}
