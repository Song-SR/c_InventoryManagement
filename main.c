#include <stdio.h>
#include <string.h>
#include <windows.h>
 
#define MAX_CODE 10
#define MAX_NAME 10
FILE * fp;
typedef struct {
    char code[MAX_CODE];
    char name[MAX_NAME];
    int price;
    int sale_total;
    int reserve;
}Inventory;

#define MAX 100
Inventory inventories[MAX] =
{
    // { "code001","사과",100,0,200 }
};
Inventory inventories2[MAX];
int key;

void makefile(), run(), sub1(), sub2();
int select_main(), select_sub1(), select_sub2();
void list_short(Inventory inventories[]);
void list(Inventory inventories[]);
void save(Inventory inventories[]);
int addinventory(Inventory inventories[]);
void plusinventory(Inventory inventories[]);
void dropinventory(Inventory inventories[]);
void sale(Inventory inventories[]);

int main(void)
{
    makefile();
    run();

    return 0;
}


void makefile(){
    fopen_s(&fp, "inventory_data.bin", "a+b");
    fclose(fp);
}

void run(){
    system("cls");
    key = 0;
    while ((key = select_main()) != 0)//선택한 메뉴가 0이 아니면 반복
    {
        switch (key)//선택한 키에 따라 기능 수행
        {
        case 1: sub1(); break;
        case 2: sub2(); break;
        case 3: list(inventories2); break;
        default: list(inventories2); printf("==잘못 선택하였습니다.==\n"); break;
        }
    }
    system("cls");
    printf("==프로그램 종료==");
}

int select_main()
{
    key = 0;
    printf("재고 관리 프로그램\n");
    printf("1:재고관리  2:매출관리  3:전체물품보기  //  0:프로그램종료\n");
    scanf("%d", &key);
    return key;
}

int select_sub1()
{
    key = 0;
    printf("재고 관리 프로그램\n");
    printf("1:물품 등록  2:입출고  3:항목제거  //  0:메인으로\n");
    scanf("%d", &key);
    return key;
}

int select_sub2()
{
    key = 0;
    printf("재고 관리 프로그램\n");
    printf("1:상품판매  2:총매출확인  //  0:메인으로\n");
    scanf("%d", &key);
    return key;
}

void sub1()
{
    system("cls");
    key = 0;
    while ((key = select_sub1()) != 0)//선택한 메뉴가 0이 아니면 반복
    {
        switch (key)//선택한 키에 따라 기능 수행
        {
        case 1:
            list_short(inventories2);
            if(addinventory(inventories)){
               save(inventories); list_short(inventories2); break; 
            }else{
                list_short(inventories2); printf("==해당 물품은 이미 등록되어 있습니다.==\n\n"); break;
            };
            
        case 2: list_short(inventories2); plusinventory(inventories); save(inventories); list_short(inventories2); break;
        case 3: list_short(inventories2); dropinventory(inventories); save(inventories); list_short(inventories2); break;
        default: list_short(inventories2); printf("==잘못 선택하였습니다.==\n"); break;
        }
    }
    system("cls");
}

void sub2()
{
    system("cls");
    key = 0;
    while ((key = select_sub2()) != 0)//선택한 메뉴가 0이 아니면 반복
    {
        switch (key)//선택한 키에 따라 기능 수행
        {
        case 1: list(inventories2); sale(inventories); save(inventories); list(inventories2); break;
        case 2: list(inventories2); break;
        default: list(inventories2); printf("==잘못 선택하였습니다.==\n"); break;
        }
    }
    system("cls");
}

void list_short(Inventory inventories[]){
    system("cls");
    fopen_s(&fp, "inventory_data.bin", "rb");
    if (fp == NULL){
        perror("error fopen");
        return;
    }
    fread(inventories, sizeof(Inventory), MAX, fp);

    printf("%-10s %-10s %-10s %-10s\n", "코드", "상품명", "단가", "재고량");
    for (int i = 0; i < MAX; i++)
    {
        if(strcmp(inventories[i].code, "")){
            printf("%-10s %-10s %-10d %-10d\n", inventories[i].code, inventories[i].name,
            inventories[i].price, inventories[i].reserve);
        }else{
            printf("\n");
            break;
        }  
    }
    fclose(fp);
}

void list(Inventory inventories[]){
    system("cls");
    fopen_s(&fp, "inventory_data.bin", "rb");
    if (fp == NULL){
        perror("error fopen");
        return;
    }
    fread(inventories, sizeof(Inventory), MAX, fp);

    printf("%-10s %-10s %-10s %-10s %-10s %-10s\n", "코드", "상품명", "단가", "판매수량", "판매액", "재고량");
    for (int i = 0; i < MAX; i++)
    {
        if(strcmp(inventories[i].code, "")){
            printf("%-10s %-10s %-10d %-10d %-10d %-10d\n", inventories[i].code, inventories[i].name, inventories[i].price,
            inventories[i].sale_total, (inventories[i].price*inventories[i].sale_total), inventories[i].reserve);
        }else{
            printf("\n");
            break;
        }  
    }
    fclose(fp);
}

void save(Inventory inventories[]){
    fopen_s(&fp, "inventory_data.bin", "wb");
    if (fp == NULL){
        perror("error fopen");
        return;
    }
    if (fwrite(inventories, sizeof(Inventory), MAX, fp) != MAX)
    {
        printf("출력 오류\n");
        return;
    }
    fclose(fp);
}

int addinventory(Inventory inventories[]){
    fopen_s(&fp, "inventory_data.bin", "rb");
    if (fp == NULL){
        perror("error fopen");
        return 0;
    }
    fread(inventories, sizeof(Inventory), MAX, fp);

    int i = 0;
    for(int j = 0; j < MAX; j++){
        if(strcmp(inventories[j].code, "")){
            
        }else{
            i = j;
            break;
        }
    }

    printf("등록할 물품의 정보를 입력하세요.\n");
    printf("코드 : ");
    scanf("%s", &(inventories[i].code));
    for(int check = 0; check < i; check++){
        if(strcmp(inventories[check].code, inventories[i].code)){
        
        }else{
            printf("해당 상품은 이미 등록되어 있습니다.");
            fclose(fp);
            return 0;
        }
    }
    printf("상품명 : ");
    scanf("%s", &(inventories[i].name));
    printf("단가 : ");
    scanf("%d", &(inventories[i].price));
    printf("수량 : ");
    scanf("%d", &(inventories[i].reserve));

    fclose(fp);
    return 1;
}

void plusinventory(Inventory inventories[]){
    char pluscode[MAX_CODE];
    int add = 0;

    fopen_s(&fp, "inventory_data.bin", "rb");
    if (fp == NULL){
        perror("error fopen");
        return;
    }
    fread(inventories, sizeof(Inventory), MAX, fp);

    printf("입출고할 물품의 코드 또는 상품명을 입력하세요 : ");
    scanf("%s", pluscode, sizeof(pluscode));

    for(int i = 0; i < MAX; i++){
        if(strcmp(inventories[i].code, pluscode)){

        }else{
            printf("입고할 수량을 입력하세요 (출고는 마이너스로 기재) : ");
            scanf("%d", &add);
            inventories[i].reserve += add;
            printf("%d", inventories[i].reserve);
            break;
        }
        
        if(strcmp(inventories[i].name, pluscode)){

        }else{
            printf("입고할 수량을 입력하세요 (출고는 마이너스로 기재) : ");
            scanf("%d", &add);
            inventories[i].reserve += add;
            printf("%d", inventories[i].reserve);
            break;
        }
    }

    fclose(fp);
}

void dropinventory(Inventory inventories[]){
    char dropcode[MAX_CODE];
    fopen_s(&fp, "inventory_data.bin", "rb");
    if (fp == NULL){
        perror("error fopen");
        return;
    }
    fread(inventories, sizeof(Inventory), MAX, fp);

    printf("삭제할 물품의 코드를 입력하세요 : ");
    scanf("%s", dropcode, sizeof(dropcode));
    for(int i = 0; i < MAX; i++){
        if(strcmp(inventories[i].code, dropcode)){

        }else{
            for(int j = i; j < MAX; j++){
                inventories[j] = inventories[j+1];
            }
            break;
        }
    }
    fclose(fp);
}

void sale(Inventory inventories[]){
    char salecode[MAX_CODE];
    int sale = 0;

    fopen_s(&fp, "inventory_data.bin", "rb");
    if (fp == NULL){
        perror("error fopen");
        return;
    }
    fread(inventories, sizeof(Inventory), MAX, fp);

    printf("판매할 물품의 코드 또는 상품명을 입력하세요 : ");
    scanf("%s", salecode, sizeof(salecode));

    for(int i = 0; i < MAX; i++){
        if(strcmp(inventories[i].code, salecode)){

        }else{
            printf("==코드:%-10s 상품명:%-10s 판매==\n", inventories[i].code, inventories[i].name);
            printf("판매할 수량을 입력하세요 (0 ~ %d) : ", inventories[i].reserve);
            scanf("%d", &sale);
            inventories[i].reserve -= sale;
            inventories[i].sale_total += sale;
            break;
        }
        
        if(strcmp(inventories[i].name, salecode)){

        }else{
            printf("==코드:%-10s 상품명:%-10s 판매==\n", inventories[i].code, inventories[i].name);
            printf("판매할 수량을 입력하세요 (0 ~ %d) : ", inventories[i].reserve);
            scanf("%d", &sale);
            inventories[i].reserve -= sale;
            inventories[i].sale_total += sale;
            break;
        }
    }

    fclose(fp);
}