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

// ������57��һ������Ϊs����������
// ��Ŀ������һ����������������һ������s���������в�����������ʹ������
// �ĺ�������s������ж�����ֵĺ͵���s���������һ�Լ��ɡ�

#include <cstdio>










































bool FindNumbersWithSum(int data[], int length, int sum, 
                        int* num1, int* num2)
{
    bool found = false;
    if(length < 1 || num1 == nullptr || num2 == nullptr)
        return found;

    int ahead = length - 1;
    int behind = 0;

    while(ahead > behind)
    {
        long long curSum = data[ahead] + data[behind];

        if(curSum == sum)
        {
            *num1 = data[behind];
            *num2 = data[ahead];
            found = true;
            break;
        }
        else if(curSum > sum)
            ahead --;
        else
            behind ++;
    }

    return found;
}




























































bool LrFindNumbersWithSum(int *data, int length, int sum, int *num1, int *num2) {
  if (data == nullptr) {
    return false;
  }
  int b = 0;
  int e = length - 1;
  int tmp_sum = data[b] + data[e];
  bool found = false;
  while (true) {
    while (b < length - 1 && tmp_sum < sum) {
      b++;
      tmp_sum = data[b] + data[e];
    }
    while (e > 0 && tmp_sum > sum) {
      e--;
      tmp_sum = data[b] + data[e];
    }
    if (tmp_sum == sum) {
      found = true;
      *num1 = data[b];
      *num2 = data[e];
      break;
    }
    if (e <= b) {
      break;
    }
  }
  return found;
}

// ====================���Դ���====================
void Test(const char* testName, int data[], int length, int sum, bool expectedReturn)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);
    
    int num1, num2;
    int result = LrFindNumbersWithSum(data, length, sum, &num1, &num2);
    if(result == expectedReturn)
    {
        if(result)
        {
            if(num1 + num2 == sum)
                printf("Passed. \n");
            else
                printf("FAILED. \n");
        }
        else
            printf("Passed. \n");
    }
    else
        printf("FAILED. \n");
}





































// ���ں�Ϊs���������֣�����������λ��������м�
void Test1()
{
    int data[] = {1, 2, 4, 7, 11, 15};
    Test("Test1", data, sizeof(data) / sizeof(int), 15, true);
}

// ���ں�Ϊs���������֣�����������λ�����������
void Test2()
{
    int data[] = {1, 2, 4, 7, 11, 16};
    Test("Test2", data, sizeof(data) / sizeof(int), 17, true);
}

// �����ں�Ϊs����������
void Test3()
{
    int data[] = {1, 2, 4, 7, 11, 16};
    Test("Test3", data, sizeof(data) / sizeof(int), 10, false);
}

// ³���Բ���
void Test4()
{
    Test("Test4", nullptr, 0, 0, false);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();

    return 0;
}

