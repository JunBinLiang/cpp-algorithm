#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>
using namespace std;
using ll = long long;

#define pb push_back
#define f first
#define s second

//Some predefined templates
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}


int to_int(string& s) {
  int res = 0;
  for(char c : s) {
    res = res * 10 + (c - '0');
  }
  return res;
}




int main()
{
  int nValue = 5;
  void *pVoid = &nValue;
  // can not dereference pVoid because it is a void pointer
  int *pInt = static_cast<int*>(pVoid); // cast from void* to int*
  cout << *pInt << endl; // can dereference pInt
  *pInt = 10;
  cout << nValue<<endl;
  return 0;
}

