#include <memory>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/ITreeAlgorithm.h"
#include "../src/RedBlackTree.h"
#include "../src/Vessel.h"
#include "../src/Node.h"

class MockRedBlackTreeAlgorithms : public ITreeAlgorithm
{
public:
	MOCK_METHOD(void, BalanceOnInsert, (Node* node), (override));
	MOCK_METHOD(void, BalanceOnDelete, (Node* node), (override));
};

TEST(RedBlackTreeTest, CanInsertRootNode) {
	auto vessel = new BaseVessel(1, "test", 1, 2, 3, 4, 5);
	auto key = 1;
	auto node = new Node(vessel, nullptr);

	auto algos = std::make_shared<MockRedBlackTreeAlgorithms>();
	EXPECT_CALL(*algos, BalanceOnInsert(node)).Times(0);

	BinaryTree tree(algos);
	tree.Insert(node);

	EXPECT_EQ(tree.Size(), 1);
}

TEST(RedBlackTreeTest, CanInsertLeafNode) {

	auto algos = std::make_shared<MockRedBlackTreeAlgorithms>();
	BinaryTree tree(algos);

	auto totalNodes = 100;
	auto totalCalls = totalNodes * (totalNodes - 1) / 2;

	EXPECT_CALL(*algos,
		BalanceOnInsert(::testing::A<Node*>()))
		.Times(totalCalls);

	for (int index = 0; index < totalNodes; index++)
	{
		tree.Insert(new Node(
			new BaseVessel(index, "test" + std::to_string(index), 1, 2, 3, 4, 5),
			nullptr));
	}
	
	EXPECT_EQ(tree.Size(), totalNodes);
}

TEST(RedBlackTreeTest, CanInsertLeafNodeAtRandom) {

	auto algos = std::make_shared<MockRedBlackTreeAlgorithms>();
	BinaryTree tree(algos);

	auto totalNodes = 100;
	EXPECT_CALL(*algos, BalanceOnInsert(::testing::A<Node*>())).Times(::testing::AnyNumber());

	for (int index = 0; index < totalNodes; index++)
	{
		tree.Insert(new Node(
			new BaseVessel(Node::GenerateKey(), "test" + std::to_string(index), 1, 2, 3, 4, 5),
			nullptr));
	}

	EXPECT_EQ(tree.Size(), totalNodes);
}