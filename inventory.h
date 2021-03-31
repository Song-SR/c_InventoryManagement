#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define MAX_CODE 10
#define MAX_NAME 10
#define MAX_DATE 20
#define MAX 100

FILE * fp;
int key, change;
struct tm *t;
time_t timer; // 시간측정

typedef struct {
    char code[MAX_CODE];
    char name[MAX_NAME];
    int price;  // 단가
    int sale_total;  // 총 판매량
    char add_date[MAX_DATE];  // 등록일
    int add_count;  // 등록 수량
    int reserve;  // 재고량
    char sale_date[MAX_DATE];  // 판매일
    int sale_count;  // 판매수량
    int plus_count;  // 입출고수량
    char plus_date[MAX_DATE];  // 입출고일
    int sale;  // 해당 판매액

}Inventory;

Inventory inventories[MAX];  // 변경할 데이터 임시 저장용도
Inventory inventories2[MAX];  // 리스트 불러오기 용도
Inventory inventories3[MAX];  // 초기화 용도 (빈 값) - 개발자용
Inventory inventories4[MAX];  // 등록 로그용
Inventory inventories5[MAX];  // 입출고 로그용

