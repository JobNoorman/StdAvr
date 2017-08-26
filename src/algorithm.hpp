#ifndef STDAVR_ALGORITHM_HPP
#define STDAVR_ALGORITHM_HPP

#include "namespace.hpp"

namespace STDAVR_NAMESPACE
{

template<class InputIt, class OutputIt>
OutputIt copy(InputIt in, InputIt in_end, OutputIt out)
{
    while (in != in_end)
        *out++ = *in++;

    return out;
}

}

#endif
