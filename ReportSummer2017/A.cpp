#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <fstream>
#include <iomanip>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define all(a) a.begin(), a.end()

long long  INF = 1e9;
int n, m;

vector<vector<pair<int,int>>> g(n, vector<pair<int,int>>());
vector<int> fup(n);
vector<int> dep(n, -1);
set<int> answ;

void dfs(int u, int d, int p){
  fup[u] = dep[u] = d;

  for (int i = 0; i < g[u].size(); i++){
    int v = g[u][i].first;
    if (v == p){
      continue;
    }
    if (dep[v] >= 0){
      fup[u] = min(fup[u], dep[v]);
    }
    else{
      dfs(v, d + 1, u);
      fup[u] = min(fup[u], fup[v]);
      if (fup[v] > d){
        answ.insert( g[u][i].second);
      }
    }
  }
}

int main() {
#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  cin >> n >> m;

  g = vector<vector<pair<int,int>>>(n, vector<pair<int,int>>());
  fup = vector<int> (n);
  dep = vector<int> (n, -1);

  for (int i = 0; i < m; i++){
    int a, b;
    cin >> a >> b;
    a--, b--;
    g[a].pb(mp(b, i));
    g[b].pb(mp(a, i));
  }

  for (int i = 0; i < n; i++){
    if (dep[i] == -1){
      dfs(i, 0, i);
    }
  }
  cout << answ.size() << endl;

  for (auto it = answ.begin(); it != answ.end(); it++){
    cout << *it + 1 << " ";
  }

}