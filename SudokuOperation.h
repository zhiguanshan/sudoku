#include <fstream>
#include <algorithm>
#include <random>
using namespace std;

/*
 生成数独时调用generate_ending()，它会调用move_step_generate()

 solve_sudoku()处理解数独，它会调用search_solution()和check()
*/
class SudokuOperation
{
public:
	//初始化
	SudokuOperation() noexcept;

	//接受-c参数生成数独终局，使用交换行列的方式在一个合法终局的基础上不断产生新终局
	void generate_ending(int num, int difficulty);

	//用于生成新终局交换
	void move_step_generate();

	//输出终局和解数独结果
	void output_result(FILE *file, int matrix[9][9], int difficulty);

	//接受-s参数解数独
	void solve_sudoku(char *filename);

	//由solve_sudoku函数调用以深搜解数独
	void search_solution(int i, int j, int (&matrix)[9][9]);

	//用于检查数据放入数独的合法性
	bool check(int i, int j, int n, int matrix[9][9]);

private:
	//现有终局数
	int num_now;

	//记录生成交换数
	int move_step_matrix[72][9];

	//记录数独终局
	int result_matrix[9][9];

	//解数独标志，初始为false
	bool success_sign;
};
