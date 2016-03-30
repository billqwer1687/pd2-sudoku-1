#include <iostream>
#include <cstdio>
using namespace std;

class Sudoku{
	public:
		Sudoku();
		Sudoku(int init_map[]);
		void giveQuestion();
		void readIn();
		void solve();
		void changeNum(int a, int b);
		void changeRow(int a, int b);
		void changeCol(int a, int b);
		void rotate(int n);
		void flip(int n);
		void transform();
		//int getElement(int index);
		//bool isCorrect();
		static const int sudokuSize=81;
		private:
		bool checkUnity(int arr[]);
		void fill_in(int now);
		int map[sudokuSize];
};	
