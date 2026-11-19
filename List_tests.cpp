#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_empty_new) {
    List<int> list;
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
}

TEST(test_empty_push_back){
    List<int> list;
    list.push_back(1);
    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.size(), 1);
}

TEST(test_empty_push_front){
    List<int> list;
    list.push_front(1);
    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.size(), 1);
}
TEST(test_size_growing){
    List<int> list;
    list.push_back(1);
    ASSERT_EQUAL(list.size(), 1);
    list.push_front(2);
    ASSERT_EQUAL(list.size(), 2);
    list.push_back(3);
    ASSERT_EQUAL(list.size(), 3);
    list.push_front(4);
    ASSERT_EQUAL(list.size(), 4);
}

TEST(test_size_shrinking){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.pop_front();
    ASSERT_EQUAL(list.size(), 3);
    list.pop_back();
    ASSERT_EQUAL(list.size(), 2);
    ASSERT_FALSE(list.empty());
}

TEST(test_empty_after_popping){
    List<int> list;
    list.push_back(1);
    list.push_front(2);
    list.push_back(3);
    list.pop_front();
    list.pop_back();
    list.pop_front();
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_TRUE(list.empty());
}

TEST(test_empty_and_size_after_clear) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.clear();
  ASSERT_TRUE(list.empty());
  ASSERT_EQUAL(list.size(), 0);
}

TEST(test_empty_and_size_reuse_after_empty) {
  List<int> list;
  list.push_back(1);
  list.pop_front();
  ASSERT_TRUE(list.empty());
  list.push_back(2);
  ASSERT_FALSE(list.empty());
  ASSERT_EQUAL(list.size(), 1);
}



TEST_MAIN()
