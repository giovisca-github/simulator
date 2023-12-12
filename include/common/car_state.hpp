#pragma once
#include "bridge/custom_message.hpp"
#include "common/math_stuff.hpp"
#include "common/types.hpp"

struct CarState {
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  enum IDX : int {
    // position
    POS = 0,
    POSX = 0,
    POSY = 1,
    POSZ = 2,
    NPOS = 3,
    // quaternion
    ATT = 3,
    ATTW = 3,
    ATTX = 4,
    ATTY = 5,
    ATTZ = 6,
    NATT = 4,
    // linear velocity
    VEL = 7,
    VELX = 7,
    VELY = 8,
    VELZ = 9,
    NVEL = 3,
    // Body rate
    OME = 10,
    OMEX = 10,
    OMEY = 11,
    OMEZ = 12,
    NOME = 3,
    // linear accelaration
    ACC = 13,
    ACCX = 13,
    ACCY = 14,
    ACCZ = 15,
    NACC = 3,
    //
    SIZE = 16
  };

  CarState();
  CarState(const Vector<IDX::SIZE>& x_);
  ~CarState();

  inline bool valid() const { return x.allFinite(); }

  void setPosition(const std::vector<Scalar>& position);
  void setVelocity(const std::vector<Scalar>& velocity);
  void setRotation(const Quaternion& quaternion);
  void setOmega(const std::vector<Scalar>& omega);
  void setStatesFromUnity(const Vehicle_sub& vehicle);
  // manage quaternion
  Quaternion q() const;

  Matrix<3, 3> R() const;  // return rotation matrix
  void setYaw(const Scalar& yaw);

  // state vector
  Vector<IDX::SIZE> x = Vector<IDX::SIZE>::Constant(NAN);
  void setZero();
  // position
  Ref<Vector<3>> p{x.segment<IDX::NPOS>(IDX::POS)};
  // orientation quaternion
  Ref<Vector<4>> qx{x.segment<IDX::NATT>(IDX::ATT)};
  // linear velocity
  Ref<Vector<3>> v{x.segment<IDX::NVEL>(IDX::VEL)};
  // angular velocity
  Ref<Vector<3>> w{x.segment<IDX::NOME>(IDX::OME)};
};

using CS = CarState;