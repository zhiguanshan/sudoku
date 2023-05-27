/*任务入口点*/
#include<cstring>
#include<string>
#include"Input.cpp"
#include"SudokuOperation.cpp"

int main(int argc, char* argv[]){
	Input input(argc, argv);
	input.input_type_analyse();

	if(input.found_error()){
	    printf("input error occurs!\n");
		return 0;
	}

	char type = input.get_type();
	int num = input.get_num();
	int diffculty = input.get_difficulty();
	char* filename = input.get_filename();
	
	SudokuOperation operation;
	switch(type){
	case 'c':
		operation.generate_ending(num, diffculty);
		break;
	case 's':
		operation.solve_sudoku(filename);
		break;
	default:
		break;
	}
    return 0; 
}
