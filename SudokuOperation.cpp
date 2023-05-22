#include "SudokuOperation.h"

SudokuOperation::SudokuOperation() noexcept
{
	memset(move_step_matrix, 0, sizeof(move_step_matrix));
	memset(result_matrix, 0, sizeof(result_matrix));
	num_now = 0;
	success_sign = false;
}

void SudokuOperation::move_step_generate()
{
	int move_dictionary1[2][3] = { { 0,3,6 },{ 0,6,3 } };
	int move_dictionary2[6][3] = { { 1,4,7 },{ 1,7,4 },{ 4,1,7 },{ 4,7,1 },{ 7,4,1 },{ 7,1,4 } };
	int move_dictionary3[6][3] = { { 2,5,8 },{ 2,8,5 },{ 5,2,8 },{ 5,8,2 },{ 8,2,5 },{ 8,5,2 } };
	int i, j, k, count = 0;
	int step[10];
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 6; j++)
		{
			for (k = 0; k < 6; k++)
			{
				memcpy_s(&step[0], 3 * sizeof(int), &move_dictionary1[i][0], 3 * sizeof(int));
				memcpy_s(&step[3], 3 * sizeof(int), &move_dictionary2[j][0], 3 * sizeof(int));
				memcpy_s(&step[6], 3 * sizeof(int), &move_dictionary3[k][0], 3 * sizeof(int));
				memcpy_s(&move_step_matrix[count], 9 * sizeof(int), &step[0], 9 * sizeof(int));
				count++;
			}
		}
	}
}

void SudokuOperation::output_result(FILE *file, int matrix[9][9], int difficulty)
{
	int pointer = 0;
	char temp[164];
	memset(temp, 0, sizeof(temp));
	random_device seed;
	ranlux48 engine(seed());
	uniform_int_distribution<> distrib(0, 10);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int random = distrib(engine);
			if(difficulty > 0 && random <= difficulty)
			{
				temp[pointer] = '$';
			}
			else
			{
				temp[pointer] = matrix[i][j] + '0';
			}
			pointer++;
			if (j != 8)
			{
				temp[pointer] = ' ';
				pointer++;
			}
		}
		temp[pointer] = '\n';
		pointer++;
	}
	temp[pointer] = '\n';
	fputs(temp, file);
}

void SudokuOperation::generate_ending(int num, int difficulty)
{
	errno_t err;
	FILE *file;
	err = fopen_s(&file, "sudoku.txt", "w");
	if (err != 0)
		printf("file doesn't exist\n");

	move_step_generate();
	int first_line[9] = { 1,9,4,3,2,5,6,7,8 };
	int joint_line[18];
	while (next_permutation(&first_line[1], &first_line[9]))
	{
		if (num_now >= num)
			break;
		int circle = 72;
		while (circle--)
		{
			if (num_now >= num)
				break;
			else
			{
				memcpy(joint_line, first_line, sizeof(first_line));
				memcpy(&joint_line[9], first_line, sizeof(first_line));
				int i = num_now % 72;
				for (int j = 0; j < 9; j++)
				{
					int step = move_step_matrix[i][j];
					memcpy(&result_matrix[j], &joint_line[step], 9 * sizeof(int));
				}
				if (file != 0)
				{
					output_result(file, result_matrix, difficulty);
				}
				num_now++;
			}
		}
	}
	if (file != 0)
		fclose(file);
}

void SudokuOperation::search_solution(int i, int j, int(&matrix)[9][9])
{
	if (success_sign == true)
		return;
	else
	{
		if (i > 8)
		{
			success_sign = true;
			return;
		}
		if (j > 8)
		{
			if (i < 8)
				search_solution(i + 1, 0, matrix);
			if (i == 8)
			{
				success_sign = true;
				return;
			}
		}
		else
		{
			if (matrix[i][j] != 0)
				search_solution(i, j + 1, matrix);
			else
			{
				if (i <= 8 && j <= 8)
				{
					for (int n = 1; n <= 9; n++)
					{
						if (check(i, j, n, matrix))
						{
							matrix[i][j] = n;
							search_solution(i, j + 1, matrix);
							if (success_sign == true)
								return;
							else
								matrix[i][j] = 0;
						}
					}
				}
			}
		}
	}
}

bool SudokuOperation::check(int i, int j, int n, int matrix[9][9])
{
	int col, row;
	//处理行
	for (col = 0; col < 9; col++)
	{
		if (matrix[i][col] == n)
			return false;
	}
	//处理列
	for (row = 0; row < 9; row++)
	{
		if (matrix[row][j] == n)
			return false;
	}
	//处理9个3*3
	int base_row = (i / 3) * 3;
	int base_col = (j / 3) * 3;
	for (row = base_row; row < base_row + 3; row++)
	{
		for (col = base_col; col < base_col + 3; col++)
		{
			if (matrix[row][col] == n)
				return false;
		}
	}
	return true;
}

void SudokuOperation::solve_sudoku(char *filename)
{
	errno_t err, erw;
	FILE *rfile, *wfile;
	err = fopen_s(&rfile, filename, "r");
	erw = fopen_s(&wfile, "sudoku.txt", "w");
	if (err != 0 || erw != 0)
		printf("the input or output file doesn't exist\n");
	else
	{
		//读取待解数独
		int puzzle_matrix[9][9];

		//*blank_or_enter处理' '和'\n'
		char blank_or_enter;
		int i, j;

		if (rfile != 0 && wfile != 0)
		{
			do
			{
				for (i = 0; i < 9; i++)
				{
					for (j = 0; j < 9; j++)
					{
						char temp;
						fscanf(rfile, "%c%c", &temp, &blank_or_enter, sizeof(char) + sizeof(char));
						if(temp >= '0'&& temp <= '9')
						{
							puzzle_matrix[i][j] = temp-'0';
						}
						else if(temp=='$')
						{
							puzzle_matrix[i][j] = 0;
						}
					}
				}

				//搜寻从puzzle_matrix中提取的数独解
				search_solution(0, 0, puzzle_matrix);
				success_sign = false;

				output_result(wfile, puzzle_matrix, 0);

			} while (fscanf(rfile, "%c", &blank_or_enter, sizeof(char)) != EOF);
		}
	}
	if (rfile != 0)
		fclose(rfile);
	if (wfile != 0)
		fclose(wfile);
}
