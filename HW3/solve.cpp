#include <iostream>
#include <vector>
using namespace std;

int main(void){
    int n, m;
    cin >> n >> m;
    vector<vector<int> > profit;
    vector<vector<int> > result;
    vector<vector<int> > max;
    profit.resize(n);
    result.resize(m+1);
    max.resize(n+1);
    for(int i=0; i<=m; i++)
        result[i].resize(m+1);
    for(int i=0; i<=n; i++)
        max[i].resize(m+1);
    for(int i=0; i<n; i++){
        profit[i].resize(m+1);
        for(int j=0; j<=m; j++){
            cin >> profit[i][j];
        }
    }
    for(int i=0; i<n ;i++){
        for(int j=0; j<=m; j++){
            for(int k=0; k+j<=m; k++){
                result[j][k] = profit[i][j] + max[i][k];
                if(result[j][k] > max[i+1][k+j]) max[i+1][k+j] = result[j][k];
            }
        }
    }
    cout << max[n][m] << endl;
    return 0;
}