#include "common/math_stuff.hpp"

std::vector<Scalar> position2Unity(const Vector<3>& pos_rh) {
  std::vector<Scalar> unity_position{-pos_rh(1), pos_rh(2), pos_rh(0)};
  return unity_position;
}

std::vector<Scalar> quaternion2Unity(const Quaternion& q_rh) {
  Matrix<3, 3> rot_mat_rh = Matrix<3, 3>::Zero();
  rot_mat_rh(0, 1) = -1.0;
  rot_mat_rh(1, 2) = 1.0;
  rot_mat_rh(2, 0) = 1.0;

  Matrix<3, 3> rot_mat_lh =
      rot_mat_rh * q_rh.toRotationMatrix() * rot_mat_rh.transpose();

  Quaternion unity_quat(rot_mat_lh);

  std::vector<Scalar> unity_quat_vec{unity_quat.x(), unity_quat.y(),
                                     unity_quat.z(), unity_quat.w()};
  return unity_quat_vec;
}
