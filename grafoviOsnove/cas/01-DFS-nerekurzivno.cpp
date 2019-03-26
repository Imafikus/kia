/*DFS nerekurzivno
Problem: Implementirati nerekurzivnu funkciju koja vrši DFS
oblilazak drveta ili grafa (zadatog pomocu lista suseda).
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
 
vector<vector<int>> susedi
    {{1, 2}, {3, 4}, {5}, {}, {6, 7}, {8}, {}, {}, {}};
 
void dfs(int cvor) {
  int brojCvorova = susedi.size();
  vector<bool> posecen(brojCvorova, false);
  stack<int> s;
  s.push(cvor);
  while (!s.empty()) {
    cvor = s.top();
    s.pop();
    if (!posecen[cvor]) {
      posecen[cvor] = true;
      cout << cvor << endl;
      for (int sused : susedi[cvor])
        if (!posecen[sused])
          s.push(sused);
    }
  }
}
 
 
int main() {
  dfs(0);
  return 0;
}
