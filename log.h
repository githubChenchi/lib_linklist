#pragma once

#define _DEBUG(msg...)		do	\
							{	\
								printf("[ %s, %s, %04d ] ",__FILE__, __FUNCTION__, __LINE__);	\
								printf(msg);	\
								printf("\r\n");	\
							} while(0)
							
#define _ERROR(msg...)     	do	\
							{	\
								printf("[ ERROR: %s, %04d] ", __FILE__,  __LINE__);	\
								printf(msg);	\
								printf("\r\n");	\
							} while(0)
							
#define _ASSERT(exp)        do	\
							{	\
                                if (!(exp)) {\
                                    printf( "[ %s ]  ",#exp);printf("\r\n");\
                                    assert(exp);\
                                }\
                            } while (0)

#define sys_log             _DEBUG 

