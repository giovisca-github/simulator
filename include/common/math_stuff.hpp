/*
Math functions for general use:
- change of frame unity (left-handed)
*/

#pragma once
#include "common/types.hpp"

// -- change reference frame unity to rh ---
std::vector<Scalar> position2Unity(const Vector<3>& pos_rh);

std::vector<Scalar> quaternion2Unity(const Quaternion& q_rh);
