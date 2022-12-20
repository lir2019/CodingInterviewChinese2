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

// ������9��������ջʵ�ֶ���
// ��Ŀ��������ջʵ��һ�����С����е��������£���ʵ��������������appendTail
// ��deleteHead���ֱ�����ڶ���β����������ڶ���ͷ��ɾ�����Ĺ��ܡ�

#include <stack>
#include <exception>
#include <stdexcept>

using namespace std;

template <typename T> class CQueue
{
public:
    CQueue(void);
    ~CQueue(void);
    
    // �ڶ���ĩβ���һ�����
    void appendTail(const T& node);

    // ɾ�����е�ͷ���
    T deleteHead();

private:
    stack<T> stack1;
    stack<T> stack2;
};

template <typename T> CQueue<T>::CQueue(void)
{
}

template <typename T> CQueue<T>::~CQueue(void)
{
}

template<typename T> void CQueue<T>::appendTail(const T& element)
{
    stack1.push(element);
} 

template<typename T> T CQueue<T>::deleteHead()
{
    if(stack2.size()<= 0)
    {
        while(stack1.size()>0)
        {
            T& data = stack1.top();
            stack1.pop();
            stack2.push(data);
        }
    }

    if(stack2.size() == 0) {
        std::logic_error ex("queue is empty");
        throw new exception(ex);
    }

    T head = stack2.top();
    stack2.pop();

    return head;
}

template <typename T> class LrCQueue
{
public:
    LrCQueue() = default;
    ~LrCQueue() = default;
    
    // �ڶ���ĩβ���һ�����
    void appendTail(const T& node) {
      stack1.push(node);
    }

    // ɾ�����е�ͷ���
    T deleteHead() {
      if (stack2.empty()) {
        while (!stack1.empty()) {
          stack2.push(stack1.top());
          stack1.pop();
        }
      }
      if (stack2.empty()) {
        std::logic_error ex("queue is empty");
        throw new exception(ex);
      }
      auto e = stack2.top();
      stack2.pop();
      return e;
    }

private:
    stack<T> stack1;
    stack<T> stack2;
};

// ====================���Դ���====================
void Test(char actual, char expected)
{
    if(actual == expected)
        printf("Test passed.\n");
    else
        printf("Test failed.\n");
}

int main(int argc, char* argv[])
{
    LrCQueue<char> queue;

    queue.appendTail('a');
    queue.appendTail('b');
    queue.appendTail('c');

    char head = queue.deleteHead();
    Test(head, 'a');

    head = queue.deleteHead();
    Test(head, 'b');

    queue.appendTail('d');
    head = queue.deleteHead();
    Test(head, 'c');

    queue.appendTail('e');
    head = queue.deleteHead();
    Test(head, 'd');

    head = queue.deleteHead();
    Test(head, 'e');

    return 0;
}

