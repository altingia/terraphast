#include "bipartitions.hpp"

#include <cassert>
#include <ostream>

#include <terraces/errors.hpp>

#include "bits.hpp"
#include "utils.hpp"

namespace terraces {

bipartition_iterator::bipartition_iterator(const ranked_bitvector& leaves, const union_find& sets,
                                           utils::stack_allocator<index> a)
        : m_alloc{a}, m_leaves{leaves}, m_sets{sets}, m_set_rep{find_set_reps()},
          m_subleaves{leaves.size(), a}, m_bip{0}, m_end{(1ull << (m_set_rep.count() - 1))} {
	utils::ensure<tree_count_overflow_error>(m_set_rep.count() < bits::word_bits,
	                                         "Huge terrace encountered");
	increase();
}

bool bipartition_iterator::in_left_partition(index i) const {
	return (m_bip & (1ull << ((i - 1) & (bits::word_bits - 1)))) != 0;
}

ranked_bitvector bipartition_iterator::find_set_reps() const {
	ranked_bitvector set_rep(m_leaves.count(), m_alloc);
	for (index i = 0; i < m_leaves.count(); ++i) {
		set_rep.set(m_sets.simple_find(i));
	}
	set_rep.update_ranks();
	return set_rep;
}

bool bipartition_iterator::is_valid() const { return m_bip < m_end; }

void bipartition_iterator::increase() {
	m_bip++;
	if (is_valid()) {
		m_subleaves.blank();
		index ii = 0;
		for (auto i = m_leaves.first_set(); i < m_leaves.last_set();
		     i = m_leaves.next_set(i)) {
			if (in_left_partition(m_set_rep.rank(m_sets.simple_find(ii)))) {
				m_subleaves.set(i);
			}
			++ii;
		}
		m_subleaves.update_ranks();
	}
}

const ranked_bitvector& bipartition_iterator::get_current_set() const { return m_subleaves; }

void bipartition_iterator::flip_sets() {
	m_subleaves.bitwise_xor(m_leaves);
	m_subleaves.update_ranks();
}

std::ostream& operator<<(std::ostream& stream, const bipartition_iterator& it) {
	for (index b = it.end_bip(), c = it.cur_bip(); b != 0u; b >>= 1, c >>= 1) {
		stream << (index)(c & 1);
	}
	stream << '/';
	for (index b = it.end_bip(); b != 0u; b >>= 1) {
		stream << (index)(b & 1);
	}
	return stream;
}

} // namespace terraces
