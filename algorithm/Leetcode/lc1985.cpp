bool COMP(string& a, string& b) {
    if(a.size() == b.size()) {
        return a > b;
    }
    return a.size() > b.size();
}

class Solution {
public:
    string kthLargestNumber(vector<string>& a, int k) {
        sort(a.begin(), a.end(), COMP);
        return a[k - 1];
    }
};
