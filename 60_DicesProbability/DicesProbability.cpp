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

// ������60��n�����ӵĵ���
// ��Ŀ����n���������ڵ��ϣ��������ӳ���һ��ĵ���֮��Ϊs������n����ӡ��s
// �����п��ܵ�ֵ���ֵĸ��ʡ�

#include <cstdio>
#include <math.h>
#include <vector>








































int g_maxValue = 6;
 
// ====================����һ====================
void Probability(int number, int* pProbabilities);
void Probability(int original, int current, int sum, int* pProbabilities);

void PrintProbability_Solution1(int number)
{
    if(number < 1)
        return;
 
    int maxSum = number * g_maxValue;
    int* pProbabilities = new int[maxSum - number + 1];
    for(int i = number; i <= maxSum; ++i)
        pProbabilities[i - number] = 0;
 
    Probability(number, pProbabilities);
 
    int total = pow((double)g_maxValue, number);
    for(int i = number; i <= maxSum; ++i)
    {
        double ratio = (double)pProbabilities[i - number] / total;
        printf("%d: %e\n", i, ratio);
    }
 
    delete[] pProbabilities;
}
 
void Probability(int number, int* pProbabilities)
{
    for(int i = 1; i <= g_maxValue; ++i)
        Probability(number, number, i, pProbabilities);
}
 
void Probability(int original, int current, int sum, 
                 int* pProbabilities)
{
    if(current == 1)
    {
        pProbabilities[sum - original]++;
    }
    else
    {
        for(int i = 1; i <= g_maxValue; ++i)
        {
            Probability(original, current - 1, i + sum, pProbabilities);
        }
    }
} 

// ====================������====================
void PrintProbability_Solution2(int number)
{
    if(number < 1)
        return;

    int* pProbabilities[2];
    pProbabilities[0] = new int[g_maxValue * number + 1];
    pProbabilities[1] = new int[g_maxValue * number + 1];
    for(int i = 0; i < g_maxValue * number + 1; ++i)
    {
        pProbabilities[0][i] = 0;
        pProbabilities[1][i] = 0;
    }
 
    int flag = 0;
    for (int i = 1; i <= g_maxValue; ++i) 
        pProbabilities[flag][i] = 1; 
    
    for (int k = 2; k <= number; ++k) 
    {
        for(int i = 0; i < k; ++i)
            pProbabilities[1 - flag][i] = 0;

        for (int i = k; i <= g_maxValue * k; ++i) 
        {
            pProbabilities[1 - flag][i] = 0;
            for(int j = 1; j <= i && j <= g_maxValue; ++j) 
                pProbabilities[1 - flag][i] += pProbabilities[flag][i - j];
        }
 
        flag = 1 - flag;
    }
 
    double total = pow((double)g_maxValue, number);
    for(int i = number; i <= g_maxValue * number; ++i)
    {
        double ratio = (double)pProbabilities[flag][i] / total;
        printf("%d: %e\n", i, ratio);
    }
 
    delete[] pProbabilities[0];
    delete[] pProbabilities[1];
}























































void LrPrintProbability_Solution(int n) {
  if (n == 0) {
    return;
  }
  constexpr int number = 6;
  const int min_s = n;
  const int max_s = number * n;
  std::vector<std::vector<double>> prob_mat;
  std::vector<double> prob_vec(max_s, 0.0);
  prob_mat.resize(n, prob_vec);
  for (int i = 0; i < number; i++) {
    prob_mat[0][i] = 1.0 / number;
  }
  for (int i = 1; i < n; i++) {
    for (int j = i; j < (i + 1) * number; j++) {
      prob_mat[i][j] += j - 1 >= 0 ? prob_mat[i - 1][j - 1] / number : 0.0;
      prob_mat[i][j] += j - 2 >= 0 ? prob_mat[i - 1][j - 2] / number : 0.0;
      prob_mat[i][j] += j - 3 >= 0 ? prob_mat[i - 1][j - 3] / number : 0.0;
      prob_mat[i][j] += j - 4 >= 0 ? prob_mat[i - 1][j - 4] / number : 0.0;
      prob_mat[i][j] += j - 5 >= 0 ? prob_mat[i - 1][j - 5] / number : 0.0;
      prob_mat[i][j] += j - 6 >= 0 ? prob_mat[i - 1][j - 6] / number : 0.0;
    }
  }
  for (int i = min_s - 1; i < max_s; i++) {
    printf("%d: %e\n", i + 1, prob_mat[n - 1][i]);
  }
}

// ====================���Դ���====================
void Test(int n)
{
    printf("Test for %d begins:\n", n);
    
    printf("Test for solution1\n");
    LrPrintProbability_Solution(n);

    printf("Test for solution2\n");
    PrintProbability_Solution2(n);

    printf("\n");
}



































int main(int argc, char* argv[])
{
    Test(1);
    Test(2);
    Test(3);
    Test(4);
    
    Test(11);

    Test(0);

    return 0;
}

