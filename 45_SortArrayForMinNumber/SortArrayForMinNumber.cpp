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

// ������45���������ų���С����
// ��Ŀ������һ�����������飬����������������ƴ�������ų�һ��������ӡ��ƴ
// �ӳ���������������С��һ����������������{3, 32, 321}�����ӡ����3����
// �����ųɵ���С����321323��

#include "cstdio"
#include "string.h"
#include <string>
#include <algorithm>
#include <set>

int compare(const void* strNumber1, const void* strNumber2);

// int��������ʮ���Ʊ�ʾ���ֻ��10λ
const int g_MaxNumberLength = 10;
 
char* g_StrCombine1 = new char[g_MaxNumberLength * 2 + 1];
char* g_StrCombine2 = new char[g_MaxNumberLength * 2 + 1];
 
void PrintMinNumber(const int* numbers, int length)
{
    if(numbers == nullptr || length <= 0)
        return;
 
    char** strNumbers = (char**)(new int[length]);
    for(int i = 0; i < length; ++i)
    {
        strNumbers[i] = new char[g_MaxNumberLength + 1];
        sprintf(strNumbers[i], "%d", numbers[i]);
    }
 
    qsort(strNumbers, length, sizeof(char*), compare);
 
    for(int i = 0; i < length; ++i)
        printf("%s", strNumbers[i]);
    printf("\n");
 
    for(int i = 0; i < length; ++i)
        delete[] strNumbers[i];
    delete[] strNumbers;
}
 
// ���[strNumber1][strNumber2] > [strNumber2][strNumber1], ����ֵ����0
// ���[strNumber1][strNumber2] = [strNumber2][strNumber1], ����ֵ����0
// ���[strNumber1][strNumber2] < [strNumber2][strNumber1], ����ֵС��0
int compare(const void* strNumber1, const void* strNumber2)
{
    // [strNumber1][strNumber2]
    strcpy(g_StrCombine1, *(const char**)strNumber1);
    strcat(g_StrCombine1, *(const char**)strNumber2);
 
    // [strNumber2][strNumber1]
    strcpy(g_StrCombine2, *(const char**)strNumber2);
    strcat(g_StrCombine2, *(const char**)strNumber1);
 
    return strcmp(g_StrCombine1, g_StrCombine2);
}

std::string LrGetMin(std::set<std::string> str_set) {
  if (str_set.empty()) {
    return std::string();
  }
  std::set<std::string> str_set_bk(str_set);
  std::set<std::string> min_str_set;
  do {
    std::string min_str = *str_set.begin();
    min_str_set.insert(min_str);
    str_set.erase(min_str);
  } while (str_set.size() > 0 && str_set.begin()->front() == min_str_set.begin()->front());
  std::string total_min_str;
  for (auto each_min_str : min_str_set) {
    str_set_bk.erase(each_min_str);
    std::string tmp_min_str = each_min_str + LrGetMin(str_set_bk);
    str_set_bk.insert(each_min_str);
    if (total_min_str.empty()) {
      total_min_str = tmp_min_str;
    } else {
      total_min_str = std::min(total_min_str, tmp_min_str);
    }
  }
  return total_min_str;
  
}

void LrPrintMinNumber(int *numbers, int length) {
  std::set<std::string> str_set;
  for (int i = 0; i < length; i++) {
    if (numbers[i] <= 0) continue;
    str_set.insert(std::to_string(numbers[i]));
  }
  printf("%s\n", LrGetMin(str_set).c_str());
}

// ====================���Դ���====================
void Test(const char* testName, int* numbers, int length, const char* expectedResult)
{
    if(testName != nullptr)
        printf("%s begins:\n", testName);

    if(expectedResult != nullptr)
        printf("Expected result is: \t%s\n", expectedResult);

    printf("Actual result is: \t");
    LrPrintMinNumber(numbers, length);

    printf("\n");
}

void Test1()
{
    int numbers[] = {3, 5, 1, 4, 2};
    Test("Test1", numbers, sizeof(numbers)/sizeof(int), "12345");
}

void Test2()
{
    int numbers[] = {3, 32, 321};
    Test("Test2", numbers, sizeof(numbers)/sizeof(int), "321323");
}

void Test3()
{
    int numbers[] = {3, 323, 32123};
    Test("Test3", numbers, sizeof(numbers)/sizeof(int), "321233233");
}

void Test4()
{
    int numbers[] = {1, 11, 111};
    Test("Test4", numbers, sizeof(numbers)/sizeof(int), "111111");
}

// ������ֻ��һ������
void Test5()
{
    int numbers[] = {321};
    Test("Test5", numbers, sizeof(numbers)/sizeof(int), "321");
}

void Test6()
{
    Test("Test6", nullptr, 0, "Don't print anything.");
}


int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();

    return 0;
}

