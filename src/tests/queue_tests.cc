#include <gtest/gtest.h>

#include <queue>

#include "../my_containers.h"

template <typename value_type>
bool check_eq(my::queue<value_type> m_queue,
              std::queue<value_type> orig_queue) {
  bool result = true;
  if (m_queue.size() == orig_queue.size()) {
    while (!m_queue.empty() && !orig_queue.empty()) {
      if (m_queue.front() != orig_queue.front()) {
        result = false;
        break;
      }
      m_queue.pop();
      orig_queue.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(QueueTests, DefaultConstructors) {
  my::queue<int> q1;
  std::queue<int> o_q1;
  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q1.size(), 0);
  EXPECT_TRUE(o_q1.empty());
  EXPECT_EQ(o_q1.size(), 0);
}

TEST(QueueTests, ListInitializerConstructor) {
  my::queue<int> q2({1, 2, 3});
  std::queue<int> o_q2;
  o_q2.push(1);
  o_q2.push(2);
  o_q2.push(3);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
  EXPECT_TRUE(check_eq(q2, o_q2));
}

TEST(QueueTests, MoveConstructor) {
  my::queue<int> source({1, 2, 3});
  my::queue<int> target(std::move(source));
  std::queue<int> o_target;
  o_target.push(1);
  o_target.push(2);
  o_target.push(3);
  EXPECT_EQ(target.size(), 3);
  EXPECT_EQ(target.front(), 1);
  EXPECT_EQ(target.back(), 3);
  EXPECT_TRUE(check_eq(target, o_target));
}

TEST(QueueTests, PushOperation) {
  my::queue<int> q3;
  q3.push(1);
  q3.push(2);
  q3.push(3);
  std::queue<int> o_q3;
  o_q3.push(1);
  o_q3.push(2);
  o_q3.push(3);
  EXPECT_EQ(q3.size(), 3);
  EXPECT_EQ(q3.front(), 1);
  EXPECT_EQ(q3.back(), 3);
  EXPECT_TRUE(check_eq(q3, o_q3));
}

TEST(QueueTests, PopOperation) {
  my::queue<int> q4({1, 2, 3});
  std::queue<int> o_q4;
  o_q4.push(1);
  o_q4.push(2);
  o_q4.push(3);
  q4.pop();
  o_q4.pop();
  EXPECT_EQ(q4.size(), 2);
  EXPECT_EQ(q4.front(), 2);
  EXPECT_EQ(q4.back(), 3);
  EXPECT_TRUE(check_eq(q4, o_q4));
}

TEST(QueueTests, SwapOperation) {
  my::queue<int> q5({1, 2, 3});
  my::queue<int> q6({4, 5, 6});
  q5.swap(q6);
  std::queue<int> o_q5;
  o_q5.push(4);
  o_q5.push(5);
  o_q5.push(6);
  std::queue<int> o_q6;
  o_q6.push(1);
  o_q6.push(2);
  o_q6.push(3);
  EXPECT_TRUE(check_eq(q5, o_q5));
  EXPECT_TRUE(check_eq(q6, o_q6));
}

TEST(QueueTests, AccessOnEmptyQueue) {
  my::queue<int> q7;
  EXPECT_THROW(q7.front(), std::logic_error);
  EXPECT_THROW(q7.back(), std::logic_error);
  EXPECT_THROW(q7.pop(), std::logic_error);
}

TEST(QueueTests, InvalidIndexing) {
  my::queue<int> q8({1, 2, 3});
  EXPECT_NO_THROW(q8.front());
  EXPECT_NO_THROW(q8.back());
  q8.pop();
  EXPECT_NO_THROW(q8.front());
  EXPECT_NO_THROW(q8.back());
}

TEST(QueueTests, QueueEqualityCheck) {
  my::queue<int> q9({1, 2, 3});
  std::queue<int> o_q9;
  o_q9.push(1);
  o_q9.push(2);
  o_q9.push(3);
  EXPECT_TRUE(check_eq(q9, o_q9));

  my::queue<int> q10({1, 2, 3, 4});
  std::queue<int> o_q10;
  o_q10.push(1);
  o_q10.push(2);
  o_q10.push(3);
  EXPECT_FALSE(check_eq(q10, o_q10));
}

TEST(QueueTests, EdgeCases) {
  my::queue<int> q11({1});
  std::queue<int> o_q11;
  o_q11.push(1);
  EXPECT_EQ(q11.size(), 1);
  EXPECT_EQ(q11.front(), 1);
  EXPECT_EQ(q11.back(), 1);
  EXPECT_TRUE(check_eq(q11, o_q11));

  my::queue<int> q12({});
  std::queue<int> o_q12;
  EXPECT_EQ(q12.size(), 0);
  EXPECT_TRUE(check_eq(q12, o_q12));
}

TEST(QueueTests, OtherTypes) {
  my::queue<double> dq({1.1, 2.2, 3.3});
  std::queue<double> odq;
  odq.push(1.1);
  odq.push(2.2);
  odq.push(3.3);
  EXPECT_TRUE(check_eq(dq, odq));

  my::queue<std::string> sq({"one", "two", "three"});
  std::queue<std::string> osq;
  osq.push("one");
  osq.push("two");
  osq.push("three");
  EXPECT_TRUE(check_eq(sq, osq));
}

TEST(QueueTests, MixedOperations) {
  my::queue<int> mixed({1, 2, 3});
  mixed.push(4);
  mixed.push(5);
  mixed.pop();
  mixed.pop();
  std::queue<int> omixed;
  omixed.push(1);
  omixed.push(2);
  omixed.push(3);
  omixed.push(4);
  omixed.push(5);
  omixed.pop();
  omixed.pop();
  EXPECT_TRUE(check_eq(mixed, omixed));
}

TEST(QueueTest, InsertManyBackSingleElement) {
  my::queue<int> q;
  q.insert_many_back(1);
  ASSERT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 1);
}

TEST(QueueTest, InsertManyBackMultipleElements) {
  my::queue<int> q;
  q.insert_many_back(1, 2, 3, 4, 5);
  ASSERT_EQ(q.size(), 5);
  EXPECT_EQ(q.front(), 1);
  q.pop();
  EXPECT_EQ(q.front(), 2);
  q.pop();
  EXPECT_EQ(q.front(), 3);
  q.pop();
  EXPECT_EQ(q.front(), 4);
  q.pop();
  EXPECT_EQ(q.front(), 5);
}

TEST(QueueTest, InsertMixedTypes) {
  my::queue<double> q;
  q.insert_many_back(1.0, 2.5, 3.14, 4.2);
  ASSERT_EQ(q.size(), 4);
  EXPECT_DOUBLE_EQ(q.front(), 1.0);
  q.pop();
  EXPECT_DOUBLE_EQ(q.front(), 2.5);
  q.pop();
  EXPECT_DOUBLE_EQ(q.front(), 3.14);
  q.pop();
  EXPECT_DOUBLE_EQ(q.front(), 4.2);
}

TEST(QueueTest, EmptyQueue) {
  my::queue<std::string> q;
  q.insert_many_back("hello", "world");
  ASSERT_EQ(q.size(), 2);
  EXPECT_STREQ(q.front().c_str(), "hello");
  q.pop();
  EXPECT_STREQ(q.front().c_str(), "world");
}
