#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#include "DES.h"
#include "md5.h"

int createKey(char *keySrc, int len)
{
    if (keySrc == NULL || len == 0)
    {
        return -1;
    }

    char hash[33];
    md5_hash(&keySrc, 1, hash);
    snprintf(keySrc, 9, "%s", &hash[8]);
    return 0;
}

int main(int argc, char **argv)
{
	char *src = NULL;
	char *dst = NULL;
	int sel = -1;

	if (argc != 4)
	{
		printf("usage: cmd [0-enc/1-des] [src] [dst]\n");
		return -1;
	}

	sel = atoi(argv[1]);
	src = argv[2];
	dst = argv[3];

	if (!(sel == 0 || sel == 1))
	{
		printf("param argv[1] is not correct!\n");
		return -1;
	}
	
	if (src == NULL)
	{
		printf("param argv[2] is not correct!\n");
		return -1;
	}
	else if (access(src, F_OK) == -1)
	{
		printf("source file does not exist!\n");
		return -1;		
	}

	char mdes[128];
	char remdes[128];
	do
    {
		printf("input passwd:");
		system("stty -echo"); //关闭控制台输入显示
		scanf("%s", mdes);
		system("stty echo"); //打开控制台输入显示
		if (strlen(mdes) > sizeof(mdes))
		{
			printf("\npassword too long!\n");
			return -1;
		}

		//创建key
        if (createKey(mdes, strlen(mdes)) < 0)
        {
            printf("create key error\n");
            return -1;
        }

        if (0 == sel)
        {//加密时要输入２次确认
            printf("\nreinput passwd:");
            system("stty -echo");
            scanf("%s", remdes);
            system("stty echo");
            if (strlen(remdes) > sizeof(remdes))
            {
                printf("\npassword too long!\n");
                return -1;
            }

            if (createKey(remdes, strlen(remdes)) < 0)
            {
                printf("create key error\n");
                return -1;
            }

            //printf("\n%s, %s\n", mdes, remdes);

            if (0 != strcmp(mdes, remdes))
            {
                printf("\ntwo times input password not the same, please input again!!!\n");
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
	} while(1);
	
	printf("\n");
	int ret = 0;
	if(0 == sel)
	{
		ret = DES_Encrypt(src, mdes, dst);
		if (ret < 0) 
		{
			if (-1 == ret)
			{
				printf("Encrypt src err!\n");
			}
			else
			{
				printf("Encrypt dst err!\n");
			}
		} 
		else
		{
			printf("Encrypt done!\n");
		}
	}
	else
	{			
		ret = DES_Decrypt(src, mdes, dst);
		if (ret < 0) 
		{
			if (-3 == ret)
			{
				printf("Encrypt src err!\n");
			}
			else
			{
				printf("Encrypt dst err!\n");
			}
		} 
		else
		{
			printf("Decrypt done!\n");
		}
	}
	return 0;
}
