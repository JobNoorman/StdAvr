#ifndef STDAVR_CSTDLIB_HPP
#define STDAVR_CSTDLIB_HPP

#include "namespace.hpp"

#include <stdlib.h>

namespace STDAVR_NAMESPACE
{

extern "C" [[noreturn]] void abort() noexcept;

} // namespace STDAVR_NAMESPACE

#endif
