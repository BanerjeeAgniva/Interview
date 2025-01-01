#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
bool dfs(int node, int parent, vector<int> &vis, vector<int> adj[]) {
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
bool isCycle(int V, vector<int> adj[]) {
  vector<int> vis(V, 0);
  // for graph with connected components
  for (int i = 0; i < V; i++) {
    if (!vis[i]) {
      if (dfs(i, -1, vis, adj) == true)
        return true;
    }
  }
  return false;
}
//-----
// Cycle in directed graph
// check picture
// after returning to node 3, when we go to node 7 then we do dfs on 7, then if
// we check 5 we see its visited but has it been visited on the same PATH? NO so
// its not a cycle
//-------
bool dfsCheck(int node, vector<vector<int>> &adj, vector<int> &vis,
              vector<int> &pathVis) {
  vis[node] = 1;
  pathVis[node] = 1;
  // traverse for adjacent nodes
  for (auto it : adj[node]) {
    // when the node is not visited
    if (!vis[it]) {
      if (dfsCheck(it, adj, vis, pathVis) == true)
        return true;
    }
    // if the node has been previously visited
    // but it has to be visited on the same path  <------- MAIN CONCEPT
    else if (pathVis[it]) {
      return true;
    }
  }

  pathVis[node] = 0;
  return false;
}

// Function to detect cycle in a directed graph.
bool isCyclic(int V, vector<vector<int>> adj) {
  vector<int> vis(V, 0);
  vector<int> pathVis(V, 0);

  for (int i = 0; i < V; i++) {
    if (!vis[i]) {
      if (dfsCheck(i, adj, vis, pathVis) == true)
        return true;
    }
  }
  return false;
}
/*
Given an m x n binary matrix mat, return the distance of the nearest 0 for each
cell. The distance between two cells sharing a common edge is 1.

Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]
*/
vector<vector<int>> nearest(vector<vector<int>> grid) {
  int n = grid.size();
  int m = grid[0].size();
  // visited and distance matrix
  vector<vector<int>> vis(n, vector<int>(m, 0));
  vector<vector<int>> dist(n, vector<int>(m, 0));
  // <coordinates, steps>
  queue<pair<pair<int, int>, int>> q;
  // traverse the matrix
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      // start BFS if cell contains 1
      if (grid[i][j] == 1) {
        q.push({{i, j}, 0});
        vis[i][j] = 1;
      }
    }
  }

  int delrow[] = {-1, 0, +1, 0};
  int delcol[] = {0, +1, 0, -1};

  // traverse till queue becomes empty
  while (!q.empty()) {
    int row = q.front().first.first;
    int col = q.front().first.second;
    int steps = q.front().second;
    q.pop();
    dist[row][col] = steps;
    // for all 4 neighbours
    for (int i = 0; i < 4; i++) {
      int nrow = row + delrow[i];
      int ncol = col + delcol[i];
      // check for valid unvisited cell
      if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
          vis[nrow][ncol] == 0) {
        vis[nrow][ncol] = 1;
        q.push({{nrow, ncol}, steps + 1});
      }
    }
  }
  // return distance matrix
  return dist;
}
/*
You are given an m x n matrix board containing letters 'X' and 'O', capture
regions that are surrounded:

Connect: A cell is connected to adjacent cells horizontally or vertically.
Region: To form a region connect every 'O' cell.
Surround: The region is surrounded with 'X' cells if you can connect the region
with 'X' cells and none of the region cells are on the edge of the board. To
capture a surrounded region, replace all 'O's with 'X's in-place within the
original board. You do not need to return anything.
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'O', 'X', 'X'},
        {'X', 'X', 'O', 'O'}
        becomes
        {'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X'},
        {'X', 'X', 'O', 'O'}
-----------------------------------
If border element is O then it will not turn into X
Consequentially any ) connected to a border 0 will not turn into X
Other all Os will turn into X
Logic ---> dfs on border O elements
-----------------------------------
Number of enclaves --> number of Os covered by Xs answer will be 4
Similar logic
*/
void dfs(int row, int col, vector<vector<int>> &vis, vector<vector<char>> &mat,
         int delrow[], int delcol[]) {
  vis[row][col] = 1;
  int n = mat.size();
  int m = mat[0].size();
  // check for top, right, bottom, left
  for (int i = 0; i < 4; i++) {
    int nrow = row + delrow[i];
    int ncol = col + delcol[i];
    // check for valid coordinates and unvisited Os
    if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && !vis[nrow][ncol] &&
        mat[nrow][ncol] == 'O') {
      dfs(nrow, ncol, vis, mat, delrow, delcol);
    }
  }
}
vector<vector<char>> fill(int n, int m, vector<vector<char>> mat) {
  int delrow[] = {-1, 0, +1, 0};
  int delcol[] = {0, 1, 0, -1};
  vector<vector<int>> vis(n, vector<int>(m, 0));
  // traverse first row and last row
  for (int j = 0; j < m; j++) {
    // check for unvisited Os in the boundary rows
    // first row
    if (!vis[0][j] && mat[0][j] == 'O') {
      dfs(0, j, vis, mat, delrow, delcol);
    }

    // last row
    if (!vis[n - 1][j] && mat[n - 1][j] == 'O') {
      dfs(n - 1, j, vis, mat, delrow, delcol);
    }
  }

  for (int i = 0; i < n; i++) {
    // check for unvisited Os in the boundary columns
    // first column
    if (!vis[i][0] && mat[i][0] == 'O') {
      dfs(i, 0, vis, mat, delrow, delcol);
    }

    // last column
    if (!vis[i][m - 1] && mat[i][m - 1] == 'O') {
      dfs(i, m - 1, vis, mat, delrow, delcol);
    }
  }

  // if unvisited O then convert to X
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!vis[i][j] && mat[i][j] == 'O')
        mat[i][j] = 'X';
    }
  }

  return mat;
}

/*
WORD LADDER
Given two distinct words startWord and targetWord, and a list denoting wordList
of unique words of equal lengths. Find the length of the shortest transformation
sequence from startWord to targetWord. Keep the following conditions in mind:

A word can only consist of lowercase characters.
Only one letter can be changed in each transformation.
Each transformed word must exist in the wordList including the targetWord.
startWord may or may not be part of the wordList

Input:
wordList = {"des","der","dfr","dgt","dfs"}
startWord = "der", targetWord = "dfs"
Output:
3
Explanation:
The length of the smallest transformation sequence from "der" to
"dfs" is 3 i.e. "der" -> (replace ‘e’ by ‘f’) -> "dfr" -> (replace ‘r’ by ‘s’)
-> "dfs". So, it takes 3 different strings for us to reach the targetWord. Each
of these strings are present in the wordList.
*/

int wordLadderLength(string startWord, string targetWord,
                     vector<string> &wordList) {
  //{word,transitions to reach ‘word’}.
  queue<pair<string, int>> q;
  q.push({startWord, 1});
  unordered_set<string> st(wordList.begin(), wordList.end());
  st.erase(startWord);
  while (!q.empty()) {
    string word = q.front().first;
    int steps = q.front().second;
    q.pop();
    //-----------------------------------
    if (word == targetWord)
      return steps;
    //-----------------------------------
    for (int i = 0; i < word.size(); i++) {
      // Now, replace each character of ‘word’ with char
      // from a-z then check if ‘word’ exists in wordList.
      char original = word[i];
      for (char ch = 'a'; ch <= 'z'; ch++) {
        word[i] = ch;
        // check if it exists in the set and push it in the queue.
        if (st.count(word)) {
          st.erase(word);
          q.push({word, steps + 1});
        }
      }
      word[i] = original; // backtrack
    }
  }
  return 0;
}

/*
G-30 : Word Ladder-II
Given two distinct words startWord and targetWord, and a list denoting wordList
of unique words of equal lengths. Find all shortest transformation sequence(s)
from startWord to targetWord. You can return them in any order possible. Example
1: Input: startWord = "der", targetWord = "dfs", wordList =
{"des","der","dfr","dgt","dfs"} Output: [ [ “der”, “dfr”, “dfs” ], [ “der”,
“des”, “dfs”] ] Explanation: The length of the smallest transformation sequence
here is 3. Following are the only two shortest ways to get to the targetWord
from the startWord : "der" -> ( replace ‘r’ by ‘s’ ) -> "des" -> ( replace ‘e’
by ‘f’ ) -> "dfs". "der" -> ( replace ‘e’ by ‘f’ ) -> "dfr" -> ( replace ‘r’ by
‘s’ ) -> "dfs".
*/

vector<vector<string>> findSequences(string beginWord, string endWord,
                                     vector<string> &wordList) {
  unordered_set<string> st(wordList.begin(), wordList.end());
  // Creating a queue ds which stores the words in a sequence which is
  // required to reach the targetWord after successive transformations.
  queue<vector<string>> q;
  // BFS traversal with pushing the new formed sequence in queue
  // when after a transformation, a word is found in wordList.
  q.push({beginWord});
  // A vector defined to store the words being currently used
  // on a level during BFS.
  vector<string> usedOnLevel;
  usedOnLevel.push_back(beginWord);
  int level = 0;
  vector<vector<string>> ans;
  while (!q.empty()) {
    vector<string> vec = q.front();
    q.pop();

    // Now, erase all words that have been
    // used in the previous levels to transform
    if (vec.size() > level) {
      level++;
      for (auto it : usedOnLevel) {
        st.erase(it);
      }
    }

    string word = vec.back();

    // store the answers if the end word matches with targetWord.
    if (word == endWord) {
      // the first sequence where we reached end
      if (ans.size() == 0) {
        ans.push_back(vec);
      } else if (ans[0].size() ==
                 vec.size()) // we want shortest transformation sequences only
      {
        ans.push_back(vec);
      }
    }
    for (int i = 0; i < word.size(); i++) {
      // Now, replace each character of ‘word’ with char
      // from a-z then check if ‘word’ exists in wordList.
      char original = word[i];
      for (char c = 'a'; c <= 'z'; c++) {
        word[i] = c;
        if (st.count(word)) {
          // Check if the word is present in the wordList and
          // push the word along with the new sequence in the queue.
          vec.push_back(word);
          q.push(vec);
          // mark as visited on the level
          usedOnLevel.push_back(word);
          vec.pop_back(); // backtrack
        }
      }
      word[i] = original; // backtrack
    }
  }
  return ans;
}

// A comparator function to sort the answer.
bool comp(vector<string> a, vector<string> b) {
  string x = "", y = "";
  for (string i : a)
    x += i;
  for (string i : b)
    y += i;

  return x < y; // you would want x to be lexicographically smaller than y
}
//-----
// Is graph bipartite?
//------
bool dfs(int node, int col, int color[], vector<int> adj[]) {
  color[node] = col;

  // traverse adjacent nodes
  for (auto it : adj[node]) {
    // if uncoloured
    if (color[it] == -1) {
      if (dfs(it, !col, color, adj) ==
          false) // colour neighbours of node with opposite colour
        return false;
    }
    // if previously coloured and have the same colour
    else if (color[it] == col) {
      return false;
    }
  }

  return true;
}

bool isBipartite(int V, vector<int> adj[]) {
  int color[V];
  for (int i = 0; i < V; i++)
    color[i] = -1;

  // for connected components
  for (int i = 0; i < V; i++) {
    if (color[i] == -1) {
      if (dfs(i, 0, color, adj) == false) // colour ith index with 0
        return false;
    }
  }
  return true;
}

//------
// TOPO SORT
// An ordering in Directed Acyclic Graph where
// x y z
// node x will come before node y and node y will come before node z
/*

        5       4
        | \   / |
        |  v v  |
        |   0   |
        |  ^ ^  |
        v /   \ v
        2       1
         \
          v
           3

5 --> 0
5 --> 2
4 --> 0
4 --> 1
2 --> 3
3 --> 1

Output: 5, 4, 2, 3, 1, 0
5 appears before 0
5 appears before 2
.
.
3 appears before 1
*/
void dfs(int node, vector<int> vis, stack<int> &st, vector<vector<int>> adj) {
  vis[node] = 1;
  for (auto it : adj[node]) // This process will ultimately lead to nodes
                            // getting pushed to stack
    if (!vis[it])
      dfs(it, vis, st, adj);

  st.push(node); // which have the least number of outward edges from them
                 // so the most dependant node (node on which other nodes will
                 // depend on) will be at the bottom of the stack
}
vector<int> topoSort(int V, vector<vector<int>> adj) {
  vector<int> vis(V, 0);
  stack<int> st;
  for (int i = 0; i < V; i++)
    if (!vis[i])
      dfs(i, vis, st, adj);

  vector<int> ans;
  while (!st.empty()) {
    ans.push_back(st.top());
    st.pop();
  }
  return ans;
}
