# API说明手册

---

## 1. 概述  

&emsp;&emsp;实现了动态单链表的基本操作（包括push、pop、find和delete），支持先进先出和后进先出两种压栈方式；理论上可以最大添加（2^32-1）个链表节点，每个节点大小动态变化，取决于压栈数据的内存大小。  

&emsp;&emsp;该库使用GCC编译，亲测OK。test文件夹内附有测试例程，如果在其它编译器下，编译出现问题，或不能正常运行，请根据所使用的编译器，优化代码。  

&emsp;&emsp;如果有需要优化的地方，或因为需要支持其它编译器而改变了代码，请新建分支，并提pull request，一起为开源做出贡献，谢谢！  

## 2. 基本数据类型和常量  

&emsp;&emsp;链表中用到的所有基本数据类型和常量定义如下：  

	typedef unsigned char uint8_t;
	
	typedef signed char int8_t;
	
	typedef unsigned short uint16_t;
	
	typedef signed short int16_t;
	
	typedef unsigned int uint32_t;
	
	typedef signed int int32_t;
	
	typedef int32_t OSStatus;
	
	#define kNoErr		(0)
	#define kGeneralErr	(-1)  

## 3. 链表结构体、控制块 及 句柄  

### 3.1 链表结构体  

	typedef struct node
	{
		struct node * next;
	    datasize_t size;
	    data_t data[1];
	} linklist;

&emsp;&emsp;单向链表，通过成员`next`指向下一个节点；  
&emsp;&emsp;由于是动态链表，链表节点的大小可变，通过成员`size`记录压栈数据大小；  
&emsp;&emsp;通过成员`data`作为可变长数据的起始地址。  

### 3.2 链表控制块  

	typedef struct
	{
	    nodesize_t node_size;
	    linklist * header;
	    linklist * pre_node;
	    linklist * cur_node;
	    linklist * next_node;
	} linklist_t;

&emsp;&emsp;链表控制块，成员`node_size`记录了链表中的节点总数；  
&emsp;&emsp;成员`header`记录了链表的头指针（PS: 头指针的成员`next`指向的下一个节点才是链表的第一个节点，标号为0）；  
&emsp;&emsp;剩下的三个成员是链表操作过程中需要的中间量，不必理会，具体用法可参见源码。

### 3.3 句柄

	typedef linklist_t * linklist_handler_t;  

&emsp;&emsp;链表的句柄，是指向链表控制块的指针。

## 4. API  

### &emsp;&emsp;4.1 创建链表  

### `OSStatus linklist_init(linklist_handler_t * linklist_handler)`  

#### &emsp;&emsp;参数  

		linklist_handler : 链表控制块的句柄指针  

#### &emsp;&emsp;返回值  

		链表创建的操作结果，kNoErr，成功，kGeneralErr，失败  

### &emsp;&emsp;4.2 数据入栈  

### `OSStatus linklist_push(linklist_handler_t * linklist_handler, push_dir_t dir, data_t * data, datasize_t size)`  

#### &emsp;&emsp;参数  
	
		linklist_handler : 链表控制块的句柄指针  
		dir : 链表节点的压栈方向  
		data : 待压栈的数据指针

#### &emsp;&emsp;返回值  

		链表节点压栈的操作结果，kNoErr，成功，kGeneralErr，失败  

### &emsp;&emsp;4.3 数据出栈  

### `OSStatus linklist_pop(linklist_handler_t * linklist_handler, data_t * * data_pp)`  

#### &emsp;&emsp;参数  
	
		linklist_handler : 链表控制块的句柄指针  
		data_pp : 保存出栈数据指针的指针

#### &emsp;&emsp;返回值  

		链表节点出栈的操作结果，kNoErr，成功，kGeneralErr，失败  

### &emsp;&emsp;【注意】 执行pop操作后，该节点中的有效数据拷贝到`(*data_pp)`后，从链表中删除，数据不再使用之后，应该执行`free(*data_pp)`操作，释放内存空间。  
 
### &emsp;&emsp;4.4 查找链表节点  

### `OSStatus linklist_node_find(linklist_handler_t * linklist_handler, uint32_t i, linklist * * dest_node)`  

#### &emsp;&emsp;参数  
	
		linklist_handler : 链表控制块的句柄指针  
		i : 链表节点的标号，第一个节点从标号0开始  
		dest_node : 存储目标链表节点指针的指针

#### &emsp;&emsp;返回值  

		链表节点查找的操作结果，kNoErr，成功，kGeneralErr，失败  

### &emsp;&emsp;4.5 删除链表节点  

### `OSStatus linklist_node_delete(linklist_handler_t * linklist_handler, uint32_t i)`    

#### &emsp;&emsp;参数  
	
		linklist_handler : 链表控制块的句柄指针  
		i : 链表节点的标号，第一个节点从标号0开始 

#### &emsp;&emsp;返回值  

		链表节点删除的操作结果，kNoErr，成功，kGeneralErr，失败  

### &emsp;&emsp;4.6 删除链表  

### `OSStatus linklist_deinit(linklist_handler_t * linklist_handler)`   

#### &emsp;&emsp;参数  
	
		linklist_handler : 链表控制块的句柄指针  

#### &emsp;&emsp;返回值  

		链表删除的操作结果，kNoErr，成功，kGeneralErr，失败  

### &emsp;&emsp;4.7 获取链表节点数  

### `OSStatus linklist_get_nodeSize(linklist_handler_t * linklist_handler, nodesize_t * nodeSize)`   

#### &emsp;&emsp;参数  
	
		linklist_handler : 链表控制块的句柄指针  
		nodeSize : 存储链表节点数目的指针

#### &emsp;&emsp;返回值  

		链表删除的操作结果，kNoErr，成功，kGeneralErr，失败  

### &emsp;&emsp;4.8 清空链表节点  

### `OSStatus linklist_empty(linklist_handler_t * linklist_handler)`   

#### &emsp;&emsp;参数  
	
		linklist_handler : 链表控制块的句柄指针  

#### &emsp;&emsp;返回值  

		链表删除的操作结果，kNoErr，成功，kGeneralErr，失败  

