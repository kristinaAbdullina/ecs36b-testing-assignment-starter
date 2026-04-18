#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "rapidcheck/gtest.h"
#include "sorting.h"

TEST(MinIndexOfArrayTests, SimpleMinIndexAtFrontOfArray) {
    int ar[] = {1, 5, 9, 2};
    EXPECT_EQ(min_index_of_array(ar, 4), 0);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtEndOfArray) {
    int ar[] = {7, 8, 9, 1};
    EXPECT_EQ(min_index_of_array(ar, 4), 3);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtMiddleOfArray) {
    int ar[] = {7, 2, 9, 5};
    EXPECT_EQ(min_index_of_array(ar, 4), 1);
}

TEST(MinIndexOfArrayTests, SimpleDuplicateMinimums) {
    int ar[] = {4, 1, 3, 1, 9};
    EXPECT_EQ(min_index_of_array(ar, 5), 1);

}

TEST(MinIndexOfArrayTests, SimpleArrayDoesNotChange) {
    int ar[] = {4, 2, 7, 1};
    int before[] = {4, 2, 7, 1};

    (void)min_index_of_array(ar, 4);

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(ar[i], before[i]);
    }
}


RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyFindMinIndex,
              ()) {
    std::vector<int> values = rc::gen::suchThat<std::vector<int>>(
       [](const std::vector<int>& v) { return !v.empty(); });

    int ar = (int)malloc(sizeof(int) values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        ar[i] = values[i];
    }

    int index = min_index_of_array(ar, (int)values.size());

    RC_ASSERT(index >= 0);
    RC_ASSERT(index < (int)values.size());

    for (size_t i = 0; i < values.size(); ++i) {
        RC_ASSERT(ar[index] <= ar[i]);
    }

    free(ar);
}

RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyArrayDoesNotChange,
              ()) {
    std::vector<int> values = rc::gen::suchThat<std::vector<int>>(
        [](const std::vector<int>& v) { return !v.empty(); });

    int ar = (int)malloc(sizeof(int) values.size());
    int* before = (int)malloc(sizeof(int) values.size());

    for (size_t i = 0; i < values.size(); ++i) {
        ar[i] = values[i];
        before[i] = values[i];
    }

    (void)min_index_of_array(ar, (int)values.size());

    for (size_t i = 0; i < values.size(); ++i) {
        RC_ASSERT(ar[i] == before[i]);
    }

    free(ar);
    free(before);
}
