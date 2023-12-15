#include "common/math_stuff.hpp"
/**
 reference frame car rh is:
 x forward
 y left 
 z up

 reference frame car unity left hand is
 x left
 y up
 z forward


 */


std::vector<Scalar> position2Unity(const Vector<3>& pos_rh) {
  std::vector<Scalar> unity_position{-pos_rh(1), pos_rh(2), pos_rh(0)};
  return unity_position;
}

std::vector<Scalar> quaternion2Unity(const Quaternion& q_rh) {
  // Matrix<3, 3> R2_rh = Matrix<3, 3>::Zero();  // change of coordinate
  // R2_rh(0, 1) = -1.0;
  // R2_rh(1, 2) = 1.0;
  // R2_rh(2, 0) = 1.0;

  // Matrix<3, 3> rot_mat_lh = R2_rh * q_rh.toRotationMatrix() * R2_rh.transpose();

  // Quaternion unity_quat(rot_mat_lh);

  // std::vector<Scalar> unity_quat_vec{unity_quat.x(), unity_quat.y(),
  //                                    unity_quat.z(), unity_quat.w()};

  std::vector<Scalar> unity_quat_vec{q_rh.y(),-q_rh.z(),-q_rh.x(),q_rh.w()};
  return unity_quat_vec;
}

std::vector<Scalar> rightHandFrame(const std::vector<Scalar>& lef_hand) {
  return {lef_hand[2], -lef_hand[0], lef_hand[1]};
}

Quaternion quaternionFromUnity(const std::vector<Scalar>& q_lh) {
  Matrix<3, 3> R2_rh = Matrix<3, 3>::Zero();
  R2_rh(0, 1) = -1.0;
  R2_rh(1, 2) = 1.0;
  R2_rh(2, 0) = 1.0;

  // Map<Quaternion> q_lh_(const_cast<Scalar*>(q_lh.data()));
  Quaternion q_lh_(q_lh[0], q_lh[1], q_lh[2], q_lh[3]);

  Matrix<3, 3> rot_mat_rh =
      R2_rh.transpose() * q_lh_.toRotationMatrix() * R2_rh;

  return Quaternion(rot_mat_rh);
}
