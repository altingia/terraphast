#ifndef BITS_HPP
#define BITS_HPP

#include <terraces/intrinsics.hpp>

namespace terraces {
namespace bits {

static_assert(std::numeric_limits<index>::radix == 2, "Our integers must be of base 2");
constexpr index word_bits = std::numeric_limits<index>::digits;

inline index block_index(index i) { return i / word_bits; }
inline index base_index(index block) { return block * word_bits; }
inline uint8_t shift_index(index i) { return i % word_bits; }
inline index set_mask(index i) { return 1ull << (i & (word_bits - 1)); }
inline index clear_mask(index i) { return ~set_mask(i); }
inline index prefix_mask(index i) { return set_mask(i) - 1; }
inline index next_bit(uint64_t block, index i) { return i + bitscan(block >> shift_index(i)); }
inline index next_bit0(index block, index i) { return i + bitscan(block); }
inline bool has_next_bit(index block, index i) { return (block >> shift_index(i)) != 0; }
inline bool has_next_bit0(index block) { return block != 0; }
inline index partial_popcount(index block, index i) { return popcount(block & prefix_mask(i)); }

} // namespace bits
} // namespace terraces

#endif // BITS_HPP
