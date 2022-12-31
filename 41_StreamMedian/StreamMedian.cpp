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

// 面试题41：数据流中的中位数
// 题目：如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么
// 中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，
// 那么中位数就是所有数值排序之后中间两个数的平均值。

#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
#include <stdexcept>

using namespace std;

template<typename T> class DynamicArray
{
public:
    void Insert(T num)
    {
        if(((min.size() + max.size()) & 1) == 0)
        {
            if(max.size() > 0 && num < max[0])
            {
                max.push_back(num);
                push_heap(max.begin(), max.end(), less<T>());

                num = max[0];

                pop_heap(max.begin(), max.end(), less<T>());
                max.pop_back();
            }

            min.push_back(num);
            push_heap(min.begin(), min.end(), greater<T>());
        }
        else
        {
            if(min.size() > 0 && min[0] < num)
            {
                min.push_back(num);
                push_heap(min.begin(), min.end(), greater<T>());

                num = min[0];

                pop_heap(min.begin(), min.end(), greater<T>());
                min.pop_back();
            }

            max.push_back(num);
            push_heap(max.begin(), max.end(), less<T>());
        }
    }

    T GetMedian()
    {
        int size = min.size() + max.size();
        if(size == 0) {
            std::logic_error ex("No numbers are available");
            throw exception(ex);
        }

        T median = 0;
        if((size & 1) == 1)
            median = min[0];
        else
            median = (min[0] + max[0]) / 2;

        return median;
    }

private:
    vector<T> min;
    vector<T> max;
};








































template<typename T>
class LrDynamicArray {
public:
  void Insert(T x) {
    if (min_vec.size() == max_vec.size() && max_vec.size() == 0) {
      max_vec.push_back(x);
      return;
    }
    T median = GetMedian();
    if (x > median) {
      if (min_vec.size() >= max_vec.size()) {
        max_vec.push_back(x);
        std::push_heap(max_vec.begin(), max_vec.end(), std::greater<T>());
      } else if (min_vec.size() < max_vec.size()) {
        std::pop_heap(max_vec.begin(), max_vec.end(), std::greater<T>());
        max_vec[max_vec.size() - 1] = x;
        std::push_heap(max_vec.begin(), max_vec.end(), std::greater<T>());
        min_vec.push_back(median);
        std::push_heap(min_vec.begin(), min_vec.end(), std::less<T>());
      }
    } else {
      if (max_vec.size() >= min_vec.size()) {
        min_vec.push_back(x);
        std::push_heap(min_vec.begin(), min_vec.end(), std::less<T>());
      } else if (max_vec.size() < min_vec.size()) {
        std::pop_heap(min_vec.begin(), min_vec.end(), std::less<T>());
        min_vec[min_vec.size() - 1] = x;
        std::push_heap(min_vec.begin(), min_vec.end(), std::less<T>());
        max_vec.push_back(median);
        std::push_heap(max_vec.begin(), max_vec.end(), std::greater<T>());
      }
    }
    return;
  }
  T GetMedian() {
    if (min_vec.size() == max_vec.size()) {
      if (min_vec.size() == 0) {
        std::logic_error ex("No numbers are available");
        throw exception(ex);
      }
      return (max_vec.front() + min_vec.front()) / 2;
    } else if (min_vec.size() < max_vec.size()) {
      return max_vec.front();
    } else {
      return min_vec.front();
    }
  }
private:
  std::vector<T> min_vec;
  std::vector<T> max_vec;
};






// ====================测试代码====================
void Test(char* testName, LrDynamicArray<double>& numbers, double expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(abs(numbers.GetMedian() - expected) < 0.0000001)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

int main(int argc, char* argv[])
{
    LrDynamicArray<double> numbers;

    printf("Test1 begins: ");
    try
    {
        numbers.GetMedian();
        printf("FAILED.\n");
    }
    catch(const exception&)
    {
        printf("Passed.\n");
    }

    numbers.Insert(5);
    Test("Test2", numbers, 5);

    numbers.Insert(2);
    Test("Test3", numbers, 3.5);

    numbers.Insert(3);
    Test("Test4", numbers, 3);

    numbers.Insert(4);
    Test("Test6", numbers, 3.5);

    numbers.Insert(1);
    Test("Test5", numbers, 3);

    numbers.Insert(6);
    Test("Test7", numbers, 3.5);

    numbers.Insert(7);
    Test("Test8", numbers, 4);

    numbers.Insert(0);
    Test("Test9", numbers, 3.5);

    numbers.Insert(8);
    Test("Test10", numbers, 4);

    return 0;
}
