class Solution {
public:
    int lastStoneWeight(vector<int>& a) {
        priority_queue<int> q;
        for(int &i : a) q.push(i);
        while(q.size() > 1) {
            int x = q.top(); q.pop();
            int y = q.top(); q.pop();
            if(x != y) {
                q.push(x - y);
            }
        }
        return (q.size() == 0) ? 0 : q.top();
    }
};
