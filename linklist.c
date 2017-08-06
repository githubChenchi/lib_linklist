#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"
#include "log.h"

//linklist init
OSStatus linklist_init(linklist_handler_t * linklist_handler)
{
    OSStatus err = kNoErr;

    if(! linklist_handler)
    {
        err = kGeneralErr;
		sys_log("[linklist_handler] can not be NULL");
		goto exit;
    }

    *linklist_handler = malloc(sizeof(linklist_t));
    if(! *linklist_handler)    //malloc fail
    {
        err = kGeneralErr;
		sys_log("malloc fail");
		goto exit;
    }
    memset(*linklist_handler, 0, sizeof(linklist_t));
    (*linklist_handler)->header = malloc(sizeof(linklist));
    if(! (*linklist_handler)->header)
    {
        err = kGeneralErr;
		sys_log("malloc fail");
		goto exit;
    }
    memset((*linklist_handler)->header, 0, sizeof(linklist));

    exit:
    return err;
}

//push to the linklist
OSStatus linklist_push(linklist_handler_t * linklist_handler, push_dir_t dir, data_t * data, datasize_t size)
{
    OSStatus err = kNoErr;

    if(! linklist_handler)
    {
        err = kGeneralErr;
		sys_log("[linklist_handler] can not be NULL");
		goto exit;
    }    

    if(! *linklist_handler)
    {
        err = kGeneralErr;
		sys_log("invalid linklist handler");
		goto exit;
    }

    switch(dir)
    {
        case DIR_FIFO:  //push to tail
            (*linklist_handler)->cur_node = malloc(sizeof(linklist) - 1 + size);
            if(! (*linklist_handler)->cur_node)
            {
                err = kGeneralErr;
				sys_log("malloc fail");
				goto exit;
            }
            memcpy((*linklist_handler)->cur_node->data, data, size);
            (*linklist_handler)->cur_node->size = size;
            if((*linklist_handler)->header->next == NULL)
            {
                (*linklist_handler)->header->next = (*linklist_handler)->cur_node;
            }
            else
            {
                 (*linklist_handler)->pre_node->next = (*linklist_handler)->cur_node;
            }
            (*linklist_handler)->pre_node = (*linklist_handler)->cur_node;
            (*linklist_handler)->pre_node->next = NULL;
            (*linklist_handler)->node_size++;
        break;

        case DIR_FILO:  //push to head
            (*linklist_handler)->cur_node = malloc(sizeof(linklist) - 1 + size);
            if(! (*linklist_handler)->cur_node)
            {
                err = kGeneralErr;
				sys_log("malloc fail");
				goto exit;
            }
            memcpy((*linklist_handler)->cur_node->data, data, size);
            (*linklist_handler)->cur_node->size = size;
            (*linklist_handler)->cur_node->next = (*linklist_handler)->header->next;
            (*linklist_handler)->header->next = (*linklist_handler)->cur_node;
            (*linklist_handler)->node_size++;
        break;

        default:
            sys_log("illegal linklist inserting direction");
            err = kGeneralErr;
        break;
    }

    exit:
    return err;
}


//pop from head
OSStatus linklist_pop(linklist_handler_t * linklist_handler, data_t * * data_pp, data_t * data_len)
{
    OSStatus err = kNoErr;

    if(! linklist_handler)
    {
        err = kGeneralErr;
		sys_log("[linklist_handler] can not be NULL");
		goto exit;
    }    

    if(! *linklist_handler)
    {
        err = kGeneralErr;
		sys_log("invalid linklist handler");
		goto exit;
    }

	if(! data_pp)
	{
		err = kGeneralErr;
		sys_log("[data_pp] can not be NULL");
		goto exit;
	}

    if((*linklist_handler)->header->next)   //node exsit
    {    
		*data_len = (*linklist_handler)->header->next->size;
        *data_pp = malloc(*data_len);
		memcpy(*data_pp, (*linklist_handler)->header->next->data, *data_len);

		linklist * temp_node = (*linklist_handler)->header->next;

		(*linklist_handler)->header->next = temp_node->next;
		(*linklist_handler)->node_size--;

		memset(temp_node, 0, sizeof(linklist) - 1 + temp_node->size);
		free(temp_node);
    }
    else
    {
        err = kGeneralErr;
		sys_log("linklist node is not exsit");
		goto exit;
    }

    exit:
    return err;
}

//llinklist get node size
OSStatus linklist_get_nodeSize(linklist_handler_t * linklist_handler, nodesize_t * nodeSize)
{
    OSStatus err = kNoErr;

    if(! linklist_handler)
    {
		err = kGeneralErr;
        sys_log("para can not be NULL");
		goto exit;
    }    

    if(! *linklist_handler)
    {
		err = kGeneralErr;
        sys_log("invalid linklist handler");
		goto exit;
    }

    if(! nodeSize)
    {
		err = kGeneralErr;
        sys_log("para can not be NULL");
		goto exit;
    }
    
    *nodeSize = (*linklist_handler)->node_size;

	exit:
    return err;
}

//linklist node find
OSStatus linklist_node_find(linklist_handler_t * linklist_handler, uint32_t i, linklist * * dest_node)
{
    OSStatus err = kNoErr;

    if(! linklist_handler)
    {
        err = kGeneralErr;
		sys_log("para can not be NULL");
		goto exit;
    }    

    if(! *linklist_handler)
    {
        err = kGeneralErr;
		sys_log("invalid linklist handler");
		goto exit;
    }

    linklist * temp_node = (*linklist_handler)->header->next;

    if(i >= (*linklist_handler)->node_size)
    {
        err = kGeneralErr;
		sys_log("linklist node is not exsit");
		goto exit;
    }

    for(int j=0; j<=i; j++)
    {
        if(j == i)
        {
            *dest_node = temp_node;
            break;
        }
        temp_node = temp_node->next;
    }

    exit:
    return err;
}

//delete a node from the linklist, i starts from 0
OSStatus linklist_node_delete(linklist_handler_t * linklist_handler, uint32_t i)
{
    OSStatus err = kNoErr;

    if(! linklist_handler)
    {
        err = kGeneralErr;
		sys_log("para can not be NULL");
		goto exit;
    }    

    if(! *linklist_handler)
    {
        err = kGeneralErr;
		sys_log("invalid linklist handler");
		goto exit;
    }

    if(i >= (*linklist_handler)->node_size)
    {
        err = kGeneralErr;
		sys_log("linklist node is not exsit");
		goto exit;
    }

    linklist * temp_node = (*linklist_handler)->header->next;
    linklist * pre_node_i = NULL;
    linklist * next_node_i = NULL;

    if(i == 0)  //node i is the first one, has no pre node
    {
        (*linklist_handler)->header->next = (*linklist_handler)->header->next->next;
    }
    else
    {
        linklist_node_find(linklist_handler, i-1, &pre_node_i);
        err = linklist_node_find(linklist_handler, i+1, &next_node_i);
        if(err != kNoErr)   //node i is the last one, has no next node
        {
            pre_node_i->next = NULL;
        }
        else
        {
            pre_node_i->next = next_node_i;
        }
    }

    for(int j=0; j<=i; j++)
    {        	        
        if(j == i)
        {
			if(temp_node == NULL)
			{
				err = kGeneralErr;				
				sys_log("current node is null");
				goto exit;
			}
			memset(temp_node, 0, sizeof(linklist) - 1 + temp_node->size);
            free(temp_node);
            (*linklist_handler)->node_size--;
            break;
        }
        temp_node = temp_node->next;
    }

    exit:
    return err;
}

//linklist empty
OSStatus linklist_empty(linklist_handler_t * linklist_handler)
{
    OSStatus err = kNoErr;
    nodesize_t node_num = 0;

    if(! linklist_handler)
    {
        err = kGeneralErr;
		sys_log("para can not be NULL");
		goto exit;
    }    

    if(! *linklist_handler)
    {
        err = kGeneralErr;
		sys_log("invalid linklist handler");
		goto exit;
    }
    
    node_num = (*linklist_handler)->node_size;

    for(int i=0; i<node_num; i++)
    {
        linklist_node_delete(linklist_handler, 0);
    }

	exit:
    return err;
}

//linklist deinit
OSStatus linklist_deinit(linklist_handler_t * linklist_handler)
{
    OSStatus err = kNoErr;
    nodesize_t node_num = 0;

    if(! linklist_handler)
    {
        err = kGeneralErr;
		sys_log("para can not be NULL");
		goto exit;
    }    

    if(! *linklist_handler)
    {
        err = kGeneralErr;
		sys_log("invalid linklist handler");
		goto exit;
    }

    err = linklist_empty(linklist_handler);
    if(err != kNoErr)
    {
        err = kGeneralErr;
		sys_log("linklist empty fail");
		goto exit;
    }

    memset(*linklist_handler, 0, sizeof(linklist_t));
    free(*linklist_handler);
    * linklist_handler = NULL;

	exit:
    return err;
}

