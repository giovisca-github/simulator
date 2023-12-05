#include "common/math_stuff.hpp"

std::vector<Scalar> position2Unity(const Vector<3>& pos_rh) {
  std::vector<Scalar> unity_position{pos_rh(0), pos_rh(2), pos_rh(1)};
  return unity_position;
}
// std::vector<Scalar> position2Unity(const Vector<3>& pos_rh) {
//   return std::vector<Scalar>();
// }
