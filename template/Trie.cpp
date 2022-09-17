const int N = 1e6;
struct Node {
    int nxt[26];
} nodes[N];
int idx = 2;

class Trie {
public:
    Trie() {
        nodes[1] = {};
    }
    
    void insert(string word) {
        int root = 1;
        for(char c : word) {
            int nxt = c - 'a';
            if(nodes[root].nxt[nxt] == 0) {
                nodes[idx] = {};
                nodes[root].nxt[nxt] = idx;
                idx++;
            } 
            root = nodes[root].nxt[nxt];
        }
    }
        
    bool startsWith(string prefix) {
        int root = 1;
        for(char c : prefix) {
            int nxt = c - 'a';
            if(nodes[root].nxt[nxt] == 0) {
                return false;
            } 
            root = nodes[root].nxt[nxt];
        }
        return true;
    }
};
