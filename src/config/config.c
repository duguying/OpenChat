/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include "config.h"

/**
 * @brief config initial
 * @details this function not alloc memory for conf* config
 * 
 * @param config_file [description]
 * @return config file handle
 */
conf* config_init(const char* config_file,conf* config){
	struct stat buf;
	
	memset(config,0,sizeof(conf));
	memset(&buf,0,sizeof(struct stat));
	stat(config_file,&buf);
	config->size=buf.st_size;
	config->config_handle=open(config_file, O_RDONLY);
	config->content=(char*)malloc(buf.st_size*sizeof(char));
	read(config->config_handle,config->content,buf.st_size);
	return config;
}

char* config_get(int config_handle, const char* key)
{
	char* rst=0;
	return rst;
}

/**
 * @brief remove the comment of config file
 * @details remove the comment of config file, the comment is begin with char #
 * 
 * @param config the struct pointer of config
 * @return the struct pointer of config, but carefully if you want to assignment
 */
void* config_remove_comment(conf* config){
	int i=0,j=0,tag=0,length=0;
	char* final=NULL;
	char* tmp=(char*)malloc(sizeof(char)*config->size);
	for (i = 0; i < config->size; ++i)
	{
		if ('#'==*(config->content+i))
		{
			tag=1;
		}else if('\n'==*(config->content+i)){
			tag=0;
			tmp[j]=*(config->content+i);
			j++;
		}else{
			if (tag==0)
			{
				tmp[j]=*(config->content+i);
				j++;
			}else{
			}
		}
	}
	length=strlen(tmp);
	final=(char*)malloc(length*sizeof(char));
	strncpy(final,tmp,length);
	free(tmp);
	tmp=NULL;
	free(config->content);
	config->content=final;
	config->size=length;
	return config;
}

/**
 * @brief remove the empty chars
 * @details [long description]
 * 
 * @param config config the struct pointer of config
 * @return [description]
 */
void* config_strip(conf* config){
	int i=0,j=0;
	char* final=NULL;
	char* tmp=(char*)malloc(sizeof(char)*config->size);

	memset(tmp,0,sizeof(char)*config->size);
	for (i = 0; i < config->size; ++i)
	{
		if (i==0)
		{
			tmp[j]=*(config->content+i);
			j++;
		}

		if ('\n'==*(config->content+i)||' '==*(config->content+i))
		{
			if (*(config->content+i)!=tmp[j-1])
			{
				tmp[j]=*(config->content+i);
				j++;
			}
		}else{
			if ('\r'!=*(config->content+i))
			{
				tmp[j]=*(config->content+i);
				j++;
			}
		}
	}
	config->size=strlen(tmp);
	final=(char*)malloc(sizeof(char)*config->size);
	strncpy(final,tmp,config->size);
	free(tmp);
	tmp=NULL;
	free(config->content);
	config->content=final;
	return config;
}

/**
 * @brief get config value line by line
 * @details [long description]
 * 
 * @param config [description]
 * @return [description]
 */
void* config_lines(conf* config){
	;
}

/**
 * @brief equation expression parse
 * @details [long description]
 * 
 * @param config [description]
 * @return [description]
 */
void* config_equation(conf* config){
	;
}

/**
 * @brief destroy the config
 * @details destroy the config struct and free the memory
 * 
 * @param config config struct
 */
void config_destroy(conf* config){
	free(config->content);
	config->content=NULL;
}