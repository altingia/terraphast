#ifndef SUPERTREE_HELPERS_HPP
#define SUPERTREE_HELPERS_HPP

#include <terraces/bitvector.hpp>
#include <terraces/constraints.hpp>
#include <terraces/stack_allocator.hpp>
#include <terraces/trees.hpp>
#include <terraces/union_find.hpp>

namespace terraces {

/** Removes all constraints from c_occ that don't lie fully within the leave set. */
bitvector filter_constraints(const ranked_bitvector& leaves, const bitvector& c_occ,
                             const constraints& c);

/** Returns a union-find representation of the sets retrieved after applying all constraints from
 * c_occ. */
union_find apply_constraints(const ranked_bitvector& leaves, const bitvector& c_occ,
                             const constraints& c, utils::stack_allocator<index> a);

/** Maps the given constraints to leaf indices. */
constraints map_constraints(const ranked_bitvector& leaves, const constraints& cs);

/** Returns a set containing all leaves of the given tree. */
ranked_bitvector leave_occ(const tree& tree, utils::stack_allocator<index> a);

} // namespace terraces

#endif // SUPERTREE_HELPERS_HPP
