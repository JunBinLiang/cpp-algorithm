#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define W while

class Solution {
public:
    int convertTime(string s, string t) {
        int a = con(s);
        int b = con(t);
        int res = 0;
        W(a + 60 <= b) {
            a += 60;
            res++;
        }
        W(a + 15 <= b) {
            a += 15;
            res++;
        }
        W(a + 5 <= b) {
            a += 5;
            res++;
        }
        W(a + 1 <= b) {
            a += 1;
            res++;
        }
        return res;
    }
    
    int con(string& s) {
        int h = (s[0] - '0') * 10 + (s[1] - '0');
        int m = (s[3] - '0') * 10 + (s[4] - '0');
        return h * 60 + m;
    }
};
