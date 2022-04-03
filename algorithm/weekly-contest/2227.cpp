using ll = long long;
#define pb push_back
#define f first
#define se second
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define W while
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define um unordered_map
#define us unordered_set

class Encrypter {
public:
    map<char, string> f;
    ve<string> dic;
    Encrypter(vector<char>& keys, vector<string>& values, vector<string>& dictionary) {
        this -> dic = dictionary;
        int n = keys.size();
        FOR(i, 0, n) {
            f[keys[i]] = values[i];
        }
    }
    
    string encrypt(string s) {
        string res = "";
        FOR(i, 0, s.size()) {
            res += f[s[i]];
        }
        return res;
    }
    
    int decrypt(string word) {
        int res = 0;
        for(string& s : dic) {
            if(is(s, word)) {
                res++;
            }
        }
        return res;
    }
    
    bool is(string& s, string t) {
        int j = 0;
        FOR(i, 0, s.size()) {
            if(f.find(s[i]) == f.end())return false;
            string &match = f[s[i]];
            for(int k = 0; k < match.size(); k++) {
                if(j >= t.size())return false;
                if(match[k] == t[j]) {
                    j++;
                } else {
                    return false;
                }
            }
        }
        return j >= t.size();
    }
};

/**
 * Your Encrypter object will be instantiated and called as such:
 * Encrypter* obj = new Encrypter(keys, values, dictionary);
 * string param_1 = obj->encrypt(word1);
 * int param_2 = obj->decrypt(word2);
 */
