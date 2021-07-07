#include <bits/stdc++.h>
using namespace std;

void diagnostics(vector<pair<vector<vector<int>>, pair<int, int>>>);
void displayGrid(vector<vector<int>>);

int main() {
	int n = 4;

	// Change starting grid here!
	vector<vector<int>> grid =
	{
		{1, 3, 12, 4},
		{14, 5, 9, 7},
		{13, 2, 0, 8},
		{11, 6, 10, 15}
	};
	set <vector<vector<int>>> s;
	pair<int, int> zeroPosition;
	for (int i = 0 ; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if ( grid[i][j] == 0) {
				zeroPosition.first = i;
				zeroPosition.second = j;
				break;
			}
		}
	}
	vector<pair<vector<vector<int>>, pair<int, int>>> finalPath;
	queue<vector<pair<vector<vector<int>>, pair<int, int>>>> q;
	q.push({{grid, zeroPosition}});
	unordered_map<int, pair<int, int>> m;

	m[1] = {0, 0};
	m[2] = {0, 1};
	m[3] = {1, 2};
	m[4] = {0, 2};
	m[5] = {1, 0};
	m[6] = {1, 1};
	m[7] = {2, 2};
	m[8] = {1, 2};
	m[9] = {2, 1};
	m[10] = {2, 2};
	m[11] = {2, 2};
	m[12] = {2, 3};
	m[13] = {2, 0};
	m[14] = {2, 1};
	m[15] = {3, 2};

	bool three, seven, nine, ten;
	three = seven = nine = ten = false;
	int aimNum = 0;
	vector<int> order = {1, 2, 4, 3, 5, 13, 9, 6, 8, 7, 14, 10, 11, 12, 15};
	unordered_set<int> fixed;
	while (!q.empty()) {
		vector<pair<vector<vector<int>>, pair<int, int>>> fullPath = q.front();
		vector<vector<int>> ft = fullPath[fullPath.size() - 1].first;
		pair<int, int> zeroPos = fullPath[fullPath.size() - 1].second;
		q.pop();
		if (find(s.begin(), s.end(), ft) != s.end()) {
			continue;
		}
		s.insert(ft);

		// displayGrid(ft);

		if (aimNum > 14) {
			cout << "SOLVED!" << endl;
			finalPath = fullPath;
			// displayGrid(ft);
			break;
		}

		int r = zeroPos.first;
		int c = zeroPos.second;
		int elem = ft[r][c];
//____________________________________________
		if (three) {
			if (ft[0][3] == 0) {
				ft[0][2] = 3;
				ft[0][3] = 4;
				ft[1][2] = 0;
				three = false;
				fixed.insert(elem);
				aimNum++;
				queue<vector<pair<vector<vector<int>>, pair<int, int>>>> tempq;
				vector<pair<vector<vector<int>>, pair<int, int>>> newPath = fullPath;
				newPath.push_back({ft, {1, 2}});
				tempq.push(newPath);
				q = tempq;
				s.clear();
				continue;
			}
		}
		if (nine) {
			if (ft[3][0] == 0) {
				ft[3][0] = 13;
				ft[2][0] = 9;
				ft[2][1] = 0;
				nine = false;
				fixed.insert(elem);
				// cout << elem << " in correct position" << endl;
				aimNum++;
				queue<vector<pair<vector<vector<int>>, pair<int, int>>>> tempq;
				vector<pair<vector<vector<int>>, pair<int, int>>> newPath = fullPath;
				newPath.push_back({ft, {2, 1}});
				tempq.push(newPath);
				q = tempq;
				s.clear();
				continue;
			}
		}
		if (seven) {
			if (ft[1][3] == 0) {
				ft[1][3] = 8;
				ft[1][2] = 7;
				ft[2][2] = 0;
				seven = false;
				fixed.insert(elem);
				aimNum++;
				queue<vector<pair<vector<vector<int>>, pair<int, int>>>> tempq;
				vector<pair<vector<vector<int>>, pair<int, int>>> newPath = fullPath;
				newPath.push_back({ft, {2, 2}});
				tempq.push(newPath);
				q = tempq;
				s.clear();
				continue;
			}
		}
		if (ten) {
			if (ft[3][1] == 0) {
				ft[3][1] = 14;
				ft[2][1] = 10;
				ft[2][2] = 0;
				ten = false;
				fixed.insert(elem);
				aimNum++;
				queue<vector<pair<vector<vector<int>>, pair<int, int>>>> tempq;
				vector<pair<vector<vector<int>>, pair<int, int>>> newPath = fullPath;
				newPath.push_back({ft, {2, 2}});
				tempq.push(newPath);
				q = tempq;
				s.clear();
				continue;
			}
		}
//____________________________________________

		if (r - 1 >= 0 && find(fixed.begin(), fixed.end(), ft[r - 1][c]) == fixed.end()) {
			vector<vector<int>> f = ft;
			f[r][c] = f[r - 1][c];
			f[r - 1][c] = 0;
			vector<pair<vector<vector<int>>, pair<int, int>>> newPath = fullPath;
			newPath.push_back({f, {r - 1, c}});
			q.push(newPath);

			pair<int, int> comp = {r, c};
			if (elem == order[aimNum] && m[elem] == comp) {
				//looking on right side stacking
				if (order[aimNum] == 4) {
					if (f[r][c + 1] == 3 || (f[r][c + 1] == 0 && f[r + 1][c + 1] == 3)) {
						continue;
					}
				}
				else if (order[aimNum] == 3) {
					if (f[0][3] == 0) {
						f[0][2] = 3;
						f[0][3] = 4;
						f[1][2] = 0;
					}
					else {
						three = true;
						aimNum--;
					}
				}
				else if (order[aimNum] == 8) {
					if (f[r][c + 1] == 7 || (f[r][c + 1] == 0 && f[r + 1][c + 1] == 7)) {
						continue;
					}
				}
				else if (order[aimNum] == 7) {
					if (f[1][3] == 0) {
						f[1][3] = 8;
						f[1][2] = 7;
						f[2][2] = 0;
					}
					else {
						seven = true;
						aimNum--;
					}
				}
				//looking on left side stacking
				else if (order[aimNum] == 13) {
					if (f[r - 1][c] == 9 || (f[r - 1][c] == 0 && f[r - 1][c + 1] == 9)) {
						continue;
					}
				}
				else if (order[aimNum] == 9) {
					if (ft[3][0] == 0) {
						ft[3][0] = 13;
						ft[2][0] = 9;
						ft[2][1] = 0;
					}
					else {
						nine = true;
						aimNum--;
					}
				}
				else if (order[aimNum] == 14) {
					if (f[r - 1][c] == 10 || (f[r - 1][c] == 0 && f[r - 1][c + 1] == 10)) {
						continue;
					}
				}
				else if (order[aimNum] == 10) {
					if (f[3][1] == 0) {
						f[3][1] = 14;
						f[2][1] = 10;
						f[2][2] = 0;
					}
					else {
						ten = true;
						aimNum--;
					}
				}
				fixed.insert(elem);
				aimNum++;
				queue<vector<pair<vector<vector<int>>, pair<int, int>>>> tempq;
				vector<pair<vector<vector<int>>, pair<int, int>>> newPath = fullPath;
				newPath.push_back({f, {r - 1, c}});
				tempq.push(newPath);
				q = tempq;
				s.clear();
				continue;
			}
		}
		if (r + 1 < n && find(fixed.begin(), fixed.end(), ft[r + 1][c]) == fixed.end()) {
			vector<vector<int>> f = ft;
			f[r][c] = f[r + 1][c];
			f[r + 1][c] = 0;
			vector<pair<vector<vector<int>>, pair<int, int>>> newPath = fullPath;

			newPath.push_back({f, {r + 1, c}});
			q.push(newPath);
			int elem = f[r][c];
			pair<int, int> comp = {r, c};

			if (elem == order[aimNum] && m[elem] == comp) {

				//looking on right side stacking
				if (order[aimNum] == 4) {
					if (f[r][c + 1] == 3 || (f[r][c + 1] == 0 && f[r + 1][c + 1] == 3)) {
						continue;
					}
				}
				else if (order[aimNum] == 3) {
					if (f[0][3] == 0) {
						f[0][2] = 3;
						f[0][3] = 4;
						f[1][2] = 0;
					}
					else {
						three = true;
						aimNum--;
					}
				}
				else if (order[aimNum] == 8) {
					if (f[r][c + 1] == 7 || (f[r][c + 1] == 0 && f[r + 1][c + 1] == 7)) {
						continue;
					}
				}
				else if (order[aimNum] == 7) {
					if (f[1][3] == 0) {
						f[1][3] = 8;
						f[1][2] = 7;
						f[2][2] = 0;
					}
					else {
						seven = true;
						aimNum--;
					}
				}
				//looking on left side stacking
				else if (order[aimNum] == 13) {
					if (f[r - 1][c] == 9 || (f[r - 1][c] == 0 && f[r - 1][c + 1] == 9)) {
						continue;
					}
				}
				else if (order[aimNum] == 9) {
					if (ft[3][0] == 0) {
						ft[3][0] = 13;
						ft[2][0] = 9;
						ft[2][1] = 0;
					}
					else {
						nine = true;
						aimNum--;
					}
				}
				else if (order[aimNum] == 14) {
					if (f[r - 1][c] == 10 || (f[r - 1][c] == 0 && f[r - 1][c + 1] == 10)) {
						continue;
					}
				}
				else if (order[aimNum] == 10) {
					if (f[3][1] == 0) {
						f[3][1] = 14;
						f[2][1] = 10;
						f[2][2] = 0;
					}
					else {
						ten = true;
						aimNum--;
					}
				}

				fixed.insert(elem);
				aimNum++;
				queue<vector<pair<vector<vector<int>>, pair<int, int>>>> tempq;
				vector<pair<vector<vector<int>>, pair<int, int>>> newPath = fullPath;
				newPath.push_back({f, {r + 1, c}});
				tempq.push(newPath);
				q = tempq;
				s.clear();
				continue;
			}
		}
		if (c - 1 >= 0 && find(fixed.begin(), fixed.end(), ft[r][c - 1]) == fixed.end()) {
			vector<vector<int>> f = ft;
			f[r][c] = f[r][c - 1];
			f[r][c - 1] = 0;
			vector<pair<vector<vector<int>>, pair<int, int>>> newPath = fullPath;

			newPath.push_back({f, {r, c - 1}});
			q.push(newPath);
			int elem = f[r][c];
			pair<int, int> comp = {r, c};
			if (elem == order[aimNum] && m[elem] == comp) {
				//looking on right side stacking
				if (order[aimNum] == 4) {
					if (f[r][c + 1] == 3 || (f[r][c + 1] == 0 && f[r + 1][c + 1] == 3)) {
						continue;
					}
				}
				else if (order[aimNum] == 3) {
					if (f[0][3] == 0) {
						f[0][2] = 3;
						f[0][3] = 4;
						f[1][2] = 0;
					}
					else {
						three = true;
						aimNum--;
					}
				}
				else if (order[aimNum] == 8) {
					if (f[r][c + 1] == 7 || (f[r][c + 1] == 0 && f[r + 1][c + 1] == 7)) {
						continue;
					}
				}
				else if (order[aimNum] == 7) {
					if (f[1][3] == 0) {
						f[1][3] = 8;
						f[1][2] = 7;
						f[2][2] = 0;
					}
					else {
						seven = true;
						aimNum--;
					}
				}
				//looking on left side stacking
				else if (order[aimNum] == 13) {
					if (f[r - 1][c] == 9 || (f[r - 1][c] == 0 && f[r - 1][c + 1] == 9)) {
						continue;
					}
				}
				else if (order[aimNum] == 9) {
					if (ft[3][0] == 0) {
						ft[3][0] = 13;
						ft[2][0] = 9;
						ft[2][1] = 0;
					}
					else {
						nine = true;
						aimNum--;
					}
				}
				else if (order[aimNum] == 14) {
					if (f[r - 1][c] == 10 || (f[r - 1][c] == 0 && f[r - 1][c + 1] == 10)) {
						continue;
					}
				}
				else if (order[aimNum] == 10) {
					if (f[3][1] == 0) {
						f[3][1] = 14;
						f[2][1] = 10;
						f[2][2] = 0;
					}
					else {
						ten = true;
						aimNum--;
					}
				}

				fixed.insert(elem);
				aimNum++;
				queue<vector<pair<vector<vector<int>>, pair<int, int>>>> tempq;
				vector<pair<vector<vector<int>>, pair<int, int>>> newPath = fullPath;
				newPath.push_back({f, {r, c - 1}});
				tempq.push(newPath);
				q = tempq;
				s.clear();
				continue;
			}
		}
		if (c + 1 < n && find(fixed.begin(), fixed.end(), ft[r][c + 1]) == fixed.end()) {
			vector<vector<int>> f = ft;
			f[r][c] = f[r][c + 1];
			f[r][c + 1] = 0;
			vector<pair<vector<vector<int>>, pair<int, int>>> newPath = fullPath;
			newPath.push_back({f, {r, c + 1}});
			q.push(newPath);
			int elem = f[r][c];
			pair<int, int> comp = {r, c};
			if (elem == order[aimNum] && m[elem] == comp) {
				//looking on right side stacking
				if (order[aimNum] == 4) {
					if (f[r][c + 1] == 3 || ((f[r][c + 1] == 0) && (f[r + 1][c + 1] == 3))) {
						continue;
					}
				}
				else if (order[aimNum] == 3) {
					if (f[0][3] == 0) {
						f[0][2] = 3;
						f[0][3] = 4;
						f[1][2] = 0;
					}
					else {
						three = true;
						aimNum--;
					}
				}
				else if (order[aimNum] == 8) {
					if (f[r][c + 1] == 7 || ((f[r][c + 1] == 0 ) && (f[r + 1][c + 1] == 7))) {
						continue;
					}
				}
				else if (order[aimNum] == 7) {
					if (f[1][3] == 0) {
						f[1][3] = 8;
						f[1][2] = 7;
						f[2][2] = 0;
					}
					else {
						seven = true;
						aimNum--;
					}
				}
				//looking on left side stacking
				else if (order[aimNum] == 13) {
					if (f[r - 1][c] == 9 || ((f[r - 1][c] == 0) && (f[r - 1][c + 1] == 9))) {
						continue;
					}
				}
				else if (order[aimNum] == 9) {
					if (ft[3][0] == 0) {
						ft[3][0] = 13;
						ft[2][0] = 9;
						ft[2][1] = 0;
					}
					else {
						nine = true;
						aimNum--;
					}
				}
				else if (order[aimNum] == 14) {
					if (f[r - 1][c] == 10 || ((f[r - 1][c] == 0) && (f[r - 1][c + 1] == 10))) {
						continue;
					}
				}
				else if (order[aimNum] == 10) {
					if (f[3][1] == 0) {
						f[3][1] = 14;
						f[2][1] = 10;
						f[2][2] = 0;
					}
					else {
						ten = true;
						aimNum--;
					}
				}

				fixed.insert(elem);
				aimNum++;
				queue<vector<pair<vector<vector<int>>, pair<int, int>>>> tempq;
				vector<pair<vector<vector<int>>, pair<int, int>>> newPath = fullPath;
				newPath.push_back({f, {r, c + 1}});
				tempq.push(newPath);
				q = tempq;
				s.clear();
				continue;
			}
		}
		// displayGrid(ft);
	}

	diagnostics(finalPath);

	return 0;
}

void diagnostics(vector<pair<vector<vector<int>>, pair<int, int>>>path) {
	for (pair<vector<vector<int>>, pair<int, int>> stage : path) {
		vector<vector<int>> grid = stage.first;
		for (vector<int> v : grid) {
			for (int x : v) {
				cout << x << " ";
			}
			cout << '\n';
		}
		cout << '\n';
	}
	cout << '\n' << "Moves: " << path.size() << '\n';
}

void displayGrid(vector<vector<int>> grid) {
	for (vector<int> v : grid) {
		for (int x : v) {
			cout << x << " ";
		}
		cout << '\n';
	}
	cout << '\n';
}