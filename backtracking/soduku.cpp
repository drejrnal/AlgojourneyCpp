//
// Created by luoxiYun on 2021/9/22.
//
/*
 * 力扣 题目36 37
 */
#include "common.h"

class soduku_series {
public:
	bool is_valid_soduku(vector<vector<char>> &board) {
		int row[10], col[10], area[10];
		memset(row, 0, sizeof(row));
		memset(col, 0, sizeof(col));
		memset(area, 0, sizeof(area));
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[0].size(); j++) {
				char c = board[i][j];
				if (c >= '0' && c <= '9') {
					int area_index = i / 3 * 3 + j / 3;
					if ((row[i] >> (c - '0')) & 1 ||
					    (col[j] >> (c - '0')) & 1 ||
					    (area[area_index] >> (c - '0')) & 1)
						return false;
					row[i] = row[i] | (1 << (c - '0'));
					col[j] = col[j] | (1 << (c - '0'));
					area[area_index] = area[area_index] | (1 << (c - '0'));
				}
			}
		}
		return true;
	}
	/*
	 * 往board中填满数字，使之满足数独
	 */
	void fill_soduku(vector<vector<char>> &board) {
		int row[10], col[10], area[10];
		memset(row, 0, sizeof(row));
		memset(col, 0, sizeof(col));
		memset(area, 0, sizeof(area));
		/*
		 * 根据初始化棋盘，确定位数组的状态
		 */
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				int area_index = i / 3 * 3 + j / 3;
				if (board[i][j] >= '0' && board[i][j] <= '9') {
					int pos = board[i][j] - '0';
					row[i] = row[i] | (1 << pos);
					col[j] = col[j] | (1 << pos);
					area[area_index] = area[area_index] | (1 << pos);
				}
			}
		}
		dfs(board, row, col, area);
	}
	bool dfs(vector<vector<char>> &board, int *row, int *col, int *area) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (board[i][j] == '.') {
					int area_index = i / 3 * 3 + j / 3;
					int k = 1;
					for (; k <= 9; k++) {
						if ((row[i] >> k) & 1 || (col[j] >> k) & 1 ||
						    (area[area_index] >> k) & 1)
							continue;
						board[i][j] = k + '0';
						row[i] = row[i] ^ (1 << k);
						col[j] = col[j] ^ (1 << k);
						area[area_index] = area[area_index] ^ (1 << k);
						if (dfs(board, row, col, area)) return true;
						board[i][j] = '.';
						row[i] = row[i] ^ (1 << k);
						col[j] = col[j] ^ (1 << k);
						area[area_index] = area[area_index] ^ (1 << k);
					}
					return false;
				}
			}
		}
		return true;
	}
};

int main() {
	soduku_series s;
	vector<vector<char>> board = {
	    {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
	    {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
	    {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
	    {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
	    {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
	    {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
	    {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
	    {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
	    {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
	s.fill_soduku(board);
	for (auto row : board) {
		for (auto col : row) cout << col << " ";
		cout << endl;
	}
	return 0;
}