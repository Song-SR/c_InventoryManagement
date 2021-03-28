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
    int quantity;
    int reserve;
}Inventory;

#define MAX 100
Inventory inventories[MAX] =
{
    // { "code001","사과",100,0,200 }
};
Inventory inventories2[MAX];

void makefile();
void run();
int selectmenu();
void list(Inventory inventories[]);
void save(Inventory inventories[]);
int addinventory(Inventory inventories[]);
void dropinventory(Inventory inventories[]);

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

void run()
{
    system("cls");
    int key = 0;
    while ((key = selectmenu()) != 0)//선택한 메뉴가 0이 아니면 반복
    {
        switch (key)//선택한 키에 따라 기능 수행
        {
        case 1:
            list(inventories2);
            if(addinventory(inventories)){
               save(inventories); list(inventories2); break; 
            }else{
                list(inventories2); printf("==해당 물품은 이미 등록되어 있습니다.==\n\n"); break;
            };
            
        // case 2: break;
        // case 3: break;
        case 4: list(inventories2); dropinventory(inventories); save(inventories); list(inventories2); break;
        case 5: list(inventories2); break;
        default: printf("잘못 선택하였습니다.\n"); break;
        }
    }
    system("cls");
    printf("프로그램 종료\n");
}

int selectmenu()
{
    int key = 0;
    printf("재고 관리 프로그램 (0:종료)\n");
    printf("1:물품 등록  2:입고  3:출고  4:항목제거  5:list\n");
    scanf("%d", &key);
    return key;
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
            inventories[i].quantity, (inventories[i].price*inventories[i].quantity), inventories[i].reserve);
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
            printf("삭제 진행중!");
            for(int j = i; j < MAX; j++){
                inventories[j] = inventories[j+1];
            }
            break;
        }
    }
    fclose(fp);
}