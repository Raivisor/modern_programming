#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <array>
#include <cstddef>

namespace biv{
    namespace generator{
        template<size_t N>
        std::array<int, N> generate();
    }
}

#endif