#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 50010, M = 210, MOD = 1e9 + 7;

int f[N][M], c[M][M];

int main()
{
    f[0][0] = 1;
    for (int i = 1; i < N; i ++ )
        for (int j = 1; j < M; j ++ )
            f[i][j] = (f[i - 1][j - 1] + (LL)(i - 1) * f[i - 1][j]) % MOD;
    for (int i = 0; i < M; i ++ )
        for (int j = 0; j <= i; j ++ )
            if (!j) c[i][j] = 1;
            else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;

    int T;
    scanf("%d", &T);
    while (T -- )
    {
        int n, a, b;
        scanf("%d%d%d", &n, &a, &b);
        printf("%lld\n", (LL)f[n - 1][a + b - 2] * c[a + b - 2][a - 1] % MOD);
    }

    return 0;
}
