#include "inventory.h"

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