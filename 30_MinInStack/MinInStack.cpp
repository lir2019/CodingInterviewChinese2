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

// ������30������min������ջ
// ��Ŀ������ջ�����ݽṹ�����ڸ�������ʵ��һ���ܹ��õ�ջ����СԪ�ص�min
// �������ڸ�ջ�У�����min��push��pop��ʱ�临�Ӷȶ���O(1)��

#include <cstdio>
#include "StackWithMin.h"
#include <stack>

template <typename T>
void Test(const char* testName, const T& stack, int expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(stack.min() == expected)
        printf("Passed.\n");
    else
        printf("Failed.\n");
}


template <typename T>
class LrStackWithMin {
public:
  LrStackWithMin() = default;
  ~LrStackWithMin() = default;
  void push(T e) {
    data_stack.push(e);
    if (min_stack.empty()) {
      min_stack.push(e);
    } else {
      min_stack.push(std::min(e, min_stack.top()));
    }
  }
  void pop() {
    data_stack.pop();
    min_stack.pop();
  }
  T min() const {
    return min_stack.top();
  }
private:
  std::stack<T> data_stack;
  std::stack<T> min_stack;
};

int main(int argc, char* argv[])
{
    LrStackWithMin<int> stack;

    stack.push(3);
    Test("Test1", stack, 3);

    stack.push(4);
    Test("Test2", stack, 3);

    stack.push(2);
    Test("Test3", stack, 2);

    stack.push(3);
    Test("Test4", stack, 2);

    stack.pop();
    Test("Test5", stack, 2);

    stack.pop();
    Test("Test6", stack, 3);

    stack.pop();
    Test("Test7", stack, 3);

    stack.push(0);
    Test("Test8", stack, 0);

    return 0;
}

