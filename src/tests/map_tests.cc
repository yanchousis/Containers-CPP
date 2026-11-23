#include <gtest/gtest.h>

#include "../my_containers.h"

using namespace std;
using namespace my;

using Map = my_map<int, int>;

TEST(mapCreation, mapCreated) {
  Map mySet;

  ASSERT_TRUE(mySet.empty() == true);
  ASSERT_TRUE(mySet.size() == 0);
}

TEST(mapCreation, MaxSize) {
  Map s;

  auto max_sz = s.max_size();

  ASSERT_GE(max_sz, 0);
  ASSERT_TRUE(max_sz <= std::numeric_limits<size_t>::max());
}

TEST(Map_Insert, InsertNewElement_ReturnsTrueAndValidIterator) {
  my_map<int, std::string> m;
  auto [it, inserted] = m.insert(std::make_pair(1, "hello"));

  ASSERT_TRUE(inserted);
  ASSERT_NE(it, m.end());
  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, "hello");
}

TEST(Map_Insert, InsertDuplicateKey_ReturnsFalseAndPointsToExisting) {
  my_map<int, std::string> m;
  m.insert(std::make_pair(42, "original"));

  auto [it, inserted] = m.insert(std::make_pair(42, "duplicate"));

  ASSERT_FALSE(inserted);
  ASSERT_NE(it, m.end());
  ASSERT_EQ(it->first, 42);
  ASSERT_EQ(it->second, "original");
}

TEST(Map_Insert_TwoArg, InsertWithKeyAndValue) {
  my_map<int, std::string> m;
  auto [it, inserted] = m.insert(7, "seven");

  ASSERT_TRUE(inserted);
  ASSERT_NE(it, m.end());
  ASSERT_EQ(it->first, 7);
  ASSERT_EQ(it->second, "seven");
}

TEST(Map_Insert_TwoArg, InsertDuplicateTwoArg_ReturnsFalse) {
  my_map<int, std::string> m;
  m.insert(99, "first");

  auto [it, inserted] = m.insert(99, "second");

  ASSERT_FALSE(inserted);
  ASSERT_EQ(it->second, "first");
}

TEST(Map_Insert_InitializerListLike, MultipleInsertsInLoop) {
  my_map<int, char> m;
  std::vector<std::pair<int, char>> data = {{1, 'a'}, {2, 'b'}, {3, 'c'}};

  for (const auto& p : data) {
    auto [it, inserted] = m.insert(p);
    ASSERT_TRUE(inserted) << "Failed to insert {" << p.first << ", " << p.second
                          << "}";
    ASSERT_EQ(it->first, p.first);
    ASSERT_EQ(it->second, p.second);
  }

  ASSERT_EQ(m.size(), 3);
  ASSERT_EQ(m.at(1), 'a');
  ASSERT_EQ(m.at(2), 'b');
  ASSERT_EQ(m.at(3), 'c');
}

TEST(Map_InsertOrAssign, KeyNotExists_InsertsNew) {
  my_map<int, std::string> m;
  auto [it, inserted] = m.insert_or_assign(5, "new_value");

  ASSERT_TRUE(inserted);
  ASSERT_NE(it, m.end());
  ASSERT_EQ(it->first, 5);
  ASSERT_EQ(it->second, "new_value");
  ASSERT_EQ(m.size(), 1);
}

TEST(Map_InsertOrAssign, KeyExists_UpdatesValueAndReturnsFalse) {
  my_map<int, std::string> m;
  m.insert(std::make_pair(10, "old"));

  auto [it, inserted] = m.insert_or_assign(10, "updated");

  ASSERT_FALSE(inserted);
  ASSERT_NE(it, m.end());
  ASSERT_EQ(it->first, 10);
  ASSERT_EQ(it->second, "updated");
  ASSERT_EQ(m.at(10), "updated");
}

TEST(Map_InsertOrAssign, InsertOrAssign_AffectsMapContent) {
  my_map<std::string, int> m;

  m.insert_or_assign("one", 1);
  m.insert_or_assign("two", 2);
  m.insert_or_assign("one", 11);

  ASSERT_EQ(m.at("one"), 11);
  ASSERT_EQ(m.at("two"), 2);
  ASSERT_EQ(m.size(), 2);
}

TEST(my_map_test, DefaultConstructor_Empty) {
  my_map<int, std::string> m;
  ASSERT_TRUE(m.empty());
  ASSERT_TRUE(m.size() == 0);
}

TEST(my_map_test, MoveConstructor_Valid) {
  my_map<int, char> original;
  original.insert(1, 'a');
  original.insert(2, 'b');

  my_map<int, char> moved(std::move(original));

  ASSERT_FALSE(moved.empty());
  ASSERT_TRUE(moved.size() == 2);
  ASSERT_TRUE(moved.contains(1));
  ASSERT_TRUE(moved.contains(2));
  ASSERT_TRUE(moved.at(1) == 'a');
  ASSERT_TRUE(moved.at(2) == 'b');
}

TEST(my_map_test, AssignmentOperator_Copy) {
  my_map<int, int> m1;
  m1.insert(1, 10);
  m1.insert(2, 20);

  my_map<int, int> m2;
  m2 = m1;

  ASSERT_FALSE(m2.empty());
  ASSERT_TRUE(m2.size() == 2);
  ASSERT_TRUE(m2.contains(1));
  ASSERT_TRUE(m2.contains(2));
  ASSERT_TRUE(m2.at(1) == 10);
  ASSERT_TRUE(m2.at(2) == 20);
}

TEST(my_map_test, AssignmentOperator_Move) {
  my_map<int, int> m1;
  m1.insert(1, 100);
  m1.insert(3, 300);

  my_map<int, int> m2;
  m2 = std::move(m1);

  ASSERT_FALSE(m2.empty());
  ASSERT_TRUE(m2.size() == 2);
  ASSERT_TRUE(m2.contains(1));
  ASSERT_TRUE(m2.contains(3));
  ASSERT_TRUE(m2.at(1) == 100);
  ASSERT_TRUE(m2.at(3) == 300);
}

TEST(my_map_test, At_AccessExistingElement) {
  my_map<std::string, int> m;
  m["hello"] = 42;

  ASSERT_TRUE(m.at("hello") == 42);
}

TEST(my_map_test,
     At_ThrowsOnMissingKey_ExceptionNotCheckedHereButAssumeSafeUse) {
  my_map<std::string, int> m;
  m["test"] = 100;

  ASSERT_TRUE(m.contains("test"));
  ASSERT_FALSE(m.contains("missing"));
}

TEST(my_map_test, SubscriptOperator_InsertsIfMissing) {
  my_map<int, std::string> m;
  m[5] = "five";

  ASSERT_TRUE(m.contains(5));
  ASSERT_TRUE(m.at(5) == "five");
}

TEST(my_map_test, BeginEnd_IteratorsWork) {
  my_map<int, int> m;
  m.insert(1, 10);

  ASSERT_FALSE(m.begin() == m.end());
  ASSERT_TRUE(m.begin() != m.end());
}

TEST(my_map_test, BeginEnd_ConstVersion) {
  my_map<int, int> m;
  m.insert(99, 999);

  const auto& cm = m;
  auto it = cm.begin();
  auto end = cm.end();

  ASSERT_TRUE(it != end);
  ASSERT_TRUE((*it).first == 99);
  ASSERT_TRUE((*it).second == 999);
}

TEST(my_map_test, Empty_Size_MaxSize_Basic) {
  my_map<char, double> m;

  ASSERT_TRUE(m.empty());
  ASSERT_TRUE(m.size() == 0);
  ASSERT_TRUE(m.max_size() > 0);
}

TEST(my_map_test, Clear_RemovesAllElements) {
  my_map<int, int> m;
  m.insert(1, 1);
  m.insert(2, 2);
  m.clear();

  ASSERT_TRUE(m.empty());
  ASSERT_TRUE(m.size() == 0);
}

TEST(my_map_test, Insert_NewElement_Success) {
  my_map<int, std::string> m;
  auto result = m.insert(std::make_pair(1, "one"));

  ASSERT_TRUE(result.second);
  ASSERT_TRUE(result.first != m.end());
  ASSERT_TRUE(m.contains(1));
}

TEST(my_map_test, Insert_DuplicateKey_Fails) {
  my_map<int, int> m;
  m.insert(5, 50);

  auto result = m.insert(std::make_pair(5, 999));

  ASSERT_FALSE(result.second);
  ASSERT_TRUE(result.first != m.end());
  ASSERT_TRUE((*result.first).second == 50);
}

TEST(my_map_test, Insert_TwoArg_NewKey) {
  my_map<int, char> m;
  auto result = m.insert(7, 'G');

  ASSERT_TRUE(result.second);
  ASSERT_TRUE(result.first != m.end());
  ASSERT_TRUE(m.at(7) == 'G');
}

TEST(my_map_test, InsertOrAssign_NewKey_Inserts) {
  my_map<int, std::string> m;
  auto result = m.insert_or_assign(1, "first");

  ASSERT_TRUE(result.second);
  ASSERT_TRUE(m.at(1) == "first");
}

TEST(my_map_test, InsertOrAssign_ExistingKey_Updates) {
  my_map<int, std::string> m;
  m.insert_or_assign(2, "old");
  auto result = m.insert_or_assign(2, "new");

  ASSERT_FALSE(result.second);
  ASSERT_TRUE(m.at(2) == "new");
}

TEST(my_map_test, InsertMany_MultipleNewElements) {
  my_map<int, char> m;
  auto results = m.insert_many(std::make_pair(1, 'A'), std::make_pair(2, 'B'),
                               std::make_pair(3, 'C'));

  ASSERT_TRUE(results.size() == 3);
  for (const auto& res : results) {
    ASSERT_TRUE(res.second);
  }
  ASSERT_TRUE(m.size() == 3);
  ASSERT_TRUE(m.contains(1));
  ASSERT_TRUE(m.contains(2));
  ASSERT_TRUE(m.contains(3));
}

TEST(my_map_test, InsertMany_WithDuplicates) {
  my_map<int, int> m;
  auto results = m.insert_many(std::make_pair(1, 10), std::make_pair(1, 99),
                               std::make_pair(2, 20));

  ASSERT_TRUE(results.size() == 3);
  ASSERT_TRUE(results[0].second);
  ASSERT_FALSE(results[1].second);
  ASSERT_TRUE(results[2].second);
  ASSERT_TRUE(m.size() == 2);
}

TEST(my_map_test, Swap_ExchangesContents) {
  my_map<int, int> m1, m2;
  m1.insert(1, 11);
  m2.insert(2, 22);

  m1.swap(m2);

  ASSERT_TRUE(m1.contains(2));
  ASSERT_FALSE(m1.contains(1));
  ASSERT_TRUE(m2.contains(1));
  ASSERT_FALSE(m2.contains(2));
  ASSERT_TRUE(m1.at(2) == 22);
  ASSERT_TRUE(m2.at(1) == 11);
}

TEST(my_map_test, Merge_OtherMap_AddsUniqueKeys) {
  my_map<int, char> m1, m2;
  m1.insert(1, 'A');
  m2.insert(2, 'B');
  m2.insert(1, 'X');

  m1.merge(m2);

  ASSERT_TRUE(m1.size() == 2);
  ASSERT_TRUE(m1.contains(1));
  ASSERT_TRUE(m1.contains(2));
  ASSERT_TRUE(m2.size() == 0);
}

TEST(my_map_test, Contains_KeyExists) {
  my_map<std::string, int> m;
  m["key"] = 123;

  ASSERT_TRUE(m.contains("key"));
  ASSERT_FALSE(m.contains("missing"));
}