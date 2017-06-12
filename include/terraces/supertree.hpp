#ifndef TERRACES_SUPERTREE_HPP
#define TERRACES_SUPERTREE_HPP

#include "constraints.hpp"
#include "fast_set.hpp"
#include "trees.hpp"

namespace terraces {

class tree_master {
public:
	tree_master(index count);

	size_t count_supertree(const tree&, const constraints&);

	/**
	 * Count trees given a number and a vector of constraints. Entry point for tree counting.
	 */
	size_t count_supertree(const constraints&);

	/**
	 * Count trees.
	 */
	size_t count_supertree(const fast_index_set&, const constraints&);

private:
	fast_index_set leaves;
};

} // namespace terraces

#endif
