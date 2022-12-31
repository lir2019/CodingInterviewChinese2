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

// ������50��һ�����ַ����е�һ��ֻ����һ�ε��ַ�
// ��Ŀ�����ַ������ҳ���һ��ֻ����һ�ε��ַ���������"abaccdeff"�������
// 'b'��

#include <cstdio>
#include <string>

char FirstNotRepeatingChar(const char* pString)
{
    if(pString == nullptr)
        return '\0';

    const int tableSize = 256;
    unsigned int hashTable[tableSize];
    for(unsigned int i = 0; i < tableSize; ++i)
        hashTable[i] = 0;

    const char* pHashKey = pString;
    while(*(pHashKey) != '\0')
        hashTable[*(pHashKey++)] ++;

    pHashKey = pString;
    while(*pHashKey != '\0')
    {
        if(hashTable[*pHashKey] == 1)
            return *pHashKey;

        pHashKey++;
    }

    return '\0';
}
































































char LrFirstNotRepeatingChar(const char *pString) {
  constexpr int char_num = 256;
  if (pString == nullptr) {
    return '\0';
  }
  int *times = new int[char_num];
  for (int i = 0; i < char_num; i++) {
    times[i] = 0;
  }
  const char *p = pString;
  while(*p != '\0') {
    times[*p]++;
    p++;
  }
  p = pString;
  while(*p != '\0' && times[*p] != 1) {
    p++;
  }
  if (*p == '\0') {
    return '\0';
  }
  delete [] times;
  return *p;
}

// ====================���Դ���====================
void Test(const char* pString, char expected)
{
    if(LrFirstNotRepeatingChar(pString) == expected)
        printf("Test passed.\n");
    else
        printf("Test failed.\n");
}

int main(int argc, char* argv[])
{
    // ����������ԣ�����ֻ����һ�ε��ַ�
    Test("google", 'l');

    // ����������ԣ�������ֻ����һ�ε��ַ�
    Test("aabccdbd", '\0');

    // ����������ԣ������ַ���ֻ����һ��
    Test("abcdefg", 'a');

    // ³���Բ��ԣ�����nullptr
    Test(nullptr, '\0');

    return 0;
}

