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

// ������20����ʾ��ֵ���ַ���
// ��Ŀ����ʵ��һ�����������ж��ַ����Ƿ��ʾ��ֵ������������С���������磬
// �ַ�����+100������5e2������-123������3.1416������-1E-16������ʾ��ֵ������12e����
// ��1a3.14������1.2.3������+-5������12e+5.4��������

#include <stdio.h>

bool scanUnsignedInteger(const char** str);
bool scanInteger(const char** str);

// ���ֵĸ�ʽ������A[.[B]][e|EC]����.B[e|EC]��ʾ������A��C����
// �����������������ţ�Ҳ����û�У�����B��һ���޷�������
bool isNumeric(const char* str)
{
    if(str == nullptr)
        return false;

    bool numeric = scanInteger(&str);

    // �������'.'�������������ֵ�С������
    if(*str == '.')
    {
        ++str;

        // ����һ�д�����||��ԭ��
        // 1. С������û���������֣�����.123����0.123��
        // 2. С����������û�����֣�����233.����233.0��
        // 3. ��ȻС����ǰ��ͺ�����������֣�����233.666
        numeric = scanUnsignedInteger(&str) || numeric;
    }

    // �������'e'����'E'�����������ŵ������ֵ�ָ������
    if(*str == 'e' || *str == 'E')
    {
        ++str;

        // ����һ�д�����&&��ԭ��
        // 1. ��e��Eǰ��û������ʱ�������ַ������ܱ�ʾ���֣�����.e1��e1��
        // 2. ��e��E����û������ʱ�������ַ������ܱ�ʾ���֣�����12e��12e+5.4
        numeric = numeric && scanInteger(&str);
    }

    return numeric && *str == '\0';
}

bool scanUnsignedInteger(const char** str)
{
    const char* before = *str;
    while(**str != '\0' && **str >= '0' && **str <= '9')
        ++(*str);

    // ��str�д�������0-9������ʱ������true
    return *str > before;
}

// �����ĸ�ʽ������[+|-]B��ʾ, ����BΪ�޷�������
bool scanInteger(const char** str)
{
    if(**str == '+' || **str == '-')
        ++(*str);
    return scanUnsignedInteger(str);
}

int LrNextStatus(const char *str, int now) {
  static int switch_table[4][8] = { 1, -1, -1, -1,  5, -1, -1, -1,
                                    2,  2,  2,  3,  6,  6,  6,  3,
                                    7,  7,  3, -1, -1, -1, -1, -1,
                                   -1, -1,  4,  4, -1, -1, -1, -1};
  if (now == -1) {
    return -1;
  }
  char c = str[0];
  int row = -1;
  int col = now;
  if (c == '+' || c == '-') {
    row = 0;
  } else if (c - '0' >= 0 && c - '0' <= 9) {
    row = 1;
  } else if (c == '.') {
    row = 2;
  } else if (c == 'e' || c == 'E') {
    row = 3;
  } else {
    return -1;
  }
  return switch_table[row][col];
}

bool LrisNumeric(const char* str) {
  if (str == nullptr) return false;
  int status = 0;
  while (*str != '\0') {
    status = LrNextStatus(str, status);
    str++;
  }
  if (status == 2 || status == 3 || status == 6) {
    return true;
  }
  return false;
}

// ====================���Դ���====================
void Test(const char* testName, const char* str, bool expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(LrisNumeric(str) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}


int main(int argc, char* argv[])
{
    Test("Test1", "100", true);
    Test("Test2", "123.45e+6", true);
    Test("Test3", "+500", true);
    Test("Test4", "5e2", true);
    Test("Test5", "3.1416", true);
    Test("Test6", "600.", true);
    Test("Test7", "-.123", true);
    Test("Test8", "-1E-16", true);
    Test("Test9", "1.79769313486232E+308", true);

    printf("\n\n");

    Test("Test10", "12e", false);
    Test("Test11", "1a3.14", false);
    Test("Test12", "1+23", false);
    Test("Test13", "1.2.3", false);
    Test("Test14", "+-5", false);
    Test("Test15", "12e+5.4", false);
    Test("Test16", ".", false);
    Test("Test17", ".e1", false);
    Test("Test18", "e1", false);
    Test("Test19", "+.", false);
    Test("Test20", "", false);
    Test("Test21", nullptr, false);

    return 0;
}
