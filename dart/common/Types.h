#ifndef _DART_TYPES_H_
#define _DART_TYPES_H_

#include <cstdint>
#include <string>
#include <Eigen/Eigen>

#include "dart/common/Config.h"

//==============================================================================
// Precision setting
//==============================================================================
//------------------------------------------------------------------------------
// Double precision
//------------------------------------------------------------------------------
#ifdef DART_DOUBLE_PRECISION

namespace dart {
typedef double Scalar;
}  // namespace dart

namespace Eigen {
typedef MatrixXd MatrixXt;
typedef Matrix3d Matrix3t;
typedef Matrix2d Matrix2t;
typedef VectorXd VectorXt;
typedef Vector3d Vector3t;
typedef Vector2d Vector2t;
}  // namespace Eigen

#else
//------------------------------------------------------------------------------
// Single precision
//------------------------------------------------------------------------------

typedef float Scalar;
}  // namespace dart

namespace Eigen {
typedef MatrixXf MatrixXt;
typedef Matrix3f Matrix3t;
typedef Matrix2f Matrix2t;
typedef VectorXf VectorXt;
typedef Vector3f Vector3t;
typedef Vector2f Vector2t;
}  // namespace Eigen

#endif

//==============================================================================
namespace dart {

typedef std::string   String;
// typedef int32_t       Int32;
// typedef uint          UInt32;
// typedef int64_t       Int64;
// typedef uint64_t      UInt64;
typedef float         Float;
typedef Scalar        Double;
typedef Scalar        Real;
typedef unsigned long DWORD;

}  // namespace dart

#endif  // _DART_COMMAND_H_
