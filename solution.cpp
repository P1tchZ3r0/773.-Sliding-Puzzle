#include <cstring>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class SimplePuzzle {
  int toKey(const vector<vector<int>> &b) {
    int key = 0;
    for (auto &row : b)
      for (int val : row)
        key = key * 6 + val;
    return key;
  }

  const vector<vector<int>> MOVES = {{1, 3}, {0, 2, 4}, {1, 5},
                                     {0, 4}, {1, 3, 5}, {2, 4}};

public:
  int solve(const vector<vector<int>> &board) {
    int start = toKey(board);
    int target = 1 * 7776 + 2 * 1296 + 3 * 216 + 4 * 36 + 5 * 6 + 0;

    if (start == target)
      return 0;

    unordered_map<int, int> dist;
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    int digits[6], temp[6];

    while (!q.empty()) {
      int state = q.front();
      q.pop();
      int curDist = dist[state];

      int s = state;
      for (int i = 5; i >= 0; i--) {
        digits[i] = s % 6;
        s /= 6;
      }

      int zero = 0;
      while (digits[zero] != 0)
        zero++;

      for (int newPos : MOVES[zero]) {
        memcpy(temp, digits, sizeof(digits));
        swap(temp[zero], temp[newPos]);

        int nextState = 0;
        for (int d : temp)
          nextState = nextState * 6 + d;

        if (!dist.count(nextState)) {
          if (nextState == target)
            return curDist + 1;
          dist[nextState] = curDist + 1;
          q.push(nextState);
        }
      }
    }

    return -1;
  }
};

class Solution {
public:
  int slidingPuzzle(vector<vector<int>> &board) {
    SimplePuzzle puzzle;
    return puzzle.solve(board);
  }
};
