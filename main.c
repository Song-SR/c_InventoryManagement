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

#define MAX 100
Inventory inventories[MAX];  // ������ ������ �ӽ� ����뵵
Inventory inventories2[MAX];  // ����Ʈ �ҷ����� �뵵
Inventory inventories3[MAX];  // �ʱ�ȭ �뵵 (�� ��) - �����ڿ�
Inventory inventories4[MAX];  // ��� �α׿�
Inventory inventories5[MAX];  // ����� �α׿�
Inventory *inv_clear = inventories2;
int key, change;
struct tm *t;
time_t timer; // �ð�����

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
    while ((key = select_main()) != 0)//������ �޴��� 0�� �ƴϸ� �ݺ�
    {
        switch (key)//������ Ű�� ���� ��� ����
        {
        case 1: sub1(); break;
        case 2: sub2(); break;
        case 3: sub3(); break;
        case 4: list(inventories2); break;
        case 99: data_clear(); save(inventories3); save_add(inventories3);
                list(inventories2); printf("==������ �ʱ�ȭ �Ϸ� (�����ڿ�)==\n\n"); break;  // data �ʱ�ȭ��(�����ڿ�)
        default: list(inventories2); printf("==�߸� �����Ͽ����ϴ�.==\n"); break;
        }
    }
    system("cls");
    printf("==���α׷� ����==");
}

int select_main()
{
    key = 0;
    printf("��� ���� ���α׷�\n");
    printf("1:������  2:�������  3:����Ȯ��  4:��ü��ǰ����  //  0:���α׷�����\n");
    scanf("%d", &key);
    return key;
}

int select_sub1()
{
    key = 0;
    printf("��� ���� ���α׷�\n");
    printf("1:��ǰ ���  2:�����  3:�׸�����  //  0:��������\n");
    scanf("%d", &key);
    return key;
}

int select_sub2()
{
    key = 0;
    printf("��� ���� ���α׷�\n");
    printf("1:��ǰ�Ǹ�  2:�Ѹ���Ȯ��  //  0:��������\n");
    scanf("%d", &key);
    return key;
}

int select_sub3()
{
    key = 0;
    printf("��� ���� ���α׷�\n");
    printf("1:��ϳ���  2:�������  3:�Ǹų���  //  0:��������\n");
    scanf("%d", &key);
    return key;
}

void sub1()
{
    system("cls");
    key = 0;
    while ((key = select_sub1()) != 0)//������ �޴��� 0�� �ƴϸ� �ݺ�
    {
        list_short(inventories2);
        switch (key)//������ Ű�� ���� ��� ����
        {
        case 1:
            if(addinventory(inventories)){
               save_add(inventories4);
               save(inventories); list_short(inventories2); break; 
            }else{
                list_short(inventories2); printf("==�ش� ��ǰ�� �̹� ��ϵǾ� �ֽ��ϴ�.==\n\n"); break;
            };
            
        case 2: plusinventory(inventories); save(inventories); save_plus(inventories5); list_short(inventories2); break;
        case 3: dropinventory(inventories); save(inventories); list_short(inventories2); break;
        default: printf("==�߸� �����Ͽ����ϴ�.==\n"); break;
        }
    }
    system("cls");
}

void sub2()
{
    system("cls");
    key = 0;
    while ((key = select_sub2()) != 0)//������ �޴��� 0�� �ƴϸ� �ݺ�
    {
        list(inventories2);
        switch (key)//������ Ű�� ���� ��� ����
        {
        case 1: sale(inventories); save(inventories); list(inventories2); break;
        case 2: break;
        default: printf("==�߸� �����Ͽ����ϴ�.==\n"); break;
        }
    }
    system("cls");
}

void sub3()
{
    // 1:��ϳ���  2:�������  3:�Ǹų���
    system("cls");
    key = 0;
    while ((key = select_sub3()) != 0)//������ �޴��� 0�� �ƴϸ� �ݺ�
    {
        switch (key)
        {
        case 1: list_addlog(inventories2); break;
        case 2: list_pluslog(inventories2); break;
        case 3: break;
        default: printf("==�߸� �����Ͽ����ϴ�.==\n"); break;
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

    printf("%-10s %-10s %-10s %-10s\n", "�ڵ�", "��ǰ��", "�ܰ�", "���");
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

    printf("%-10s %-10s %-10s %-10s %-10s %-10s\n", "�ڵ�", "��ǰ��", "�ܰ�", "�Ǹż���", "�Ǹž�", "���");
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

    printf("%-20s %-10s %-10s %-10s %-10s\n", "��¥", "�ڵ�", "��ǰ��", "�ܰ�", "��ϼ���");
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

    printf("%-20s %-10s %-10s %-10s %-10s\n", "��¥", "�ڵ�", "��ǰ��", "�԰�/���", "��ϼ���");
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
        printf("��� ����\n");
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
        printf("��� ����\n");
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

    timer = time(NULL);
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

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

    printf("������� ��ǰ�� �ڵ� �Ǵ� ��ǰ���� �Է��ϼ��� : ");
    scanf("%s", pluscode, sizeof(pluscode));

    for(int i = 0; i < MAX; i++){
        if(strcmp(inventories[i].code, pluscode)){

        }else{
            printf("�԰��� ������ �Է��ϼ��� (���� ���̳ʽ��� ����) : ");
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
            printf("�԰��� ������ �Է��ϼ��� (���� ���̳ʽ��� ����) : ");
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

    printf("������ ��ǰ�� �ڵ带 �Է��ϼ��� : ");
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

    printf("�Ǹ��� ��ǰ�� �ڵ� �Ǵ� ��ǰ���� �Է��ϼ��� : ");
    scanf("%s", salecode, sizeof(salecode));

    for(int i = 0; i < MAX; i++){
        if(strcmp(inventories[i].code, salecode)){

        }else{
            printf("==�ڵ�:%-10s ��ǰ��:%-10s �Ǹ�==\n", inventories[i].code, inventories[i].name);
            printf("�Ǹ��� ������ �Է��ϼ��� (0 ~ %d) : ", inventories[i].reserve);
            scanf("%d", &sale);
            inventories[i].reserve -= sale;
            inventories[i].sale_total += sale;

            


            break;
        }
        
        if(strcmp(inventories[i].name, salecode)){

        }else{
            printf("==�ڵ�:%-10s ��ǰ��:%-10s �Ǹ�==\n", inventories[i].code, inventories[i].name);
            printf("�Ǹ��� ������ �Է��ϼ��� (0 ~ %d) : ", inventories[i].reserve);
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