#pragma once
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
    SIZE = 3
  };
  CarState();
  CarState(const Vector<IDX::SIZE>& x_);
  ~CarState();

  inline bool valid() const { return x.allFinite(); }

  void setPosition(const std::vector<Scalar>& position);

  Vector<IDX::SIZE> x = Vector<IDX::SIZE>::Constant(NAN);  // state vector

  // position
  Ref<Vector<3>> p{x.segment<IDX::NPOS>(IDX::POS)};
};

using CS = CarState;