#include "chainerx/routines/loss.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

#include "chainerx/array.h"
#include "chainerx/backend.h"
#include "chainerx/backprop_mode.h"
#include "chainerx/backward_builder.h"
#include "chainerx/backward_context.h"
#include "chainerx/constant.h"
#include "chainerx/device.h"
#include "chainerx/dtype.h"
#include "chainerx/graph.h"
#include "chainerx/kernels/math.h"
#include "chainerx/macro.h"
#include "chainerx/routines/creation.h"
#include "chainerx/routines/math.h"
#include "chainerx/routines/type_util.h"
#include "chainerx/scalar.h"
#include "chainerx/shape.h"
#include "chainerx/strides.h"

namespace chainerx {

Array MeanAbsoluteError(const Array& y, const Array& targ) {
    return Absolute(y - targ).Mean();
}

Array MeanSquaredError(const Array& y, const Array& targ) {
    return SquaredDifference(y, targ).Mean();
}

Array GaussianKLDivergence(const Array& mu, const Array& ln_var, const std::string& reduction) {
    const Array& var = Exp(ln_var);
    const Array& mean_square = Square(mu);
    
    Array loss = (mean_square + var - ln_var - 1) * 0.5;

    if (reduction == "sum"){
        return loss.Sum();
    } else if (reduction == "mean") {
        return loss.Mean();
    } else {
        return loss;
    }
}

Array Hinge(const Array& y, const Array& targ, const std::string& reduction) {

}

}