#include<stdio.h>
#include<stdlib.h>

#define COLS 100000
#define ROWS 10000

int sum_array_cols(int** a)
{
    int i, j, sum = 0;

    for (i=0; i<ROWS; i++) // 열을 순회
        for (j=0; j<COLS; j++) // 현재 열의 각 행의 값을 더함
            sum += a[i][j];

	return sum;
}

int sum_array_rows(int** a)
{
    int i, j, sum = 0;

    for (j=0; j<COLS; j++)  // 행을 순회
        for (i=0; i<ROWS; i++)  // 현재 행의 각 열의 값을 더함
            sum += a[i][j];

	return sum;
}

int main()
{
    int** a;
    int i, j;

    a = (int**)malloc(sizeof(int*) * ROWS);  // 행을 저장하는 포인터 배열 생성

    for(i = 0; i < ROWS; i++)
        a[i] = (int*)malloc(sizeof(int)*COLS);  // 각 행에 열을 저장하는 배열 생성


    for(i = 0; i < ROWS; i++)
        for(j = 0; j < COLS; j++)
            a[i][j] = i;  // 배열을 초기화

#ifdef SUM_COLS     
    int sum = sum_array_cols(a);  // 열 방향으로 배열 요소 합 계산
    printf("sum_cols ... \n");
#endif

#ifdef SUM_ROWS
    printf("sum_rows ... \n");
    int sum = sum_array_rows(a);  // 행 방향으로 배열 요소 합 계산
#endif

    printf("sum = %d\n", sum);  // 결과 출력

    return 0;
}