struct Trie {
    vector<vector<int>> tr;
    unordered_set<int> words;
    int id = 1;

    Trie() {
        vector<int> childs(26, -1);
        tr.push_back(childs);
    }
    
    void add(string& s) {
        int u = 0;
        for(int i = 0; i < s.size(); i++) {
            if(tr[u][s[i] - 'a'] == -1) {
                if(tr.size() == id) {
                    vector<int> childs(26, -1);
                    tr.push_back(childs);
                }
                tr[u][s[i] - 'a'] = id++;
            }
            u = tr[u][s[i] - 'a'];
        }
        words.insert(u);
    }
    string find(string& s) {
        int u = 0;
        string ans = "";
        for(int i = 0; i < s.size() && u != -1; i++) {
            u = tr[u][s[i] - 'a'];
            if(u != -1) {
                ans += s[i];
            }
            if(words.find(u) != words.end()) return ans;
        }
        return "";
    }
};
