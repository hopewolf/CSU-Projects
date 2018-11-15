#include <stem.h>
#include <gtest/gtest.h>

TEST(protAlg, step1) {
    Stem ss;
    EXPECT_EQ("abc", ss.step1("abc"));
    EXPECT_EQ("def", ss.step1("\'def"));
}

// TEST(portAlg, step2) {
//     Stem ss;
//     string t = "abcsses";
//     ss.step2(t);
//     EXPECT_EQ("abcss", t);
// }
//
TEST(portAlg, myStep) {
    Stem ss;
    EXPECT_EQ("people\'s", ss.step1("\'people\'s"));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
