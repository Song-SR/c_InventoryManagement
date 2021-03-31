#include "inventory.h"

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

void data_clear(){
    fopen_s(&fp, "log_adddata.bin", "w");
    fclose(fp);
    fopen_s(&fp, "log_plusdata.bin", "w");
    fclose(fp);
    system("cls");
}