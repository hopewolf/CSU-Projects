#include <stem.h>
#include <gtest/gtest.h>

TEST(helperFunc, isVowel) 
{    
    Stem ss;
    for(char c = 'a'; c<= 'z'; ++c) {
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            EXPECT_TRUE(ss.isVowel(c));
        else
            EXPECT_FALSE(ss.isVowel(c));
    }
}
