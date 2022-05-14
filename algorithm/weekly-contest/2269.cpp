class Solution {
public:
    int divisorSubstrings(int n, int k) {
        int res = 0;
        string s = to_string(n);
        for(int i = 0; i < s.size(); i++) {
            if(i + k - 1 >= s.size()) break;
            int sum = 0;
            for(int j = i; j < i + k; j++) {
                sum = sum * 10 + (s[j] - '0');
            }
            if(sum != 0 && n % sum == 0) res++;
        }
        return res;
    }
};
