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

// ������40����С��k����
// ��Ŀ������n���������ҳ�������С��k��������������4��5��1��6��2��7��3��8
// ��8�����֣�����С��4��������1��2��3��4��

#include <cstdio>

#include <set>
#include <vector>
#include <iostream>
#include <functional>
#include <stdlib.h>
#include <exception>
#include <stdexcept>

using namespace std;

int Partition(int data[], int length, int start, int end);

// Random Partition
int RandomInRange(int min, int max)
{
    int random = rand() % (max - min + 1) + min;
    return random;
}

void Swap(int* num1, int* num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int Partition(int data[], int length, int start, int end)
{
    if(data == nullptr || length <= 0 || start < 0 || end >= length) {
      std::logic_error ex("Invalid Parameters");
      throw new std::exception(ex);
    }

    int index = RandomInRange(start, end);
    Swap(&data[index], &data[end]);

    int small = start - 1;
    for(index = start; index < end; ++ index)
    {
        if(data[index] < data[end])
        {
            ++ small;
            if(small != index)
                Swap(&data[index], &data[small]);
        }
    }

    ++ small;
    Swap(&data[small], &data[end]);

    return small;
}

// ====================����1====================
void GetLeastNumbers_Solution1(int* input, int n, int* output, int k)
{
    if(input == nullptr || output == nullptr || k > n || n <= 0 || k <= 0)
        return;

    int start = 0;
    int end = n - 1;
    int index = Partition(input, n, start, end);
    while(index != k - 1)
    {
        if(index > k - 1)
        {
            end = index - 1;
            index = Partition(input, n, start, end);
        }
        else
        {
            start = index + 1;
            index = Partition(input, n, start, end);
        }
    }

    for(int i = 0; i < k; ++i)
        output[i] = input[i];
}

// ====================����2====================
typedef multiset<int, std::greater<int> >            intSet;
typedef multiset<int, std::greater<int> >::iterator  setIterator;

void GetLeastNumbers_Solution2(const vector<int>& data, intSet& leastNumbers, int k)
{
    leastNumbers.clear();

    if(k < 1 || data.size() < k)
        return;

    vector<int>::const_iterator iter = data.begin();
    for(; iter != data.end(); ++ iter)
    {
        if((leastNumbers.size()) < k)
            leastNumbers.insert(*iter);

        else
        {
            setIterator iterGreatest = leastNumbers.begin();

            if(*iter < *(leastNumbers.begin()))
            {
                leastNumbers.erase(iterGreatest);
                leastNumbers.insert(*iter);
            }
        }
    }
}

int LrPartition(int *input, int b, int e, int k) {
  if (e - b == 1) {
    return k;
  } else if (e - b == 2) {
    if (input[b] > input[e-1]) {
      std::swap(input[b], input[e-1]);
    }
    return k;
  }

  int m = (b + e) / 2;
  int pivot = input[m];
  int f = b;
  int l = e - 1;
  while (l > f) {
    while (input[f] <= pivot) {
      f++;
    }
    while (input[l] > pivot) {
      l--;
    }
    if (l > f) {
      std::swap(input[l], input[f]);
    }
  }
  return l;
}

void LrGetLeastNumbers_Solution(int* input, int n, int* output, int k) {
  if (k > n || !input || !output) return;
  k--;
  int b = 0, e = n;
  int tmp_k = LrPartition(input, 0, n, k);

  while (tmp_k != k) {
    if (tmp_k > k) {
      e = tmp_k;
    } else if (tmp_k < k){
      b = tmp_k;
    }
    tmp_k = LrPartition(input, b, e, k);
  }
  for (int i = 0; i <= k; i++) {
    output[i] = input[i];
  }
}

// ====================���Դ���====================
void Test(char* testName, int* data, int n, int* expectedResult, int k)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    vector<int> vectorData;
    for(int i = 0; i < n; ++ i)
        vectorData.push_back(data[i]);

    if(expectedResult == nullptr)
        printf("The input is invalid, we don't expect any result.\n");
    else
    {
        printf("Expected result: \n");
        for(int i = 0; i < k; ++ i)
            printf("%d\t", expectedResult[i]);
        printf("\n");
    }

    printf("Result for solution1:\n");
    int* output = new int[k];
    LrGetLeastNumbers_Solution(data, n, output, k);
    if(expectedResult != nullptr)
    {
        for(int i = 0; i < k; ++ i)
            printf("%d\t", output[i]);
        printf("\n");
    }

    delete[] output;

    printf("Result for solution2:\n");
    intSet leastNumbers;
    GetLeastNumbers_Solution2(vectorData, leastNumbers, k);
    printf("The actual output numbers are:\n");
    for(setIterator iter = leastNumbers.begin(); iter != leastNumbers.end(); ++iter)
        printf("%d\t", *iter);
    printf("\n\n");
}

// kС������ĳ���
void Test1()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1, 2, 3, 4};
    Test("Test1", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k��������ĳ���
void Test2()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Test("Test2", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k��������ĳ���
void Test3()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int* expected = nullptr;
    Test("Test3", data, sizeof(data) / sizeof(int), expected, 10);
}

// k����1
void Test4()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1};
    Test("Test4", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k����0
void Test5()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int* expected = nullptr;
    Test("Test5", data, sizeof(data) / sizeof(int), expected, 0);
}

// ����������ͬ������
void Test6()
{
    int data[] = {4, 5, 1, 6, 2, 7, 2, 8};
    int expected[] = {1, 2};
    Test("Test6", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// �����ָ��
void Test7()
{
    int* expected = nullptr;
    Test("Test7", nullptr, 0, expected, 0);
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

