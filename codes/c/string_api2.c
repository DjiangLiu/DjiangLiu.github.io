#include <stdio.h>
#include <string.h>
#include <assert.h>

size_t My_strlen1(const char *str)
{
	//size_t是标准C库中定义的，应为unsigned int，在64位系统中为 long unsigned int。
	//size_t中的t是type（类型）的意思。size_t的意思是size of type，即某种类型的大小（字节数）
	size_t count = 0;
	if (str==NULL)
	{
		return 0;
	}
	
	while (*str!='\0')
	{
		count++;
		//str是一个字符串指针，每次指向下一个
		str++;
	}
	return count;
}

size_t My_strlen2(const char *str)
{
	//先用eos指向字符串的头部，然后移动到末尾
	//最后末尾减头部，在减'\0'
	if (str==NULL)
	{
		return 0;
	}
	
	const char *eos = str;
	while (*eos++);
	return (size_t)(eos - str - 1);
}

size_t My_strlen3(const char *str)
{
	//利用子串进行递归查找
	//最简子问题
	if (str==NULL||*str=='\0')
	{
		return 0;
	}
	return 1+My_strlen3(str+1);
}

size_t My_strlen4(const char *str)
{
	return (str==NULL||*str=='\0')?0:1+My_strlen4(str+1);
}

char *My_strcpy(char *dst,const char *src)
{
	char *s=dst;
	while (*s++=*src++);
	return dst;	
}

int My_strcmp(const char *s1,const char *s2)
{
	//断言只在调试版本有效，如果为假则抛出异常
	//release版本已取消，debug可用
	//assert(s1!=NULL&&s2!=NULL);
	if (s1==NULL||s2==NULL)
	{
		return 0;
	}
	while (*s1&&*s2&&(*s1==*s2))
	{
		s1++;
		s2++;
	}
	return *s1-*s2;	
}

int main(void)
{
	//循环比递归更好，涉及栈和函数调用约定。
	//内核层严禁使用递归
	//一定要对参数的合法性进行验证
	const char *str = "hello world";
	const char *str2 = "hello world";
	char buf[128] = {0};
	My_strcpy(buf,str);
	printf("%s\n",buf);

	if(My_strcmp(str,str2)==0)
	{
		printf("str == str2\n");
	}
	else
	{
		printf("str != str2\n");
	}
	

	printf("%d\n",sizeof(size_t));
	printf("%d\n",My_strlen1(str));
	printf("%d\n",My_strlen2(str));
	printf("%d\n",My_strlen3(str));
	printf("%d\n",My_strlen4(str));
	printf("%d\n",strlen(str));
	getchar();
	return 0;
}