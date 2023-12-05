#include "kvs.h"
#include <string.h>

// 새로운 키와 값을 저장
// 매개변수로 kvs 객체(키값 쌍 저장하고 관리), 키 문자열, 값 문자열 주어짐
int set(kvs_t* kvs, const char* key, const char* value)
{
	//printf("set: %s, %s\n", key, value);

	// 새로운 node_t 노드를 동적 할당
	node_t* newNode = (node_t*)malloc(sizeof(node_t));

	// 메모리 할당 실패 시
	if(!newNode) {
		return -1;
	}

	// 키와 값을 복사
	strcpy(newNode->key, key);
	newNode->value = strdup(value);

	// 새로운 노드를 리스트의 맨 앞에 추가
	newNode->next = kvs->db;
	kvs->db = newNode;

	// 데이터 개수 증가
	kvs->items++;

	return 0;
}

