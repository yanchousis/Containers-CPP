#include <gtest/gtest.h>

#include "../my_containers.h"

using namespace std;
using namespace my;

TEST(Creationmy_set, SetCreated) {
  my_set<int> mySet;

  ASSERT_TRUE(mySet.empty() == true);
  ASSERT_TRUE(mySet.size() == 0);
}

TEST(Creationmy_set, initialized) {
  my_set<int> mySet = {-5, 10, 15};

  ASSERT_TRUE(mySet.empty() == false);
  ASSERT_TRUE(mySet.size() == 3);
}

TEST(Creationmy_set, emptyInitializer) {
  my_set<int> mySet = {};

  ASSERT_TRUE(mySet.empty() == true);
  ASSERT_TRUE(mySet.size() == 0);
}

TEST(Creationmy_set, copyConstructor) {
  my_set<int> mySet = {-5, 10, -25, 7, 15};

  my_set<int> copy{mySet};

  ASSERT_TRUE(mySet.empty() == copy.empty());
  ASSERT_TRUE(mySet.size() == copy.size());
}

// Insert
TEST(insertmy_set, OneValue) {
  my_set<int> mySet;
  int value = 88;

  mySet.insert(value);

  ASSERT_TRUE(mySet.empty() == false);
  ASSERT_TRUE(mySet.size() == 1);
}

TEST(insertmy_set, TwoValues) {
  my_set<int> mySet;
  int value = 88;
  mySet.insert(value);
  value = 96;

  mySet.insert(value);

  ASSERT_TRUE(mySet.empty() == false);
  ASSERT_TRUE(mySet.size() == 2);
}
//
// Clear
TEST(clear_emptySet, nothing_changed) {
  my_set<int> mySet;

  mySet.clear();

  ASSERT_TRUE(mySet.empty() == true);
  ASSERT_TRUE(mySet.size() == 0);
}

TEST(clear_Set, cleared) {
  my_set<int> mySet;
  int value = 88;
  mySet.insert(value);
  value = 96;
  mySet.insert(value);

  mySet.clear();

  ASSERT_TRUE(mySet.empty() == true);
  ASSERT_TRUE(mySet.size() == 0);
}

TEST(contains_empty_set, false) {
  my_set<int> mySet;

  bool result = mySet.contains(10);

  ASSERT_TRUE(mySet.empty() == true);
  ASSERT_TRUE(mySet.size() == 0);
  ASSERT_TRUE(result == false);
}

TEST(contains_set, true) {
  my_set<int> mySet;
  int value = 10;
  mySet.insert(value);

  bool result = mySet.contains(value);

  ASSERT_TRUE(mySet.empty() == false);
  ASSERT_TRUE(mySet.size() == 1);
  ASSERT_TRUE(result == true);
}

TEST(contains_set, false) {
  my_set<int> mySet;
  int value = 15;
  mySet.insert(value);

  bool result = mySet.contains(10);

  ASSERT_TRUE(mySet.empty() == false);
  ASSERT_TRUE(mySet.size() == 1);
  ASSERT_TRUE(result == false);
}

TEST(my_setfind, existsValue_iteratorToElement) {
  my_set<int> mySet;
  int value = 88;
  mySet.insert(value);
  value = 96;
  mySet.insert(value);
  value = -10;
  mySet.insert(value);
  value = -5;
  mySet.insert(value);
  value = 3;
  mySet.insert(value);

  auto result = mySet.find(-5);

  ASSERT_TRUE(*result == -5);
  ASSERT_TRUE(mySet.size() == 5);
}

TEST(my_setfind, notExistsValue_iteratorToEnd) {
  my_set<int> mySet;
  int value = 88;
  mySet.insert(value);
  value = 96;
  mySet.insert(value);
  value = -10;
  mySet.insert(value);
  value = -5;
  mySet.insert(value);
  value = 3;
  mySet.insert(value);

  auto result = mySet.find(5);

  ASSERT_TRUE(result == mySet.end());
  ASSERT_TRUE(mySet.size() == 5);
}

// TEST(my_seterase, ExistsValue_nodeDeleted) {
//   my_set<int> mySet;
//   int value = 88;
//   mySet.insert(value);
//   value = 96;
//   mySet.insert(value);
//   value = -10;
//   mySet.insert(value);
//   value = -5;
//   mySet.insert(value);
//   value = 3;
//   mySet.insert(value);
//   auto iter = mySet.find(88);
//   vector<int> expected = {-10, -5, 3, 96};
//   vector<int> result;

//  mySet.erase(iter);

//  for (auto it = mySet.begin(); it != mySet.end(); ++it) {
//    result.push_back(*it);
//  }
//  ASSERT_TRUE(result == expected);
//  ASSERT_TRUE(mySet.size() == 4);
//}

TEST(my_seterase, emptyTree_iteratorEnd) {
  my_set<int> mySet;

  mySet.erase(mySet.begin());

  ASSERT_TRUE(mySet.begin() == mySet.end());
  ASSERT_TRUE(mySet.size() == 0);
  ASSERT_TRUE(mySet.empty());
}

TEST(my_setbegin, emptyTree_iteratorEnd) {
  my_set<int> mySet;

  auto it = mySet.begin();

  ASSERT_TRUE(it == mySet.end());
  ASSERT_TRUE(mySet.size() == 0);
  ASSERT_TRUE(mySet.empty());
}

using Set = my_set<int>;

Set make_test_set() {
  Set s;
  s.insert(10);
  s.insert(5);
  s.insert(15);
  s.insert(7);
  return s;
}

TEST(my_set, copyConstructor) {
  Set original = make_test_set();
  ASSERT_TRUE(original.size() == 4);

  Set copy = original;

  ASSERT_TRUE(copy.size() == 4);
  ASSERT_TRUE(copy.contains(10));
  ASSERT_TRUE(copy.contains(5));
  ASSERT_TRUE(copy.contains(15));
  ASSERT_TRUE(copy.contains(7));

  original.insert(1);
  ASSERT_TRUE(copy.size() == 4);
}

TEST(my_set, moveConstructor) {
  Set original = make_test_set();
  ASSERT_TRUE(original.size() == 4);

  Set moved = std::move(original);

  ASSERT_TRUE(moved.size() == 4);
  ASSERT_TRUE(moved.contains(10));
  ASSERT_TRUE(moved.contains(7));

  ASSERT_TRUE(original.size() == 0);
  ASSERT_TRUE(original.empty());
}

TEST(my_set, copyAssignment) {
  Set a, b;
  a.insert(1);
  a.insert(2);

  b = a;

  ASSERT_TRUE(b.size() == 2);
  ASSERT_TRUE(b.contains(1));
  ASSERT_TRUE(b.contains(2));

  a.insert(3);
  ASSERT_TRUE(b.size() == 2);
}

TEST(my_set, moveAssignment) {
  Set a, b;
  a.insert(100);
  a.insert(200);

  b = std::move(a);

  ASSERT_TRUE(b.size() == 2);
  ASSERT_TRUE(b.contains(100));
  ASSERT_TRUE(b.contains(200));
  ASSERT_TRUE(a.empty());
  ASSERT_TRUE(a.size() == 0);
}

TEST(my_set, selfCopyAssignment) {
  Set a;
  a.insert(1);
  a.insert(2);

  a = a;

  ASSERT_TRUE(a.size() == 2);
  ASSERT_TRUE(a.contains(1));
  ASSERT_TRUE(a.contains(2));
}

TEST(my_set, doubleMove) {
  Set a = make_test_set();
  Set b = std::move(a);
  Set c = std::move(a);

  ASSERT_TRUE(a.empty());
  ASSERT_TRUE(b.size() == 4);
  ASSERT_TRUE(c.size() == 0);
}

TEST(my_set, assignWithCopy) {
  Set a, b;
  a.insert(1);
  b.insert(10);
  b.insert(20);

  b = a;

  ASSERT_TRUE(b.size() == 1);
  ASSERT_TRUE(b.contains(1));
  ASSERT_FALSE(b.contains(10));
}

TEST(my_set, assignWithMove) {
  Set a, b;
  a.insert(100);
  b.insert(1);
  b.insert(2);

  b = std::move(a);

  ASSERT_TRUE(b.size() == 1);
  ASSERT_TRUE(b.contains(100));
  ASSERT_TRUE(a.size() == 0);
}

TEST(my_set, emptySetOperations) {
  Set empty;
  ASSERT_TRUE(empty.empty());

  Set copy = empty;
  ASSERT_TRUE(copy.empty());

  Set moved = std::move(empty);
  ASSERT_TRUE(moved.empty());
  ASSERT_TRUE(empty.empty());

  Set target;
  target = std::move(empty);
  ASSERT_TRUE(target.empty());
}

TEST(my_set, Swap) {
  Set a, b;
  a.insert(1);
  a.insert(2);
  a.insert(6);
  b.insert(3);
  b.insert(4);

  a.swap(b);

  ASSERT_TRUE(a.contains(3));
  ASSERT_TRUE(a.contains(4));
  ASSERT_TRUE(b.contains(1));
  ASSERT_TRUE(b.contains(2));
  ASSERT_TRUE(b.contains(6));
  ASSERT_TRUE(a.size() == 2);
  ASSERT_TRUE(b.size() == 3);
}

TEST(my_set, SwapSelf) {
  Set a, b;
  a.insert(1);
  a.insert(2);

  a.swap(a);

  ASSERT_TRUE(a.size() == 2);
  ASSERT_TRUE(a.contains(1));
  ASSERT_TRUE(a.contains(2));
}

TEST(mySetTest, MergeSplice) {
  Set a, b;
  a.insert(1);
  a.insert(2);
  b.insert(3);
  b.insert(4);

  ASSERT_TRUE(a.size() == 2);
  ASSERT_TRUE(b.size() == 2);

  a.merge(b);

  ASSERT_TRUE(a.size() == 4);
  ASSERT_TRUE(a.contains(3));
  ASSERT_TRUE(a.contains(4));
  ASSERT_TRUE(b.size() == 0);
}

TEST(mySetTest, MaxSize) {
  Set s;

  auto max_sz = s.max_size();

  ASSERT_GE(max_sz, (size_t)0);
  ASSERT_TRUE(max_sz <= std::numeric_limits<size_t>::max());
}

TEST(my_set, insertMany_Empty) {
  Set s;

  auto res = s.insert_many();

  ASSERT_TRUE(res.size() == 0);
}

TEST(my_set, insertMany_oneElement) {
  my_set<int> s;

  auto res = s.insert_many(42);

  ASSERT_TRUE(res.size() == 1);
  ASSERT_TRUE(res[0].second);
  ASSERT_TRUE(*res[0].first == 42);
}

TEST(my_set, insertMany_multipleUnique) {
  my_set<int> s;
  auto res = s.insert_many(1, 2, 3);

  ASSERT_TRUE(res.size() == 3);
  for (auto &p : res) {
    ASSERT_TRUE(p.second);
  }
}

TEST(my_set, insertMany_withDoubles) {
  Set s;

  auto res = s.insert_many(1, 2, 1, 3, 2);

  ASSERT_TRUE(res.size() == 5);
  ASSERT_TRUE(s.size() == 3);
  ASSERT_FALSE(s.empty());
  ASSERT_TRUE(res[0].second);
  ASSERT_TRUE(res[1].second);
  ASSERT_FALSE(res[2].second);
  ASSERT_TRUE(res[3].second);
  ASSERT_FALSE(res[4].second);
}

TEST(my_set, insert_withDoubles) {
  Set s;
  s.insert(1);
  s.insert(2);
  s.insert(1);
  s.insert(3);
  s.insert(2);

  ASSERT_TRUE(s.size() == 3);
  ASSERT_FALSE(s.empty());
}

TEST(Iter, EmptySet_BeginIsEnd) {
  my_set<int> mySet;

  ASSERT_TRUE(mySet.begin() == mySet.end());
}

TEST(Iter, BeginIsMinimalElement) {
  my_set<int> mySet;
  int value = 88;
  mySet.insert(value);
  value = 96;
  mySet.insert(value);
  value = -150;
  mySet.insert(value);

  ASSERT_TRUE(*mySet.begin() == value);
}

// TEST(Iter, InorderWalking_PrefixIncrement) {
//   my_set<int> mySet;
//   mySet.insert(-10);
//   mySet.insert(5);
//   mySet.insert(15);
//   mySet.insert(7);
//   vector<int> expected = {-10, 5, 7, 15};
//   vector<int> result;

//  for (auto it = mySet.begin(); it != mySet.end(); ++it) {
//    result.push_back(*it);
//  }

//  ASSERT_TRUE(result == expected);
//}

TEST(Iter, PostfixIncrement) {
  my_set<int> mySet;
  mySet.insert(15);
  mySet.insert(-10);
  auto it = mySet.begin();

  auto copy = it++;

  ASSERT_TRUE(*copy == -10);
  ASSERT_TRUE(*it == 15);
}

TEST(Iter, EndMinusOneIsMax_PrefixDecrement) {
  my_set<int> mySet;
  mySet.insert(-10);
  mySet.insert(50);
  mySet.insert(25);
  auto it = mySet.end();

  --it;

  ASSERT_TRUE(*it == 50);
}

TEST(Iter, EndMinusOneIsMax_PostfixDecrement) {
  my_set<int> mySet;
  mySet.insert(-10);
  mySet.insert(50);
  mySet.insert(25);
  auto it = mySet.end();

  it--;
  auto copy = it--;

  ASSERT_TRUE(*it == 25);
  ASSERT_TRUE(*copy == 50);
}

TEST(Iter, BidirectionalWalking) {
  my_set<int> mySet;
  mySet.insert(-10);
  mySet.insert(50);
  mySet.insert(25);

  auto it = mySet.begin();
  ++it;
  ++it;
  --it;
  --it;

  ASSERT_TRUE(*it == -10);
}

TEST(Iter, ArrowDoesNotCorruptOnMultipleCalls) {
  my::my_set<std::string> strSet;
  strSet.insert("hello");
  strSet.insert("world");

  auto it1 = strSet.begin();
  auto it2 = ++strSet.begin();

  ASSERT_TRUE(it1->size() == 5);
  ASSERT_TRUE(it2->size() == 5);
  ASSERT_TRUE(*it1 == "hello");
  ASSERT_TRUE(*it2 == "world");
}