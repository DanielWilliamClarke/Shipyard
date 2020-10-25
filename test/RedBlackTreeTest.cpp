#include <memory>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../src/ITreeAlgorithm.h"
#include "../src/RedBlackTree.h"
#include "../src/Node.h"
#include "../src/Vessel.h"

class MockRedBlackTreeAlgorithms : public ITreeAlgorithm
{
public:
	MOCK_METHOD(void, BalanceOnInsert, (Node* node), (override));
	MOCK_METHOD(void, BalanceOnDelete, (Node* node), (override));
};

TEST(RedBlackTreeTest, CanInsertNode) {
	
	auto algos = std::make_shared<MockRedBlackTreeAlgorithms>();

	BinaryTree tree(algos);

	auto vessel = new BaseVessel("test", 1, 2, 3, 4, 5);

	auto key = 1;

	auto node = new Node(key, vessel, nullptr);

	tree.Insert(key, node);
}