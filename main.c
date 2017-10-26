/*







*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cjson/cJSON.h"
#include "cjson/cJSON_ex.h"

#include "types.h"
#include "list.h"


struct list_head NodeListHead[HASHLISTLENTGH];

/**
 * @brief init list hash table head.
 *
 * @returns none.
 *
 */
void init_listtable(void)
{
	int headpos = 0;
	/*init list head*/
	for(headpos = 0; headpos < HASHLISTLENTGH;headpos++)
	{
		INIT_LIST_HEAD(&NodeListHead[headpos]);
	}
}

/**
 * @brief 根据字符串计算hash值.
 * @input 
 * @returns hash值.
 *
 */
int GetHash(char *string)
{
	int hash = 0;
	int flag = 0;
	char *p = NULL;
	int data16 = 0;
	p = string;
	while(*p != '\0')
	{
		if(flag)
		{
			data16 |=  (*p++)<<8;
		}
		else
		{
			data16 = (*p++);
		}
		hash ^= 0x9e3779b9 + (data16<<6) + (data16>>2);
		flag ^= 1;
	}
	hash = abs(hash);
	hash = hash % HASHLISTLENTGH;
	return hash;
}


/**
 * @brief : add member to hash table list.
 *
 * @returns 0:ok  -1:error.
 *
 */
int NodeAdd(NODE node,struct list_head *head)
{
	NODE *pnode = NULL;
	struct list_head *listhead = NULL;
	struct list_head *listpos = NULL;

	listhead = head;
	listpos = listhead->next;
	while(listpos != listhead)
	{	
		pnode = list_entry(listpos, NODE, list);
		if(0 == strcmp(pnode->name,node.name))
		{
			printf(" %s already exist\n",pnode->name);
			return -1;
		}
		listpos = listpos->next;
	}
	pnode = malloc(sizeof(NODE));
	if(pnode == NULL)
	{
		return -1;
	}
	strcpy(pnode->name, node.name);
	strcpy(pnode->id, node.id);
	list_add_tail(&pnode->list,head);
	return 0;
}


/**
 * @brief : remove listmember from list.
 *	@input : delete which list member from which list
 * @returns 0:ok  -1:error.
 *
 */
int NodeDel(struct list_head *listpos,struct list_head *head)
{
	NODE *pnode;
	if(list_empty_careful(head))
	{
		printf("error : empty list \n");
		return -1;
	}
	list_del(listpos);
	pnode = list_entry(listpos, NODE, list);
	free(pnode);
	pnode = NULL;
	return 0;
}

/**
 * @brief : delete and free memory from a list.
 * @input : delete which list,the head point of list 
 * @returns 0:ok  .
 *
 */
int DelAllNode(struct list_head *head)
{
	struct list_head *listhead = NULL;
	struct list_head *listpos = NULL;
	listhead = head;
	listpos = listhead->next;
	while(listpos != listhead)
	{	
		listpos = listpos->next;
		NodeDel(listpos->prev,head);
	}

	return 0;
}


/**
 * @brief : delete and free memory from tablelist.
 * @input : none
 * @returns 0:ok  .
 *
 */
int DelTableNode(void)
{
	int cnt;
	for(cnt = 0;cnt < HASHLISTLENTGH;cnt++)
	{
		DelAllNode(&NodeListHead[cnt]);
	}
	return 0;
}


int loadfile(void)
{
	char indata[1000];
	int errname,errid;
	FILE * pFile;
	cJSON *root_json =NULL;
	char name[100];
	char id[30];
	NODE node;
	int pos;
	pFile = fopen ("./indata" , "r");
	if (pFile == NULL)
	{
		return -1;
	}
	memset(indata, '\0', sizeof(indata));
	
	while(NULL != fgets (indata , 1000 , pFile))
	{
		root_json = cJSON_Parse(indata);
		if(root_json == NULL)
		{
			
			fprintf(stderr, "Parse Json Config Error before: [%s]\n",  cJSON_GetErrorPtr()); 
			fprintf(stderr, "[%s]\n", indata);  
			continue;
		}

		errname = getItemString(root_json,"name",name);
		errid = getItemString(root_json,"id",id);
		if(!errname && !errid)
		{
			strcpy(node.name,name);
			strcpy(node.id,id);
			pos = GetHash(node.name);
			NodeAdd(node, &NodeListHead[pos]);
		}

	}
	printf("load file end \n");
	fclose(pFile);
	unlink("./indata");
	return 0;
}


/**
 * @brief : print info of table list.
 * @input : none
 * @returns NONE  .
 *
 */
void PrintInfo(void)
{
	NODE *pnode = NULL;
	struct list_head *listhead = NULL;
	struct list_head *listpos = NULL;
	int hashval = 0;
	for(hashval = 0;hashval < HASHLISTLENTGH;hashval++)
	{
		listhead = &NodeListHead[hashval];
		listpos = listhead->next;
		while(listpos != listhead)
		{	
			pnode = list_entry(listpos, NODE, list);
			printf("    hashval:%d  id:%s name : %s \n",hashval,pnode->id,pnode->name);
			listpos = listpos->next;
		}
	}
}

/**
 * @brief : entry of program.
 * @input : none
 * @returns 0  .
 *
 */
int main(int argc, char *argv[])
{		
	init_listtable();
	
	while(1)
	{
		if(0 == loadfile())
		{
			printf("add \n");
			PrintInfo();
			DelTableNode();
			printf("del \n");
			PrintInfo();
		}
		sleep(5);
	}

	return 0;
}


