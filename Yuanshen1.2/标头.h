#pragma once
typedef struct count
{
	int threestars;
	int fourstars;
	int fivestars;
	int fourbaodi;
	int fivebaodi;
	int sum;
	int recordfivestars[200];
	int recordfourstars[2000];
}Count;

typedef struct count_characters
{
	int up;
	int qing;
	int keqing;
	int mona;
	int qiqi;
	int diluke;
}count_characters;

typedef struct name
{
	char fivestarcharacter[50];
	char fourstarcharacter1[50];
	char fourstarcharacter2[50];
	char fourstarcharacter3[50];
}name;

void changzhu(Count* countp, int flag);
void juese(Count* countp, int flag, name name);
int judge(int result, Count* countp);
int judgefourbaodi9(int result, Count* countp);
int random(void);
void count(Count* countp, int a);
void analyse(Count* countp, int* record);
int* output(Count* countp, int flag, int* n, int* ret);
void fourstars(name name);
void fivestars(name name);
