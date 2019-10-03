#include <stdio.h>
#include <string.h>
#include <assert.h>

size_t My_strlen1(const char *str)
{
	//size_t�Ǳ�׼C���ж���ģ�ӦΪunsigned int����64λϵͳ��Ϊ long unsigned int��
	//size_t�е�t��type�����ͣ�����˼��size_t����˼��size of type����ĳ�����͵Ĵ�С���ֽ�����
	size_t count = 0;
	if (str == NULL)
	{
		return 0;
	}

	while (*str != '\0')
	{
		count++;
		//str��һ���ַ���ָ�룬ÿ��ָ����һ��
		str++;
	}
	return count;
}

size_t My_strlen2(const char *str)
{
	//����eosָ���ַ�����ͷ����Ȼ���ƶ���ĩβ
	//���ĩβ��ͷ�����ڼ�'\0'
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
	//�����Ӵ����еݹ����
	//���������
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
	//����ֻ�ڵ��԰汾��Ч�����Ϊ�����׳��쳣
	//release�汾��ȡ����debug����
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
	static unsigned char* last;//����ָ�����ַ���
	unsigned char* str;//���ص��ַ���
	const unsigned char* ctrl = (const unsigned char*)demial;//�ָ���

	//���ָ��������������С�����32����ΪASCII�ַ��������0~255����Ҳ��˵������255����3λ��Ҳ���ǳ���8һ������32�е�һ������
	unsigned char map[32];
	int count;

	//��map��0��֮�������������0�Ķ�Ϊ0
	for (count = 0; count < 32; count++)
	{
		map[count] = 0;
	}

	//��ƥ���ַ�������У�
	//������㷨�ǰ�ƥ����ַ�������λ���൱�ڳ���8������ֵ������
	//ƥ���ַ���7���õ�����λ���õ��Ľ���ǰ�1���Ƶ�λ�����������λ����7��
	//Ҳ�������ܱ�ʾ�����ֵ127
	do
	{
		map[*ctrl >> 3] |= (1 << (*ctrl & 7));
	} while (*ctrl++);

	/*
	ԭʼ�ַ����Ƿ�Ϊ�գ����Ϊ�ձ�ʾ�ڶ��λ�ȡ��ʣ���ַ��ķָ�����
	*/
	if (string_org)
	{
		str = (unsigned char*)string_org;
	}
	else
	{
		str = last;
	}

	//���б��в����Ƿ���ƥ����ַ���������Թ�
	while ((map[*str >> 3] & (1 << (*str & 7))) && *str)
	{
		str++;
	}

	//������Ҫɨ����ַ���
	string_org = (char*)str;

	//��ʼɨ��
	for (; *str; str++)
	{
		if (map[*str >> 3] & (1 << (*str & 7)))
		{
			*str++ = '\0';
			break;
		}
	}

	last = str;//��ʣ��ı��浽��̬����last��
	if (string_org == (char*)str)
	{
		return NULL;//û���ҵ���Ҳ�����ƶ�ָ���λ��
	}
	else
	{
		return string_org;//�ҵ��ˣ�����֮ǰ�ַ�����ͷָ��
	}
}


char*  My_strtok_r2(char* string_org, const char* demial, char** last)
{
	const char* spanp; //span��ʾ�ָ���p��ʾָ��
	char c, sc; //c��ʾchar�ַ���sc��ʾ span char
	char* tok;  //token��ʾ�ָ��Ķ�
	//����ʼ��β��ΪNULL��ʱ��˵��û���ַ������ң����Է���NULL
	if (string_org == NULL && (string_org = *last) == NULL)
	{
		return (NULL);
	}
	//��goto��ɵ�ѭ������ɨ���ַ�����ʱ�򣬵���������Ҫƥ����ַ�ʱ���Թ�����ַ���        
count:
	c = *string_org++;
	for (spanp = demial; (sc = *spanp++) != 0; )
	{
		if (c == sc)
		{
			goto count;
		}
	}
	//��һ���ַ�Ϊ0�����ʾ�����������������last��ΪNULL��������NULL            
	if (c == 0)
	{
		*last = NULL;
		return (NULL);
	}
	//��ԭʼ���ַ���ָ����ˡ�            
	tok = string_org - 1;
	//��ʼɨ���ַ������Ƿ���Ҫƥ����ַ���֮������ƥ���ַ�֮ǰ�Ĳ��ַ��ء�
	//�⿴���Ǹ�����ѭ��������Դ�ַ�����ƥ���ַ������ߵ���βʱ��Ҳ����string_org��sc��ΪNULLʱ�������ѭ�������ߵ�return(tok)����ѭ����
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
	//ѭ���ȵݹ���ã��漰ջ�ͺ�������Լ����
	//�ں˲��Ͻ�ʹ�õݹ�
	//һ��Ҫ�Բ����ĺϷ��Խ�����֤
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