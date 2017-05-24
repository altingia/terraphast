#ifndef TERRACES_CONSTRAINTS_HPP
#define TERRACES_CONSTRAINTS_HPP

#include <vector>

#include "trees.hpp"

namespace terraces {

struct constraint {
	index left;
	index shared;
	index right;

	constraint(index left, index shared, index right)
	        : left{left}, shared{shared}, right{right} {}

	bool operator==(const constraint& o) const {
		return left == o.left && shared == o.shared && right == o.right;
	}

	bool operator!=(const constraint& o) const { return !(o == *this); }
};

std::ostream& operator<<(std::ostream& s, const constraint& c);

using constraints = std::vector<constraint>;

constraints compute_constraints(const std::vector<tree>& trees);

} // namespace terraces

#endif
