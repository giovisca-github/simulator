#include "common/car_state.hpp"

CarState::CarState() { setZero(); }
CarState::CarState(const Vector<IDX::SIZE>& x_) : x{x_} {}

CarState::~CarState() {}

void CarState::setPosition(const std::vector<Scalar>& position) {
  x[CS::POSX] = position[0];
  x[CS::POSY] = position[1];
  x[CS::POSZ] = position[2];
};

void CarState::setVelocity(const std::vector<Scalar>& velocity) {
  x[CS::VELX] = velocity[0];
  x[CS::VELY] = velocity[1];
  x[CS::VELZ] = velocity[2];
}

Quaternion CarState::q() const {
  return Quaternion(x(ATTW), x(ATTX), x(ATTY), x(ATTZ));
}

void CarState::setRotation(const Quaternion& quaternion) {
  x(IDX::ATTW) = quaternion.w();
  x(IDX::ATTX) = quaternion.x();
  x(IDX::ATTY) = quaternion.y();
  x(IDX::ATTZ) = quaternion.z();
}

void CarState::setOmega(const std::vector<Scalar>& omega) {
  x[CS::OMEX] = omega[0];
  x[CS::OMEY] = omega[1];
  x[CS::OMEZ] = omega[2];
}
void CarState::setStatesFromUnity(const Vehicle_sub& vehicle) {
  setPosition(rightHandFrame(vehicle.position));
  setVelocity(rightHandFrame(vehicle.velocity_lin));
  setOmega(rightHandFrame(vehicle.velocity_ang));
  setRotation(quaternionFromUnity(vehicle.rotation));
}

Matrix<3, 3> CarState::R() const {
  return Quaternion(x(ATTW), x(ATTX), x(ATTY), x(ATTZ)).toRotationMatrix();
}

void CarState::setYaw(const Scalar& yaw) {
  Quaternion q;
  q = Eigen::AngleAxis<Scalar>(yaw, Eigen::Vector3f::UnitZ());

  setRotation(q);
}

void CarState::setZero() {
  x.setZero();
  x(ATTW) = 1.0;
}
