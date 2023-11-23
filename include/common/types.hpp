/*
custom type used in class definitions or in the coede
*/

#pragma once
#include <eigen3/Eigen/Eigen>

using Scalar = float;

struct Commands {
  Scalar throttle{0};
  Scalar steering{0};
};  // namespace struct Commands

// -------- EIGEN --------------

// Define `Dynamic` matrix size.
static constexpr int Dynamic = Eigen::Dynamic;

// Using shorthand for `Matrix<ros, cols>` with scalar type.
template <int rows = Dynamic, int cols = Dynamic>
using Matrix = Eigen::Matrix<Scalar, rows, cols>;

// Using shorthand for `Image<ros, cols>` with scalar type.
template <int rows = Dynamic, int cols = Dynamic>
using Image_mat = Eigen::Matrix<uint8_t, rows, cols>;

// Using shorthand for `Depth_image_mat<ros, cols>` with scalar type.
template <int rows = Dynamic, int cols = Dynamic>
using Depth_image_mat = Eigen::Matrix<float_t, rows, cols>;

// Using shorthand for `Matrix<ros, cols>` with scalar type.
template <int rows = Dynamic, int cols = Dynamic>
using ImageMatrixRowMajor = Eigen::Matrix<uint8_t, rows, cols, Eigen::RowMajor>;

// Using shorthand for `Matrix<ros, cols>` with scalar type.
template <int rows = Dynamic, int cols = Dynamic>
using DepthImageMatrixRowMajor =
    Eigen::Matrix<float_t, rows, cols, Eigen::RowMajor>;

// Using shorthand for `Matrix<ros, cols>` with scalar type.
template <int rows = Dynamic, int cols = Dynamic>
using MatrixRowMajor = Eigen::Matrix<Scalar, rows, cols, Eigen::RowMajor>;

// Using shorthand for `Vector<ros>` with scalar type.
template <int rows = Dynamic>
using Vector = Matrix<rows, 1>;

// Using shorthand for `Image<ros>` with scalar type.
template <int rows = Dynamic>
using Image = Image_mat<rows, 1>;

// Using shorthand for `Image<ros>` with scalar type.
template <int rows = Dynamic>
using DepthImage = Depth_image_mat<rows, 1>;

// Vector bool
template <int rows = Dynamic>
using BoolVector = Eigen::Matrix<bool, -1, 1>;

// Using shorthand for `Array<rows, cols>` with scalar type.
template <int rows = Dynamic, int cols = rows>
using Array = Eigen::Array<Scalar, rows, cols>;

// Using `SparseMatrix` with type.
using SparseMatrix = Eigen::SparseMatrix<Scalar>;

// Using SparseTriplet with type.
using SparseTriplet = Eigen::Triplet<Scalar>;

// Using `Quaternion` with type.
using Quaternion = Eigen::Quaternion<Scalar>;

// Using `Ref` for modifier references.
template <class Derived>
using Ref = Eigen::Ref<Derived>;

// // Using `ConstRef` for constant references.
// template<class Derived>
// using ConstRef = const Eigen::Ref<const Derived>;

// Using `Map`.
template <class Derived>
using Map = Eigen::Map<Derived>;

static constexpr Scalar Gz = -9.81;
const Vector<3> GVEC{0.0, 0.0, Gz};
