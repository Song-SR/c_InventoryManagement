#include "inventory.h"

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