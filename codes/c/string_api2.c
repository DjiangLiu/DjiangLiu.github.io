#include <stdio.h>
#include <string.h>
#include <assert.h>

size_t My_strlen1(const char *str)
{
	//size_t是标准C库中定义的，应为unsigned int，在64位系统中为 long unsigned int。
	//size_t中的t是type（类型）的意思。size_t的意思是size of type，即某种类型的大小（字节数）
	size_t count = 0;
	if (str == NULL)
	{
		return 0;
	}

	while (*str != '\0')
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
	if (str == NULL)
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
	if (str == NULL || *str == '\0')
	{
		return 0;
	}
	return 1 + My_strlen3(str + 1);
}

size_t My_strlen4(const char *str)
{
	return (str == NULL || *str == '\0') ? 0 : 1 + My_strlen4(str + 1);
}

char *My_strcpy(char *dst, const char *src)
{
	char *s = dst;
	while (*s++ = *src++);
	return dst;
}

int My_strcmp(const char *s1, const char *s2)
{
	//断言只在调试版本有效，如果为假则抛出异常
	//release版本已取消，debug可用
	//assert(s1!=NULL&&s2!=NULL);
	if (s1 == NULL || s2 == NULL)
	{
		return 0;
	}
	while (*s1&&*s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

char *My_strtok_r1(char* string_org, const char* demial)
{
	static unsigned char* last;//保存分隔后的字符串
	unsigned char* str;//返回的字符串
	const unsigned char* ctrl = (const unsigned char*)demial;//分隔符

	//将分隔符放在索引表中。定义32是因为ASCII字符表最多是0~255个，也是说用最大的255右移3位，也就是除以8一定会是32中的一个数。
	unsigned char map[32];
	int count;

	//把map清0，之后相与操作，与0的都为0
	for (count = 0; count < 32; count++)
	{
		map[count] = 0;
	}

	//把匹配字符放入表中，
	//放入的算法是把匹配的字符右移三位，相当于除以8，的数值并加上
	//匹配字符与7，得到低三位，得到的结果是把1左移的位数，最大左移位数是7，
	//也就是所能表示的最大值127
	do
	{
		map[*ctrl >> 3] |= (1 << (*ctrl & 7));
	} while (*ctrl++);

	/*
	原始字符串是否为空，如果为空表示第二次获取的剩余字符的分隔部分
	*/
	if (string_org)
	{
		str = (unsigned char*)string_org;
	}
	else
	{
		str = last;
	}

	//在列表中查找是否有匹配的字符，如果有略过
	while ((map[*str >> 3] & (1 << (*str & 7))) && *str)
	{
		str++;
	}

	//重置需要扫描的字符串
	string_org = (char*)str;

	//开始扫描
	for (; *str; str++)
	{
		if (map[*str >> 3] & (1 << (*str & 7)))
		{
			*str++ = '\0';
			break;
		}
	}

	last = str;//把剩余的保存到静态变量last中
	if (string_org == (char*)str)
	{
		return NULL;//没有找到，也就是移动指针的位置
	}
	else
	{
		return string_org;//找到了，返回之前字符串的头指针
	}
}


char*  My_strtok_r2(char* string_org, const char* demial, char** last)
{
	const char* spanp; //span表示分隔，p表示指针
	char c, sc; //c表示char字符，sc表示 span char
	char* tok;  //token表示分隔的段
	//当开始结尾都为NULL的时候，说明没有字符被查找，所以返回NULL
	if (string_org == NULL && (string_org = *last) == NULL)
	{
		return (NULL);
	}
	//由goto组成的循环是在扫描字符串的时候，当遇到所需要匹配的字符时，略过这个字符。        
count:
	c = *string_org++;
	for (spanp = demial; (sc = *spanp++) != 0; )
	{
		if (c == sc)
		{
			goto count;
		}
	}
	//下一个字符为0，则表示到达了搜索结果，把last置为NULL，并返回NULL            
	if (c == 0)
	{
		*last = NULL;
		return (NULL);
	}
	//把原始的字符串指针回退。            
	tok = string_org - 1;
	//开始扫描字符串中是否含有要匹配的字符，之后把这个匹配字符之前的部分返回。
	//这看似是个无限循环，但当源字符串和匹配字符串都走到结尾时，也就是string_org和sc都为NULL时，最外层循环最后会走到return(tok)结束循环。
	for (;;)
	{
		c = *string_org++;
		spanp = demial;
		do
		{
			if ((sc = *spanp++) == c)
			{
				if (c == 0)
				{
					string_org = NULL;
				}
				else
				{
					string_org[-1] = 0;
				}
				*last = string_org;
				return (tok);
			}
		} while (sc != 0);
	}
}


char* My_strtok(char *s, const char *delim)
{
	static char *lasts;
	return My_strtok_r2(s, delim, &lasts);
}

int main(void)
{
	//循环比递归更好，涉及栈和函数调用约定。
	//内核层严禁使用递归
	//一定要对参数的合法性进行验证
	const char *str = "hello world";
	const char *str2 = "hello world";
	char buf[128] = { 0 };
	My_strcpy(buf, str);
	printf("%s\n", buf);

	if (My_strcmp(str, str2) == 0)
	{
		printf("str == str2\n");
	}
	else
	{
		printf("str != str2\n");
	}



	printf("%d\n", sizeof(size_t));
	printf("%d\n", My_strlen1(str));
	printf("%d\n", My_strlen2(str));
	printf("%d\n", My_strlen3(str));
	printf("%d\n", My_strlen4(str));
	printf("%d\n", strlen(str));




	char str4[] = "- This, a sample string.";
	char * pch1;
	printf("Splitting string \"%s\" into tokens:\n", str4);
	pch1 = My_strtok_r1(str4, " ,.-");
	while (pch1 != NULL)
	{
		printf("%s\n", pch1);
		pch1 = My_strtok_r1(NULL, " ,.-");
	}


	char str5[] = "- This, a sample string.";
	char * pch;
	printf("Splitting string \"%s\" into tokens:\n", str5);
	pch = My_strtok(str5, " ,.-");
	while (pch != NULL)
	{
		printf("%s\n", pch);
		pch = My_strtok(NULL, " ,.-");
	}





	getchar();
	return 0;
}