#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"��ͷ.h"

//���򻹿��Խ����ĵط���
//  2.��ɫ�غͳ�פ�طֿ����㱣�׸��� 3.�󱣵׻��������
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
	strcpy(name.fivestarcharacter, "�����軪");
	strcpy(name.fourstarcharacter1, "����");
	strcpy(name.fourstarcharacter2, "��ɯ����");
	strcpy(name.fourstarcharacter3, "����");
	printf("%s", "�������������������ع�ͥ������类���ɫ��ʱ��Ը����������������\n\n");
	while (1)
	{
		srand((unsigned int)time(NULL)+100);
		int flag, flag1;
		printf("%s", "��ѡ��Ҫ��ȡ�Ŀ���:��ɫ��������1����פ��������2��\n");
		scanf_s("%d", &flag);
		printf("%s", "����������������ʮ��������1������������2���Զ���������3����������������\n");
		scanf_s("%d", &flag1);
		if (flag == 1)
		{
			juese(countp, flag1, name);
		}
		if (flag == 2)
		{
			changzhu(countp, flag1, name);
		}
		printf("%s\n", "�����������������˳���Ըϵͳ������0,�����鿨������1����������������");
		scanf_s("%d", &flag);
		if (flag == 0)
		{
			printf("������Ʒ/��ɫ�ܳ�����%d\n", countp->threestars);
			printf("������Ʒ/��ɫ�ܳ�����%d\n", countp->fourstars);
			printf("������Ʒ/��ɫƽ�����ʣ�%.4f\n", ((double)((double)countp->fourstars / (double)countp->sum)) * 100);
			printf("������Ʒ/��ɫ�ܳ�����%d\n", countp->fivestars);
			printf("������Ʒ/��ɫƽ�����ʣ�%.4f\n", ((double)((double)countp->fivestars / (double)countp->sum)) * 100);
			printf("����Ϊÿ�����ǽ�ɫ������ó�����\n\n");
			for (int i = 0; i < countp->fivestars; i++)
			{
				printf("%d ", countp->recordfivestars[i] + 1);
			}
			analyse(countp, countp->recordfivestars);
			printf("\n�ܳ�����%d\n", countp->sum);
			printf("%s", "������������������лʹ����Ըϵͳ����������������\n\n\n\n\n");
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
		printf("��%.4d����ϲ�������%d����Ʒ/��ɫ", countp->sum - n + 1 + i, ret[i]);
		for (int j = 0; j < ret[i]; j++)
		{
			printf("%s", "��");
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
		printf("��%.4d����ϲ�������%d����Ʒ/��ɫ", (countp->sum) - n + 1 + i, ret[i]);
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
			printf("%s", "��");
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
		printf("����������ȡ����Ŀ:");
		scanf_s("%d", n);
	}
	
	ret = (int*)malloc(*n * sizeof(int));
	if (ret == NULL)
	{
		printf("��Ǹ������̫���ڴ治�㣬�����޷�����\n");
		*n = -1;  //��������changzhu��juese���������forѭ����һ��ʼ�Ͳ������������Ӷ��������ѭ����ִ��if��䷢���쳣ʹ���������
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
					countp->fourbaodi = 9;  // ���Ǻ����ǵ�ʮ�����׳�ͻ���ȳ����ǣ�ͬʱȷ����һ��һ���������
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

int judge(int result,Count* countp)    //�������ʿ��������������Ǹ��ʱ��׹��ܣ�
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

int judgefourbaodi9(int result, Count* countp)   //���ǵھŷ����׸��ʿ��������������Ǹ��ʱ��׹��ܣ�
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

int random(void)    //�����������
{
	int ret = 0;
	ret = rand() % 1000;
	return ret;
}

void count(Count* countp, int a)   //���������׼�����
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
		//������Ǻ����ǳ���ͬʱ�����������bug���Ȼ�Ҫ���һ��
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
	printf("\n\n������Ʒ������ó�������Ϊ��%lf\n",average4);
	printf("������Ʒ������ó�������Ϊ��%lf\n",average5);
	printf("������Ʒ������ó�������Ϊ��%lf\n",variance);
}

void fourstars(name name)
{
	int result0 = random();
	if (result0 >= 500)
	{
		printf("����");
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
	printf("����");
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
			printf("%s", "����");
		}
		if (result2 == 2)
		{
			printf("%s", "��");
		}
		if (result2 == 3)
		{
			printf("%s", "Ī��");
		}
		if (result2 == 4)
		{
			printf("%s", "����");
		}
		if (result2 == 0)
		{
			printf("%s", "��¬��");
		}
	}
}