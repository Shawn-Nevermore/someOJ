# Cow Cycling

## 题意
有 N 头牛骑车跑圈，每头都有能量 E，总共 D 圈，速度为 x 圈/分钟（自行选择），领头的消耗 x*x 的能量，其余的消耗 x 的能量，问跑完 D 圈最少需要多少时间？（注：只要有一头牛过线就算完成，换领跑不消耗时间）

1 <= N <= 20，
1 <= D <= 100，
1 <= E <= 100

## 分析
（1）确定状态
先考虑**最后一步**：本题的最优策略一定是前 N-1 头牛耗尽能量，由第 N 头牛撞线成功跑完 D 圈。

（2）转移方程
设 `dp[i][j][k]` 表示此时第 i 头牛领跑，已经跑了 j 圈，消耗能量 k 的状态下的最少耗时。那么 `dp[i][j][k]` 的状态可转移为：

- 第 i 头牛继续领跑：消耗一分钟，速度为 v 圈/分钟。
- 头牛更换：不消耗时间，此时已经跑过 j 圈的非头牛消耗的体力是 j;

因此得到方程： 
- `dp[i][j + v][k + v * v] = min(dp[i][j + v][k + v * v], dp[i][j][k] + 1);`
- `dp[i + 1][j][j] = min(dp[i + 1][j][j], dp[i][j][k])`

（3）初始条件，边界情况
设初始条件：`dp[1][0][0] = 0;`

## 代码
```cpp
#include<iostream>
#include<climits>
using namespace std;
int dp[32][128][128];
 
int main()
{
	int n, e, d, i, j, k, v, result = INT_MAX;
	scanf("%d%d%d", &n, &e, &d);
	for(i = 0; i <= n; ++i)
		for(j = 0; j <= d; ++j)
			for(k = 0; k <= e; ++k)
				dp[i][j][k] = INT_MAX;
				
	dp[1][0][0] = 0;
	for(i = 1; i <= n; ++i)
		for(j = 0; j < d; ++j)
			for(k = 0; k <= e; ++k)
				if(dp[i][j][k] != INT_MAX){
					for(v = 0; j+v<=d && k+v*v <= e; ++v)
						dp[i][j + v][k + v * v] = min(dp[i][j + v][k + v * v], dp[i][j][k] + 1);			
					if(i < n)
						dp[i + 1][j][j] = min(dp[i + 1][j][j], dp[i][j][k]);
				}	

	for(k = 0; k <= e; ++k)
		result = min(result, dp[n][d][k]);
	if(result >= INT_MAX){
		printf("0");
	}
	else {
		printf("%d", result);
	}		
	return 0;
}

```