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

template <typename U, typename T, class Cmp>
ostream &operator<<(ostream &out, const unordered_map<U, T, Cmp> &a)
{
  out << "{";
  bool first = true;
  for (auto &p : a)
  {
    out << (first ? "" : ", ");
    out << p.first << ":" << p.second;
    first = 0;
  }
  out << "}";
  return out;
}

int dp[102][243];
bool seen[6][102];
um<int, string> f;
bool is = false;
const int SIZE = 5, INF = 1000000;
int T = 0, POS = 0;

string convert(int n) { 
    string res = "00000";
    int pos = 0;
    W(n > 0) {
        int m = n % 3;
        n /= 3;
        res[pos ++] = (char)(m + '0');
    }
    return res;
}

void init() {
    for(int i = 0; i < 102; i ++) {
        for(int state = 0; state < 243; state ++) {
            dp[i][state] = INF;
        }
    }
    memset(seen, false, sizeof(seen));
    
    if(!is) {
        is = true;
        for(int state = 0; state < 243; state ++) {
            f[state] = convert(state);         
        }
    }
}
pair<bool, int> valid(int pos, string& s, string& t) {
    int cost = 0;
    pair<bool, int> FALSE = {false, -1};
    ve<int> cover;
    for(int i = 0; i < T; i++) {
        if(s[i] == '0') { //empty
            if(seen[i + 1][pos]) { 
                return FALSE;
            }
        }
        else if(s[i] == '1') { //single open
            if(i > 0 && s[i - 1] == '1') { //maintaining
                cost += 1;
            } else {
                cost += 2;
            }
            
        } else { //double kill
            if(t[i] == '2') {
                return FALSE;
            }
            
            if(t[i] == '1') {
                if(i > 0 && s[i - 1] == '2') {
                    cost += 1;
                } else {
                    cost += 3;
                }
                cover.pb(i);
            }
            
            if(t[i] == '0') {
                if(i > 0 && s[i - 1] == '2') {
                    cost += 1;
                } else {
                    cost += 3;
                }
            }
        }
    }
    
    if(cover.size() > 0) {
        for(int i = 0; i < cover.size(); i++) {
            int j = i + 1;
            int cnt = 1;
            W(j < cover.size() && cover[j] - cover[j - 1] == 1) {
                j++;
                cnt++;
            }
            cost -= ((cnt - 1) + 2);
            i = j - 1;
        }    
    }
    
    
    return {true, cost};
} 

ve<int> STATES = {0, 3, 9, 27, 81, 243};

class Solution {
public:
    int defendSpaceCity(vector<int>& time, vector<int>& positions) {
        int res = INF;
        init();
        T = 0;
        POS = 0;
        
        for(int i = 0; i < time.size(); i++) {
            seen[time[i]][positions[i] + 1] = true;
            T = max(T, time[i]);
            POS = max(POS, positions[i] + 1);
        }

        
        dp[0][0] = 0;
        for(int pos = 1; pos <= POS; pos ++) {
            for(int curState = 0; curState < STATES[T]; curState ++) {
                int ans = INF;
                string& s = f[curState];
                for(int preState = 0; preState < STATES[T] ; preState ++) {
                    if(dp[pos - 1][preState] == INF) continue;
                    string& t = f[preState];
                    pair<bool, int> pa = valid(pos, s, t);
                    if(pa.first) {
                        ans = min(ans, pa.second + dp[pos - 1][preState]);
                    }
                }
                dp[pos][curState] = ans;
            }
        }
        
        
        for(int state = 0; state < 243; state ++) {
            res = min(res, dp[POS][state]);
        } 
        return res;
    }
};
