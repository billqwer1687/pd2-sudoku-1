#include "Sudoku.h"
#include <algorithm>
#include <ctime>
using namespace std;

int cnt, ans[81];
int row[9][10], col[9][10], cell[9][10];

Sudoku::Sudoku(){
	for (int i=0; i<sudokuSize; ++i)
		map[i] = 0;
}

void Sudoku::giveQuestion(){
	cout << "8 0 0 0 0 0 0 0 0\n";
	cout << "0 0 7 5 0 0 0 0 9\n";
	cout << "0 3 0 0 0 0 1 8 0\n";
	cout << "0 6 0 0 0 1 0 5 0\n";
	cout << "0 0 9 0 4 0 0 0 0\n";
	cout << "0 0 0 7 5 0 0 0 0\n";
	cout << "0 0 2 0 7 0 0 0 4\n";
	cout << "0 0 0 0 0 3 6 1 0\n";
	cout << "0 0 0 0 0 0 8 0 0\n";
}

void Sudoku::readIn(){
	for (int i=0; i<sudokuSize; ++i)
		scanf("%d",&map[i]);
}

void Sudoku::changeNum(int a, int b){
	for (int i=0; i<sudokuSize; ++i)
		if (map[i]==a) map[i]=b;
		else if (map[i]==b) map[i]=a;
}

void Sudoku::changeRow(int a, int b){
	for (int i=0; i<9 ; ++i){
		swap(map[a*27+ 0+i], map[b*27+ 0+i]);
		swap(map[a*27+ 9+i], map[b*27+ 9+i]);
		swap(map[a*27+18+i], map[b*27+18+i]);
	}
}

void Sudoku::changeCol(int a, int b){
	for (int i=0; i<sudokuSize; i+=9){
		swap(map[a*3+0+i],map[b*3+0+i]);
		swap(map[a*3+1+i],map[b*3+1+i]);
		swap(map[a*3+2+i],map[b*3+2+i]);
	}
}

void Sudoku::rotate(int n){
	n %= 4;
	int copy_map[sudokuSize], i, j, k;
	for (k=0; k<n; ++k){
		for (i=0; i<81; ++i)
			copy_map[i] = map[i];
		for (i=0; i<9; ++i)
			for (j=0; j<9; ++j)
				map[(8-i)+9*j] = copy_map[9*i+j];
	}
}

void Sudoku::flip(int n){
	if (n==0){
		for (int i=0; i<9; ++i){
			swap(map[ 0+i], map[72+i]);
			swap(map[ 9+i], map[63+i]);
			swap(map[18+i], map[54+i]);
			swap(map[27+i], map[45+i]);
		}
	}
	else{
		for (int i=0; i<=72; i+=9){
			swap(map[0+i], map[8+i]);
			swap(map[1+i], map[7+i]);
			swap(map[2+i], map[6+i]);
			swap(map[3+i], map[5+i]);
		}
	}
}

void Sudoku::transform(){
	readIn();
	srand(time(NULL));
	changeNum(rand()%9+1, rand()%9+1);
	changeRow(rand()%3, rand()%3);
	changeCol(rand()%3, rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
	for (int i=0; i<sudokuSize; ++i)
		printf ("%d%c", map[i], (i+1)%9==0 ? '\n' : ' ');
}

void Sudoku::solve(){
	for (int i=0; i<9; ++i){
		for (int j=0; j<9; ++j){
			if (map[9*i+j]!=0){
				row[i][map[9*i+j]] ++;
				col[j][map[9*i+j]] ++;
				cell[i/3*3+j/3][map[9*i+j]] ++;
			}
		}
	}
	for (int i=0; i<9; ++i)
		for (int j=1; j<=10; ++j)
			if (row[i][j]>1 || col[i][j]>1){
				cout << 0 << endl;
				return;
			}
	cnt = 0;
	fill_in(0);
	cout << cnt << endl;
	if (cnt==1){
		for (int i=0; i<sudokuSize; ++i)
			printf ("%d%c", ans[i], (i+1)%9==0 ? '\n' : ' ');
	}
}

void Sudoku::fill_in(int now){
	if (cnt>1)
		return;
	if (now==81){
		cnt ++;
		if (cnt > 1) return;
		for (int i=0; i<81; ++i)
			ans[i] = map[i];
		return;
	}
	if (map[now]!=0)
		fill_in(now+1);
	else{
		int x=now/9, y=now%9;
		for (int i=1; i<=9; ++i){
			if (!row[x][i] && !col[y][i] && !cell[x/3*3+y/3][i]){
				row[x][i] = col[y][i] = cell[x/3*3+y/3][i] = 1;
				map[now] = i;
				fill_in(now+1);
				row[x][i] = col[y][i] = cell[x/3*3+y/3][i] = 0;
				map[now] = 0;
			}
		}
	}
	return;
}
