#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[30];
	char tel_num[30];
} Data;

int cnt = 0;
int len = 5;


int Insert(Data * self)
{
	char name[30];
	char number[30];
	printf("[Insert]\n");
	printf("Input Name: ");
	scanf("%s", name);
	printf("Input Tel Number: ");
	scanf("%s", number);
	printf("\n");

	strcpy(self[cnt].name, name);
	strcpy(self[cnt].tel_num, number);
}

int Delete(Data*save2)
{
	int i = 0;
	char name[30];
	printf("[Delete]\n");
	printf("Input Name: ");
	scanf("%s", name);
	for(i;i<cnt;i++) {
		if(strcmp(save2[i].name, name)==0){
			break;
		}
	}
	while (i < cnt)
	{
		strcpy(save2[i].name, save2[i + 1].name);
		strcpy(save2[i].tel_num, save2[i + 1].tel_num);
		i++;
	}

}

int Search(Data*list)
{
	char name[30];
	printf("[Search]\n");
	printf("Input Name: ");
	scanf("%s", name);
	for (int i = 0; i < cnt; i++) {
		if (strcmp(list[i].name, name)==0) {
			printf("Name: %s    Tel Num: %s\n\n", list[i].name, list[i].tel_num);
			break;
		}
	}
	
}

int Print_all(Data * save)
{
	printf("[Print All]\n");
	for (int i = 0; i < cnt; i++) {
		printf("Name:%s   Tel Num:%s\n\n", save[i].name, save[i].tel_num);
	}
}


int main()
{
		Data* info = (Data*)malloc(sizeof(Data) * len);
		
	


	char input[30];

	int num = 0, flag = 0;
	int j = 0;
	int ret;

	FILE* ptr1 = NULL;
	FILE* ptr2 = fopen("text1.txt", "rt");

	while (1) {
		ret = fscanf(ptr2,"%s %s", info[j].name, info[j].tel_num);
		if (ret == EOF)
			break;
		cnt++;
		if (cnt == len) {
			len += 3;
			Data* new_size;
			new_size = (Data*)malloc(sizeof(Data) * len);
			for (int i = 0; i < cnt; i++) {
				new_size[i] = info[i];
			}
			info = new_size;
			free(new_size);
		}
		j++;
	}

	while (1) {
		
		printf("***** MENU *****\n");
		printf("1.Insert\n");
		printf("2.Delete\n");
		printf("3.Search\n");
		printf("4.Print all\n");
		printf("5.Exit\n");
		printf("Choose the item: ");
		fgets(input, sizeof(input), stdin);
		input[strlen(input) - 1] = 0;
		num = input[0] - '0';
		
		
		while (!(num >= 1 && num <= 5)||strlen(input)>=2)
		{
			printf("다시 입력!!!\n");
			fgets(input, sizeof(input), stdin);
			input[strlen(input) - 1] = 0;
			num = input[0] - '0';
			flag = 0;
		}
		printf("c:%d l:%d\n", cnt, len);
		if (cnt == len) {
			len += 3;
			Data* new_size = (Data*)malloc(sizeof(Data) * len);
			/*for (int i = 0; i < cnt; i++) {
				strcpy(new_size[i].name, info[i].name);
				strcpy(new_size[i].tel_num, info[i].tel_num);
			}*/
			memcpy(new_size, info, cnt * sizeof(Data));
			free(info);
			info = new_size;
			//free(new_size);
		}
		printf("\n");

		switch (num)
		{
		case 1:
			
			
			Insert(info);
			cnt++;
			flag = 1;
			break;
		case 2:
			Delete(info);
			cnt--;
			flag = 1;
			break;
		case 3:
			Search(info);
			flag = 1;
			break;
		case 4:
			Print_all(info);
			flag = 0;
			break;
		case 5:
			ptr1 = fopen("text1.txt", "wt");
			for (int i = 0; i < cnt; i++) {
				fprintf(ptr1, "%s ", info[i].name);
				fprintf(ptr1,"%s \n",info[i].tel_num);
			}
			free(info);
			return 0;
		default:

			break;
		}
		if (flag == 1)
			while (getchar() != '\n');
		
	}

	fclose(ptr1);
	fclose(ptr2);
	return 0;
}