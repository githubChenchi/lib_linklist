#pragma once

#include "type_define.h"

typedef enum 
{
    DIR_FIFO,
    DIR_FILO
} push_dir_t;

#define DIR_DEFAULT DIR_FIFO

typedef uint8_t data_t;

typedef uint32_t datasize_t;

typedef uint32_t nodesize_t;

typedef int32_t linklist_id_t;

#pragma pack(push)
#pragma pack(1)
typedef struct node
{
	struct node * next;
    datasize_t size;
    data_t data[1];
} linklist;
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    nodesize_t node_size;
    linklist * header;
    linklist * pre_node;
    linklist * cur_node;
    linklist * next_node;
} linklist_t;
#pragma pack(pop)

typedef linklist_t * linklist_handler_t;

extern OSStatus linklist_init(linklist_handler_t * linklist_handler);
extern OSStatus linklist_push(linklist_handler_t * linklist_handler, push_dir_t dir, data_t * data, datasize_t size);
extern OSStatus linklist_pop(linklist_handler_t * linklist_handler, data_t * * data_pp, data_t * data_len);
extern OSStatus linklist_get_nodeSize(linklist_handler_t * linklist_handler, uint8_t * nodeSize);
extern OSStatus linklist_node_find(linklist_handler_t * linklist_handler, uint32_t i, linklist * * dest_node);
extern OSStatus linklist_node_delete(linklist_handler_t * linklist_handler, uint32_t i);
extern OSStatus linklist_empty(linklist_handler_t * linklist_handler);
extern OSStatus linklist_deinit(linklist_handler_t * linklist_handler);
