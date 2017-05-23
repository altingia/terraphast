#ifndef TERRACES_BITMATRIX_HPP
#define TERRACES_BITMATRIX_HPP

#include <vector>

#include "trees.hpp"

namespace terraces {

class bitmatrix {
public:
	bitmatrix(index rows, index cols);

	index rows() const;
	index cols() const;

	bool get(index row, index col) const;
	void set(index row, index col, bool val);
	/** Writes the bit rows 'in1' and 'in2' to row 'out'. */
	void row_or(index in1, index in2, index out);

private:
	index m_rows;
	index m_cols;
	std::vector<bool> m_vec; // yes, it's evil
};
}

#endif
