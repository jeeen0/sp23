#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node {
	char key[100];
	char* value;
	struct node* next; // 다음 노드를 가리키는 포인터 
};	
typedef struct node node_t;


struct kvs{ // KVS 전체를 나타냄 
	struct node* db; // database
	int items; // number of data 
};
typedef struct kvs kvs_t; 


kvs_t* open();
int close(kvs_t* kvs); // free all memory space KVS에 할당된 모든 메모리 공간을 해제
int set(kvs_t* kvs, const char* key, const char* value); // return -1 if failed.
char* get(kvs_t* kvs, const char* key); // return NULL if not found. 
