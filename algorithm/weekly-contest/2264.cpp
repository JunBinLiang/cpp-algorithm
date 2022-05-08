class Solution {
public:
    string largestGoodInteger(string s) {
        vector<string> a;
        for(int i = 0; i < s.size(); i++) {
            if(i + 1 < s.size() && i + 2 < s.size() && s[i] == s[i + 1] && s[i] == s[i + 2]) {
                string ss = "" ;
                ss += s[i];
                ss += s[i + 1];
                ss += s[i + 2];
                a.push_back(ss);
            }
        }
        sort(a.begin(), a.end());
        if(a.size() == 0) return "";
        return a[a.size() - 1];
    }
};
