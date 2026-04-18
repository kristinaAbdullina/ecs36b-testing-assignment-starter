#include <cstdlib>
#include "gtest/gtest.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(GetSortedTests, SimpleSortSortedArray) {
    int ar[] = {1, 2, 3, 4, 5};

    int* sorted = get_sorted(ar, 5);

    EXPECT_THAT(std::vector<int>(sorted, sorted + 5), ::testing::ElementsAre(1, 2, 3, 4, 5));

    free(sorted);


}

TEST(GetSortedTests, SimpleSortReverseSortedArray) {
    int ar[] = {5, 4, 3, 2, 1};

    int* sorted = get_sorted(ar, 5);

    EXPECT_THAT(std::vector<int>(sorted, sorted + 5), ::testing::ElementsAre(1, 2, 3, 4, 5));

    free(sorted);
}

TEST(GetSortedTests, SimpleSortAverageArray) {
    int ar[] = {12, 45, 10, 8, 13};

    int* sorted = get_sorted(ar, 5);

    EXPECT_THAT(std::vector<int>(sorted, sorted + 5), ::testing::ElementsAre(8, 10, 12, 13, 45));

    free(sorted);


}

TEST(GetSortedTests, SimpleSortArrayWithDuplicates) {
    int ar[] = {5, 5, 6, 3};

    int* sorted = get_sorted(ar, 4);

    EXPECT_THAT(std::vector<int>(sorted, sorted + 4), ::testing::ElementsAre(3, 5, 5, 6));

    free(sorted);
}

TEST(GetSortedTests, SimpleOriginalDoesNotChange) {
    int ar[] = {12, 45, 10, 8, 13};
    int before[] = {12, 45, 10, 8, 13};

    int* sorted = get_sorted(ar, 5);

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(ar[i], before[i]);
    }

    free(sorted);


}

TEST(GetSortedTests, SimpleCopyWasMade) {
    int ar[] = {3, 1, 2};

    int* sorted = get_sorted(ar, 3);

    EXPECT_NE(sorted, ar);
    EXPECT_THAT(std::vector<int>(sorted, sorted + 3), ::testing::ElementsAre(1, 2, 3));

    free(sorted);


}


RC_GTEST_PROP(GetSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    int* ar = (int)malloc(sizeof(int) values.size());
    copy_vector_to_array(values, ar);

    int* sorted = get_sorted(ar, (int)values.size());

    for (size_t i = 1; i < values.size(); ++i) {
        RC_ASSERT(sorted[i - 1] <= sorted[i]);
    }

    free(ar);
    free(sorted);

}

RC_GTEST_PROP(GetSortedTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    int* ar = (int)malloc(sizeof(int) values.size());
    int* before = (int)malloc(sizeof(int) values.size());

    copy_vector_to_array(values, ar);
    copy_vector_to_array(values, before);

    int* sorted = get_sorted(ar, (int)values.size());

    for (size_t i = 0; i < values.size(); ++i) {
        RC_ASSERT(ar[i] == before[i]);
    }

    free(ar);
    free(before);
    free(sorted);
}

RC_GTEST_PROP(GetSortedTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    int* ar = (int)malloc(sizeof(int) values.size());
    copy_vector_to_array(values, ar);

    int* sorted = get_sorted(ar, (int)values.size());

    RC_ASSERT(sorted != ar);

    for (size_t i = 1; i < values.size(); ++i) {
        RC_ASSERT(sorted[i - 1] <= sorted[i]);
    }

    free(ar);
    free(sorted);

}











