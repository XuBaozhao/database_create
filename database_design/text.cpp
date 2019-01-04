#include<iostream>
#include<sstream>
using namespace std;
int main()
{
    string s = "321";

  stringstream ss;
  ss<<s;

  int i;
  ss>>i;
  cout<<i+1<<endl;
    return 0;
}
