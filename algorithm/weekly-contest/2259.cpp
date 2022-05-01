class Solution {
public:
    string removeDigit(string s, char digit) {
        vector<string> a;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == digit) {
                string t = "";
                for(int j = 0; j < s.size(); j++) {
                    if(i != j) t += s[j];
                }
                a.push_back(t);
            }
        }
        sort(a.begin(), a.end());
        return a[a.size() - 1];
    }
};
