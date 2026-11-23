#include <gtest/gtest.h>

#include <algorithm>
#include <array>

#include "../my_containersplus.h"
TEST(ArrayConstructorTests, DefaultInitialization) {
  my::array<int, 4> arr;
  EXPECT_EQ(arr.size(), 4U);
  EXPECT_EQ(arr.empty(), false);
}

TEST(ArrayConstructorTests, ValueInitialization) {
  my::array<int, 4> arr{1, 2, 3, 4};
  EXPECT_EQ(arr.size(), 4U);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);
}

TEST(ArrayConstructorTests, CopyConstructor) {
  my::array<int, 4> ref{1, 2, 3, 4};
  my::array<int, 4> copy(ref);
  EXPECT_EQ(copy.size(), 4U);
  EXPECT_EQ(copy[0], 1);
  EXPECT_EQ(copy[1], 2);
  EXPECT_EQ(copy[2], 3);
  EXPECT_EQ(copy[3], 4);
}

TEST(ArrayConstructorTests, MoveConstructor) {
  my::array<int, 4> src{1, 2, 3, 4};
  my::array<int, 4> moved(std::move(src));
  EXPECT_EQ(moved.size(), 4U);
  EXPECT_EQ(moved[0], 1);
  EXPECT_EQ(moved[1], 2);
  EXPECT_EQ(moved[2], 3);
  EXPECT_EQ(moved[3], 4);
}

TEST(ArrayConstructorTests, AssignOperator) {
  my::array<int, 4> src{1, 2, 3, 4};
  my::array<int, 4> dest(src);

  EXPECT_EQ(dest.size(), 4U);
  EXPECT_EQ(dest[0], 1);
  EXPECT_EQ(dest[1], 2);
  EXPECT_EQ(dest[2], 3);
  EXPECT_EQ(dest[3], 4);
}

TEST(ArrayConstructorTests, MoveAssignOperator) {
  my::array<int, 4> src{1, 2, 3, 4};
  my::array<int, 4> dest;
  dest = std::move(src);
  EXPECT_EQ(dest.size(), 4U);
  EXPECT_EQ(dest[0], 1);
  EXPECT_EQ(dest[1], 2);
  EXPECT_EQ(dest[2], 3);
  EXPECT_EQ(dest[3], 4);
}

TEST(ElementAccessTests, AtMethod) {
  my::array<int, 4> arr{1, 2, 3, 4};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(1), 2);
  EXPECT_EQ(arr.at(2), 3);
  EXPECT_EQ(arr.at(3), 4);

  EXPECT_THROW(arr.at(-1), std::out_of_range);
  EXPECT_THROW(arr.at(4), std::out_of_range);
}

TEST(ElementAccessTests, SquareBrackets) {
  my::array<int, 4> arr{1, 2, 3, 4};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);
}

TEST(ElementAccessTests, FrontMethod) {
  my::array<int, 4> arr{1, 2, 3, 4};
  EXPECT_EQ(arr.front(), 1);
}

TEST(ElementAccessTests, BackMethod) {
  my::array<int, 4> arr{1, 2, 3, 4};
  EXPECT_EQ(arr.back(), 4);
}

TEST(SizeTests, EmptyArray) {
  my::array<int, 0> empty_array;
  EXPECT_EQ(empty_array.size(), 0U);
  EXPECT_EQ(empty_array.empty(), true);
}

TEST(SizeTests, NonEmptyArray) {
  my::array<int, 4> nonempty_array{1, 2, 3, 4};
  EXPECT_EQ(nonempty_array.size(), 4U);
  EXPECT_EQ(nonempty_array.empty(), false);
}

TEST(SizeTests, MaxSizeComparison) {
  my::array<int, 4> array;
  std::array<int, 4> std_array;
  EXPECT_EQ(array.max_size(), std_array.max_size());
}

TEST(FillFunctionTests, FillIntArray) {
  my::array<int, 4> arr{1, 2, 3, 4};
  arr.fill(21);
  EXPECT_EQ(arr[0], 21);
  EXPECT_EQ(arr[1], 21);
  EXPECT_EQ(arr[2], 21);
  EXPECT_EQ(arr[3], 21);
}

TEST(SwapFunctionTests, SwapArrays) {
  my::array<int, 4> arr1{1, 2, 3, 4};
  my::array<int, 4> arr2{5, 6, 7, 8};
  arr1.swap(arr2);
  EXPECT_EQ(arr1[0], 5);
  EXPECT_EQ(arr1[1], 6);
  EXPECT_EQ(arr1[2], 7);
  EXPECT_EQ(arr1[3], 8);

  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
}

TEST(IterationTests, BeginEndPointers) {
  my::array<int, 4> arr{1, 2, 3, 4};
  EXPECT_EQ(arr.begin(), &arr[0]);
  EXPECT_EQ(arr.end(), (&arr[0]) + 4);
}

TEST(IterationTests, DataPointer) {
  my::array<int, 4> arr{1, 2, 3, 4};
  EXPECT_EQ(arr.data(), &arr[0]);
}

TEST(IterationTests, IteratingThroughArray) {
  my::array<int, 4> arr{1, 2, 3, 4};
  auto iter = arr.begin();
  for (const auto &el : arr) {
    EXPECT_EQ(*iter, el);
    ++iter;
  }
}
