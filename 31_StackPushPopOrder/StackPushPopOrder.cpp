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

// ������31��ջ��ѹ�롢��������
// ��Ŀ�����������������У���һ�����б�ʾջ��ѹ��˳�����жϵڶ���������
// ��Ϊ��ջ�ĵ���˳�򡣼���ѹ��ջ���������־�����ȡ���������1��2��3��4��
// 5��ĳջ��ѹջ���У�����4��5��3��2��1�Ǹ�ѹջ���ж�Ӧ��һ���������У���
// 4��3��5��1��2�Ͳ������Ǹ�ѹջ���еĵ������С�

#include <cstdio>
#include <iostream>
#include <stack>

bool IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
    bool bPossible = false;

    if(pPush != nullptr && pPop != nullptr && nLength > 0)
    {
        const int* pNextPush = pPush;
        const int* pNextPop = pPop;

        std::stack<int> stackData;

        while(pNextPop - pPop < nLength)
        {
            // ������ջ��ջ��Ԫ�ز���Ҫ������Ԫ��
            // ��ѹ��һЩ������ջ
            while(stackData.empty() || stackData.top() != *pNextPop)
            {
                // ����������ֶ�ѹ�븨��ջ�ˣ��˳�ѭ��
                if(pNextPush - pPush == nLength)
                    break;

                stackData.push(*pNextPush);

                pNextPush ++;
            }

            if(stackData.top() != *pNextPop)
                break;

            stackData.pop();
            pNextPop ++;
        }

        if(stackData.empty() && pNextPop - pPop == nLength)
            bPossible = true;
    }

    return bPossible;
}

bool LrIsPopOrder(const int *pPush, const int *pPop, int nlength) {
  std::stack<int> stk;
  int i = 0;
  int k = 0;
  while (k < nlength) {
    while (i < nlength && pPush[i] != pPop[k]) {
//      std::cout << "i: " << pPush[i] << std::endl;
//      std::cout << "k: " << pPop[k] << std::endl;
      stk.push(pPush[i]);
      i++;
    }
    if (i == nlength) {
 //     std::cout << "aaa" << std::endl;
      return false;
    }
    k++;
    i++;
 //   std::cout << "sss: " << stk.top() << std::endl;
 //   std::cout << "kkk: " << pPop[k] << std::endl;
    while (!stk.empty() && k < nlength && stk.top() == pPop[k]) {
      stk.pop();
      k++;
    }
    if (stk.empty() && k == nlength) {
 //     std::cout << "bbb" << std::endl;
      return true;
    }
  }
 // std::cout << "ccc" << std::endl;
  return false;
}

// ====================���Դ���====================
void Test(const char* testName, const int* pPush, const int* pPop, int nLength, bool expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(LrIsPopOrder(pPush, pPop, nLength) == expected)
        printf("Passed.\n");
    else
        printf("failed.\n");
}

void Test1()
{
    const int nLength = 5;
    int push[nLength] = {1, 2, 3, 4, 5};
    int pop[nLength] = {4, 5, 3, 2, 1};
    
    Test("Test1", push, pop, nLength, true);
}

void Test2()
{
    const int nLength = 5;
    int push[nLength] = {1, 2, 3, 4, 5};
    int pop[nLength] = {3, 5, 4, 2, 1};
    
    Test("Test2", push, pop, nLength, true);
}

void Test3()
{
    const int nLength = 5;
    int push[nLength] = {1, 2, 3, 4, 5};
    int pop[nLength] = {4, 3, 5, 1, 2};
    
    Test("Test3", push, pop, nLength, false);
}

void Test4()
{
    const int nLength = 5;
    int push[nLength] = {1, 2, 3, 4, 5};
    int pop[nLength] = {3, 5, 4, 1, 2};
    
    Test("Test4", push, pop, nLength, false);
}

// push��pop����ֻ��һ������
void Test5()
{
    const int nLength = 1;
    int push[nLength] = {1};
    int pop[nLength] = {2};

    Test("Test5", push, pop, nLength, false);
}

void Test6()
{
    const int nLength = 1;
    int push[nLength] = {1};
    int pop[nLength] = {1};

    Test("Test6", push, pop, nLength, true);
}

void Test7()
{
    Test("Test7", nullptr, nullptr, 0, false);
}
 
int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();

    return 0;
}

