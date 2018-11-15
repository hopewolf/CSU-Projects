#include <stem.h>
#include <gtest/gtest.h>

TEST(portAlg, step1) // to disable type DISABLED_...
{
	Stem ss;
    ASSERT_EQ("",ss.step1(""));
	EXPECT_EQ("masses", ss.step1("masses"));
	EXPECT_EQ("cause", ss.step1("\'cause"));
}

TEST(portAlg, step2)
{
	Stem ss;
	string t = "exceed";
	ss.step2(t);
	EXPECT_EQ("programmers", t);
}

TEST(portAlg, step3)
{
	Stem ss;
	string t = "decry";
	ss.step2(t);
	EXPECT_EQ("exceptional", t);
}


TEST(portAlg, step4) 
{
    Stem ss;
    ASSERT_TRUE(ss.isVowel('o'));
    string test = "goateedly";
    ss.step3(test);
    EXPECT_EQ("goat", test);
    EXPECT_NE("goateedly", test);
}
