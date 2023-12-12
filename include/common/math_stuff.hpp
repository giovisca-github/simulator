/*
Math functions for general use:
- change of frame unity (left-handed)
*/

#pragma once
#include "common/types.hpp"
#include "iostream"

// -- change reference frame from rh to unity ---
std::vector<Scalar> position2Unity(const Vector<3>& pos_rh);

std::vector<Scalar> quaternion2Unity(const Quaternion& q_rh);

// --change frome from unity to rh
std::vector<Scalar> rightHandFrame(const std::vector<Scalar>& lef_hand);

Quaternion quaternionFromUnity(const std::vector<Scalar>& q_lh);