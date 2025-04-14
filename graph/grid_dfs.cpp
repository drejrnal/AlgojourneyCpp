#include "common.h"

using ll = long long;
class GridDfsSearch {
	vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

public:
	bool isBorder(vector<vector<int>>& grid, int row, int col) {
		if (row == 0 || row == grid.size() - 1 || col == 0 ||
		    col == grid[0].size() - 1)
			return true;
		else if (grid[row][col] != grid[row + dirs[0][0]][col + dirs[0][1]] ||
		         grid[row][col] != grid[row + dirs[1][0]][col + dirs[1][1]] ||
		         grid[row][col] != grid[row + dirs[2][0]][col + dirs[2][1]] ||
		         grid[row][col] != grid[row + dirs[3][0]][col + dirs[3][1]])
			return true;
		return false;
	}
	bool isOutOfGridBorder(int row, int col, int row_size, int col_size) const {
		return row < 0 || row > row_size - 1 || col < 0 || col > col_size - 1;
	}
	vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col,
	                                int color) {
		// from (row, col) to its border
		vector<vector<int>> res = grid;
		ll m = grid.size(), n = grid[0].size();
		vector<vector<bool>> visited(m, vector<bool>(n, false));
		dfs(res, grid, row, col, color, visited);
		return res;
	}
	void dfs(vector<vector<int>>& res, vector<vector<int>>& grid, int row,
	         int col, int color, vector<vector<bool>>& visited) {
		if (visited[row][col]) return;
		visited[row][col] = true;
		if (isBorder(grid, row, col)) {
			res[row][col] = color;
		}
		for (auto dir : dirs) {
			int x = row + dir[0], y = col + dir[1];
			if (isOutOfGridBorder(x, y, grid.size(), grid[0].size()) ||
			    visited[x][y])
				continue;
			if (grid[x][y] == grid[row][col]) {
				dfs(res, grid, x, y, color, visited);
			}
		}
	}
};

int main() {
	GridDfsSearch dfs_search;
	vector<vector<int>> grid = {{1, 1}, {1, 2}};
	dfs_search.colorBorder(grid, 0, 0, 3);
	for (auto row : grid) {
		for (auto col : row) cout << col << " ";
		cout << endl;
	}
	return 0;
}