#include "the4.h"

// do not add extra libraries here

int divide_land(int X, int Y, bool** possible_plots){
    std::vector<std::vector<int>> dp(X+1, std::vector<int>(Y+1, 0));
    for(int i=1; i<=X; i++){
        for(int j=1; j<=Y; j++){
            if(possible_plots[i][j] == true){
                dp[i][j]=0;
            }
            else{
                dp[i][j] = i*j;
                for(int k=1; k<i; k++){
                    int min = dp[i-k][j] + dp[k][j];
                    if(min < dp[i][j]) dp[i][j] = min;
                }
                for(int k=1; k<j; k++){
                    int min = dp[i][j-k] + dp[i][k];
                    if(min < dp[i][j]) dp[i][j] = min;
                }
            }
        }
    }
    return dp[X][Y];
}