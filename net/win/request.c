#include "datatype.h"
#include <string.h>
#include <stdio.h>

#define TOKEN1 ' '
#define TOKEN2 ':'
#define TOKEN3 '?'
#define TOKEN4 '&'
#define TOKEN5 '='
#define OFFSET 2

char* get_line(char **s)
{
	char *p,*r = *s;
	for(;;)
	{
		if(**s == '\r' && *(*s+1)=='\n')
		{
			if(r != *s)
			{
				p = (char*)apr_memory_alloc(*s - r+1);
				strncpy(p,r,*s - r);
				p[*s - r] = '\0';
				*s += OFFSET;
				return p;
			}
			else
				return NULL;
		}
		else
			(*s)++;
	}
}

char * get_line_part(char **s,char token)
{
	char *r = *s;
	while(**s!='\0')
	{
		if(**s == token)
		{
			**s = '\0';
			(*s)++;
			return r;
		}
		else
			(*s)++;
	}
	*s = r; // it was not found
	return NULL;
}

int read_request_line(apr_hash_table *htable,char *s1)
{
	char *s2 = s1,*p;
	p = get_line_part(&s2,TOKEN1);
	if( p != NULL)
	{
		//get method of the http protocol	
		element *e = create_element(p,METHOD,strlen(p)+1);
		chained_hash_insert(htable,e);
	}
	p = get_line_part(&s2,TOKEN1);
	if( p != NULL)
	{
		//get url and parameters
		char *s3 = p;element *e;
		p = get_line_part(&s3,TOKEN3);
		if(p == NULL)
			p = s3; //drop the parameters! haha

		e = create_element(p,URI,strlen(p)+1);
		chained_hash_insert(htable,e);	
	}
	
	//get version of the http protocol 
	chained_hash_insert(htable,create_element(s2,PROTOCOL,strlen(s2)+1));	
}

int read_request_header(apr_hash_table *htable,char *s1)
{
	char *s2 = s1,*p;
	p = get_line_part(&s2,TOKEN2);
	if(p)
	{
		element *e = create_element(s2,p,strlen(s2)+1);
		chained_hash_insert(htable,e);
		return TRUE;
	}
	return FALSE;
}

void create_request_structure(request_t **p_request)
{
	*p_request = create_hash_table(sizeof(request_t));
	(*p_request)->header = create_hash_table(REQ_HASH_SIZ);
}

void destroy_request_structure(request_t **p_request)
{
	if((*p_request)->header != NULL)
		destroy_apr_hash_table((*p_request)->header);

	apr_memory_free(*p_request);
	*p_request = NULL;
}

void read_request(request_t *p_request,char *buffer,int len)
{ 
	int i = 0;
	char *s = buffer,*p;

	while((p =get_line(&s))!=NULL)
	{
		if(i == 0)
			read_request_line(p_request->header,p);
		else
			read_request_header(p_request->header,p);
		i++;
		apr_memory_free(p);
	}
}
