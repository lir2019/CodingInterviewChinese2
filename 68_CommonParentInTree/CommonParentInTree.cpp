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

// 面试题68：树中两个结点的最低公共祖先
// 题目：输入两个树结点，求它们的最低公共祖先。

#include <cstdio>
#include <list>
#include <vector>























































struct TreeNode 
{
    int                       m_nValue;    
    std::vector<TreeNode*>    m_vChildren;    
};

TreeNode* CreateTreeNode(int value);
void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild);
void PrintTreeNode(const TreeNode* pNode);
void PrintTree(const TreeNode* pRoot);
void DestroyTree(TreeNode* pRoot);

TreeNode* CreateTreeNode(int value)
{
    TreeNode* pNode = new TreeNode();
    pNode->m_nValue = value;

    return pNode;
}

void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild)
{
    if(pParent != nullptr)
    {
        pParent->m_vChildren.push_back(pChild);
    }
}

void PrintTreeNode(const TreeNode* pNode)
{
    if(pNode != nullptr)
    {
        printf("value of this node is: %d.\n", pNode->m_nValue);

        printf("its children is as the following:\n");
        std::vector<TreeNode*>::const_iterator i = pNode->m_vChildren.begin();
        while(i < pNode->m_vChildren.end())
        {
            if(*i != nullptr)
                printf("%d\t", (*i)->m_nValue);
        }

        printf("\n");
    }
    else
    {
        printf("this node is nullptr.\n");
    }

    printf("\n");
}

void PrintTree(const TreeNode* pRoot)
{
    PrintTreeNode(pRoot);

    if(pRoot != nullptr)
    {
        std::vector<TreeNode*>::const_iterator i = pRoot->m_vChildren.begin();
        while(i < pRoot->m_vChildren.end())
        {
            PrintTree(*i);
            ++i;
        }
    }
}

void DestroyTree(TreeNode* pRoot)
{
    if(pRoot != nullptr)
    {
        std::vector<TreeNode*>::iterator i = pRoot->m_vChildren.begin();
        while(i < pRoot->m_vChildren.end())
        {
            DestroyTree(*i);
            ++i;
        }

        delete pRoot;
    }
}

using namespace std;

bool GetNodePath(const TreeNode* pRoot, const TreeNode* pNode, list<const TreeNode*>& path)
{
    if(pRoot == pNode)
        return true;
 
    path.push_back(pRoot);
 
    bool found = false;

    vector<TreeNode*>::const_iterator i = pRoot->m_vChildren.begin();
    while(!found && i < pRoot->m_vChildren.end())
    {
        found = GetNodePath(*i, pNode, path);
        ++i;
    }
 
    if(!found)
        path.pop_back();
 
    return found;
}

const TreeNode* GetLastCommonNode
(
    const list<const TreeNode*>& path1, 
    const list<const TreeNode*>& path2
)
{
    list<const TreeNode*>::const_iterator iterator1 = path1.begin();
    list<const TreeNode*>::const_iterator iterator2 = path2.begin();
    
    const TreeNode* pLast = nullptr;
 
    while(iterator1 != path1.end() && iterator2 != path2.end())
    {
        if(*iterator1 == *iterator2)
            pLast = *iterator1;
 
        iterator1++;
        iterator2++;
    }
 
    return pLast;
}

const TreeNode* GetLastCommonParent(const TreeNode* pRoot, const TreeNode* pNode1, const TreeNode* pNode2)
{
    if(pRoot == nullptr || pNode1 == nullptr || pNode2 == nullptr)
        return nullptr;
 
    list<const TreeNode*> path1;
    GetNodePath(pRoot, pNode1, path1);
 
    list<const TreeNode*> path2;
    GetNodePath(pRoot, pNode2, path2);
 
    return GetLastCommonNode(path1, path2);
}

















































void LrGetAncesters(const TreeNode *pNode, const TreeNode *pTarget, bool &finish, std::vector<const TreeNode *> &pAncesters) {
  if (finish) {
    return;
  }
  if (pNode == nullptr) {
    return;
  }
  if (pTarget == pNode) {
    finish = true;
    return;
  }
  pAncesters.push_back(pNode);
  for (auto child : pNode->m_vChildren) {
    LrGetAncesters(child, pTarget, finish, pAncesters);
    if (finish) {
      return;
    }
  }
  pAncesters.pop_back();
}

const TreeNode *LrGetLastCommonParent(const TreeNode* pRoot, const TreeNode* pNode1, const TreeNode* pNode2) {
  if (pRoot == nullptr || pNode1 == nullptr || pNode2 == nullptr) {
    return nullptr;
  }
  std::vector<const TreeNode *> pAnc1, pAnc2;
  bool is_finish1 = false, is_finish2 = false;
  LrGetAncesters(pRoot, pNode1, is_finish1, pAnc1);
  LrGetAncesters(pRoot, pNode2, is_finish2, pAnc2);
  const TreeNode *last_anc = nullptr;
  for (int i = 0; i < pAnc1.size() && i < pAnc2.size(); i++) {
    if (pAnc1[i] == pAnc2[i]) {
      last_anc = pAnc1[i];
    } else {
      break;
    }
  }
  return last_anc;
}


// ====================测试代码====================
void Test(const char* testName, const TreeNode* pRoot, const TreeNode* pNode1, const TreeNode* pNode2, TreeNode* pExpected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    const TreeNode* pResult = LrGetLastCommonParent(pRoot, pNode1, pNode2);

    if((pExpected == nullptr && pResult == nullptr) || 
        (pExpected != nullptr && pResult != nullptr && pResult->m_nValue == pExpected->m_nValue))
        printf("Passed.\n");
    else
        printf("Failed.\n");
}

// 形状普通的树
//              1
//            /   \
//           2     3
//       /       \
//      4         5
//     / \      / |  \
//    6   7    8  9  10
void Test1()
{
    TreeNode* pNode1 = CreateTreeNode(1);
    TreeNode* pNode2 = CreateTreeNode(2);
    TreeNode* pNode3 = CreateTreeNode(3);
    TreeNode* pNode4 = CreateTreeNode(4);
    TreeNode* pNode5 = CreateTreeNode(5);
    TreeNode* pNode6 = CreateTreeNode(6);
    TreeNode* pNode7 = CreateTreeNode(7);
    TreeNode* pNode8 = CreateTreeNode(8);
    TreeNode* pNode9 = CreateTreeNode(9);
    TreeNode* pNode10 = CreateTreeNode(10);

    ConnectTreeNodes(pNode1, pNode2);
    ConnectTreeNodes(pNode1, pNode3);

    ConnectTreeNodes(pNode2, pNode4);
    ConnectTreeNodes(pNode2, pNode5);

    ConnectTreeNodes(pNode4, pNode6);
    ConnectTreeNodes(pNode4, pNode7);

    ConnectTreeNodes(pNode5, pNode8);
    ConnectTreeNodes(pNode5, pNode9);
    ConnectTreeNodes(pNode5, pNode10);

    Test("Test1", pNode1, pNode6, pNode8, pNode2);
}

// 树退化成一个链表
//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
void Test2()
{
    TreeNode* pNode1 = CreateTreeNode(1);
    TreeNode* pNode2 = CreateTreeNode(2);
    TreeNode* pNode3 = CreateTreeNode(3);
    TreeNode* pNode4 = CreateTreeNode(4);
    TreeNode* pNode5 = CreateTreeNode(5);

    ConnectTreeNodes(pNode1, pNode2);
    ConnectTreeNodes(pNode2, pNode3);
    ConnectTreeNodes(pNode3, pNode4);
    ConnectTreeNodes(pNode4, pNode5);

    Test("Test2", pNode1, pNode5, pNode4, pNode3);
}

// 树退化成一个链表，一个结点不在树中
//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
void Test3()
{
    TreeNode* pNode1 = CreateTreeNode(1);
    TreeNode* pNode2 = CreateTreeNode(2);
    TreeNode* pNode3 = CreateTreeNode(3);
    TreeNode* pNode4 = CreateTreeNode(4);
    TreeNode* pNode5 = CreateTreeNode(5);

    ConnectTreeNodes(pNode1, pNode2);
    ConnectTreeNodes(pNode2, pNode3);
    ConnectTreeNodes(pNode3, pNode4);
    ConnectTreeNodes(pNode4, pNode5);

    TreeNode* pNode6 = CreateTreeNode(6);

    Test("Test3", pNode1, pNode5, pNode6, nullptr);
}

// 输入nullptr
void Test4()
{
    Test("Test4", nullptr, nullptr, nullptr, nullptr);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();

    return 0;
}

