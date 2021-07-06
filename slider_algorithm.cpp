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
			}
		}
	}
	queue<pair<vector<vector<int>>, pair<int, int>>> q;
	q.push({grid, zeroPosition});

	map<int, pair<int, int>> m;

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
	set<int> fixed;
	while (!q.empty()) {
		vector<vector<int>> ft = q.front().first;
		pair<int, int> zeroPos = q.front().second;
		q.pop();
		if (find(s.begin(), s.end(), ft) != s.end()) {
			continue;
		}
		s.insert(ft);

		// displayGrid(ft);

		if (aimNum > 14) {
			cout << "SOLVED!" << endl;
			displayGrid(ft);
			break;
		}
		// cout << order[aimNum] << endl;

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
				// cout << elem << " in correct position" << endl;
				aimNum++;
				queue<pair<vector<vector<int>>, pair<int, int>>> tempq;
				tempq.push({ft, {1, 2}});
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
				queue<pair<vector<vector<int>>, pair<int, int>>> tempq;
				tempq.push({ft, {2, 1}});
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
				// cout << elem << " in correct position" << endl;
				aimNum++;
				queue<pair<vector<vector<int>>, pair<int, int>>> tempq;
				tempq.push({ft, {2, 2}});
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
				// cout << elem << " in correct position" << endl;
				aimNum++;
				queue<pair<vector<vector<int>>, pair<int, int>>> tempq;
				tempq.push({ft, {2, 2}});
				q = tempq;
				s.clear();
				continue;
			}
		}
//____________________________________________


		if (r - 1 >= 0 && find(fixed.begin(), fixed.end(), ft[r - 1][c]) == fixed.end()) {
			// cout << "above swap" << endl;
			vector<vector<int>> f = ft;
			f[r][c] = f[r - 1][c];
			f[r - 1][c] = 0;
			q.push({f, {r - 1, c}});

			pair<int, int> comp = {r, c};
			if (elem == order[aimNum] && m[elem] == comp) {
				// cout << order[aimNum] << " is in correct spot" << endl;
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
						// cout << "three IS TRUE" << endl;
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
						// cout << "NINE IS TRUE" << endl;
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
						// cout << "TEN IS TRUE" << endl;
						aimNum--;
					}
				}
				fixed.insert(elem);
				// cout << elem << " in correct position" << endl;
				aimNum++;
				queue<pair<vector<vector<int>>, pair<int, int>>> tempq;
				tempq.push({f, {r - 1, c}});
				q = tempq;
				s.clear();
				continue;
			}
		}
		if (r + 1 < n && find(fixed.begin(), fixed.end(), ft[r + 1][c]) == fixed.end()) {
			// cout << "below swap" << endl;
			vector<vector<int>> f = ft;
			f[r][c] = f[r + 1][c];
			f[r + 1][c] = 0;
			q.push({f, {r + 1, c}});

			int elem = f[r][c];
			pair<int, int> comp = {r, c};

			if (elem == order[aimNum] && m[elem] == comp) {
				// cout << order[aimNum] << " is in correct spot" << endl;

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
						// cout << "NINE IS TRUE" << endl;
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
						// cout << "TEN IS TRUE" << endl;
						aimNum--;
					}
				}

				fixed.insert(elem);
				// cout << elem << " in correct position" << endl;
				aimNum++;
				queue<pair<vector<vector<int>>, pair<int, int>>> tempq;
				tempq.push({f, {r + 1, c}});
				q = tempq;
				s.clear();
				continue;
			}
		}
		if (c - 1 >= 0 && find(fixed.begin(), fixed.end(), ft[r][c - 1]) == fixed.end()) {
			// cout << "left swap" << endl;
			vector<vector<int>> f = ft;
			f[r][c] = f[r][c - 1];
			f[r][c - 1] = 0;
			q.push({f, {r, c - 1}});

			int elem = f[r][c];
			pair<int, int> comp = {r, c};
			if (elem == order[aimNum] && m[elem] == comp) {
				// cout << order[aimNum] << " is in correct spot" << endl;
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
						// cout << "NINE IS TRUE" << endl;
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
						// cout << "TEN IS TRUE" << endl;
						aimNum--;
					}
				}

				fixed.insert(elem);
				// cout << elem << " in correct position" << endl;
				aimNum++;
				queue<pair<vector<vector<int>>, pair<int, int>>> tempq;
				tempq.push({f, {r, c - 1}});
				q = tempq;
				s.clear();
				continue;
			}
		}
		if (c + 1 < n && find(fixed.begin(), fixed.end(), ft[r][c + 1]) == fixed.end()) {
			// cout << "right swap" << endl;
			vector<vector<int>> f = ft;
			f[r][c] = f[r][c + 1];
			f[r][c + 1] = 0;
			q.push({f, {r, c + 1}});

			int elem = f[r][c];
			pair<int, int> comp = {r, c};
			if (elem == order[aimNum] && m[elem] == comp) {
				// cout << order[aimNum] << " is in correct spot" << endl;
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
						// cout << "NINE IS TRUE" << endl;
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
						// cout << "TEN IS TRUE" << endl;
						aimNum--;
					}
				}

				fixed.insert(elem);
				// cout << elem << " in correct position" << endl;
				aimNum++;
				queue<pair<vector<vector<int>>, pair<int, int>>> tempq;
				tempq.push({f, {r, c + 1}});
				q = tempq;
				s.clear();
				continue;
			}
		}
		// displayGrid(ft);
	}
	// cout << order[aimNum] << endl;
	return 0;
}
