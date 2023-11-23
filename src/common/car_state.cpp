#include "common/car_state.hpp"

CarState::CarState() {}
CarState::CarState(const Vector<IDX::SIZE>& x_) : x{x_} {}

CarState::~CarState() {}

void CarState::setPosition(const Scalar& pos_x, const Scalar& pos_y,
                           const Scalar& pos_z) {
  x[CS::POSX] = pos_x;
  x[CS::POSY] = pos_y;
  x[CS::POSZ] = pos_z;
};
