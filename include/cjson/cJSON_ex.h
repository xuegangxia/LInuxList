#ifndef cJSON_EX__h
#define cJSON_EX__h

#include "cJSON.h"
#include "stdio.h"
#include "stdlib.h"

static inline int getItemInt(cJSON *item,char *field)
{
	cJSON *jvalue = NULL;
	int res = -1;
	if(item)
	{
		jvalue = cJSON_GetObjectItem(item,field);
		if(jvalue && jvalue->type == cJSON_Number) 
			res = jvalue->valueint;
	}
	return res;
}

static inline float getItemDouble(cJSON *item,char *field)
{
	cJSON *jvalue = NULL;
	float res = 0;
	if(item)
	{
		jvalue = cJSON_GetObjectItem(item,field);
		if(jvalue && jvalue->type == cJSON_Number) 
			res = jvalue->valuedouble;
	}
	return res;
}

static inline int getItemString(cJSON *item,char *field,char string[])
{
	cJSON *jvalue = NULL;
	int res = -1;
	if(item)
	{
		jvalue = cJSON_GetObjectItem(item,field);
		if(jvalue && jvalue->type == cJSON_String)
		{
			strcpy(string,jvalue->valuestring);
			res = 0;
		}
	}
	return res;
}



#endif