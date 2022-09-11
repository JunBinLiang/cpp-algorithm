vector<int> pre(string& pattern){
  vector<int> pre(pattern.size());
  int l=0,r=1;
  while(r < pattern.size()()){
    if(pattern[r] == pattern[l]){
      pre[r] = l + 1;
      l++;
      r++;
    }else{
      if(l == 0)r++;
      else{
            l = pre[l-1];
          }
    }
  }
  return pre;
}
