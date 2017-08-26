#ifndef STDAVR_CSTDDEF_HPP
#define STDAVR_CSTDDEF_HPP

#include "namespace.hpp"

#include <stddef.h>

namespace STDAVR_NAMESPACE
{

using size_t = ::size_t;
using ptrdiff_t = ::ptrdiff_t;
using nullptr_t = ::nullptr_t;
using max_align_t = ::max_align_t;

}

#endif
