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

