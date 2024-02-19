#include <string>
#include <iostream>

using namespace std;  

const int sqn = 1e3 + 5;
int n, m;

struct node {  // 定义块状链表
  node* nxt;
  int size;
  char d[(sqn << 1) + 5];

  node() { size = 0, nxt = NULL; }

  void pb(char c) { d[size++] = c; }
}* head = NULL;

void check(node* p) {  // 判断，记得要分裂
  if (p->size >= (sqn << 1)) {
    node* q = new node;
    for (int i = sqn; i < p -> size; i++) q->pb(p->d[i]);
    p -> size = sqn, q->nxt = p -> nxt, p->nxt = q;
  }
}

void insert(char c, int k) {  // 元素插入，借助链表来理解
  node* p = head;
  int tot, cnt;
  if (k > n++) { //append to the end
    while (p->nxt != NULL) p = p->nxt;
    p -> pb(c), check(p);
    return;
  }
  for (tot = head -> size; p != NULL && tot < k; p = p->nxt, tot += p -> size);
  tot -= p -> size, cnt = k - tot - 1;
  for (int i = p->size - 1; i >= cnt; i--) p -> d[i + 1] = p->d[i];
  p -> d[cnt] = c, p -> size++;
  check(p);
}

char query(int k) {  // 查询第k字母
  node* p;
  int tot;
  for (p = head, tot = head->size; p != NULL && tot < k; p = p -> nxt, tot += p->size);
  tot -= p -> size;
  return p -> d[k - tot - 1];
}

void solve() {
  string s;
  cin >> s >> m;
  n = s.size();
  
  head = new node;
  node* cur = head;

  for (int i = 0; i < n; i++) {
    if (i % sqn == 0 && i > 0) cur -> nxt = new node, cur = cur -> nxt;
    cur -> pb(s[i]);
  }
  
  while(m--) {
    char op; int k;
    cin >> op;
    if(op == 'Q') {
      cin >> k;
      printf("%c\n", query(k));
    } else {
      char a; 
      cin >> a >> k;
      insert(a, k);
    }
  }
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

