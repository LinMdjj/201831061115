#include"pch.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstring>
#include<stdio.h>
#include<iomanip>
#include<time.h>
using namespace std;
const int N = 1000;


struct WORD                                               //定义一个结构体，存储单词
{
	char word[20];                                          //存单词
	int time;                                               //单次出现的次数
};


int main()
{
	int i;
	int desin;
	ofstream outfile;
	double t;
	int code = 0, j = 0, allword = 0;                                                      //路径打开文件
	char ch;
	char s[20];
	struct WORD data[N];
	char file[100], savefile[100];//定义输出文件
	t = (double)clock();
	//********************************************************************************************
	//打开文本文件
	cout << "***********请输入文件路径:***********" << endl;
	cin >> file;//文件路径输入   
	FILE *fp;
	if ((fp = fopen(file, "r+")) == NULL)//文件无法打开则提示
	{
		cout << "无法打开文件！" << endl;
		exit(0);
	}

	//********************************************************************************************
	//将单词输出并判定

	while (!feof(fp))
	{
		ch = getc(fp);
		if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))
		{
			allword++;
			s[code] = ch;
			code++;
		}
		else
		{
			s[code] = '\0';
			allword++;

			if (strlen(s) != 0)
			{
				strcpy(data[j].word, s);                                //存储单词
				data[j].time = 1;
				code = 0;
				j++;
			}
			else continue;
		}

	}


	//****************************************************************************************************
	//将单词的大写转化为小写
	int k = j;

	for (int t = 0; t < k; t++)
	{
		int w = 0;
		while (data[t].word[w])
		{
			if (data[t].word[w] >= 'A'&&data[t].word[w] <= 'Z')
				data[t].word[w] = data[t].word[w] + 32;
			w++;
		}

	}

	//************************************************************************************************************
	// 进行排序
	for (int t = 0; t < k; t++)
		for (int r = 0; r < k - t - 1; r++)
		{
			struct WORD temp;
			if (strcmp(data[r].word, data[r + 1].word) > 0)
			{
				temp = data[r];
				data[r] = data[r + 1];
				data[r + 1] = temp;
			}

		}

	int count = k;

	for (int t = 0; t < k - 1; t++)
	{
		for (int r = t + 1; r < k; r++)
			if (strcmp(data[t].word, data[r].word) == 0)
			{
				++data[t].time;

				for (int p = r; p < k - 1; p++)
					data[p] = data[p + 1];
				--k;
				data[k].time = 0;
				--r;
			}
	}

	for (int t = 0; t < k; t++)
		for (int r = t + 1; r < k - 1; r++)
		{
			struct WORD temp;
			if (data[t].time < data[r].time)
			{
				temp = data[t];
				data[t] = data[r];
				data[r] = temp;
			}
		}



	//**********************************************************************************************************
	//打印单词和频率
	cout << "**************************************************************************\n";
	cout << setiosflags(ios::left) << setw(15) << "单词" << "		" << "次数" << endl;                   //输出到文件
	for (i = 0; i < 10; i++)
	{
		if (data[i].time != 0)
		{
			cout << setiosflags(ios::left) << setw(15) << data[i].word << "		" << data[i].time << endl;
		}
	}
	cout << "******************************************************************************\n";
	cout << "总单词个数：" << count << endl;
	cout << "总字符个数：" << allword << endl;
	cout << "不同的单词个数：" << k << endl;
	cout << "是否需要存入文件？" << endl;
	fclose(fp);
	//**************************************************************************************************
	//将单词存入指定的文件中
	cout << "\n1.YES\n0.NO" << endl;
	cin >> desin;
	if (desin == 1)
	{
		cout << "***********请输入传出数据路径:***********（例：c:/outfile.txt）" << endl;
		cin >> savefile;//文件路径输入
		if ((fp = fopen(savefile, "r+")) == NULL)//文件无法打开则提示
		{
			cout << "无法打开文件！" << endl;
			exit(0);
		}
		outfile.open(savefile);
		outfile << setiosflags(ios::left) << setw(15) << "单词" << "		" << "出现次数" << endl;                   //输出到文件
		for (i = 0; i < 10; i++)
		{
			if (data[i].time != 0)
			{
				outfile << setiosflags(ios::left) << setw(15) << data[i].word << "		" << data[i].time << endl;
			}
		}
		outfile << "总单词个数：" << count << endl;
		outfile << "总字符个数：" << allword << endl;
		outfile << "不同的单词个数：" << k << endl;
		cout << "文件已储存" << endl;
		//关闭文件
		outfile.close();

	}
	else

		return 0;
}