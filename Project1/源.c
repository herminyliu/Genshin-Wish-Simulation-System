#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"标头.h"

//程序还可以进步的地方：
//  2.角色池和常驻池分开计算保底概率 3.大保底还有问题额
int main()
{
	Count count;
	count.threestars = 0;
	count.fourstars = 0;
	count.fivestars = 0;
	count.fourbaodi = 0;
	count.fivebaodi = 0;
	count.sum = 0;
	Count *countp = &count;
	name name;
	strcpy(name.fivestarcharacter, "神里凌华");
	strcpy(name.fourstarcharacter1, "早柚");
	strcpy(name.fourstarcharacter2, "罗莎莉亚");
	strcpy(name.fourstarcharacter3, "雷泽");
	printf("%s", "————————白鹭归庭：神里绫华角色限时祈愿————————\n\n");
	while (1)
	{
		srand((unsigned int)time(NULL)+100);
		int flag, flag1;
		printf("%s", "请选择要抽取的卡池:角色池请输入1，常驻池请输入2：\n");
		scanf_s("%d", &flag);
		printf("%s", "————————十连请输入1，单抽请输入2，自定义请输入3————————\n");
		scanf_s("%d", &flag1);
		if (flag == 1)
		{
			juese(countp, flag1, name);
		}
		if (flag == 2)
		{
			changzhu(countp, flag1, name);
		}
		printf("%s\n", "————————退出祈愿系统请输入0,继续抽卡请输入1————————");
		scanf_s("%d", &flag);
		if (flag == 0)
		{
			printf("三星物品/角色总出数：%d\n", countp->threestars);
			printf("四星物品/角色总出数：%d\n", countp->fourstars);
			printf("四星物品/角色平均出率：%.4f\n", ((double)((double)countp->fourstars / (double)countp->sum)) * 100);
			printf("五星物品/角色总出数：%d\n", countp->fivestars);
			printf("五星物品/角色平均出率：%.4f\n", ((double)((double)countp->fivestars / (double)countp->sum)) * 100);
			printf("以下为每个五星角色抽出所用抽数：\n\n");
			for (int i = 0; i < countp->fivestars; i++)
			{
				printf("%d ", countp->recordfivestars[i] + 1);
			}
			analyse(countp, countp->recordfivestars);
			printf("\n总抽数：%d\n", countp->sum);
			printf("%s", "————————感谢使用祈愿系统————————\n\n\n\n\n");
			break;
		}
		else
			continue;
	}
	return 0;
}

void changzhu(Count* countp,int flag)
{
	int n, m;
	int* np = &n;
	int* ret = &m;
	ret = output(countp, flag, np, ret);
	for (int i = 0; i < *np; i++)
	{
		printf("第%.4d发恭喜您抽出了%d星物品/角色", countp->sum - n + 1 + i, ret[i]);
		for (int j = 0; j < ret[i]; j++)
		{
			printf("%s", "★");
		}
		printf("\n");
	}
	free(ret);
}

void juese(Count* countp,int flag,name name)
{	
	int n, m;
	int* np = &n;
	int* ret = &m;
	ret = output(countp, flag, np, ret);
	for (int i = 0; i < *np; i++)
	{
		printf("第%.4d发恭喜您抽出了%d星物品/角色", (countp->sum) - n + 1 + i, ret[i]);
		if (ret[i] == 5)
		{
			fivestars(name);
		}
		if (ret[i] == 4)
		{
			fourstars(name);
		}
		for (int j = 0; j < ret[i]; j++)
		{
			printf("%s", "★");
		}
		printf("\n");
	}
	free(ret);
}

int* output(Count* countp, int flag, int* n, int* ret)
{
	if (flag == 1)
		*n = 10;
	if (flag == 2)
		*n = 1;
	if (flag == 3)
	{
		printf("请输入具体抽取的数目:");
		scanf_s("%d", n);
	}
	
	ret = (int*)malloc(*n * sizeof(int));
	if (ret == NULL)
	{
		printf("抱歉，数字太大，内存不足，程序无法运行\n");
		*n = -1;  //这里是让changzhu和juese函数里面的for循环从一开始就不满足条件，从而不会进入循环，执行if语句发生异常使程序崩溃。
	}
	else
	{
		int result = 0;
		for (int i = 0; i < *n; i++)
		{
			result = random();
			switch (countp->fourbaodi)
			{
			case 9:
			{
				if (judge(result, countp) == 5)
				{
					ret[i] = 5;
					count(countp, 5);
					countp->fourbaodi = 9;  // 五星和四星第十发保底冲突，先出五星，同时确保下一发一定最低四星
				}
				else
				{
					ret[i] = 4;
					count(countp, 4);
				}
				break;
			}
			case 8:
			{
				ret[i] = judgefourbaodi9(result, countp);
				count(countp, ret[i]);
				break;
			}
			default:
			{
				ret[i] = judge(result, countp);
				count(countp, ret[i]);
				break;
			}
			}
		}
	}
	return ret;
}

int judge(int result,Count* countp)    //基础概率控制器（包含五星概率保底功能）
{
	int add = 60 * (countp->fivebaodi - 72);
	if (add > 0)
	{
		if (result >= 994 - add)   //0.6%
			return 5;
		if (result <= 993 - add && result > 942 - add)  //5.1%
			return 4;
		if (result <= 942 - add)
			return 3;
	}
	else
	{
		if (result >= 994)   //0.6%
			return 5;
		if (result <= 993 && result > 942)  //5.1%
			return 4;
		if (result <= 942)
			return 3;
	}
}

int judgefourbaodi9(int result, Count* countp)   //四星第九发保底概率控制器（包含五星概率保底功能）
{
	int add = 60 * (countp->fivebaodi - 72);
	if (add > 0)
	{
		if (result >= 994 - add)
			return 5;
		if (result <= 993 - add && result > 432 - add)   //56.1%
			return 4;
		if (result <= 432 - add)
			return 3;
	}
	else
	{
		if (result >= 994)   //0.6%
			return 5;
		if (result <= 993 && result > 432)  //56.1%
			return 4;
		if (result <= 432)
			return 3;
	}
}

int random(void)    //随机数生成器
{
	int ret = 0;
	ret = rand() % 1000;
	return ret;
}

void count(Count* countp, int a)   //出货、保底计数器
{
	countp->sum++;
	if (a == 3)
	{
		countp->threestars++;
		countp->fourbaodi++;
		countp->fivebaodi++;
	}
	if (a == 4)
	{
		countp->recordfourstars[countp->fourstars] = countp->fourbaodi;
		countp->fourstars++;
		countp->fourbaodi = 0;
		countp->fivebaodi++;
	}
	if (a == 5)
	{
		countp->recordfivestars[countp->fivestars] = countp->fivebaodi;
		countp->fivestars++;
		countp->fourbaodi = 0;
		countp->fivebaodi = 0;
		//如果四星和五星抽中同时触发。。会出bug，等会要解决一下
	}
}

void analyse(Count* countp, int* record)
{
	double average4, average5, variance;
	double sum1 = 0;
	average4 = (double)((double)countp->sum - (double)countp->fourbaodi) / (double)countp->fourstars;
	average5 = (double)((double)countp->sum - (double)countp->fivebaodi) / (double)countp->fivestars;
	for (int i = 0; i < countp->fivestars; i++)
	{
		sum1 += pow((record[i] - average5), 2);
	}
	variance = pow(sum1 / (double)countp->fivestars, 0.5);
	printf("\n\n四星物品抽出所用抽数期望为：%lf\n",average4);
	printf("五星物品抽出所用抽数期望为：%lf\n",average5);
	printf("五星物品抽出所用抽数方差为：%lf\n",variance);
}

void fourstars(name name)
{
	int result0 = random();
	if (result0 >= 500)
	{
		printf("——");
		int result1 = random();
		int result2 = result1 / 333;
		if (result2 == 0)
		{
			printf("%s", name.fourstarcharacter1);
		}
		if (result2 == 1)
		{
			printf("%s", name.fourstarcharacter2);
		}
		if (result2 == 2)
		{
			printf("%s", name.fourstarcharacter3);
		}
	}
}

void fivestars(name name)
{
	int result0 = random();
	static int flagfivestars = 0;
	printf("——");
	if (flagfivestars == 1 || result0 >= 500)
	{
		printf("%s",name.fivestarcharacter);
		flagfivestars = 0;
	}
	else
	{
		flagfivestars = 1;
		int result1 = random();
		int result2 = result1 / 200;
		if (result2 == 1)
		{
			printf("%s", "刻晴");
		}
		if (result2 == 2)
		{
			printf("%s", "琴");
		}
		if (result2 == 3)
		{
			printf("%s", "莫娜");
		}
		if (result2 == 4)
		{
			printf("%s", "七七");
		}
		if (result2 == 0)
		{
			printf("%s", "迪卢克");
		}
	}
}