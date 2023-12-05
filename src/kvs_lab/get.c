#include "kvs.h"
#include <string.h>

char* get(kvs_t* kvs, const char* key)
{
	// 현재 노드를 가리키는 포인터를 초기화
	node_t* currentNode = kvs->db;

	// 연결 리스트를 순회
	while (currentNode != NULL) {
		// 현재 노드의 키가 찾고자 하는 키와 일치하는지 확인 
		if (strcmp(currentNode->key, key) == 0) {
			// 일치한다면, 현재 노드의 값을 복사하여 반환
			char* value = strdup(currentNode->value);
			return value;
		}

		// 현재 노드를 다음 노드로 이동
		currentNode = currentNode->next;
	}

	// 찾는 키가 없다면 NULL 반환
	return NULL; 
}

