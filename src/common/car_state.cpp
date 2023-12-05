#include "common/car_state.hpp"

CarState::CarState() {}
CarState::CarState(const Vector<IDX::SIZE>& x_) : x{x_} {}

CarState::~CarState() {}

void CarState::setPosition(const std::vector<Scalar>& position) {
  x[CS::POSX] = position[0];
  x[CS::POSY] = position[1];
  x[CS::POSZ] = position[2];
};
