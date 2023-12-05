#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<limits.h>

//#define MAX_NUM 1000
//#define MAX_NUM 100000000
//#define MAX_NUM 10000
#define MAX_NUM 10000000
//#define MAX_NUM 1000000000
//#define MAX_NUM INT_MAX
//#define MAX_NUM 100000

#define IDENT 0

struct vec {
	int len;
	int *data;
};
typedef struct vec vec_t;

int* get_vec_start(vec_t* v);

int vec_length(vec_t* v)
{
	assert(v);
	return v->len;
}

void combine(vec_t* v, int *dest)
{
	//assert(dest);

	long length = vec_length(v); // 벡터의 길이를 한 번만 계산
	long limit = length - 1;
	int *d = get_vec_start(v); // 벡터의 시작 주소 얻어옴
	int x = IDENT; // 초기값 설정

	long i; 
	/* Combine 2 elements at a time */
	for (i = 0; i < limit; i+=2) {
		x = x + (d[i] + d[i+1]);
	}

	/* Finish any remaining elements */
	for(i = 0; i < length; i++){ // 벡터의 모든 요소를 반복하면서 OP를 적용하여 누적
		x = x + d[i];
	}

	*dest = x; // 최종 결과를 dest에 저장
}

int* get_vec_start(vec_t* v)
{
	assert(v);
	return v->data;
}

void init(vec_t* v)
{
	assert(v);
	v->len = MAX_NUM;
	v->data = (int*) malloc(sizeof(int) * MAX_NUM);

	// init 
	for(int i = 0; i < MAX_NUM; i++)
		v->data[i] = i;
}

int main()
{
	printf("This is the naive version .. \n");

	vec_t info; 
	int result; 

	// init 
	init(&info);

	// combine 
	combine(&info, &result);
	//printf("combined val = %d\n", result);

	free(info.data); // 메모리 해제
	return 0;
}