#include "kvs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NUM 100


int main()
{
	kvs_t* kvs = open(); // kvs 생성하고 초기화, 그 주소를 kvs 변수에 저장 

	if(!kvs) { // kvs 생성 실패했다면 (NULL)
		printf("Failed to open kvs\n"); // 실패 메세지 출력
		return -1; // -1 반환하여 프로그램 종료 
	}
 
	FILE* file = fopen("query.dat", "r");
	if(!file) {
		printf("Failed to open file: query.dat");
		exit(EXIT_FAILURE);
	}

	char line[MAX_NUM];
	while(fgets(line, sizeof(line), file)) {
		char* op = strtok(line, ",");
		char* key = strtok(NULL, ",");
		char* value = strtok(NULL, ",");

		value[strlen(value)-1] = '\0';

		if(strcmp(op, "set") == 0) {
			set(kvs, key, value);
		} else if (strcmp(op, "get") == 0) {
			char* result = get(kvs, key);
			
			FILE* out = fopen("answer.dat", "a");
			if(out) {
				if (result) {
					fprintf(out, "%s\n", result);
					free(result);
				} else {
					fprintf(out, "%s\n", "-1");
				}
				fclose(out);
			}
		}
	}
	fclose(file);

	close(kvs); // 작업이 끝난 후 close 함수를 호출하여 kvs 닫음 -> 할당된 모든 메모리 해제 
	
	return 0; // 성공적으로 끝남. 0 반환 
}

