#include <vector>
#include <cstdlib>
#include <string>
#include "gtest/gtest.h"
#include "formatting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

auto word_generator() {
    return rc::gen::container<std::string>(
        rc::gen::inRange('a', 'z' + 1)
    );
}

auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    /std::vector<std::string> out;
    for (int n : numbers) {
        out.push_back(std::to_string(n));
    }
    return out;
}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    char program[] = "SortInts";
    char a1[] = "25";
    char a2[] = "83";
    char a3[] = "17";
    char a4[] = "24";
    char* argv[] = {program, a1, a2, a3, a4};

    int* ar_out = NULL;
    int len_out = 0;

    parse_args(5, argv, &ar_out, &len_out);

    EXPECT_EQ(len_out, 4);
    EXPECT_EQ(ar_out[0], 25);
    EXPECT_EQ(ar_out[1], 83);
    EXPECT_EQ(ar_out[2], 17);
    EXPECT_EQ(ar_out[3], 24);

    free(ar_out);
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    char program[] = "SortInts";
    char* argv[] = {program};

    int* ar_out = (int*)0x1;
    int len_out = -1;

    parse_args(1, argv, &ar_out, &len_out);

    EXPECT_EQ(len_out, 0);
    EXPECT_EQ(ar_out, nullptr);
}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              ()
) {
    std::vector<int> numbers = rc::gen::suchThat<std::vector<int>>(
        [](const std::vector<int>& v) { return !v.empty(); });

    std::vector<std::string> strs = vector_of_ints_to_vector_of_strings(numbers);
    std::vector<std::vector<char>> storage;
    std::vector<char> argv;

    storage.push_back(std::vector<char>{'S','o','r','t','I','n','t','s','\0'});
    argv.push_back(storage[0].data());

    for (const auto& s : strs) {
        storage.push_back(std::vector<char>(s.begin(), s.end()));
        storage.back().push_back('\0');
        argv.push_back(storage.back().data());
    }

    int* ar_out = NULL;
    int len_out = 0;

    parse_args((int)argv.size(), argv.data(), &ar_out, &len_out);

    RC_ASSERT(len_out == (int)numbers.size());
    for (size_t i = 0; i < numbers.size(); ++i) {
        RC_ASSERT(ar_out[i] == numbers[i]);
    }

    free(ar_out);
}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    char program[] = "SortInts";
    char* argv[] = {program};

    int* ar_out = (int*)0x1;
    int len_out = -1;

    parse_args(1, argv, &ar_out, &len_out);

    RC_ASSERT(len_out == 0);
    RC_ASSERT(ar_out == NULL);
}
