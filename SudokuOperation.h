#include <fstream>
#include <algorithm>
using namespace std;

class SudokuOperation
{
public:
	//初始化
	SudokuOperation() noexcept;

	//接受-c参数生成数独终局
	void generate_ending(int num, int difficulty);

	//输出终局和解数独结果
	void output_result(FILE *file, int matrix[9][9], int difficulty);

	//接受-s参数解数独
	void solve_sudoku(char *filename);

	//由solve_sudoku函数调用以深搜解数独
	void search_solution(int i, int j, int (&matrix)[9][9]);

	//检查数独合法性
	bool check(int i, int j, int n, int matrix[9][9]);

private:
	//现有终局数
	int num_now;

	//记录数独终局
	int result_matrix[9][9];

	//解数独标志，初始为false
	bool success_sign;
};
