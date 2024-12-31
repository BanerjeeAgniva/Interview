#include <queue>
#include <vector>
using namespace std;

vector<int> bfsOfGraph(vector<vector<int>> &adj) {
  queue<int> q;
  int n = adj.size();
  q.push(0);
  vector<int> bfs;
  vector<int> visited(n, 0);
  visited[0] = 1;
  bfs.push_back(0);
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    for (int neighbour : adj[node]) { // visit all connected neighbours
      if (!visited[neighbour]) {
        bfs.push_back(neighbour);
        visited[neighbour] = 1;
        q.push(neighbour);
      }
    }
  }
  return bfs;
}

void dfs(vector<vector<int>> &adj, vector<int> &visited, int ele) {
  visited[ele] = 1;
  for (int i = 0; i < adj.size(); i++)
    if (adj[ele][i] == 1 && visited[i] == -1)
      dfs(adj, visited, i);
}

int numProvinces(
    vector<vector<int>> adj,
    int V) { // number of connected components --> number of provinces
  vector<int> visited(V, -1);
  int ans = 0;
  for (int row = 0; row < V; row++) {
    for (int col = 0; col < V; col++) {
      if (adj[row][col] == 1 && visited[row] == -1) {
        dfs(adj, visited, col);
        ans++;
      }
    }
  }
  return ans;
}