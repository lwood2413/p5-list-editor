#include "List.hpp"
#include "unit_test_framework.hpp"
#include <vector>

struct Point {
  int x;
  int y;
};

static void fill(List<int> &list, const std::vector<int> &values) {
  for (size_t i = 0; i < values.size(); ++i) {
    list.push_back(values[i]);
  }
}

static void check(const List<int> &list, const std::vector<int> &expected) {
  ASSERT_EQUAL(list.size(), static_cast<int>(expected.size()));
  ASSERT_EQUAL(list.empty(), expected.empty());

  List<int>::Iterator it = list.begin();
  for (size_t i = 0; i < expected.size(); ++i) {
    ASSERT_TRUE(it != list.end());
    ASSERT_EQUAL(*it, expected[i]);
    ++it;
  }
  ASSERT_TRUE(it == list.end());

  it = list.end();
  for (size_t i = expected.size(); i > 0; --i) {
    --it;
    ASSERT_EQUAL(*it, expected[i - 1]);
  }
  ASSERT_TRUE(it == list.begin());
}

TEST(test_empty_new_list) {
  List<int> list;
  ASSERT_TRUE(list.empty());
  ASSERT_EQUAL(list.size(), 0);
}

TEST(test_empty_after_push) {
  List<int> a;
  a.push_back(1);
  ASSERT_FALSE(a.empty());
  ASSERT_EQUAL(a.size(), 1);

  List<int> b;
  b.push_front(1);
  ASSERT_FALSE(b.empty());
  ASSERT_EQUAL(b.size(), 1);
}

TEST(test_size_grows_with_pushes) {
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

TEST(test_size_shrinks_with_pops) {
  List<int> list;
  fill(list, {1, 2, 3, 4});
  list.pop_front();
  ASSERT_EQUAL(list.size(), 3);
  list.pop_back();
  ASSERT_EQUAL(list.size(), 2);
  ASSERT_FALSE(list.empty());
}

TEST(test_empty_after_popping_everything) {
  List<int> list;
  fill(list, {1, 2});
  list.pop_front();
  list.pop_back();
  ASSERT_TRUE(list.empty());
  ASSERT_EQUAL(list.size(), 0);
}

TEST(test_clear_populated) {
  List<int> list;
  fill(list, {1, 2, 3});
  list.clear();
  ASSERT_TRUE(list.empty());
  ASSERT_EQUAL(list.size(), 0);
  ASSERT_TRUE(list.begin() == list.end());
}

TEST(test_clear_empty_and_reuse) {
  List<int> list;
  list.clear();
  ASSERT_TRUE(list.empty());
  ASSERT_EQUAL(list.size(), 0);

  fill(list, {1, 2});
  list.clear();
  list.push_back(5);
  check(list, {5});
  ASSERT_EQUAL(list.front(), 5);
  ASSERT_EQUAL(list.back(), 5);
}

TEST(test_reuse_after_empty) {
  List<int> list;
  list.push_back(1);
  list.pop_front();
  ASSERT_TRUE(list.empty());
  list.push_back(2);
  ASSERT_FALSE(list.empty());
  ASSERT_EQUAL(list.size(), 1);
}

TEST(test_front_back_single_element) {
  List<int> a;
  a.push_back(7);
  ASSERT_EQUAL(a.front(), 7);
  ASSERT_EQUAL(a.back(), 7);

  List<int> b;
  b.push_front(8);
  ASSERT_EQUAL(b.front(), 8);
  ASSERT_EQUAL(b.back(), 8);
}

TEST(test_front_back_push_back) {
  List<int> list;
  fill(list, {1, 2, 3});
  ASSERT_EQUAL(list.front(), 1);
  ASSERT_EQUAL(list.back(), 3);
}

TEST(test_front_back_push_front) {
  List<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  ASSERT_EQUAL(list.front(), 3);
  ASSERT_EQUAL(list.back(), 1);
}

TEST(test_front_back_mixed_pushes) {
  List<int> list;
  list.push_back(2);
  list.push_front(1);
  list.push_back(3);
  list.push_front(0);
  ASSERT_EQUAL(list.front(), 0);
  ASSERT_EQUAL(list.back(), 3);
}

TEST(test_front_back_after_pops) {
  List<int> list;
  fill(list, {1, 2, 3, 4});
  list.pop_front();
  ASSERT_EQUAL(list.front(), 2);
  ASSERT_EQUAL(list.back(), 4);
  list.pop_back();
  ASSERT_EQUAL(list.front(), 2);
  ASSERT_EQUAL(list.back(), 3);
}

TEST(test_front_back_pop_to_one_element) {
  List<int> a;
  fill(a, {1, 2});
  a.pop_back();
  ASSERT_EQUAL(a.front(), 1);
  ASSERT_EQUAL(a.back(), 1);

  List<int> b;
  fill(b, {1, 2});
  b.pop_front();
  ASSERT_EQUAL(b.front(), 2);
  ASSERT_EQUAL(b.back(), 2);
}

TEST(test_front_back_reuse_after_empty) {
  List<int> list;
  list.push_back(1);
  list.pop_front();
  list.push_back(9);
  ASSERT_EQUAL(list.front(), 9);
  ASSERT_EQUAL(list.back(), 9);
}

TEST(test_front_write_through_reference) {
  List<int> list;
  fill(list, {1, 2, 3});
  list.front() = 10;
  ASSERT_EQUAL(list.front(), 10);
  ASSERT_EQUAL(list.back(), 3);
  check(list, {10, 2, 3});

  List<int> single;
  single.push_back(1);
  single.front() = 5;
  ASSERT_EQUAL(single.back(), 5);
}

TEST(test_back_write_through_reference) {
  List<int> list;
  fill(list, {1, 2, 3});
  list.back() = 30;
  ASSERT_EQUAL(list.back(), 30);
  ASSERT_EQUAL(list.front(), 1);
  check(list, {1, 2, 30});

  List<int> single;
  single.push_back(1);
  single.back() = 6;
  ASSERT_EQUAL(single.front(), 6);
}

TEST(test_push_front_order) {
  List<int> list;
  list.push_front(1);
  check(list, {1});
  list.push_front(2);
  list.push_front(3);
  check(list, {3, 2, 1});
}

TEST(test_push_back_order) {
  List<int> list;
  list.push_back(1);
  check(list, {1});
  list.push_back(2);
  list.push_back(3);
  check(list, {1, 2, 3});
}

TEST(test_push_mixed_order) {
  List<int> list;
  list.push_front(1);
  list.push_back(2);
  list.push_front(0);
  list.push_back(3);
  check(list, {0, 1, 2, 3});
}

TEST(test_pop_front_links) {
  List<int> list;
  fill(list, {1, 2, 3});
  list.pop_front();
  check(list, {2, 3});
  list.pop_front();
  check(list, {3});
  list.pop_front();
  check(list, {});
}

TEST(test_pop_back_links) {
  List<int> list;
  fill(list, {1, 2, 3});
  list.pop_back();
  check(list, {1, 2});
  list.pop_back();
  check(list, {1});
  list.pop_back();
  check(list, {});
}

TEST(test_pop_to_empty_then_push) {
  List<int> list;
  list.push_back(1);
  list.pop_front();
  ASSERT_TRUE(list.empty());
  list.push_front(2);
  check(list, {2});
  list.pop_back();
  ASSERT_TRUE(list.empty());
  list.push_back(3);
  check(list, {3});
}

TEST(test_iterator_empty_list) {
  List<int> list;
  ASSERT_TRUE(list.begin() == list.end());
  ASSERT_FALSE(list.begin() != list.end());
}

TEST(test_iterator_dereference_and_modify) {
  List<int> list;
  fill(list, {1, 2, 3});
  List<int>::Iterator it = list.begin();
  ASSERT_EQUAL(*it, 1);
  *it = 10;
  ASSERT_EQUAL(list.front(), 10);
  ++it;
  *it = 20;
  check(list, {10, 20, 3});
}

TEST(test_iterator_increment) {
  List<int> list;
  fill(list, {1, 2, 3});
  List<int>::Iterator it = list.begin();
  ASSERT_EQUAL(*(it++), 1);
  ASSERT_EQUAL(*it, 2);
  ASSERT_EQUAL(*(++it), 3);
  ++it;
  ASSERT_TRUE(it == list.end());
}

TEST(test_iterator_decrement) {
  List<int> list;
  fill(list, {1, 2, 3});
  List<int>::Iterator it = list.end();
  ASSERT_EQUAL(*(--it), 3);
  ASSERT_EQUAL(*(it--), 3);
  ASSERT_EQUAL(*it, 2);
  --it;
  ASSERT_TRUE(it == list.begin());
  ++it;
  --it;
  ASSERT_TRUE(it == list.begin());
}

TEST(test_iterator_equality) {
  List<int> list;
  fill(list, {1, 2});
  List<int>::Iterator a = list.begin();
  List<int>::Iterator b = list.begin();
  ASSERT_TRUE(a == b);
  ASSERT_FALSE(a != b);
  ++b;
  ASSERT_TRUE(a != b);
  ASSERT_FALSE(a == b);
  ++a;
  ASSERT_TRUE(a == b);
  ASSERT_TRUE(list.end() == list.end());
  ASSERT_TRUE(list.begin() != list.end());
}

TEST(test_iterator_default_constructed) {
  List<int>::Iterator d1;
  List<int>::Iterator d2;
  ASSERT_TRUE(d1 == d2);
  ASSERT_FALSE(d1 != d2);

  List<int> empty_list;
  ASSERT_TRUE(d1 != empty_list.begin());
  ASSERT_TRUE(d1 != empty_list.end());

  List<int> list;
  fill(list, {1, 2});
  ASSERT_TRUE(d1 != list.begin());
  ASSERT_TRUE(d1 != list.end());
}

TEST(test_iterator_arrow_operator) {
  List<Point> list;
  Point p1 = {1, 2};
  Point p2 = {3, 4};
  list.push_back(p1);
  list.push_back(p2);
  List<Point>::Iterator it = list.begin();
  ASSERT_EQUAL(it->x, 1);
  ASSERT_EQUAL(it->y, 2);
  it->x = 10;
  ASSERT_EQUAL(list.front().x, 10);
  ++it;
  ASSERT_EQUAL(it->x, 3);
  ASSERT_EQUAL(it->y, 4);
}

TEST(test_iterator_copy_and_assign) {
  List<int> list;
  fill(list, {1, 2, 3});
  List<int>::Iterator a = list.begin();
  List<int>::Iterator b = a;
  ASSERT_TRUE(a == b);
  ++a;
  ASSERT_EQUAL(*b, 1);
  ASSERT_TRUE(a != b);
  b = a;
  ASSERT_TRUE(a == b);
  ASSERT_EQUAL(*b, 2);
}

TEST(test_insert_at_begin) {
  List<int> list;
  fill(list, {2, 3});
  List<int>::Iterator r = list.insert(list.begin(), 1);
  ASSERT_EQUAL(*r, 1);
  ASSERT_TRUE(r == list.begin());
  check(list, {1, 2, 3});
  ASSERT_EQUAL(list.front(), 1);
}

TEST(test_insert_at_end) {
  List<int> list;
  fill(list, {1, 2});
  List<int>::Iterator r = list.insert(list.end(), 3);
  ASSERT_EQUAL(*r, 3);
  check(list, {1, 2, 3});
  ASSERT_EQUAL(list.back(), 3);
}

TEST(test_insert_in_middle) {
  List<int> list;
  fill(list, {1, 3});
  List<int>::Iterator it = list.begin();
  ++it;
  List<int>::Iterator r = list.insert(it, 2);
  ASSERT_EQUAL(*r, 2);
  check(list, {1, 2, 3});
  ++r;
  ASSERT_TRUE(r == it);
}

TEST(test_insert_into_empty_list) {
  List<int> list;
  List<int>::Iterator r = list.insert(list.end(), 5);
  ASSERT_EQUAL(*r, 5);
  check(list, {5});
  ASSERT_EQUAL(list.front(), 5);
  ASSERT_EQUAL(list.back(), 5);
  list.push_back(6);
  list.push_front(4);
  check(list, {4, 5, 6});
}

TEST(test_erase_first) {
  List<int> list;
  fill(list, {1, 2, 3});
  List<int>::Iterator r = list.erase(list.begin());
  ASSERT_EQUAL(*r, 2);
  ASSERT_TRUE(r == list.begin());
  check(list, {2, 3});
  ASSERT_EQUAL(list.front(), 2);
}

TEST(test_erase_last) {
  List<int> list;
  fill(list, {1, 2, 3});
  List<int>::Iterator it = list.end();
  --it;
  List<int>::Iterator r = list.erase(it);
  ASSERT_TRUE(r == list.end());
  check(list, {1, 2});
  ASSERT_EQUAL(list.back(), 2);
}

TEST(test_erase_middle) {
  List<int> list;
  fill(list, {1, 2, 3});
  List<int>::Iterator it = list.begin();
  ++it;
  List<int>::Iterator r = list.erase(it);
  ASSERT_EQUAL(*r, 3);
  check(list, {1, 3});
}

TEST(test_erase_only_element) {
  List<int> list;
  list.push_back(5);
  List<int>::Iterator r = list.erase(list.begin());
  ASSERT_TRUE(r == list.end());
  check(list, {});
  list.push_back(6);
  check(list, {6});
}

TEST(test_erase_all_in_loop) {
  List<int> list;
  fill(list, {1, 2, 3, 4});
  List<int>::Iterator it = list.begin();
  while (it != list.end()) {
    it = list.erase(it);
  }
  check(list, {});
  list.push_front(1);
  check(list, {1});
}

TEST(test_copy_constructor_contents) {
  List<int> a;
  fill(a, {1, 2, 3});
  List<int> b(a);
  check(b, {1, 2, 3});
  ASSERT_EQUAL(b.front(), 1);
  ASSERT_EQUAL(b.back(), 3);
  check(a, {1, 2, 3});
}

TEST(test_copy_constructor_independent) {
  List<int> a;
  fill(a, {1, 2, 3});
  List<int> b(a);
  a.push_back(4);
  a.front() = 9;
  check(a, {9, 2, 3, 4});
  check(b, {1, 2, 3});
  b.pop_back();
  check(a, {9, 2, 3, 4});
  check(b, {1, 2});
}

TEST(test_copy_constructor_empty_and_single) {
  List<int> a;
  List<int> b(a);
  check(b, {});
  b.push_back(1);
  check(b, {1});
  check(a, {});

  List<int> c;
  c.push_back(7);
  List<int> d(c);
  check(d, {7});
}

TEST(test_assignment_to_empty) {
  List<int> a;
  fill(a, {1, 2, 3});
  List<int> b;
  b = a;
  check(b, {1, 2, 3});
  check(a, {1, 2, 3});
}

TEST(test_assignment_different_sizes) {
  List<int> a;
  fill(a, {1, 2, 3});

  List<int> larger;
  fill(larger, {7, 8, 9, 10, 11});
  larger = a;
  check(larger, {1, 2, 3});

  List<int> smaller;
  smaller.push_back(4);
  smaller = a;
  check(smaller, {1, 2, 3});
}

TEST(test_assignment_independent) {
  List<int> a;
  fill(a, {1, 2, 3});
  List<int> b;
  fill(b, {9, 9});
  b = a;
  b.push_back(5);
  check(a, {1, 2, 3});
  a.pop_front();
  check(b, {1, 2, 3, 5});
  check(a, {2, 3});
}

TEST(test_assignment_empty_to_populated) {
  List<int> a;
  List<int> b;
  fill(b, {1, 2, 3});
  b = a;
  check(b, {});
  b.push_back(4);
  check(b, {4});
}

TEST(test_self_assignment) {
  List<int> a;
  fill(a, {1, 2, 3});
  List<int> &ref = a;
  a = ref;
  check(a, {1, 2, 3});
  a.push_back(4);
  check(a, {1, 2, 3, 4});
}

TEST(test_chained_assignment) {
  List<int> a;
  fill(a, {1, 2});
  List<int> b;
  List<int> c;
  c = b = a;
  check(a, {1, 2});
  check(b, {1, 2});
  check(c, {1, 2});
}

TEST(test_lifecycle_many_lists) {
  for (int i = 0; i < 50; ++i) {
    List<int> a;
    fill(a, {1, 2, 3, 4, 5});
    List<int> b(a);
    List<int> c;
    c = b;
    b.pop_front();
    c.pop_back();
    a.clear();
  }
  List<int> final_list;
  fill(final_list, {1, 2, 3});
  check(final_list, {1, 2, 3});
}

TEST_MAIN()