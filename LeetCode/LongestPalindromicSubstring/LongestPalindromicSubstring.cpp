// LongestPalindromicSubstring.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<string>
#include <vector>

//暴力解法
//暴力算法的复杂度是 O(N^3)，而且中间有很多步骤是可以省略的，比如s[i:j]被判断是否回文，我们还要对s[i-1:j+1]判断一次，其实这时候只要比较s[i-1] == s[j+1]就可以了
class Solution1
{
public:

    bool IsPalindromicSubstring(std::string s)
    {
        int N = s.size();
        for (int i = 0, j= N-1; i < s.size() / 2; ++i, --j)
        {
            if (s[i] != s[j])
                return false;
            continue;
        }
        return true;
    }

    std::string LongestPalindromicSubstring(std::string s)
    {
        int MaxLen = 0;
        int StartIndex = 0, EndIndex = 0;
        int N = s.size();
        for(int i=0; i<N; ++i)
            for (int j = 0; j < N; ++j)
            {
                if (IsPalindromicSubstring(s.substr(i, j - i + 1)))
                {
                    if (MaxLen < (j - i + 1))
                    {
                        MaxLen = j - i + 1;
                        StartIndex = i;
                        EndIndex = j;
                    }
                }
            }

        return s.substr(StartIndex, EndIndex - StartIndex + 1);
    }
  
};



//DP解法
//DP状态方程 dp[i][j] == (s[i] == s[j]) && dp[i+1][j-1]
//重点是我们该怎么遍历呢？遍历有两种方式，从顶向下，和从底向上。这里的底和顶到底是以什么为标准呢？ 答案是长度。
//为什么这么说？因为我们的长子串结果是由短子串结果决定的，如果我们还是像暴力算法那样遍历，首先就面临一个问题，那就是从第二个DP开始，我们就拿不到现成的结果。
//比如dp[1][2]按照公式该判断 s[1]==s[2] && dp[2][1]，可dp[2][1]并不存在。所以length=2的子串的回文判断是一个特殊的情况
//还有一种遍历方法，是根据长度来遍历，因为很明显的我们知道，DP[i][j]依赖DP[i+1][j-1]的计算结果，那么根据长度来遍历，是很容易理解的，这也不存在i==j的情况

class Solution2
{
public:
    std::string LongestPalindromicSubstring(std::string s)
    {
        
        int MaxLen = 1;
        int StartIndex = 0, EndIndex = 0;
        int N = s.size();
        std::vector<std::vector<bool>> dp(N, std::vector<bool>(N, false));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (i == j)
                    dp[i][j] = true;
        for (int i = 1; i < N; ++i)
            for (int j = 0; j < i; ++j)
            {
                if ((i - j) == 1)
                {
                    dp[j][i] = s[i] == s[j];
                }
                else
                {
                    dp[j][i] = (s[j] == s[i]) && dp[j + 1][i - 1];
                    if (dp[j][i])
                    {
                        if (MaxLen < (i - j + 1))
                        {
                            MaxLen = i - j + 1;
                            StartIndex = j;
                            EndIndex = i;
                        }
                    }
                }

            }

        return s.substr(StartIndex, EndIndex - StartIndex + 1);
    }

};


//manacher algorithm


int main()
{
    Solution2 sln;
    std::string s("babad");
    std::cout << sln.LongestPalindromicSubstring(s) << std::endl;
}
