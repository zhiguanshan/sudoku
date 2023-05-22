#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<tchar.h>
using namespace std;

/*处理输入类*/
class Input
{
public:
	/*初始化Input类*/
	Input(int argc, char *argv[]);
	
	/*解析参数*/
	void input_type_analyse();

	//读取的string转为int
	int tran_string_to_int(char string[]);

	/*解析参数*/
	char get_type();

	//检测-c参数后的数字
	int get_num();

	//检测-s参数后的文件路径
	char* get_filename();

	//检测-m参数后的路径
	int get_difficulty();

	//错误捕获
	bool found_error();

private:
	int argc;
	char **argv;
	int num;
	int difficulty;
	char type;
	char* filename;
	bool input_error;
};
