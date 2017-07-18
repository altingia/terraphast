#ifndef SUPERTREE_VARIANTS_MULTITREE_HPP
#define SUPERTREE_VARIANTS_MULTITREE_HPP

#include "multitree_impl.hpp"
#include "supertree_variants.hpp"

#include <memory>
#include <stack>

namespace terraces {
namespace variants {

class multitree_callback : public abstract_callback<multitree_node*> {
private:
	multitree_impl::storage_blocks<multitree_node> m_nodes;
	multitree_impl::storage_blocks<index> m_leaves;
	std::stack<multitree_node*> m_accumulators;

	multitree_node* alloc_node() { return m_nodes.get(); }

	multitree_node* alloc_nodes(index num) { return m_nodes.get_range(num); }

	std::pair<index*, index*> alloc_leaves(const ranked_bitvector& leaves) {
		auto size = leaves.count();
		auto a_leaves = m_leaves.get_range(size);
		index i = 0;
		for (auto el : leaves) {
			a_leaves[i++] = el;
		}
		return {a_leaves, a_leaves + size};
	}

public:
	using return_type = multitree_node*;

	return_type base_one_leaf(index i) {
		return multitree_impl::make_single_leaf(alloc_node(), i);
	}
	return_type base_two_leaves(index i, index j) {
		return multitree_impl::make_two_leaves(alloc_node(), i, j);
	}
	return_type base_unconstrained(const ranked_bitvector& leaves) {
		return multitree_impl::make_unconstrained(alloc_node(), alloc_leaves(leaves));
	}
	return_type null_result() { return nullptr; }

	return_type fast_return_value(const bipartition_iterator& bip_it) {
		return multitree_impl::make_unexplored(alloc_node(), alloc_leaves(bip_it.leaves()));
	}

	return_type begin_iteration(const bipartition_iterator& bip_it, const bitvector&,
	                            const constraints&) {
		auto acc = multitree_impl::make_alternative_array(
		        alloc_node(), alloc_nodes(bip_it.num_bip()), bip_it.leaves().count());
		m_accumulators.push(acc);
		return acc;
	}

	return_type accumulate(multitree_node* acc, multitree_node* node) {
		assert(acc == m_accumulators.top());
		assert(node == (acc->alternative_array.end - 1));
		assert(acc->num_leaves == node->num_leaves);
		acc->num_trees += node->num_trees;
		// node is already linked from combine(.,.)
		return acc;
	}

	return_type combine(multitree_node* left, multitree_node* right) {
		auto acc = m_accumulators.top();
		auto& aa = acc->alternative_array;
		auto result = multitree_impl::make_inner_node(aa.end, left, right);
		++aa.end;
		return result;
	}

	void finish_iteration() { m_accumulators.pop(); }
};

} // namespace variants
} // namespace terraces

#endif // SUPERTREE_VARIANTS_MULTITREE_HPP
