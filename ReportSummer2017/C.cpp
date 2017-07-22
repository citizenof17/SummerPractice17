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

double eps = 1e-7;
long long  INF = 1e9;

int n, m;

vector<vector<int>> g(n, vector<int>());
vector<vector<int>> gr(n, vector<int>());
vector<int> used(n, -1);
vector<int> fo;

bool f = true;
void dfs(int u, int p, int clr){
  used[u] = clr;

  for (int i = 0; i < g[u].size(); i++){
    if (!used[g[u][i]]){
      dfs(g[u][i], u, clr);
    }
  }

  fo.pb(u);
}

void dfs2(int u, int i, int clr){
  used[u] = clr;
  for (int i = 0; i < gr[u].size(); i++){
    if (!used[gr[u][i]]){
      dfs2(gr[u][i], u, clr);
    }
  }
}

int main() {
#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  cin >> n >> m;

  set<pair<int,int>> was;
  set<pair<int,int>> wasr;

  g = vector<vector<int>>(n, vector<int>());
  gr =  vector<vector<int>>(n, vector<int>());
  used = vector<int>(n, 0);
  fo = vector<int>();

  for (int i = 0; i < m; i++){
    int a, b;
    cin >> a >> b;

    a--, b--;

    if (a != b && !was.count(mp(a,b))){
      g[a].pb(b);
    }

    if (a != b &&  !wasr.count(mp(b,a))){
      gr[b].pb(a);
    }
  }

  for (int i = 0; i < n; i++){
    if (!used[i]){
      dfs(i, i, 1);
    }
  }
  used = vector<int>(n, 0);

  reverse(all(fo));

  int clr = 1;

  for (int i = 0; i < n; i++){
    if (!used[fo[i]]){
      dfs2(fo[i], i + 1, clr++);
    }
  }

  cout << clr - 1 << endl;

  for (int i = 0; i < n; i++){
    cout << used[i] << " ";
  }
}