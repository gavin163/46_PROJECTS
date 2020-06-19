// AVLSet_SanityCheckTests.cpp
//
// ICS 46 Spring 2020
// Project #4: Set the Controls for the Heart of the Sun
//
// This is a set of "sanity checking" unit tests for your AVLSet
// implementation, provided primarily as a mechanism for ensuring that
// your implementation is compatible with the unit tests we'll be using
// to test it, and to give you a quick example of how each of the member
// functions works.  These tests don't verify all of the functionality
// you're implementing.
//
// As with the sanity-checking unit tests you saw in other projects, you
// should not modify these in any way -- don't add #include directives,
// and don't change the code within the tests.  These should all compile
// and pass before you submit your AVLSet implementation.

#include <string>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>
#include "AVLSet.hpp"


TEST(AVLSet_SanityCheckTests, inheritFromSet)
{
    AVLSet<int> s1;
    Set<int>& ss1 = s1;
    int sz1 = ss1.size();
    sz1 = 0;

    AVLSet<std::string> s2;
    Set<std::string>& ss2 = s2;
    int sz2 = ss2.size();
    sz2 = 0;
}


TEST(AVLSet_SanityCheckTests, canCreateAndDestroy)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;
}


TEST(AVLSet_SanityCheckTests, heightOfEmptyIsNegativeOne)
{
    AVLSet<int> s;
    ASSERT_EQ(-1, s.height());
}


TEST(AVLSet_SanityCheckTests, canCopyConstructToCompatibleType)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;

    AVLSet<int> s1Copy{s1};
    AVLSet<std::string> s2Copy{s2};
}


TEST(AVLSet_SanityCheckTests, canMoveConstructToCompatibleType)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;

    AVLSet<int> s1Copy{std::move(s1)};
    AVLSet<std::string> s2Copy{std::move(s2)};
}


TEST(AVLSet_SanityCheckTests, canAssignToCompatibleType)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;

    AVLSet<int> s3;
    AVLSet<std::string> s4;

    s1 = s3;
    s2 = s4;

    ASSERT_EQ(0, s3.size());
    ASSERT_EQ(0, s4.size());
    ASSERT_EQ(-1, s3.height());
    ASSERT_EQ(-1, s4.height());
    EXPECT_EQ(s1.height(), s3.height());
    EXPECT_EQ(s2.height(), s4.height());
    EXPECT_EQ(s1.size(), s3.size());
    EXPECT_EQ(s2.size(), s4.size());
}


TEST(AVLSet_SanityCheckTests, canMoveAssignToCompatibleType)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;

    AVLSet<int> s3;
    AVLSet<std::string> s4;

    s1 = std::move(s3);
    s2 = std::move(s4);
}


TEST(AVLSet_SanityCheckTests, isImplemented)
{
    AVLSet<int> s1;
    EXPECT_TRUE(s1.isImplemented());

    AVLSet<std::string> s2;
    EXPECT_TRUE(s2.isImplemented());
}


TEST(AVLSet_SanityCheckTests, containsElementsAfterAdding)
{
    AVLSet<int> s1;
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_TRUE(s1.contains(11));
    EXPECT_TRUE(s1.contains(1));
    EXPECT_TRUE(s1.contains(5));
    EXPECT_FALSE(s1.contains(3));
    s1.add(3);
    EXPECT_TRUE(s1.contains(3));
}


TEST(AVLSet_SanityCheckTests, doesNotContainElementsNotAdded)
{
    AVLSet<int> s1;
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_FALSE(s1.contains(21));
    EXPECT_FALSE(s1.contains(2));
    EXPECT_FALSE(s1.contains(9));
}


TEST(AVLSet_SanityCheckTests, sizeIsNumberOfElementsAdded)
{
    AVLSet<int> s1;
    s1.add(11);
    s1.add(1);
    s1.add(5);
    EXPECT_TRUE(s1.contains(11));
    EXPECT_TRUE(s1.contains(1));
    EXPECT_TRUE(s1.contains(5));
    EXPECT_EQ(3, s1.size());
}

TEST(AVLSet_SanityCheckTests, NotBalancedsizeIsNumberOfElementsAdded)
{
    AVLSet<int> s1{false};
    s1.add(11);
    s1.add(1);
    s1.add(5);
    s1.add(5);
    EXPECT_TRUE(s1.contains(11));
    EXPECT_TRUE(s1.contains(1));
    EXPECT_TRUE(s1.contains(5));
    EXPECT_FALSE(s1.contains(6));
    EXPECT_EQ(3, s1.size());
    EXPECT_EQ(2,s1.height());
}

TEST(AVLSet_SanityCheckTests, heightDependsOnBalancing)
{
    AVLSet<int> balanced{true};
    balanced.add(1);
    balanced.add(2);
    balanced.add(3);

    AVLSet<int> notBalanced{false};
    notBalanced.add(1);
    notBalanced.add(2);
    notBalanced.add(3);

    EXPECT_EQ(1, balanced.height());
    EXPECT_EQ(2, notBalanced.height());
}


TEST(AVLSet_SanityCheckTests, BSTcanProvideTraversals)
{
    AVLSet<int> s{false};
    s.add(10);
    s.add(0);
    s.add(20);
    s.add(30);
    s.add(40);
    s.add(50);
    
    EXPECT_TRUE(s.contains(10));
    EXPECT_TRUE(s.contains(20));
    EXPECT_TRUE(s.contains(30));
    EXPECT_FALSE(s.contains(70));
    EXPECT_TRUE(s.contains(40));
    EXPECT_TRUE(s.contains(50));
    EXPECT_TRUE(s.contains(0));
    EXPECT_EQ(6,s.size());
    EXPECT_EQ(4,s.height());
    
    std::vector<int> preElements;
    std::vector<int> inElements;
    std::vector<int> postElements;

    s.preorder([&](const int& element) { preElements.push_back(element); });
    s.inorder([&](const int& element) { inElements.push_back(element); });
    s.postorder([&](const int& element) { postElements.push_back(element); });
    

    std::vector<int> expectedPreElements{10,0, 20, 30, 40, 50};
    std::vector<int> expectedInElements{0,10, 20, 30, 40, 50};
    std::vector<int> expectedPostElements{0,50, 40, 30, 20, 10};

    ASSERT_EQ(6, preElements.size());
    ASSERT_EQ(6, inElements.size());
    ASSERT_EQ(6, postElements.size());

    for (unsigned int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(preElements[i], expectedPreElements[i]);
        EXPECT_EQ(inElements[i], expectedInElements[i]);
        EXPECT_EQ(postElements[i], expectedPostElements[i]);
    }
}

TEST(AVLSet_SanityCheckTests, AVLcanProvideTraversals)
{
    AVLSet<int> s;
    std::vector<int> test{3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
    for(int i = 0; i < test.size(); ++i){
        s.add(test[i]);
    }
    
    EXPECT_EQ(16,s.size());
    EXPECT_EQ(4,s.height());
    
    std::vector<int> preElements;
    std::vector<int> inElements;
    std::vector<int> postElements;

    s.preorder([&](const int& element) { preElements.push_back(element); });
    s.inorder([&](const int& element) { inElements.push_back(element); });
    s.postorder([&](const int& element) { postElements.push_back(element); });
    

    std::vector<int> expectedPreElements{7,4,2,1,3,6,5,13,11,9,8,10,12,15,14,16};
    std::vector<int> expectedInElements{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    std::vector<int> expectedPostElements{1, 3, 2, 5, 6, 4, 8, 10, 9, 12, 11, 14, 16, 15, 13, 7};

    ASSERT_EQ(16, preElements.size());
    ASSERT_EQ(16, inElements.size());
    ASSERT_EQ(16, postElements.size());

    for (unsigned int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(preElements[i], expectedPreElements[i]);
        EXPECT_EQ(inElements[i], expectedInElements[i]);
        EXPECT_EQ(postElements[i], expectedPostElements[i]);
    }
}