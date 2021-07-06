#include <bits/stdc++.h>
using namespace std;

void displayGrid(vector<vector<int>> grid) {
	for (vector<int> v : grid) {
		for (int x : v) {
			cout << x << " ";
		}
		cout << '\n';
	}
	cout << '\n';
}

int main() {
	int n = 4;
	vector<vector<int>> solved =
	{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 0}
	};

	vector<vector<int>> grid =
	{
		{6, 7, 2, 3},
		{9, 13, 1, 14},
		{5, 8, 4, 10},
		{12, 11, 15, 0}
	};
	set <vector<vector<int>>> s;

	queue<pair<vector<vector<int>>, pair<int, int>>> q;
	q.push({grid, {3, 3}});

	while (!q.empty()) {
		vector<vector<int>> ft = q.front().first;
		pair<int, int> zeroPos = q.front().second;
		q.pop();
		if (find(s.begin(), s.end(), ft) != s.end()) {
			continue;
		}
		s.insert(ft);

		displayGrid(ft);
		if (ft[0][0] == 1)break;

		if (ft == solved) {
			cout << "SOLVED!";
			break;
		}

		int r = zeroPos.first;
		int c = zeroPos.second;

		if (r - 1 >= 0) {
			vector<vector<int>> f = ft;
			f[r][c] = f[r - 1][c];
			f[r - 1][c] = 0;
			q.push({f, {r - 1, c}});
		}
		if (r + 1 < n) {
			vector<vector<int>> f = ft;
			f[r][c] = f[r + 1][c];
			f[r + 1][c] = 0;
			q.push({f, {r + 1, c}});
		}
		if (c - 1 >= 0) {
			vector<vector<int>> f = ft;
			f[r][c] = f[r][c - 1];
			f[r][c - 1] = 0;
			q.push({f, {r, c - 1}});
		}
		if (c + 1 < n) {
			vector<vector<int>> f = ft;
			f[r][c] = f[r][c + 1];
			f[r][c + 1] = 0;
			q.push({f, {r, c + 1}});
		}

	}
	return 0;
}