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
    int ladderLength(string s, string t, vector<string>& a) {
        queue<string> q1, q2;
        int cnt1 = 1, cnt2 = 1;
        
        us<string> se1(a.begin(), a.end());
        us<string> se2(a.begin(), a.end());
        
        us<string> forward;
        us<string> backward;
        
        if(se1.find(t) == se1.end()) { // can not transform
            return 0;
        }
        
        
        q1.push(s), q2.push(t);
        forward.insert(s), backward.insert(t);
        
        W(q1.size() > 0 || q2.size() > 0) {
            if(q1.size() > 0) {
                cnt1++;
                int size = q1.size();
                FOR(i, 0, size) {
                    string root = q1.front(); q1.pop();
                    ve<string> add;
                    for(auto& nxt : se1) {
                        if(com(root, nxt)) {
                            if(backward.find(nxt) != backward.end()) { // other direction has searched
                                return cnt1 + cnt2 - 1;
                            }
                            q1.push(nxt), forward.insert(nxt);
                            add.pb(nxt);
                        }
                    }
                                        
                    for(string& nxt : add) {
                        se1.erase(nxt);
                    }
                }
            }
            
            if(q2.size() > 0) {
                cnt2++;
                int size = q2.size();
                FOR(i, 0, size) {
                    string root = q2.front(); q2.pop();
                    ve<string> add;
                    for(auto& nxt : se2) {
                        if(com(root, nxt)) {
                            if(forward.find(nxt) != forward.end()) { // other direction has searched
                                return cnt1 + cnt2 - 1;
                            }
                            q2.push(nxt), backward.insert(nxt);
                            add.pb(nxt);
                        }
                    }
                    
                    //cout << "q2 " << root <<" " << add << endl;
                    
                    for(string& nxt : add) {
                        se2.erase(nxt);
                    }
                }
            }
        }
        return 0;
    }
    
    bool com(string& s1, const string& s2) {
        int cnt = 0;
        FOR(i, 0, s1.size()) {
            cnt += ((s1[i] != s2[i]) ? 1 : 0);
            if(cnt > 1) return false;
        }
        return cnt == 1;
    }
};
