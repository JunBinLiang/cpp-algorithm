using namespace std;
using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

// Some predefined templates
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

class Solution {
public:
    int maxTrailingZeros(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        int res = 0;
        ve<ve<int>> pre1(n, ve<int>(m, 0));
        ve<ve<int>> pre2(n, ve<int>(m, 0));
        ve<ve<int>> b(n, ve<int>(m, 0));
        ve<ve<int>> c(n, ve<int>(m, 0));
        FOR(i, 0, n) {
            FOR(j, 0, m) {
                int val = a[i][j];
                int cnt1 = 0, cnt2 = 0;
                int id = i * m + j;
                W(val % 2 == 0) {
                    val /= 2;
                    cnt1++;
                }
                W(val % 5 == 0) {
                    val /= 5;
                    cnt2++;
                }
                b[i][j] = cnt1;
                c[i][j] = cnt2;
            }
        }
        for(int j = 0; j < m; j++) {
            for(int i = 0; i < n; i++) {
                pre1[i][j] += b[i][j];
                if(i > 0) pre1[i][j] += pre1[i - 1][j];
                
                pre2[i][j] += c[i][j];
                if(i > 0) pre2[i][j] += pre2[i - 1][j];
            }
        }
        FOR(i, 0, n) {
            int cnt1 = 0, cnt2 = 0;
            FOR(j, 0, m) {
                int c1 = pre1[i][j] + cnt1;
                int c2 = pre2[i][j] + cnt2;
                res = max(res, min(c1, c2));
                cnt1 += b[i][j];
                cnt2 += c[i][j];
            }
        }
        FOR(i, 0, n) {
            int cnt1 = 0, cnt2 = 0;
            for(int j = m - 1; j >= 0; j--) {
                int c1 = pre1[i][j] + cnt1;
                int c2 = pre2[i][j] + cnt2;
                res = max(res, min(c1, c2));
                cnt1 += b[i][j];
                cnt2 += c[i][j];
            }
        }
        for(int j = 0; j < m; j++) {
            for(int i = n - 1; i >= 0; i--) {
                pre1[i][j] = b[i][j];
                if(i + 1 < n) pre1[i][j] += pre1[i + 1][j];
                
                pre2[i][j] = c[i][j];
                if(i + 1 < n) pre2[i][j] += pre2[i + 1][j];
            }
        }
        
        
        
        FOR(i, 0, n) {
            int cnt1 = 0, cnt2 = 0;
            FOR(j, 0, m) {
                int c1 = pre1[i][j] + cnt1;
                int c2 = pre2[i][j] + cnt2;
                res = max(res, min(c1, c2));
                cnt1 += b[i][j];
                cnt2 += c[i][j];
            }
        }
        
        
        FOR(i, 0, n) {
            int cnt1 = 0, cnt2 = 0;
            for(int j = m - 1; j >= 0; j--) {
                int c1 = pre1[i][j] + cnt1;
                int c2 = pre2[i][j] + cnt2;
                res = max(res, min(c1, c2));
                cnt1 += b[i][j];
                cnt2 += c[i][j];
            }
        }
        
        return res;
        
        
    }
};

/*
[[534,575,625,84,20,999,35],[208,318,96,380,819,102,669]]
*/
