#include <bits/stdc++.h>
using namespace std;

int coinChange(vector<int>& coins, int N) {
    const int INF = INT_MAX - 1;   // avoid overflow on +1
    vector<int> dp(N + 1, INF);
    dp[0] = 0;                     // 0 coins needed for amount 0

    for (int c : coins) {          // for each coin
        for (int amt = c; amt <= N; amt++) {
            if (dp[amt - c] + 1 < dp[amt])
                dp[amt] = dp[amt - c] + 1;
        }
    }
    return dp[N] >= INF ? -1 : dp[N];
}

// Optional: reconstruct which coins were used
vector<int> getCoinsUsed(vector<int>& coins, int N) {
    const int INF = INT_MAX - 1;
    vector<int> dp(N + 1, INF), parent(N + 1, -1);
    dp[0] = 0;
    for (int c : coins)
        for (int amt = c; amt <= N; amt++)
            if (dp[amt - c] + 1 < dp[amt]) {
                dp[amt] = dp[amt - c] + 1;
                parent[amt] = c;   // coin used at this amount
            }
    vector<int> used;
    if (dp[N] >= INF) return used;
    while (N > 0) { used.push_back(parent[N]); N -= parent[N]; }
    return used;
}

int main() {
    vector<int> coins = {1, 3, 4};
    int N = 6;
    cout << "Min coins: " << coinChange(coins, N) << "\n"; // 2 (3+3)
    for (int c : getCoinsUsed(coins, N)) cout << c << " "; // 3 3
}
