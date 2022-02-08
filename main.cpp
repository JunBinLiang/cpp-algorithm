
#include<iostream>
#include<vector>
#include<string>
using namespace std;
using ll = long long;

//Some predefined templates
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "]";
  return out;
}



int main()
{

    return 0;
}

