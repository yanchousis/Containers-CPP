#include <gtest/gtest.h>

#include "../my_containersplus.h"

using namespace std;
using namespace my;

using Multiset = my_multiset<int>;

Multiset make_test_mset() {
  Multiset s;
  s.insert(10);
  s.insert(5);
  s.insert(15);
  s.insert(7);
  return s;
}

TEST(multisetCreation, multisetCreated) {
  Multiset mySet;

  ASSERT_TRUE(mySet.empty() == true);
  ASSERT_TRUE(mySet.size() == 0);
}

TEST(multiset, MaxSize) {
  Multiset s;

  auto max_sz = s.max_size();

  ASSERT_GE(max_sz, (size_t)0);
  ASSERT_TRUE(max_sz <= std::numeric_limits<size_t>::max());
}

TEST(Creation, initialized) {
  Multiset mySet = {-5, 10, 15};

  ASSERT_TRUE(mySet.empty() == false);
  ASSERT_TRUE(mySet.size() == 3);
}

TEST(Creation, emptyInitializer) {
  Multiset mySet = {};

  ASSERT_TRUE(mySet.empty() == true);
  ASSERT_TRUE(mySet.size() == 0);
}

TEST(multiset, copyConstructor) {
  Multiset original = make_test_mset();
  ASSERT_TRUE(original.size() == 4);

  Multiset copy = original;

  ASSERT_TRUE(copy.size() == 4);
  ASSERT_TRUE(copy.contains(10));
  ASSERT_TRUE(copy.contains(5));
  ASSERT_TRUE(copy.contains(15));
  ASSERT_TRUE(copy.contains(7));

  original.insert(1);
  ASSERT_TRUE(copy.size() == 4);
}

TEST(Multiset, moveConstructor) {
  Multiset original = make_test_mset();
  ASSERT_TRUE(original.size() == 4);

  Multiset moved = std::move(original);

  ASSERT_TRUE(moved.size() == 4);
  ASSERT_TRUE(moved.contains(10));
  ASSERT_TRUE(moved.contains(7));

  ASSERT_TRUE(original.size() == 0);
  ASSERT_TRUE(original.empty());
}

TEST(Multiset, copyAssignment) {
  Multiset a, b;
  a.insert(1);
  a.insert(2);

  b = a;

  ASSERT_TRUE(b.size() == 2);
  ASSERT_TRUE(b.contains(1));
  ASSERT_TRUE(b.contains(2));

  a.insert(3);
  ASSERT_TRUE(b.size() == 2);
}

TEST(Multiset, moveAssignment) {
  Multiset a, b;
  a.insert(100);
  a.insert(200);

  b = std::move(a);

  ASSERT_TRUE(b.size() == 2);
  ASSERT_TRUE(b.contains(100));
  ASSERT_TRUE(b.contains(200));
  ASSERT_TRUE(a.empty());
  ASSERT_TRUE(a.size() == 0);
}

TEST(Multiset, selfCopyAssignment) {
  Multiset a;
  a.insert(1);
  a.insert(2);

  a = a;

  ASSERT_TRUE(a.size() == 2);
  ASSERT_TRUE(a.contains(1));
  ASSERT_TRUE(a.contains(2));
}

TEST(Multiset, doubleMove) {
  Multiset a = make_test_mset();
  Multiset b = std::move(a);
  Multiset c = std::move(a);

  ASSERT_TRUE(a.empty());
  ASSERT_TRUE(b.size() == 4);
  ASSERT_TRUE(c.size() == 0);
}

TEST(Multiset, assignWithCopy) {
  Multiset a, b;
  a.insert(1);
  b.insert(10);
  b.insert(20);

  b = a;

  ASSERT_TRUE(b.size() == 1);
  ASSERT_TRUE(b.contains(1));
  ASSERT_FALSE(b.contains(10));
}

TEST(Multiset, assignWithMove) {
  Multiset a, b;
  a.insert(100);
  b.insert(1);
  b.insert(2);

  b = std::move(a);

  ASSERT_TRUE(b.size() == 1);
  ASSERT_TRUE(b.contains(100));
  ASSERT_TRUE(a.size() == 0);
}

TEST(Multiset, emptySetOperations) {
  Multiset empty;
  ASSERT_TRUE(empty.empty());

  Multiset copy = empty;
  ASSERT_TRUE(copy.empty());

  Multiset moved = std::move(empty);
  ASSERT_TRUE(moved.empty());
  ASSERT_TRUE(empty.empty());

  Multiset target;
  target = std::move(empty);
  ASSERT_TRUE(target.empty());
}

TEST(Multiset, EmptySet_BeginIsEnd) {
  Multiset mySet;

  ASSERT_TRUE(mySet.begin() == mySet.end());
}

TEST(Multiset, BeginIsMinimalElement) {
  Multiset mySet;
  int value = 88;
  mySet.insert(value);
  value = 96;
  mySet.insert(value);
  value = -150;
  mySet.insert(value);

  ASSERT_TRUE(*mySet.begin() == value);
}

TEST(Multiset, InorderWalking_PrefixIncrement) {
  Multiset mySet;
  mySet.insert(-10);
  mySet.insert(5);
  mySet.insert(15);
  mySet.insert(7);
  vector<int> expected = {-10, 5, 7, 15};
  vector<int> result;

  for (auto it = mySet.begin(); it != mySet.end(); ++it) {
    result.push_back(*it);
  }

  ASSERT_TRUE(result == expected);
}

TEST(Multiset, PostfixIncrement) {
  Multiset mySet;
  mySet.insert(15);
  mySet.insert(-10);
  auto it = mySet.begin();

  auto copy = it++;

  ASSERT_TRUE(*copy == -10);
  ASSERT_TRUE(*it == 15);
}

TEST(Multiset, EndMinusOneIsMax_PrefixDecrement) {
  Multiset mySet;
  mySet.insert(-10);
  mySet.insert(50);
  mySet.insert(25);
  auto it = mySet.end();

  --it;

  ASSERT_TRUE(*it == 50);
}

TEST(Multiset, EndMinusOneIsMax_PostfixDecrement) {
  Multiset mySet;
  mySet.insert(-10);
  mySet.insert(50);
  mySet.insert(25);
  auto it = mySet.end();

  it--;
  auto copy = it--;

  ASSERT_TRUE(*it == 25);
  ASSERT_TRUE(*copy == 50);
}

TEST(Multiset, BidirectionalWalking) {
  Multiset mySet;
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

TEST(Multiset, ArrowDoesNotCorruptOnMultipleCalls) {
  my::my_multiset<std::string> strSet;
  strSet.insert("hello");
  strSet.insert("world");

  auto it1 = strSet.begin();
  auto it2 = ++strSet.begin();

  ASSERT_TRUE(it1->size() == 5);
  ASSERT_TRUE(it2->size() == 5);
  ASSERT_TRUE(*it1 == "hello");
  ASSERT_TRUE(*it2 == "world");
}

TEST(clear_emptyMultiset, nothing_changed) {
  Multiset mySet;

  mySet.clear();

  ASSERT_TRUE(mySet.empty() == true);
  ASSERT_TRUE(mySet.size() == 0);
}

TEST(clear_Multiset, cleared) {
  Multiset mySet;
  int value = 88;
  mySet.insert(value);
  value = 96;
  mySet.insert(value);

  mySet.clear();

  ASSERT_TRUE(mySet.empty() == true);
  ASSERT_TRUE(mySet.size() == 0);
}

TEST(erase_Multiset, ExistsValue_nodeDeleted) {
  Multiset mySet;
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
  auto iter = mySet.find(88);
  vector<int> expected = {-10, -5, 3, 96};
  vector<int> result;

  mySet.erase(iter);

  for (auto it = mySet.begin(); it != mySet.end(); ++it) {
    result.push_back(*it);
  }
  ASSERT_TRUE(result == expected);
  ASSERT_TRUE(mySet.size() == 4);
}

TEST(erase_Multiset, emptyTree_iteratorEnd) {
  Multiset mySet;

  mySet.erase(mySet.begin());

  ASSERT_TRUE(mySet.begin() == mySet.end());
  ASSERT_TRUE(mySet.size() == 0);
  ASSERT_TRUE(mySet.empty());
}

TEST(find_Multiset, existsValue_iteratorToElement) {
  Multiset mySet;
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

TEST(find_Multiset, notExistsValue_iteratorToEnd) {
  Multiset mySet;
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

TEST(Multiset, Swap) {
  Multiset a, b;
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

TEST(Multiset, SwapSelf) {
  Multiset a, b;
  a.insert(1);
  a.insert(2);

  a.swap(a);

  ASSERT_TRUE(a.size() == 2);
  ASSERT_TRUE(a.contains(1));
  ASSERT_TRUE(a.contains(2));
}

TEST(Multiset, MergeSplice) {
  Multiset a, b;
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

TEST(Multiset_LowerBound, EmptySet_ReturnsEnd) {
  Multiset ms;

  auto it = ms.lower_bound(5);

  ASSERT_TRUE(it == ms.end());
}

TEST(Multiset_LowerBound, KeyExists_ReturnsFirstEqual) {
  Multiset ms;
  ms.insert(1);
  ms.insert(3);
  ms.insert(3);
  ms.insert(5);

  auto it = ms.lower_bound(3);

  ASSERT_TRUE(*it == 3);
}

TEST(Multiset_LowerBound, KeyNotExists_ReturnsNextGreater) {
  Multiset ms;
  ms.insert(1);
  ms.insert(3);
  ms.insert(5);

  auto it = ms.lower_bound(2);

  ASSERT_TRUE(*it == 3);
}

TEST(Multiset_LowerBound, KeyGreaterThanAll_ReturnsEnd) {
  Multiset ms;
  ms.insert(1);
  ms.insert(3);
  ms.insert(5);

  auto it = ms.lower_bound(10);

  ASSERT_TRUE(it == ms.end());
}

TEST(Multiset_LowerBound, KeyLessThanAll_ReturnsBegin) {
  Multiset ms;
  ms.insert(1);
  ms.insert(3);
  ms.insert(5);

  auto it = ms.lower_bound(-5);

  ASSERT_TRUE(it == ms.begin());
  ASSERT_TRUE(*it == 1);
}

TEST(Multiset_UpperBound, EmptySet_ReturnsEnd) {
  Multiset ms;

  auto it = ms.upper_bound(5);

  ASSERT_TRUE(it == ms.end());
}

TEST(Multiset_UpperBound, KeyExists_ReturnsAfterLastEqual) {
  Multiset ms;
  ms.insert(1);
  ms.insert(3);
  ms.insert(3);
  ms.insert(3);
  ms.insert(5);

  auto it = ms.upper_bound(3);

  ASSERT_TRUE(*it == 5);
}

TEST(Multiset_UpperBound, KeyNotExists_ReturnsFirstGreater) {
  Multiset ms;
  ms.insert(1);
  ms.insert(3);
  ms.insert(5);

  auto it = ms.upper_bound(2);

  ASSERT_TRUE(*it == 3);
}

TEST(Multiset_UpperBound, KeyGreaterThanAll_ReturnsEnd) {
  Multiset ms;
  ms.insert(1);
  ms.insert(3);
  ms.insert(5);

  auto it = ms.upper_bound(10);

  ASSERT_TRUE(it == ms.end());
}

TEST(Multiset_UpperBound, KeyLessThanAll_ReturnsBegin) {
  Multiset ms;
  ms.insert(1);
  ms.insert(3);
  ms.insert(5);

  auto it = ms.upper_bound(-5);

  ASSERT_TRUE(it == ms.begin());
  ASSERT_TRUE(*it == 1);
}

TEST(Multiset_EqualRange, EmptySet_BothAreEnd) {
  my_multiset<int> ms;

  auto range = ms.equal_range(5);

  ASSERT_TRUE(range.first == ms.end());
  ASSERT_TRUE(range.second == ms.end());
}

TEST(Multiset_EqualRange, SingleElement_Found) {
  my_multiset<int> ms;
  ms.insert(42);

  auto range = ms.equal_range(42);

  ASSERT_TRUE(*range.first == 42);
  ASSERT_TRUE(++range.first == range.second);
}

TEST(Multiset_EqualRange, MultipleDuplicates) {
  Multiset ms;
  ms.insert(2);
  ms.insert(2);
  ms.insert(2);

  auto range = ms.equal_range(2);

  int count = 0;
  for (auto it = range.first; it != range.second; ++it) {
    ASSERT_TRUE(*it == 2);
    ++count;
  }
  ASSERT_TRUE(count == 3);
}

TEST(Multiset_EqualRange, KeyNotFound) {
  Multiset ms;
  ms.insert(1);
  ms.insert(3);
  ms.insert(5);

  auto range = ms.equal_range(2);

  ASSERT_TRUE(range.first == range.second);
  ASSERT_TRUE(range.first == ms.lower_bound(2));
  ASSERT_TRUE(range.second == ms.upper_bound(2));
}

TEST(Multiset_EqualRange, KeyAtTheEnd) {
  Multiset ms;
  ms.insert(10);
  ms.insert(20);
  ms.insert(30);

  auto range = ms.equal_range(30);

  ASSERT_TRUE(*range.first == 30);
  ASSERT_TRUE(range.second == ms.end());
}

TEST(Multiset_EqualRange, KeyBeforeAll) {
  Multiset ms;
  ms.insert(10);
  ms.insert(20);
  ms.insert(30);

  auto range = ms.equal_range(5);

  ASSERT_TRUE(range.first == ms.begin());
  ASSERT_TRUE(*range.first == 10);
  ASSERT_TRUE(range.second == ms.begin());
}

// Count

TEST(Multiset_Count, EmptySet_ReturnsZero) {
  Multiset ms;

  ASSERT_TRUE(ms.count(5) == 0);
}

TEST(Multiset_Count, KeyNotPresent_ReturnsZero) {
  Multiset ms;
  ms.insert(1);
  ms.insert(3);
  ms.insert(5);

  ASSERT_TRUE(ms.count(2) == 0);
  ASSERT_TRUE(ms.count(-10) == 0);
  ASSERT_TRUE(ms.count(100) == 0);
}

TEST(Multiset_Count, SingleElement_Present_ReturnsOne) {
  Multiset ms;
  ms.insert(42);
  ASSERT_TRUE(ms.count(42) == 1);
}

TEST(Multiset_Count, MultipleDuplicates_ReturnsCorrectCount) {
  Multiset ms;
  ms.insert(3);
  ms.insert(3);
  ms.insert(3);
  ms.insert(3);

  ASSERT_TRUE(ms.count(3) == 4);
}

TEST(Multiset_Count, MixedValues_OnlyCountsRequested) {
  Multiset ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  ms.insert(3);
  ms.insert(3);
  ms.insert(3);

  ASSERT_TRUE(ms.count(1) == 1);
  ASSERT_TRUE(ms.count(2) == 2);
  ASSERT_TRUE(ms.count(3) == 3);
  ASSERT_TRUE(ms.count(4) == 0);
}

TEST(Multiset_Count, AfterErase_CountDecreases) {
  my_multiset<int> ms;
  ms.insert(5);
  ms.insert(5);
  ms.insert(5);

  ASSERT_TRUE(ms.count(5) == 3);

  ms.erase(ms.find(5));
  ASSERT_TRUE(ms.count(5) == 2);

  ms.erase(ms.find(5));
  ASSERT_TRUE(ms.count(5) == 1);

  ms.erase(ms.find(5));
  ASSERT_TRUE(ms.count(5) == 0);

  ASSERT_TRUE(ms.find(5) == ms.end());
}

TEST(Multiset_Count, StringKeys_CorrectlyCounts) {
  my_multiset<std::string> ms;
  ms.insert("hello");
  ms.insert("hello");
  ms.insert("world");

  ASSERT_TRUE(ms.count("hello") == 2);
  ASSERT_TRUE(ms.count("world") == 1);
  ASSERT_TRUE(ms.count("hi") == 0);
}

TEST(Multiset_Count, FloatPrecision_ButExactMatch) {
  my_multiset<double> ms;
  ms.insert(1.1);
  ms.insert(1.1);
  ms.insert(1.1000000000000001);
  my_multiset<double> precise;
  precise.insert(1.5);
  precise.insert(1.5);
  precise.insert(2.0);

  ASSERT_TRUE(precise.count(1.5) == 2);
  ASSERT_TRUE(precise.count(2.0) == 1);
  ASSERT_TRUE(precise.count(1.499999999999) == 0);
}

TEST(Multiset_Count, CountViaEqualRange) {
  Multiset ms;
  size_t manual_count = 0;
  ms.insert(7);
  ms.insert(7);
  ms.insert(7);

  auto range = ms.equal_range(7);
  for (auto it = range.first; it != range.second; ++it) {
    ++manual_count;
  }

  ASSERT_TRUE(ms.count(7) == 3);
  ASSERT_TRUE(manual_count == 3);
  ASSERT_TRUE(ms.count(7) == manual_count);
}

TEST(Multiset, insertMany_withDoubles) {
  Multiset s;

  auto res = s.insert_many(1, 2, 1, 3, 2);

  ASSERT_TRUE(res.size() == 5);
  ASSERT_TRUE(s.size() == 5);
  ASSERT_FALSE(s.empty());
  ASSERT_TRUE(res[0].second);
  ASSERT_TRUE(res[1].second);
  ASSERT_TRUE(res[2].second);
  ASSERT_TRUE(res[3].second);
  ASSERT_TRUE(res[4].second);
}

TEST(Multiset, insert_withDoubles) {
  Multiset s;
  s.insert(1);
  s.insert(2);
  s.insert(1);
  s.insert(3);
  s.insert(2);

  ASSERT_TRUE(s.size() == 5);
  ASSERT_FALSE(s.empty());
}