/*******************************************************************
Copyright(c) 2016, Harry He
All rights reserved.

Distributed under the BSD license.
(See accompanying file LICENSE.txt at
https://github.com/zhedahht/CodingInterviewChinese2/blob/master/LICENSE.txt)
*******************************************************************/

//==================================================================
// 《剑指Offer——名企面试官精讲典型编程题》代码
// 作者：何海涛
//==================================================================

// 面试题19：正则表达式匹配
// 题目：请实现一个函数用来匹配包含'.'和'*'的正则表达式。模式中的字符'.'
// 表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。在本题
// 中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"
// 和"ab*ac*a"匹配，但与"aa.a"及"ab*a"均不匹配。

#include <cstdio>
#include <cstring>

bool matchCore(const char* str, const char* pattern);

bool match(const char* str, const char* pattern)
{
    if(str == nullptr || pattern == nullptr)
        return false;

    return matchCore(str, pattern);
}

bool matchCore(const char* str, const char* pattern)
{
    if(*str == '\0' && *pattern == '\0')
        return true;

    if(*str != '\0' && *pattern == '\0')
        return false;

    if(*(pattern + 1) == '*')
    {
        if(*pattern == *str || (*pattern == '.' && *str != '\0'))
            // 进入有限状态机的下一个状态
            return matchCore(str + 1, pattern + 2)
            // 继续留在有限状态机的当前状态 
            || matchCore(str + 1, pattern)
            // 略过一个'*' 
            || matchCore(str, pattern + 2);
        else
            // 略过一个'*'
            return matchCore(str, pattern + 2);
    }

    if(*str == *pattern || (*pattern == '.' && *str != '\0'))
        return matchCore(str + 1, pattern + 1);

    return false;
}

enum class Status {
  ST0 = 0, // end
  ST1 = 1, // c
  ST2 = 2, // c*
  ST3 = 3, // .
  ST4 = 4, // .*
};

Status LrGetStatus(const char *pat) {
  if (strlen(pat) == 0) {
    return Status::ST0;
  }
  if (pat[0] != '.') {
    if ((strlen(pat) == 1) || (strlen(pat) > 1 && pat[1] != '*')) {
      return Status::ST1;
    } else {
      return Status::ST2;
    }
  } else {
    if ((strlen(pat) == 1) || (strlen(pat) > 1 && pat[1] != '*')) {
      return Status::ST3;
    } else {
      return Status::ST4;
    }
  }
  return Status::ST0;
}

bool Lrmatch(const char *str, const char *pat) {
  if (str[0] == '\0' && pat[0] == '\0') {
    return true;
  }
  switch (LrGetStatus(pat)) {
    case Status::ST0: {
        // \0
        if (strlen(str) == 0) {
          return true;
        } else {
          return false;
        }
      } break;
    case Status::ST1: {
        // c
        if (strlen(str) == 0) {
          return false;
        }
        if (str[0] == pat[0]) {
          return Lrmatch(str + 1, pat + 1);
        }
      } break;
    case Status::ST2: {
        // c*
        if (strlen(str) == 0) {
          return Lrmatch(str, pat + 2);
        }
        if (str[0] == pat[0]) {
          return Lrmatch(str + 1, pat) || Lrmatch(str, pat + 2);
        } else {
          return Lrmatch(str, pat + 2);
        }
      } break;
    case Status::ST3: {
        // .
        if (strlen(str) == 0) {
          return false;
        }
        return Lrmatch(str + 1, pat + 1);
      } break;
    case Status::ST4: {
        // .*
        if (strlen(str) == 0) {
          return Lrmatch(str, pat + 2);
        }
        return Lrmatch(str + 1, pat) || Lrmatch(str, pat + 2);
      } break;
      default: break;
  }
  return false;
}

// ====================测试代码====================
void Test(const char* testName, const char* string, const char* pattern, bool expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(Lrmatch(string, pattern) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

int main(int argc, char* argv[])
{
    Test("Test01", "", "", true);
    Test("Test02", "", ".*", true);
    Test("Test03", "", ".", false);
    Test("Test04", "", "c*", true);
    Test("Test05", "a", ".*", true);
    Test("Test06", "a", "a.", false);
    Test("Test07", "a", "", false);
    Test("Test08", "a", ".", true);
    Test("Test09", "a", "ab*", true);
    Test("Test10", "a", "ab*a", false);
    Test("Test11", "aa", "aa", true);
    Test("Test12", "aa", "a*", true);
    Test("Test13", "aa", ".*", true);
    Test("Test14", "aa", ".", false);
    Test("Test15", "ab", ".*", true);
    Test("Test16", "ab", ".*", true);
    Test("Test17", "aaa", "aa*", true);
    Test("Test18", "aaa", "aa.a", false);
    Test("Test19", "aaa", "a.a", true);
    Test("Test20", "aaa", ".a", false);
    Test("Test21", "aaa", "a*a", true);
    Test("Test22", "aaa", "ab*a", false);
    Test("Test23", "aaa", "ab*ac*a", true);
    Test("Test24", "aaa", "ab*a*c*a", true);
    Test("Test25", "aaa", ".*", true);
    Test("Test26", "aab", "c*a*b", true);
    Test("Test27", "aaca", "ab*a*c*a", true);
    Test("Test28", "aaba", "ab*a*c*a", false);
    Test("Test29", "bbbba", ".*a*a", true);
    Test("Test30", "bcbbabab", ".*a*a", false);

    return 0;
}

