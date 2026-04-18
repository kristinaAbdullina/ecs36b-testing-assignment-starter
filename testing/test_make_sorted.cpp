#include <cstdlib>
#include <vector>
#include "gtest/gtest.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"
#include "test_helpers.h"

TEST(MakeSortedTests, SimpleSortSortedArray) {
    int ar[] = {1, 2, 3, 4, 5};

    make_sorted(ar, 5);

    EXPECT_THAT(std::vector<int>(ar, ar + 5), ::testing::ElementsAre(1, 2, 3, 4, 5));
}

TEST(MakeSortedTests, SimpleSortReverseSortedArray) {
    int ar[] = {5, 4, 3, 2, 1};

    make_sorted(ar, 5);

    EXPECT_THAT(std::vector<int>(ar, ar + 5), ::testing::ElementsAre(1, 2, 3, 4, 5));
}


TEST(MakeSortedTests, SimpleSortAverageArray) {
    int ar[] = {12, 45, 10, 8, 13};

    make_sorted(ar, 5);

    EXPECT_THAT(std::vector<int>(ar, ar + 5), ::testing::ElementsAre(8, 10, 12, 13, 45));
}

TEST(MakeSortedTests, SimpleSortArrayWithDuplicates) {
    int ar[] = {5, 5, 6, 3};

    make_sorted(ar, 4);

    EXPECT_THAT(std::vector<int>(ar, ar + 4), ::testing::ElementsAre(3, 5, 5, 6));
}

RC_GTEST_PROP(MakeSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    int* ar = (int)malloc(sizeof(int) values.size());
    copy_vector_to_array(values, ar);

    make_sorted(ar, (int)values.size());

    for (size_t i = 1; i < values.size(); ++i) {
        RC_ASSERT(ar[i - 1] <= ar[i]);
    }

    free(ar);
}
