#include <memory>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../src/ITreeAlgorithm.h"
#include "../src/RedBlackTree.h"
#include "../src/Node.h"

class MockRedBlackTreeAlgorithms : public ITreeAlgorithm
{
public:
	MOCK_METHOD(void, BalanceOnInsert, (Node* node), (override));
	MOCK_METHOD(void, BalanceOnDelete, (Node* node), (override));
};

TEST(RedBlackTreeTest, CanInsertNode) {
	
	auto algos = std::make_shared<MockRedBlackTreeAlgorithms>();

	BinaryTree tree(algos);



}