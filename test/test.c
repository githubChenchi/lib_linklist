#include <stdio.h>
#include <string.h>
#include "linklist.h"
#include "log.h"

void test_push_pop(void)
{
	OSStatus err = kNoErr;	
	linklist_handler_t linklist_handler = NULL;
	data_t * data = NULL;
	data_t buf[10] = {0};

	err = linklist_init(&linklist_handler);
	if(err != kNoErr)
	{
		sys_log("linklist init error");
		goto exit;
	}

	for(int i=0; i<3; i++)
	{
		switch(i)		
		{
			case 0:
				strcpy(buf, "123");
				break;
		
			case 1:
				strcpy(buf, "3456");
				break;

			case 2:
				strcpy(buf, "7890");
				break;
		}

		err = linklist_push(&linklist_handler, DIR_FIFO, buf, strlen(buf));
		if(err != kNoErr)
		{
			sys_log("linklist push error");
			goto exit;
		}
		sys_log("push node is: %s, node size is: %d", buf, linklist_handler->node_size);
	}

	for(int i=0; i<4; i++)
	{
		err = linklist_pop(&linklist_handler, &data);
		if(err != kNoErr)
		{
			sys_log("linklist pop error");
			goto exit;
		}	
		sys_log("pop node is: %s, left size is: %d", data, linklist_handler->node_size);
	}

exit:
	sys_log("######## Done !");
}

void test_push_find(void)
{
	OSStatus err = kNoErr;	
	linklist_handler_t linklist_handler = NULL;
	linklist * node_to_find = NULL;
	data_t buf[10] = {0};

	err = linklist_init(&linklist_handler);
	if(err != kNoErr)
	{
		sys_log("linklist init error");
		goto exit;
	}

	for(int i=0; i<3; i++)
	{
		switch(i)		
		{
			case 0:
				strcpy(buf, "123");
				break;
		
			case 1:
				strcpy(buf, "3456");
				break;

			case 2:
				strcpy(buf, "7890");
				break;
		}

		err = linklist_push(&linklist_handler, DIR_FIFO, buf, strlen(buf));
		if(err != kNoErr)
		{
			sys_log("linklist push error");
			goto exit;
		}
		sys_log("push node is: %s, node size is: %d", buf, linklist_handler->node_size);
	}

	for(int i=0; i<4; i++)
	{
		err = linklist_node_find(&linklist_handler, i, &node_to_find);
		if(err != kNoErr)
		{
			sys_log("linklist node find error");
			goto exit;
		}
		sys_log("find node is: %s, left size is: %d", node_to_find->data, linklist_handler->node_size);		
	}

exit:
	sys_log("######## Done !");
}

void test_push_delete(void)
{
	OSStatus err = kNoErr;	
	linklist_handler_t linklist_handler = NULL;
	linklist * node_to_find = NULL;
	data_t buf[10] = {0};

	err = linklist_init(&linklist_handler);
	if(err != kNoErr)
	{
		sys_log("linklist init error");
		goto exit;
	}

	for(int i=0; i<3; i++)
	{
		switch(i)		
		{
			case 0:
				strcpy(buf, "123");
				break;
		
			case 1:
				strcpy(buf, "3456");
				break;

			case 2:
				strcpy(buf, "7890");
				break;
		}

		err = linklist_push(&linklist_handler, DIR_FIFO, buf, strlen(buf));
		if(err != kNoErr)
		{
			sys_log("linklist push error");
			goto exit;
		}
		sys_log("push node is: %s, node size is: %d", buf, linklist_handler->node_size);
	}

	for(int i=0; i<4; i++)
	{		
		err = linklist_node_delete(&linklist_handler, 0);
		if(err != kNoErr)
		{
			sys_log("linklist node delete error");
			goto exit;
		}
		sys_log("delete node ok, left size is: %d", linklist_handler->node_size);

		err = linklist_node_find(&linklist_handler, 0, &node_to_find);
		if(err != kNoErr)
		{
			sys_log("linklist node find error");
			goto exit;
		}
		sys_log("find node is: %s, left size is: %d", node_to_find->data, linklist_handler->node_size);		
	}

exit:
	linklist_deinit(&linklist_handler);
	sys_log("######## Done !");
}
