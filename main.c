#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
 
#define MAX_CODE 10
#define MAX_NAME 10
#define MAX_DATE 20
FILE * fp;
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

#define MAX 100
Inventory inventories[MAX];  // 변경할 데이터 임시 저장용도
Inventory inventories2[MAX];  // 리스트 불러오기 용도
Inventory inventories3[MAX];  // 초기화 용도 (빈 값) - 개발자용
Inventory inventories4[MAX];  // 등록 로그용
Inventory inventories5[MAX];  // 입출고 로그용
Inventory *inv_clear = inventories2;
int key, change;
struct tm *t;
time_t timer; // 시간측정

void makefile(), run(), sub1(), sub2(), sub3();
int select_main(), select_sub1(), select_sub2();
void list_short(Inventory inventories[]);
void list(Inventory inventories[]);
void list_addlog(Inventory inventories[]);
void list_pluslog(Inventory inventories[]);
void save(Inventory inventories[]);
void save_add(Inventory inventories[]);
void save_plus(Inventory inventories[]);
int addinventory(Inventory inventories[]);
void plusinventory(Inventory inventories[]);
void dropinventory(Inventory inventories[]);
void sale(Inventory inventories[]);
void show_add(Inventory inventories[]);
void data_clear();

int main(void)
{
    makefile();
    run();

    return 0;
}


void makefile(){
    fopen_s(&fp, "inventory_data.bin", "a+b");
    fclose(fp);
    fopen_s(&fp, "log_adddata.bin", "a+b");
    fclose(fp);
    fopen_s(&fp, "log_plusdata.bin", "a+b");
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
        case 3: sub3(); break;
        case 4: list(inventories2); break;
        case 99: data_clear(); save(inventories3); save_add(inventories3);
                list(inventories2); printf("==데이터 초기화 완료 (개발자용)==\n\n"); break;  // data 초기화용(개발자용)
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
    printf("1:재고관리  2:매출관리  3:내역확인  4:전체물품보기  //  0:프로그램종료\n");
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

int select_sub3()
{
    key = 0;
    printf("재고 관리 프로그램\n");
    printf("1:등록내역  2:입출고내역  3:판매내역  //  0:메인으로\n");
    scanf("%d", &key);
    return key;
}

void sub1()
{
    system("cls");
    key = 0;
    while ((key = select_sub1()) != 0)//선택한 메뉴가 0이 아니면 반복
    {
        list_short(inventories2);
        switch (key)//선택한 키에 따라 기능 수행
        {
        case 1:
            if(addinventory(inventories)){
               save_add(inventories4);
               save(inventories); list_short(inventories2); break; 
            }else{
                list_short(inventories2); printf("==해당 물품은 이미 등록되어 있습니다.==\n\n"); break;
            };
            
        case 2: plusinventory(inventories); save(inventories); save_plus(inventories5); list_short(inventories2); break;
        case 3: dropinventory(inventories); save(inventories); list_short(inventories2); break;
        default: printf("==잘못 선택하였습니다.==\n"); break;
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
        list(inventories2);
        switch (key)//선택한 키에 따라 기능 수행
        {
        case 1: sale(inventories); save(inventories); list(inventories2); break;
        case 2: break;
        default: printf("==잘못 선택하였습니다.==\n"); break;
        }
    }
    system("cls");
}

void sub3()
{
    // 1:등록내역  2:입출고내역  3:판매내역
    system("cls");
    key = 0;
    while ((key = select_sub3()) != 0)//선택한 메뉴가 0이 아니면 반복
    {
        switch (key)
        {
        case 1: list_addlog(inventories2); break;
        case 2: list_pluslog(inventories2); break;
        case 3: break;
        default: printf("==잘못 선택하였습니다.==\n"); break;
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

void list_addlog(Inventory inventories[]){
    system("cls");
    fopen_s(&fp, "log_adddata.bin", "rb");
    if (fp == NULL){
        perror("error fopen");
        return;
    }
    fread(inventories, sizeof(Inventory), MAX, fp);

    printf("%-20s %-10s %-10s %-10s %-10s\n", "날짜", "코드", "상품명", "단가", "등록수량");
    for (int i = 0; i < MAX; i++)
    {
        if(strcmp(inventories[i].code, "")){
            printf("%-20s %-10s %-10s %-10d %-10d\n", inventories[i].add_date, inventories[i].code,
            inventories[i].name, inventories[i].price, inventories[i].reserve);
        }else{
            printf("\n");
            break;
        }  
    }
    fclose(fp);
}

void list_pluslog(Inventory inventories[]){
    system("cls");
    fopen_s(&fp, "log_plusdata.bin", "rb");
    if (fp == NULL){
        perror("error fopen");
        return;
    }
    fread(inventories, sizeof(Inventory), MAX, fp);

    printf("%-20s %-10s %-10s %-10s %-10s\n", "날짜", "코드", "상품명", "입고/출고", "등록수량");
    for (int i = 0; i < MAX; i++)
    {
        if(strcmp(inventories[i].code, "")){
            printf("%-20s %-10s %-10s %-10d %-10d\n", inventories[i].add_date, inventories[i].code,
            inventories[i].name, inventories[i].plus_count, inventories[i].reserve);
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

void save_add(Inventory inventories[]){
    fopen_s(&fp, "log_adddata.bin", "wb");
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

void save_plus(Inventory inventories[]){
    fopen_s(&fp, "log_plusdata.bin", "wb");
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

    timer = time(NULL);
	t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

    sprintf(inventories[i].add_date, "%d-%d-%d %d:%d", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min);

    for(int k = 0; k < MAX; k++){
        if(strcmp(inventories4[k].code, "")){
            
        }else{
            inventories4[k] = inventories[i];
            break;
        }
    }

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
            inventories[i].plus_count = add;
            for(int k = 0; k < MAX; k++){
                if(strcmp(inventories5[k].code, "")){
            
                }else{
                    inventories5[k] = inventories[i];
                    break;
                }
            }

            break;
        }
        
        if(strcmp(inventories[i].name, pluscode)){

        }else{
            printf("입고할 수량을 입력하세요 (출고는 마이너스로 기재) : ");
            scanf("%d", &add);
            inventories[i].reserve += add;
            inventories[i].plus_count = add;
            for(int k = 0; k < MAX; k++){
                if(strcmp(inventories5[k].code, "")){
            
                }else{
                    inventories5[k] = inventories[i];
                    break;
                }
            }
            
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

void data_clear(){
    fopen_s(&fp, "log_adddata.bin", "w");
    fclose(fp);
    fopen_s(&fp, "log_plusdata.bin", "w");
    fclose(fp);
    system("cls");
}