
#include <catch.hpp>

#include <terraces/unconstrained_enumerator.hpp>

namespace terraces {
namespace tests {

TEST_CASE("small_bipartition", "[unconstrained]") {
	small_bipartition bip{0b00101001011100};
	auto step = [&](index i) {
		CHECK(bip.is_valid());
		CHECK(bip.left_mask() == i);
		bip.next();
	};

	CHECK(bip.is_valid());
	step(0b00000000000100);
	step(0b00000000001000);
	step(0b00000000001100);
	step(0b00000000010000);
	step(0b00000000010100);
	step(0b00000000011000);
	step(0b00000000011100);
	step(0b00000001000000);
	step(0b00000001000100);
	step(0b00000001001000);
	step(0b00000001001100);
	step(0b00000001010000);
	step(0b00000001010100);
	step(0b00000001011000);
	step(0b00000001011100);
	step(0b00001000000000);
	step(0b00001000000100);
	step(0b00001000001000);
	step(0b00001000001100);
	step(0b00001000010000);
	step(0b00001000010100);
	step(0b00001000011000);
	step(0b00001000011100);
	step(0b00001001000000);
	step(0b00001001000100);
	step(0b00001001001000);
	step(0b00001001001100);
	step(0b00001001010000);
	step(0b00001001010100);
	step(0b00001001011000);
	step(0b00001001011100);
	CHECK(!bip.is_valid());
}

name_map make_names(const std::vector<index>& leaves) {
	name_map result;
	result.reserve(leaves.size());
	std::transform(leaves.begin(), leaves.end(), std::back_inserter(result),
	               [](index i) { return i == none ? "" : std::to_string(i); });
	return result;
}

TEST_CASE("unconstrained_tree_iterator small", "[unconstrained]") {
	tree t(5, {none, none, none});
	std::vector<index> leaf_perm(t.size(), 0);
	t[0] = {none, none, none};
	multitree_nodes::unconstrained leaves;
	index leaves_data[] = {0, 1, 2};
	leaves.begin = leaves_data;
	leaves.end = leaves.begin + sizeof(leaves_data) / sizeof(index);
	std::vector<std::pair<tree, std::vector<index>>> result(3, {t, leaf_perm});
	unconstrained_tree_iterator it{leaves, t, leaf_perm, 0};
	index i = 0;
	result[i] = {t, leaf_perm};
	std::cout << as_newick(t, make_names(leaf_perm)) << "\n";
	while (it.has_next()) {
		++i;
		it.next();
		result[i] = {t, leaf_perm};
		std::cout << as_newick(t, make_names(leaf_perm)) << "\n";
	}
	CHECK(i == result.size() - 1);
}

TEST_CASE("unconstrained_tree_iterator", "[unconstrained]") {
	tree t(13, {none, none, none});
	std::vector<index> leaf_perm(t.size(), 0);
	t[0] = {none, 1, 2};
	t[1] = {0, none, none};
	t[2] = {0, none, none};
	leaf_perm[0] = none;
	leaf_perm[1] = 0;
	multitree_nodes::unconstrained leaves;
	index leaves_data[] = {1, 2, 3, 4, 5, 6};
	leaves.begin = leaves_data;
	leaves.end = leaves.begin + sizeof(leaves_data) / sizeof(index);
	std::vector<std::pair<tree, std::vector<index>>> result(945, {t, leaf_perm});
	unconstrained_tree_iterator it{leaves, t, leaf_perm, 2};
	index i = 0;
	result[i] = {t, leaf_perm};
	std::cout << as_newick(t, make_names(leaf_perm)) << "\n";
	while (it.has_next()) {
		++i;
		it.next();
		result[i] = {t, leaf_perm};
		std::cout << as_newick(t, make_names(leaf_perm)) << "\n";
	}
	CHECK(i == result.size() - 1);
}

} // namespace tests
} // namespace terraces
