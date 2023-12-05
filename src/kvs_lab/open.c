#include "kvs.h"

// kvs 생성하고 초기화한 후 그 주소를 반환 
kvs_t* open()
{
	kvs_t* kvs = (kvs_t*) malloc (sizeof(kvs_t));
	// kvs_t 타입의 메모리 공간을 동적으로 할당
	// 그 메모리 공간의 주소를 kvs 포인터에 저장

	if(kvs) // 메모리 할당이 성공적으로 이루어졌으면 
		kvs->items = 0; // kvs 객체의 items 필드를 0으로 초기화
	return kvs; // 생성된 kvs 객체의 주소 반환
}

