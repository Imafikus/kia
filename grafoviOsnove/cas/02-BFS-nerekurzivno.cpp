/* Nerekurzivni BFS
Problem: Implementiraj nerekurzivnu funkciju koja vrši BFS obilazak drveta ili grafa.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
vector<vector<int>> susedi
    {{1, 2}, {3, 4}, {5}, {}, {6, 7}, {8}, {}, {}, {}};
 
void bfs(int cvor) {
  int brojCvorova = susedi.size();
  vector<bool> posecen(brojCvorova, false);
  queue<int> s;
  s.push(cvor);
  while (!s.empty()) {
    cvor = s.front();
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
  bfs(0);
  return 0;
}
