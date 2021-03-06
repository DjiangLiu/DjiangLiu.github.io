#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void get_filename(const char *path, char *buf, int min_len)
{
	strcpy_s(buf, min_len, strrchr(path, '\\') + 1);
	printf("%s\n", buf);
}

void get_gx(char *url, char *buf, int min_len)
{
	const char *delim = "?&";
	char *next = NULL;

	char *p1 = strtok_s(url, delim, &next);
	while (p1 != NULL)
	{
		p1 = strtok_s(NULL, delim, &next);
		char *p2 = strstr(p1, "wd=");
		//此处有bug尚未解决
		if (p2 != NULL)
		{
			strcpy_s(buf, min_len, p2);
			printf("%s\n", buf);
		}

	}
}

void IntToBin(int a)
{
	int i = 0;
	int sum = 0;
	int array[8] = { 0 };//创建一个八个元素的数组，只是为了在输出时完全以二进制序列的形式输出，否则为逆序。
	for (i=0; i<8; i++)//八位二进制序列，因此控制八次
	{
		sum = a & 1;//与1便得到这个数的最后一位
		if (sum == 1)
		{
			array[i] = 1;
		}
		else
		{
			array[i] = 0;
		}
		a = a >> 1;//更新这个二进制序列
	}
	for (i=7; i>=0; i--)//逆序输出
	{
		printf("%d", array[i]);
	}
	//printf("\n");
}

void IPv4ToInt(char *ip)
{
		
		//分隔符可以用多种
		const char *delim = ".";
		char *next = NULL;

		char *p2 = strtok_s(ip, delim, &next);
		while (p2 != NULL)
		{
			//printf("%x\n", atoi(p2));
			IntToBin(atoi(p2));
			p2 = strtok_s(NULL, delim, &next);
		}
}

int main(void)
{
	const char *path = "c:\\doc\\test.txt";
	char buf1[128] = { 0 };
	char buf2[128] = { 0 };

	int min_len = sizeof(buf1) > strlen(path) ? strlen(path) : sizeof(buf1) - 1;
	//copy长度应小于等于buf-1，最后一个'\0'
	get_filename(path, buf1, min_len);

	char url[] = "https://www.baidu.com/baidu?wd=mallocfree&tn=monline_4_dg&ie=utf-8";
	//get_gx(url, buf2, strlen(url));

	char ip[] = "192.168.1.254";
	IPv4ToInt(ip);

	getchar();
	return 0;
}