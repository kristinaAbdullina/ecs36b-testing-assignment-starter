#include <cstdlib>
#include <vector>
#include <algorithm>
#include "test_helpers.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"


TEST(SwapTests, SimpleSwapTwoValues) {
    int a = 6;
    int b = 7;
    swap(&a, &b);
    EXPECT_EQ(a, 7);
    EXPECT_EQ(b, 6);
}

TEST(SwapTests, SimpleSwapValuesInArray) {
    int ar[] = {1, 2, 3, 4, 5};
    swap (&ar[1], &ar[2]);
    EXPECT_EQ(ar[0], 1);
    EXPECT_EQ(ar[1], 3);
    EXPECT_EQ(ar[2], 2);
    EXPECT_EQ(ar[3], 4);
    EXPECT_EQ(ar[4], 5);
}

RC_GTEST_PROP(SwapTests,
              PropertySwapTwoValues,
              (int a_start, int b_start)
) {
    int a = a_start;
    int b = b_start;
    swap(&a, &b);
    rc_assert(a== b_start);
    rc_assert(b == a_start);
}


RC_GTEST_PROP(SwapTests,
              PropertySwapValuesInArray,
              (const std::vector<int>& values)
) {
    RC_PRE(values.size() >= 2);

    int* ar = (int)malloc(sizeof(int) values.size());
    copy_vector_to_array(values, ar);

    swap(&ar[0], &ar[1]);

    RC_ASSERT(ar[0] == values[1]);
    RC_ASSERT(ar[1] == values[0]);

    for (size_t i = 2; i < values.size(); ++i) {
        RC_ASSERT(ar[i] == values[i]);
    }

    free(ar);
}
