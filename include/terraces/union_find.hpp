#ifndef TERRACES_UNION_FIND_HPP
#define TERRACES_UNION_FIND_HPP

#include <algorithm>

#include "stack_allocator.hpp"
#include "trees.hpp"

namespace terraces {

class union_find {
public:
	using value_type = index;

private:
	std::vector<index, utils::stack_allocator<index>> m_parent;
#ifndef NDEBUG
	bool m_compressed;
#endif

public:
	union_find(index, utils::stack_allocator<index> a);
	index find(index);
	index simple_find(index) const;
	index size() const;
	void compress();
	void merge(index, index);
	bool is_representative(index) const;
};

} // namespace terraces

#endif
