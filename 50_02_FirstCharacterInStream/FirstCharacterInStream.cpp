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

// ������50���������ַ����е�һ��ֻ����һ�ε��ַ�
// ��Ŀ����ʵ��һ�����������ҳ��ַ����е�һ��ֻ����һ�ε��ַ������磬����
// �ַ�����ֻ����ǰ�����ַ�"go"ʱ����һ��ֻ����һ�ε��ַ���'g'�����Ӹ���
// �����ж���ǰ�����ַ�"google"ʱ����һ��ֻ����һ�ε��ַ���'l'��

#include <cstdio>
#include <vector>
#include <limits>
#include <map>

using namespace std;

class CharStatistics
{
public:
    CharStatistics() : index(0)
    {
        for(int i = 0; i < 256; ++i)
            occurrence[i] = -1;
    }

    void Insert(char ch)
    {
        if(occurrence[ch] == -1)
            occurrence[ch] = index;
        else if(occurrence[ch] >= 0)
            occurrence[ch] = -2;

        index++;
    }

    char FirstAppearingOnce()
    {
        char ch = '\0';
        int minIndex = numeric_limits<int>::max();
        for(int i = 0; i < 256; ++i)
        {
            if(occurrence[i] >= 0 && occurrence[i] < minIndex)
            {
                ch = (char) i;
                minIndex = occurrence[i];
            }
        }

        return ch;
    }

private:
    // occurrence[i]: A character with ASCII value i;
    // occurrence[i] = -1: The character has not found;
    // occurrence[i] = -2: The character has been found for mutlple times
    // occurrence[i] >= 0: The character has been found only once
    int occurrence[256];
    int index;
};



























































class LrCharStatistics {
public:
  char FirstAppearingOnce() {
    int ret = '\0';
    int pos = std::numeric_limits<int>::max();
    for (auto char_pos : char_pos_map) {
      if (char_pos.second < pos) {
        pos = char_pos.second;
        ret = char_pos.first;
      }
    }
    return ret;
  }
  void Insert(char c) {
    times[c]++;
    cur_idx++;
    if (times[c] == 1) {
      char_pos_map.insert(std::make_pair(int(c), cur_idx));
    } else if (times[c] == 2) {
      char_pos_map.erase(int(c));
    }
  }
private:
  static constexpr int char_num = 256;
  int cur_idx = -1;
  std::vector<int> times = std::vector<int>(char_num, 0);
  std::map<int, int> char_pos_map;
};



// ====================���Դ���====================
template <typename T>
void Test(const char* testName, T chars, char expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(chars.FirstAppearingOnce() == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

int main(int argc, char* argv[])
{
    LrCharStatistics chars;

    Test("Test1", chars, '\0');

    chars.Insert('g');
    Test("Test2", chars, 'g');

    chars.Insert('o');
    Test("Test3", chars, 'g');

    chars.Insert('o');
    Test("Test4", chars, 'g');

    chars.Insert('g');
    Test("Test5", chars, '\0');

    chars.Insert('l');
    Test("Test6", chars, 'l');

    chars.Insert('e');
    Test("Test7", chars, 'l');

    return 0;
}

