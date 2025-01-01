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
/*
You are given an m x n grid where each cell can have one of three values:

0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every day, any fresh orange that is 4-directionally adjacent to a rotten orange
becomes rotten.

Return the minimum number of days that must elapse until NO cell has a fresh
orange. If this is impossible, return -1.
*/
int orangesRotting(vector<vector<int>> &grid) {
  if (grid.empty())
    return 0;
  int m = grid.size(), n = grid[0].size(), days = 0, tot = 0, cnt = 0;
  /*
Total_oranges tot - It will store total number of oranges in the grid ( Rotten +
Fresh ) Count - It cnt will store the total number of oranges rotten by us .
Total_time days - total time taken to rotten.
  */
  queue<pair<int, int>> rotten;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] != 0)
        tot++;
      if (grid[i][j] == 2)
        rotten.push({i, j}); // push the rotten orange indices into queue
    }
  }

  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};

  while (!rotten.empty()) {
    int k = rotten.size(); // number of rotten oranges currently in the queue
    cnt += k;
    while (k--) {
      int x = rotten.front().first, y = rotten.front().second;
      rotten.pop();
      for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] != 1)
          continue;
        grid[nx][ny] = 2;
        rotten.push({nx, ny});
      }
    }
    if (!rotten.empty())
      days++; // we have oranges in queue which will rot in a days time
  }

  return tot == cnt ? days : -1;
}
/*
FLOOD FILL
You are given an image represented by an m x n grid of integers image, where
image[i][j] represents the pixel value of the image. You are also given three
integers sr, sc, and color. Your task is to perform a flood fill on the image
starting from the pixel image[sr][sc].

To perform a flood fill:

Begin with the starting pixel and change its color to color.
Perform the same process for each pixel that is directly adjacent (pixels that
share a side with the original pixel, either horizontally or vertically) and
shares the same color as the starting pixel. Keep repeating this process by
checking neighboring pixels of the updated pixels and modifying their color if
it matches the original color of the starting pixel. The process stops when
there are no more adjacent pixels of the original color to update. Return the
modified image after performing the flood fill.

Example 1:

Input: image = [[1,1,1],
                [1,1,0],
                [1,0,1]], sr = 1, sc = 1, color = 2

Output:         [[2,2,2],
                 [2,2,0],
                 [2,0,1]]
*/
void dfs(int row, int col, vector<vector<int>> &ans, vector<vector<int>> &image,
         int newColor, int delRow[], int delCol[], int iniColor) {
  // color with new color
  ans[row][col] = newColor;
  int n = image.size();
  int m = image[0].size();
  // there are exactly 4 neighbours
  for (int i = 0; i < 4; i++) {
    int nrow = row + delRow[i];
    int ncol = col + delCol[i];
    // check for valid coordinate
    // then check for same initial color and unvisited pixel
    if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
        image[nrow][ncol] == iniColor && ans[nrow][ncol] != newColor) {
      dfs(nrow, ncol, ans, image, newColor, delRow, delCol, iniColor);
    }
  }
}
vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc,
                              int newColor) {
  int iniColor = image[sr][sc];
  vector<vector<int>> ans = image;
  int delRow[] = {-1, 0, +1, 0};
  int delCol[] = {0, +1, 0, -1};
  dfs(sr, sc, ans, image, newColor, delRow, delCol, iniColor);
  return ans;
}
/*
Detect cycle in undirected graph

*/
bool dfs(int node, int parent, int vis[], vector<int> adj[]) {
  vis[node] = 1;
  // visit adjacent nodes
  for (auto adjacentNode : adj[node]) {
    // unvisited adjacent node
    if (!vis[adjacentNode]) {
      if (dfs(adjacentNode, node, vis, adj) == true)
        return true;
    }
    // visited node but not a parent node
    else if (adjacentNode != parent)
      return true;
  }
  return false;
}
// Function to detect cycle in an undirected graph.
bool isCycle(int V, vector<int> adj[]) {
  int vis[V] = {0};
  // for graph with connected components
  for (int i = 0; i < V; i++) {
    if (!vis[i]) {
      if (dfs(i, -1, vis, adj) == true)
        return true;
    }
  }
  return false;
}