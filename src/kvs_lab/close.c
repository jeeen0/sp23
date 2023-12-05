#include "kvs.h"

// 닫고자 하는 kvs를 나타냄 -> 할당된 메모리 해제 
int close(kvs_t* kvs)
{
	// 현재 노드를 가리키는 포인터를 초기화
	node_t* currentNode = kvs->db;
	node_t* nextNode = NULL;

	// 연결 리스트를 순회하며 각 노드에 할당된 메모리를 해제
	while (currentNode != NULL) {
		nextNode = currentNode->next;
		if (currentNode->value != NULL) {
			free(currentNode->value);
		}
		free(currentNode);
		currentNode = nextNode;
	}
	free(kvs);

	return 0;
}

