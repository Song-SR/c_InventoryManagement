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
    // { "code001","���",100,0,200 }
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
    while ((key = selectmenu()) != 0)//������ �޴��� 0�� �ƴϸ� �ݺ�
    {
        switch (key)//������ Ű�� ���� ��� ����
        {
        case 1:
            list(inventories2);
            if(addinventory(inventories)){
               save(inventories); list(inventories2); break; 
            }else{
                list(inventories2); printf("==�ش� ��ǰ�� �̹� ��ϵǾ� �ֽ��ϴ�.==\n\n"); break;
            };
            
        // case 2: break;
        // case 3: break;
        case 4: list(inventories2); dropinventory(inventories); save(inventories); list(inventories2); break;
        case 5: list(inventories2); break;
        default: printf("�߸� �����Ͽ����ϴ�.\n"); break;
        }
    }
    system("cls");
    printf("���α׷� ����\n");
}

int selectmenu()
{
    int key = 0;
    printf("��� ���� ���α׷� (0:����)\n");
    printf("1:��ǰ ���  2:�԰�  3:���  4:�׸�����  5:list\n");
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

    printf("%-10s %-10s %-10s %-10s %-10s %-10s\n", "�ڵ�", "��ǰ��", "�ܰ�", "�Ǹż���", "�Ǹž�", "���");
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
        printf("��� ����\n");
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

    printf("����� ��ǰ�� ������ �Է��ϼ���.\n");
    printf("�ڵ� : ");
    scanf("%s", &(inventories[i].code));
    for(int check = 0; check < i; check++){
        if(strcmp(inventories[check].code, inventories[i].code)){
        
        }else{
            printf("�ش� ��ǰ�� �̹� ��ϵǾ� �ֽ��ϴ�.");
            fclose(fp);
            return 0;
        }
    }
    printf("��ǰ�� : ");
    scanf("%s", &(inventories[i].name));
    printf("�ܰ� : ");
    scanf("%d", &(inventories[i].price));
    printf("���� : ");
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

    printf("������ ��ǰ�� �ڵ带 �Է��ϼ��� : ");
    scanf("%s", dropcode, sizeof(dropcode));
    for(int i = 0; i < MAX; i++){
        if(strcmp(inventories[i].code, dropcode)){

        }else{
            printf("���� ������!");
            for(int j = i; j < MAX; j++){
                inventories[j] = inventories[j+1];
            }
            break;
        }
    }
    fclose(fp);
}