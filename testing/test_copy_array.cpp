#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(CopyArrayTests, SimpleValuesAreSame) {
    int ar[] = {4, 8, 15, 16, 23, 42};
    int len = 6;

    int* copy = copy_array(ar, len);

    for (int i = 0; i < len; ++i) {
        EXPECT_EQ(copy[i], ar[i]);
    }

    free(copy);


}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {

        int ar[] = {1, 3, 5, 7};
        int original[] = {1, 3, 5, 7};

        int* copy = copy_array(ar, 4);

        for (int i = 0; i < 4; ++i) {
            EXPECT_EQ(ar[i], original[i]);
        }

        free(copy);

}

TEST(CopyArrayTests, SimpleCopyWasMade) {
    int ar[] = {11, 22, 33, 44};
    int len = 4;

    int* copy = copy_array(ar, len);

    EXPECT_NE(copy, ar);

    for (int i = 0; i < len; ++i) {
        EXPECT_EQ(copy[i], ar[i]);
    }

    free(copy);
}


RC_GTEST_PROP(CopyArrayTests,
              PropertyValuesAreSame,
              (const std::vector<int>& values)
) {
    int* ar = (int)malloc(sizeof(int) values.size());
    copy_vector_to_array(values, ar);

    int* copy = copy_array(ar, (int)values.size());

    RC_ASSERT(elements_in_vector_and_array_are_same(values, copy));

    free(ar);
    free(copy);

}

RC_GTEST_PROP(CopyArrayTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    int* ar = (int)malloc(sizeof(int) values.size());
    int* before = (int)malloc(sizeof(int) values.size());

    copy_vector_to_array(values, ar);
    copy_vector_to_array(values, before);

    int* copy = copy_array(ar, (int)values.size());

    for (size_t i = 0; i < values.size(); ++i) {
        RC_ASSERT(ar[i] == before[i]);
    }

    free(ar);
    free(before);
    free(copy);

}

RC_GTEST_PROP(CopyArrayTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    int* ar = (int)malloc(sizeof(int) values.size());
    copy_vector_to_array(values, ar);

    int* copy = copy_array(ar, (int)values.size());

    RC_ASSERT(copy != ar);

    for (size_t i = 0; i < values.size(); ++i) {
        RC_ASSERT(copy[i] == ar[i]);
    }

    free(ar);
    free(copy);

}



