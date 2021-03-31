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

void data_clear(){
    fopen_s(&fp, "log_adddata.bin", "w");
    fclose(fp);
    fopen_s(&fp, "log_plusdata.bin", "w");
    fclose(fp);
    system("cls");
}