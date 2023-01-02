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

// 面试题65：不用加减乘除做加法
// 题目：写一个函数，求两个整数之和，要求在函数体内不得使用＋、－、×、÷
// 四则运算符号。

#include <cstdio>

int Add(int num1, int num2)
{
    int sum, carry;
    do
    {
        sum = num1 ^ num2;
        carry = (num1 & num2) << 1;

        num1 = sum;
        num2 = carry;
    }
    while(num2 != 0);

    return num1;
}



















































int LrAdd(int num1, int num2) {
  constexpr int width = sizeof(int) * 8;
  int res = 0;
  bool flag = false;
  for (int i = 0; i < width; i++) {
    int mask = (int)1 << i;
    int num1_bit = num1 & mask;
    int num2_bit = num2 & mask;
    int count = 0;
    if (flag) count++;
    if (num1_bit) count++;
    if (num2_bit) count++;
    if (count == 3) {
      res = res | mask;
      flag = true;
    } else if (count == 2) {
      flag = true;
    } else if (count == 1) {
      res = res | mask;
      flag = false;
    } else if (count == 0) {
      flag = false;
    }
  }
  return res;
}

// ====================测试代码====================
void Test(int num1, int num2, int expected)
{
    int result = LrAdd(num1, num2);
    if(result == expected)
        printf("%d + %d is %d. Passed\n", num1, num2, result);
    else
        printf("%d + %d is %d. FAILED\n", num1, num2, result);
}

int main(int argc, char* argv[])
{
    Test(1, 2, 3);
    Test(111, 899, 1010);

    Test(-1, 2, 1);
    Test(1, -2, -1);

    Test(3, 0, 3);
    Test(0, -4, -4);

    Test(-2, -8, -10);

    return 0;
}

