#include <gtest/gtest.h>

#include <list>
#include <stdexcept>
#include <string>

#include "../my_containers.h"

TEST(LIST_CONSTRUCTOR, ConstructorCase1) {
  my::list<int> my_list_int;
  my::list<double> my_list_double;
  my::list<std::string> my_list_string;

  EXPECT_EQ(my_list_int.size(), 0U);
  EXPECT_EQ(my_list_double.size(), 0U);
  EXPECT_EQ(my_list_string.size(), 0U);
}

TEST(LIST_CONSTRUCTOR, ConstructorCase2) {
  my::list<int> my_list_int(5);
  my::list<double> my_list_double(5);
  my::list<std::string> my_list_string(5);

  EXPECT_EQ(my_list_int.size(), 5U);
  EXPECT_EQ(my_list_double.size(), 5U);
  EXPECT_EQ(my_list_string.size(), 5U);
}

TEST(LIST_INITIALIZATION, InitializationCase1) {
  my::list<int> my_list_int{1, 4, 8, 9};
  my::list<double> my_list_double{1.4, 4.8, 8.9, 9.1};
  my::list<std::string> my_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(my_list_int.size(), 4U);
  EXPECT_EQ(my_list_double.size(), 4U);
  EXPECT_EQ(my_list_string.size(), 4U);
}

TEST(LIST_COPY_ASSIGNMENT, CopyAssignmentCase1) {
  my::list<int> my_list_ref_int{1, 4, 8, 9};
  my::list<int> my_list_res_int(my_list_ref_int);

  my::list<double> my_list_ref_double{1.4, 4.8, 8.9, 9.1};
  my::list<double> my_list_res_double(my_list_ref_double);

  my::list<std::string> my_list_ref_string{"Hello", ",", "world", "!"};
  my::list<std::string> my_list_res_string(my_list_ref_string);

  EXPECT_EQ(my_list_res_int.size(), 4U);
  EXPECT_EQ(my_list_res_int.front(), 1);

  EXPECT_EQ(my_list_res_double.size(), 4U);
  EXPECT_EQ(my_list_res_double.front(), 1.4);

  EXPECT_EQ(my_list_res_string.size(), 4U);
  EXPECT_EQ(my_list_res_string.front(), "Hello");
}

TEST(LIST_MOVE_ASSIGNMENT, MoveAssignmentCase1) {
  my::list<int> my_list_ref_int{1, 4, 8, 9};
  my::list<int> my_list_res_int = std::move(my_list_ref_int);

  my::list<double> my_list_ref_double{1.4, 4.8, 8.9, 9.1};
  my::list<double> my_list_res_double = std::move(my_list_ref_double);

  my::list<std::string> my_list_ref_string{"Hello", ",", "world", "!"};
  my::list<std::string> my_list_res_string = std::move(my_list_ref_string);

  EXPECT_EQ(my_list_ref_int.size(), 0U);
  EXPECT_EQ(my_list_res_int.size(), 4U);
  EXPECT_EQ(my_list_res_int.front(), 1);

  EXPECT_EQ(my_list_ref_double.size(), 0U);
  EXPECT_EQ(my_list_res_double.size(), 4U);
  EXPECT_EQ(my_list_res_double.front(), 1.4);

  EXPECT_EQ(my_list_ref_string.size(), 0U);
  EXPECT_EQ(my_list_res_string.size(), 4U);
  EXPECT_EQ(my_list_res_string.front(), "Hello");
}

TEST(LIST_SORT, SortCase1) {
  my::list<int> my_list_int{8, 1, 4, 9};
  my::list<double> my_list_double{9.1, 1.4, 4.8, 8.9};
  my::list<std::string> my_list_string{"world", "Hello", "!", ","};

  my_list_int.sort();
  my_list_double.sort();
  my_list_string.sort();

  EXPECT_EQ(my_list_int.front(), 1);
  EXPECT_EQ(my_list_double.front(), 1.4);
  EXPECT_EQ(my_list_string.front(), "!");
}

TEST(LIST_REVERSE, ReverseCase1) {
  my::list<int> my_list_int{1, 4, 8, 9};
  my::list<double> my_list_double{1.4, 4.8, 8.9, 9.1};
  my::list<std::string> my_list_string{"Hello", ",", "world", "!"};

  my_list_int.reverse();
  my_list_double.reverse();
  my_list_string.reverse();

  EXPECT_EQ(my_list_int.front(), 9);
  EXPECT_EQ(my_list_double.front(), 9.1);
  EXPECT_EQ(my_list_string.front(), "!");
}

TEST(LIST_UNIQUE, UniqueCase1) {
  my::list<int> my_list_int{1, 1, 4, 4, 8, 8, 8, 9, 9, 9, 9, 9};
  my::list<double> my_list_double{1.4, 4.8, 1.4, 4.8, 8.9, 9.1,
                                    1.4, 4.8, 8.9, 8.9, 9.1};
  my::list<std::string> my_list_string{"Hello", ",",     "Hello", ",",
                                         "world", ",",     "world", "!",
                                         "!",     "world", "!"};

  my_list_int.unique();
  my_list_double.unique();
  my_list_string.unique();

  EXPECT_EQ(my_list_int.size(), 4U);
  EXPECT_EQ(my_list_double.size(), 10U);
  EXPECT_EQ(my_list_string.size(), 10U);
}

TEST(LIST_SIZE, SizeCase1) {
  my::list<int> my_list_int{1, 4, 8, 9};
  my::list<double> my_list_double{1.4, 4.8, 8.9, 9.1};
  my::list<std::string> my_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(my_list_int.size(), 4U);
  EXPECT_EQ(my_list_double.size(), 4U);
  EXPECT_EQ(my_list_string.size(), 4U);
}

TEST(LIST_EMPTY, EmptyCase1) {
  my::list<int> my_list_int{1, 4, 8, 9};
  my::list<double> my_list_double{1.4, 4.8, 8.9, 9.1};
  my::list<std::string> my_list_string{"Hello", ",", "world", "!"};

  EXPECT_FALSE(my_list_int.empty());
  EXPECT_FALSE(my_list_double.empty());
  EXPECT_FALSE(my_list_string.empty());
}

TEST(LIST_FRONT, FrontCase1) {
  my::list<int> my_list_int{1, 4, 8, 9};
  my::list<double> my_list_double{1.4, 4.8, 8.9, 9.1};
  my::list<std::string> my_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(my_list_int.front(), 1);
  EXPECT_EQ(my_list_double.front(), 1.4);
  EXPECT_EQ(my_list_string.front(), "Hello");
}

TEST(LIST_BACK, BackCase1) {
  my::list<int> my_list_int{1, 4, 8, 9};
  my::list<double> my_list_double{1.4, 4.8, 8.9, 9.1};
  my::list<std::string> my_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(my_list_int.back(), 9);
  EXPECT_EQ(my_list_double.back(), 9.1);
  EXPECT_EQ(my_list_string.back(), "!");
}

TEST(LIST_SWAP, SwapCase1) {
  my::list<int> my_list_ref_int{1, 4, 8, 9};
  my::list<int> my_list_res_int{12, 13};

  my::list<double> my_list_ref_double{1.4, 4.8, 8.9, 9.1};
  my::list<double> my_list_res_double{11.0, 12.0, 13.0};

  my::list<std::string> my_list_ref_string{"Hello", ",", "world", "!"};
  my::list<std::string> my_list_res_string{"12", "13", "14", "15"};

  my_list_ref_int.swap(my_list_res_int);
  my_list_ref_double.swap(my_list_res_double);
  my_list_ref_string.swap(my_list_res_string);

  EXPECT_EQ(my_list_ref_int.size(), 2U);
  EXPECT_EQ(my_list_ref_int.front(), 12);
  EXPECT_EQ(my_list_res_int.size(), 4U);
  EXPECT_EQ(my_list_res_int.front(), 1);

  EXPECT_EQ(my_list_ref_double.size(), 3U);
  EXPECT_EQ(my_list_ref_double.front(), 11.0);
  EXPECT_EQ(my_list_res_double.size(), 4U);
  EXPECT_EQ(my_list_res_double.front(), 1.4);

  EXPECT_EQ(my_list_ref_string.size(), 4U);
  EXPECT_EQ(my_list_ref_string.front(), "12");
  EXPECT_EQ(my_list_res_string.size(), 4U);
  EXPECT_EQ(my_list_res_string.front(), "Hello");
}

TEST(LIST_MERGE, MergeCase1) {
  my::list<int> my_list_ref_int{3, 5};
  my::list<int> my_list_res_int{1, 4, 8, 9};

  my::list<double> my_list_ref_double{5.6, 7.1};
  my::list<double> my_list_res_double{1.4, 4.8, 8.9, 9.1};

  my::list<std::string> my_list_ref_string{"Hi"};
  my::list<std::string> my_list_res_string{"Hello", ",", "world", "!"};

  my_list_res_int.merge(my_list_ref_int);
  my_list_res_double.merge(my_list_ref_double);
  my_list_res_string.merge(my_list_ref_string);

  EXPECT_EQ(my_list_ref_int.size(), 0U);
  EXPECT_EQ(my_list_res_int.size(), 6U);
  EXPECT_EQ(my_list_ref_double.size(), 0U);
  EXPECT_EQ(my_list_res_double.size(), 6U);
  EXPECT_EQ(my_list_ref_string.size(), 0U);
  EXPECT_EQ(my_list_res_string.size(), 5U);

  const std::vector<int> expected_int = {1, 3, 4, 5, 8, 9};
  const std::vector<double> expected_double = {1.4, 4.8, 5.6, 7.1, 8.9, 9.1};
  const std::vector<std::string> expected_string = {"Hello", ",", "Hi", "world",
                                                    "!"};

  auto res_iter = my_list_res_int.begin();
  for (const auto &val : expected_int) {
    EXPECT_EQ(*res_iter, val);
    ++res_iter;
  }

  auto res_iter2 = my_list_res_double.begin();
  for (const auto &val : expected_double) {
    EXPECT_EQ(*res_iter2, val);
    ++res_iter2;
  }

  auto res_iter3 = my_list_res_string.begin();
  for (const auto &val : expected_string) {
    EXPECT_EQ(*res_iter3, val);
    ++res_iter3;
  }
}

TEST(LIST_ERASE, EraseCase1) {
  my::list<int> my_list_int{1, 4, 8, 9};
  my::list<double> my_list_double{1.4, 4.8, 8.9, 9.1};
  my::list<std::string> my_list_string{"Hello", ",", "world", "!"};

  auto it_int = my_list_int.begin();
  my_list_int.erase(it_int++);

  auto it_double = my_list_double.begin();
  my_list_double.erase(it_double++);

  auto it_string = my_list_string.begin();
  my_list_string.erase(it_string++);

  EXPECT_EQ(my_list_int.size(), 3U);
  EXPECT_EQ(my_list_double.size(), 3U);
  EXPECT_EQ(my_list_string.size(), 3U);
}

TEST(LIST_CLEAR, ClearCase1) {
  my::list<int> my_list_int{1, 4, 8, 9};
  my::list<double> my_list_double{1.4, 4.8, 8.9, 9.1};
  my::list<std::string> my_list_string{"Hello", ",", "world", "!"};

  my_list_int.clear();
  my_list_double.clear();
  my_list_string.clear();

  EXPECT_EQ(my_list_int.size(), 0U);
  EXPECT_EQ(my_list_double.size(), 0U);
  EXPECT_EQ(my_list_string.size(), 0U);
}

TEST(LIST_POP_FRONT, PopFrontCase1) {
  my::list<int> my_list_int{1, 4, 8, 9};
  my::list<double> my_list_double{1.4, 4.8, 8.9, 9.1};
  my::list<std::string> my_list_string{"Hello", ",", "world", "!"};

  my_list_int.pop_front();
  my_list_double.pop_front();
  my_list_string.pop_front();

  EXPECT_EQ(my_list_int.size(), 3U);
  EXPECT_EQ(my_list_double.size(), 3U);
  EXPECT_EQ(my_list_string.size(), 3U);

  EXPECT_EQ(my_list_int.front(), 4);
  EXPECT_EQ(my_list_double.front(), 4.8);
  EXPECT_EQ(my_list_string.front(), ",");
}

TEST(LIST_POP_BACK, PopBackCase) {
  my::list<int> my_list_int{1};
  my::list<double> my_list_double{1.4};
  my::list<std::string> my_list_string{"Hello"};

  my_list_int.pop_back();
  my_list_double.pop_back();
  my_list_string.pop_back();

  EXPECT_EQ(my_list_int.size(), 0U);
  EXPECT_EQ(my_list_double.size(), 0U);
  EXPECT_EQ(my_list_string.size(), 0U);
}

TEST(LIST_POP_BACK, PopBackCase1) {
  my::list<int> my_list_int{1, 4, 8, 9};
  my::list<double> my_list_double{1.4, 4.8, 8.9, 9.1};
  my::list<std::string> my_list_string{"Hello", ",", "world", "!"};

  my_list_int.pop_back();
  my_list_double.pop_back();
  my_list_string.pop_back();

  EXPECT_EQ(my_list_int.size(), 3U);
  EXPECT_EQ(my_list_double.size(), 3U);
  EXPECT_EQ(my_list_string.size(), 3U);

  EXPECT_EQ(my_list_int.back(), 8);
  EXPECT_EQ(my_list_double.back(), 8.9);
  EXPECT_EQ(my_list_string.back(), "world");
}

TEST(LIST_POP_BACK, PopBackCase2) {
  my::list<int> my_list_int{1, 4};
  my::list<double> my_list_double{1.4, 4.8};
  my::list<std::string> my_list_string{"Hello", ","};

  my_list_int.pop_back();
  my_list_double.pop_back();
  my_list_string.pop_back();

  EXPECT_EQ(my_list_int.size(), 1U);
  EXPECT_EQ(my_list_double.size(), 1U);
  EXPECT_EQ(my_list_string.size(), 1U);

  EXPECT_EQ(my_list_int.back(), 1);
  EXPECT_EQ(my_list_double.back(), 1.4);
  EXPECT_EQ(my_list_string.back(), "Hello");
}

TEST(LIST_ITERATOR, IteratorCase1) {
  my::list<int> lol = {1, 2, 3, 4, 6, 43};
  std::list<int> lol_orig = {1, 2, 3, 4, 6, 43};

  auto itr = lol.begin();
  auto itr_orig = lol_orig.begin();

  auto end = lol.end();
  auto end_orig = lol_orig.end();

  while (itr != end && itr_orig != end_orig) {
    EXPECT_EQ(*itr, *itr_orig);
    itr++;
    itr_orig++;
  }
}

TEST(EraseTest, EmptyList) {
  my::list<int> l;
  auto it = l.begin();
  l.erase(it);
  EXPECT_TRUE(l.empty());
}

TEST(EraseTest, SingleElementList) {
  my::list<int> l = {42};
  auto it = l.begin();
  l.erase(it);
  EXPECT_TRUE(l.empty());
}

TEST(EraseTest, RemoveFirstElement) {
  my::list<int> l = {1, 2, 3};
  auto it = l.begin();
  l.erase(it);
  EXPECT_EQ(l.front(), 2);
  EXPECT_EQ(l.size(), 2);
}

TEST(EraseTest, RemoveMiddleElement) {
  my::list<int> l = {1, 2, 3};
  auto it = ++l.begin();
  l.erase(it);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 3);
  EXPECT_EQ(l.size(), 2);
}

TEST(EraseTest, OutOfBounds) {
  my::list<int> l = {1, 2, 3};
  auto it = l.end();
  l.erase(it);
  EXPECT_EQ(l.size(), 3);
}

TEST(EraseTest, ComplexScenario) {
  my::list<int> l = {1, 2, 3, 4, 5};
  auto it = ++(++(++(l.begin())));
  l.erase(it);
  EXPECT_EQ(l.size(), 4);
  it = ++(++(++(l.begin())));
  EXPECT_EQ(*it, 5);
}

TEST(max_size, case1) {
  my::list<int> my_list_int{1, 4, 8, 9};
  std::list<int> std_list_int{1, 4, 8, 9};

  my::list<double> my_list_double{1.4, 4.8, 8.9, 9.1};
  std::list<double> std_list_double{1.4, 4.8, 8.9, 9.1};

  my::list<std::string> my_list_string{"Hello", ",", "world", "!"};
  std::list<std::string> std_list_string{"Hello", ",", "world", "!"};

  EXPECT_GE(my_list_int.max_size(), std_list_int.max_size());
  EXPECT_GE(my_list_double.max_size(), std_list_double.max_size());
  EXPECT_GE(my_list_string.max_size(), std_list_string.max_size());
}

TEST(insert_many, case0) {
  my::list<int> lol = {1, 2, 3, 4, 6, 0};
  size_t size = 9;
  auto itr = lol.begin();
  for (int i = 0; i < 3; ++i) {
    ++itr;
  }
  my::list<int>::const_iterator citr = itr;
  lol.insert_many(citr, 13, 11, 12);

  itr = lol.begin();
  for (int i = 0; i < 3; ++i) {
    ++itr;
  }
  EXPECT_EQ(lol.size(), size);
  EXPECT_EQ(*itr, 13);
  ++itr;
  EXPECT_EQ(*itr, 11);
  ++itr;
  EXPECT_EQ(*itr, 12);
  ++itr;
  EXPECT_EQ(*itr, 4);
}

TEST(insert_many_back, case0) {
  my::list<int> lol = {1, 2, 3, 4, 6, 0};
  size_t size = 9;

  lol.insert_many_back(13, 11, 12);

  EXPECT_EQ(lol.size(), size);
  auto itr = lol.begin();
  for (int i = 0; i < 5; ++i) {
    ++itr;
  }
  EXPECT_EQ(*itr, 0);
  ++itr;
  EXPECT_EQ(*itr, 13);
  ++itr;
  EXPECT_EQ(*itr, 11);
  ++itr;
  EXPECT_EQ(*itr, 12);
}

TEST(insert_many_front, case0) {
  my::list<int> lol = {1, 2, 3, 4, 6, 0};
  size_t size = 9;

  lol.insert_many_front(13, 11, 12);

  EXPECT_EQ(lol.size(), size);
  auto itr = lol.begin();

  itr = lol.begin();
  EXPECT_EQ(*itr, 12);
  ++itr;
  EXPECT_EQ(*itr, 11);
  ++itr;
  EXPECT_EQ(*itr, 13);
  ++itr;
  EXPECT_EQ(*itr, 1);
}

template <typename T>
bool lists_equal(const my::list<T> &a, const my::list<T> &b) {
  if (a.size() != b.size()) return false;
  auto it1 = a.begin();
  auto it2 = b.begin();
  while (it1 != a.end()) {
    if (*it1 != *it2) return false;
    ++it1;
    ++it2;
  }
  return true;
}

TEST(SpliceTest, SpliceEmptyOther) {
  my::list<int> list1 = {1, 2, 3};
  my::list<int> list2;

  list1.splice(list1.begin(), list2);

  EXPECT_TRUE(lists_equal(list1, my::list<int>{1, 2, 3}));
  EXPECT_TRUE(list2.empty());
}

TEST(SpliceTest, SpliceIntoEmptyList) {
  my::list<int> list1 = {1, 2};
  my::list<int> list2 = {4, 5, 6};

  list1.splice(++list1.begin(), list2);

  EXPECT_TRUE(lists_equal(list1, my::list<int>{1, 4, 5, 6, 2}));
  EXPECT_TRUE(list2.empty());
}

TEST(SpliceTest, SpliceIntoEmptyList2) {
  my::list<int> list1 = {1, 2};
  my::list<int> list2 = {4, 5, 6};

  list1.splice(list1.begin(), list2);

  EXPECT_TRUE(lists_equal(list1, my::list<int>{4, 5, 6, 1, 2}));
  EXPECT_TRUE(list2.empty());
}

TEST(SpliceTest, SpliceAtBegin) {
  my::list<int> list1 = {1, 2, 3};
  my::list<int> list2 = {4, 5};

  list1.splice(list1.end(), list2);

  EXPECT_TRUE(lists_equal(list1, my::list<int>{1, 2, 3, 4, 5}));
  EXPECT_TRUE(list2.empty());
}

TEST(SpliceTest, SpliceAtEnd) {
  my::list<int> list1 = {1, 2, 3};
  my::list<int> list2;

  list1.splice(list1.end(), list2);

  EXPECT_TRUE(lists_equal(list1, my::list<int>{1, 2, 3}));
  EXPECT_TRUE(list2.empty());
}

TEST(AssignmentTest, OperatorsAreNoexcept) {
  EXPECT_TRUE(noexcept(my::list<int>{} = std::initializer_list<int>{}));
  EXPECT_TRUE(noexcept(my::list<int>{} = my::list<int>{}));
  EXPECT_TRUE(noexcept(my::list<int>{} = my::list<int>{}));
}

TEST(AssignmentTest, AssignInitializerList) {
  my::list<int> list1 = {1, 2, 3};
  list1 = {4, 5, 6, 7};
  my::list<int> list2 = {4, 5, 6, 7};
  EXPECT_TRUE(lists_equal(list1, list2));
  EXPECT_EQ(list1.size(), 4);
}

TEST(CLEAR, clear) {
  my::list<int> list1 = {1, 2, 3};
  list1.clear();
  EXPECT_EQ(list1.size(), 0);
}

TEST(AssignmentTest, AssignEmptyInitializerList) {
  my::list<int> list1 = {1, 2, 3};
  list1 = {};

  EXPECT_TRUE(list1.empty());
  EXPECT_EQ(list1.size(), 0);
}

TEST(AssignmentTest, CopyAssignment) {
  my::list<int> list1 = {1, 2, 3};
  my::list<int> list2 = {10, 20};

  list2 = list1;

  EXPECT_TRUE(lists_equal(list1, list2));
  EXPECT_EQ(list2.size(), 3);
}

TEST(AssignmentTest, CopyAssignmentFromEmpty) {
  my::list<int> list1;
  my::list<int> list2 = {1, 2, 3};

  list2 = list1;

  EXPECT_TRUE(list2.empty());
}

TEST(AssignmentTest, CopyAssignmentToEmpty) {
  my::list<int> list1 = {1, 2, 3};
  my::list<int> list2;

  list2 = list1;

  EXPECT_TRUE(lists_equal(list1, list2));
}

TEST(AssignmentTest, SelfCopyAssignment) {
  my::list<int> list1 = {1, 2, 3};
  list1 = list1;
  EXPECT_TRUE(lists_equal(list1, my::list<int>{1, 2, 3}));
  EXPECT_EQ(list1.size(), 3);
}

TEST(AssignmentTest, MoveAssignment) {
  my::list<int> list2 = {10, 20};
  my::list<int> temp = {4, 5, 6};
  list2 = std::move(temp);

  EXPECT_TRUE(lists_equal(list2, my::list<int>{4, 5, 6}));
  EXPECT_TRUE(temp.empty());
}

TEST(AssignmentTest, MoveAssignmentFromEmpty) {
  my::list<int> list1 = {1, 2, 3};
  my::list<int> empty_list;

  list1 = std::move(empty_list);

  EXPECT_TRUE(list1.empty());
  EXPECT_TRUE(empty_list.empty());
}

TEST(AssignmentTest, MoveAssignmentToEmpty) {
  my::list<int> list1;
  my::list<int> list2 = {7, 8, 9};

  list1 = std::move(list2);

  EXPECT_TRUE(lists_equal(list1, my::list<int>{7, 8, 9}));
  EXPECT_TRUE(list2.empty());
}

TEST(PUSH_FRONT, push_front) {
  my::list<int> list1;
  list1.push_front(1);
  my::list<int> list2 = {1};

  EXPECT_TRUE(lists_equal(list1, list2));

  EXPECT_EQ(list1.size(), 1);
}

TEST(MERGE, merge) {
  my::list<int> list1;
  my::list<int> list2 = {1, 2, 3};
  list1.merge(list2);

  EXPECT_TRUE(lists_equal(list1, my::list<int>{1, 2, 3}));
}

TEST(splice, insert) {
  my::list<int> list1;
  my::list<int> list2 = {4};

  list1.splice(list1.end(), list2);

  EXPECT_EQ(list1.size(), 1);
  EXPECT_TRUE(lists_equal(list1, my::list<int>{4}));
}

TEST(INSERT, insert) {
  my::list<int> list1;
  // my::list<int> list2={4};

  list1.insert(list1.end(), 4);

  EXPECT_EQ(list1.size(), 1);
  EXPECT_TRUE(lists_equal(list1, my::list<int>{4}));
}

TEST(INSERT, insert2) {
  my::list<int> list1{2};

  list1.insert(list1.end(), 4);

  EXPECT_EQ(list1.size(), 2);
  EXPECT_TRUE(lists_equal(list1, my::list<int>{2, 4}));
}

TEST(INSERT, insert3) {
  my::list<int> list1{2};

  list1.insert(list1.begin(), 4);

  EXPECT_EQ(list1.size(), 2);
  EXPECT_TRUE(lists_equal(list1, my::list<int>{4, 2}));
}