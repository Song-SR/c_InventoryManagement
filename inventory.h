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
time_t timer; // �ð�����

typedef struct {
    char code[MAX_CODE];
    char name[MAX_NAME];
    int price;  // �ܰ�
    int sale_total;  // �� �Ǹŷ�
    char add_date[MAX_DATE];  // �����
    int add_count;  // ��� ����
    int reserve;  // ���
    char sale_date[MAX_DATE];  // �Ǹ���
    int sale_count;  // �Ǹż���
    int plus_count;  // ��������
    char plus_date[MAX_DATE];  // �������
    int sale;  // �ش� �Ǹž�

}Inventory;

Inventory inventories[MAX];  // ������ ������ �ӽ� ����뵵
Inventory inventories2[MAX];  // ����Ʈ �ҷ����� �뵵
Inventory inventories3[MAX];  // �ʱ�ȭ �뵵 (�� ��) - �����ڿ�
Inventory inventories4[MAX];  // ��� �α׿�
Inventory inventories5[MAX];  // ����� �α׿�

