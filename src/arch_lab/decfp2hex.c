#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

typedef unsigned char* pointer;

bool is64bit() // 현재 시스템이 64비트 아키텍처인지 확인하는 함수
{
	return sizeof(void*) == 8;
}

bool isBigEndian() // 시스템의 엔디안(빅 엔디안 또는 리틀 엔디안)을 확인하는 함수
{
	int num = 1;
	return !*((char*)&num);
}

// 리틀 엔디안 형식으로 바이트를 출력하는 함수
//LITTLE ENDIAN : 데이터의 상위 바이트가 메모리의 높은 주소에 저장되는 엔디안 방식
void le_show_bytes(pointer start, size_t len) {
	for (size_t i = len; i > 0; i--) {
		printf("%.2X", start[i-1]); // 바이트를 16진수로 출력 (리틀 엔디안)
	}
	printf("\n");
	return;
}

// 빅 엔디안 형식으로 바이트를 출력하는 함수
// BIG ENDIAN : 데이터의 상위 바이트가 메모리의 낮은 주소에 저장되는 엔디안 방식
void be_show_bytes(pointer start, size_t len) {
	for (size_t i = 0; i < len; i++) {
		printf("%.2X", start[i]); // 바이트를 16진수로 출력 (빅 엔디안)
	}
	printf("\n");
	return;
}

int main(int argc, char* argv[]) // 숫자 입력 받는 인수
{
	if(argc < 2){ // 입력이 없는 경우 프로그램 종료
		printf("Usage: ./a.out number\n");
		exit(0);
	}
	double d = atof(argv[1]);

    printf("ARCH=%d\n", is64bit() ? 64 : 32); // 시스템 아키텍처(32비트 또는 64비트) 출력
    printf("ORDERING=%s\n", isBigEndian() ? "BIG_ENDIAN" : "LITTLE_ENDIAN"); // 시스템 엔디안 정보 출력

    uint64_t u;
    memcpy(&u, &d, sizeof(double)); // 부동 소수점 값을 64비트 정수로 변환

	// 입력된 부동 소수점 값을 십진수, 십육진수로 출력
    printf("MYANS: DEC=%.3lf HEX=", d);
    isBigEndian() ? be_show_bytes((pointer)&u, sizeof(uint64_t)) : le_show_bytes((pointer)&u, sizeof(uint64_t));
    printf("\n");
	return 0;
}
