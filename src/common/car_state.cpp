#include "common/car_state.hpp"

CarState::CarState() { setZero(); }
CarState::CarState(const Vector<IDX::SIZE>& x_) : x{x_} {}

CarState::~CarState() {}

void CarState::setPosition(const std::vector<Scalar>& position) {
  x[CS::POSX] = position[0];
  x[CS::POSY] = position[1];
  x[CS::POSZ] = position[2];
};
Quaternion CarState::q() const {
  return Quaternion(x(ATTW), x(ATTX), x(ATTY), x(ATTZ));
}

void CarState::set_q(const Quaternion& quaternion) {
  x(IDX::ATTW) = quaternion.w();
  x(IDX::ATTX) = quaternion.x();
  x(IDX::ATTY) = quaternion.y();
  x(IDX::ATTZ) = quaternion.z();
}

Matrix<3, 3> CarState::R() const {
  return Quaternion(x(ATTW), x(ATTX), x(ATTY), x(ATTZ)).toRotationMatrix();
}

void CarState::setYaw(const Scalar& yaw) {
  Quaternion q;
  q = Eigen::AngleAxis<Scalar>(yaw, Eigen::Vector3f::UnitZ());

  set_q(q);
}

void CarState::setZero() {
  x.setZero();
  x(ATTW) = 1.0;
}
