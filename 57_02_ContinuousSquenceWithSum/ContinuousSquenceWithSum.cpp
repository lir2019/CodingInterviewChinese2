/*******************************************************************
Copyright(c) 2016, Harry He
All rights reserved.

Distributed under the BSD license.
(See accompanying file LICENSE.txt at
https://github.com/zhedahht/CodingInterviewChinese2/blob/master/LICENSE.txt)
*******************************************************************/

//==================================================================
// ����ָOffer�����������Թپ������ͱ���⡷����
// ���ߣ��κ���
//==================================================================

// ������57��������Ϊs��������������
// ��Ŀ������һ������s����ӡ�����к�Ϊs�������������У����ٺ�������������
// ��������15������1+2+3+4+5=4+5+6=7+8=15�����Խ����ӡ��3����������1��5��
// 4��6��7��8��

#include <cstdio>























































void PrintContinuousSequence(int small, int big);

void FindContinuousSequence(int sum)
{
    if(sum < 3)
        return;

    int small = 1; 
    int big = 2;
    int middle = (1 + sum) / 2;
    int curSum = small + big;

    while(small < middle)
    {
        if(curSum == sum)
            PrintContinuousSequence(small, big);

        while(curSum > sum && small < middle)
        {
            curSum -= small;
            small ++;

            if(curSum == sum)
                PrintContinuousSequence(small, big);
        }

        big ++;
        curSum += big;
    }
}

void PrintContinuousSequence(int small, int big)
{
    for(int i = small; i <= big; ++ i)
        printf("%d ", i);

    printf("\n");
}




















































void LrFindContinuousSequence(int sum) {
  int b = 1;
  int e = 2;
  int tmp_sum = b + e;
  int max_b = sum / 2;
  int max_e = (sum + 1) / 2;
  bool change = true;
  while (change) {
    change = false;
    if (b < max_b && tmp_sum > sum) {
      tmp_sum -= b;
      b++;
      change = true;
    }
    if (e < max_e && tmp_sum < sum) {
      e++;
      tmp_sum += e;
      change = true;
    }
    if (tmp_sum == sum) {
      for (int i = b; i <= e; i++) {
        printf("%d ", i);
      }
      printf("\n");
      e++;
      tmp_sum += e;
      change = true;
    }
  }
}



// ====================���Դ���====================
void Test(const char* testName, int sum)
{
    if(testName != nullptr)
        printf("%s for %d begins: \n", testName, sum);

    LrFindContinuousSequence(sum);
}

int main(int argc, char* argv[])
{
    Test("test1", 1);
    Test("test2", 3);
    Test("test3", 4);
    Test("test4", 9);
    Test("test5", 15);
    Test("test6", 100);

    return 0;
}

