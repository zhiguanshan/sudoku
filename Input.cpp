#include"Input.h"

/*构造函数*/
Input::Input(int argc, char *argv[])
{
	this->argc = argc;
	this->argv = argv;
	filename = NULL;
	type = 0;
	num = 0;
	difficulty = 0;
	input_error = false;
}

/*判断参数类型等信息*/
void Input::input_type_analyse()
{
	if(argc < 3)
	{
		input_error = true;
		printf("参数数量过少\n");
	}
	else
	{
		//生成数独
		if (strcmp(argv[1], "-c") == 0)
		{
			type = 'c';
			num = tran_string_to_int(argv[2]);
			if(argc == 5 && strcmp(argv[3], "-m") == 0)
			{
				difficulty = tran_string_to_int(argv[4]);
				if(difficulty < 0 || difficulty > 5)
				{
					input_error=true;
					printf("难度设置错误\n");
				}
			}
		}
		else if (strcmp(argv[1], "-s") == 0)//解数独
		{
			type = 's';
			filename = argv[2];

			//文件存在检测
			errno_t err;
			FILE *tryopen;
			err = fopen_s(&tryopen, filename, "r");
			if (err != 0)
			{
				input_error = true;
				printf("文件不存在\n");
			}
		}
		else //参数错误
		{
			input_error = true;
			printf("参数输入错误! error found in method Input::inputTypeAnalyse()\n");
		}
	}
}

char Input::get_type()
{
	return type;
}

int Input::get_num()
{
	return num;
}

int Input::get_difficulty()
{
	return difficulty;
}

char* Input::get_filename()
{
	return filename;
}

bool Input::found_error()
{
	return input_error;
}

int Input::tran_string_to_int(char string[])
{
	int len = strlen(string);
	int temp_num = 0;
	for (int i = 0; i < len; i++)
	{
		if (string[i] >= '0'&&string[i] <= '9')
			temp_num = temp_num * 10 + (string[i] - '0');
		else
		{
			input_error = true;
			cout<<"error found in parameter, you should input only integar\n";
			return -1;
		}
	}
	return temp_num;
}
