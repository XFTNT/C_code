#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#define MAX 100
#define NAME 20
#define SEX 10
#define TELE 12
#define ADDR 30
void menu();




typedef struct peo
{
    char name[NAME];
    char sex[SEX];
    int age;
    char tele[TELE];
    char addr[ADDR];
}peo;
typedef struct contact
{
    peo* data;
    int count;
    int capacity;

}contact;


void menu()
{
    printf("**********************************\n");
    printf("********1.add    2.del************\n");
    printf("********3.serch  4.modify*********\n");
    printf("********5.show   6.sort***********\n");
    printf("********0.exit********************\n");
    printf("**********************************\n");
}
void LoadContact(contact* pc)
{
    FILE* pfread = fopen("contact.txt", "rb");
    if (pfread == NULL)
    {
        perror("LoadContact");
        return;
    }
    peo tem = {0};
    while ((fread(&tem, sizeof(peo), 1, pfread)) == 1)
    {
        if (pc->capacity == pc->count)
        {
            peo* ptr = (peo*)realloc(pc->data, (pc->capacity + 2) * sizeof(peo));
            if (ptr == NULL)
            {
                printf("%s", strerror(errno));
                return;
            }
            else
            {
                pc->data = ptr;
                pc->capacity += 2;
                printf("more space!\n");
            }
        }
        pc->data[pc->count] = tem;
        pc->count++;
    }
    fclose(pfread);
    pfread = NULL;
}

int InitContact(contact* pc)
{
    pc->count = 0;
    pc->data = (peo*)calloc(3, sizeof(peo));
    if (pc->data == NULL)
    {
        printf("%s\n", strerror(errno));
        return 1;
    }
    pc->capacity = 3;
    LoadContact(pc);
    return 0;


}
void AddContact(contact* pc)
{
    assert(pc);
    if (pc->count == 100)
    {
        printf("full\n");
        return;
    }
    if (pc->capacity == pc->count)
    {
        peo* ptr = (peo*)realloc(pc->data, (pc->capacity + 2) * sizeof(peo));
        if (ptr == NULL)
        {
            printf("%s", strerror(errno));
            return;
        }
        else
        {
            pc->data = ptr;
            pc->capacity += 2;
            printf("more space!\n");
        }
    }
    printf("name:");
    scanf("%s", pc->data[pc->count].name);
    printf("sex:");
    scanf("%s", pc->data[pc->count].sex);
    printf("age:");
    scanf("%d", &pc->data[pc->count].age);
    printf("tele:");
    scanf("%s", pc->data[pc->count].tele);
    printf("addr:");
    scanf("%s", pc->data[pc->count].addr);  
    pc->count++;
    printf("add succeed!\n");
}
void ShowContact(contact* pc)
{
    assert(pc);
    int i = 0;
    printf("%-20s\t%-10s\t%-5s\t%-12s\t%-30s\n", "name", "sex", "age", "tele", "addr");
    for (i; i < pc->count; i++)
    {
        printf("%-20s\t%-10s\t%-5d\t%-12s\t%-30s\n", pc->data[i].name, pc->data[i].sex, pc->data[i].age, pc->data[i].tele, pc->data[i].addr);
    }
    printf("show over!\n");
}
void DelContact(contact* pc)
{
    if (pc->count == 0)
        {
            printf("no message\n");
            return;
        }
    int sigh = 0;
    assert(pc);
    printf("del name:");
    char sert[NAME];
    scanf("%s", sert);
    for (int i = 0; i < pc->count; i++)
    {
        if(strcmp(sert, pc->data[i].name) == 0)
        {
            sigh = 1;
            while(i != pc->count)
            {
                strcpy(pc->data[i].name, pc->data[i+1].name);
                strcpy(pc->data[i].sex, pc->data[i+1].sex);
                pc->data[i].age = pc->data[i+1].age;
                strcpy(pc->data[i].tele, pc->data[i+1].tele);
                strcpy(pc->data[i].addr, pc->data[i+1].addr);
                i++;
            }
            pc->count--;
            printf("del over!\n");
        }
    }
    if (sigh == 0)
    {
        printf("no find!\n");
    }
}
void SearchContact(contact* pc)
{
    assert(pc);
    if (pc->count == 0)
        {
            printf("no message\n");
            return;
        }
    int sigh = 0;
    printf("search name:");
    char sert[NAME];
    scanf("%s", sert);
    for (int i = 0; i < pc->count; i++)
    {
        if(strcmp(sert, pc->data[i].name) == 0)
        {
            sigh = 1;
            printf("%-20s\t%-10s\t%-5s\t%-12s\t%-30s\n", "name", "sex", "age", "tele", "addr");
            printf("%-20s\t%-10s\t%-5d\t%-12s\t%-30s\n", pc->data[i].name, pc->data[i].sex, pc->data[i].age, pc->data[i].tele, pc->data[i].addr);
        }
    }
    if (sigh = 0)
    {
        printf("no find!\n");
    }
}
void ModifyContact(contact* pc)
{
    assert(pc);
    if (pc->count == 0)
        {
            printf("no message\n");
            return;
        }
    int sigh = 0;
    printf("search name:");
    char sert[NAME];
    scanf("%s", sert);
    for (int i = 0; i < pc->count; i++)
    {
        if(strcmp(sert, pc->data[i].name) == 0)
        {
            sigh = 1;
            printf("name:");
            scanf("%s", pc->data[i].name);
            printf("sex:");
            scanf("%s", pc->data[i].sex);
            printf("age:");
            scanf("%d", &pc->data[i].age);
            printf("tele:");
            scanf("%s", pc->data[i].tele);
            printf("addr:");
            scanf("%s", pc->data[i].addr);
            printf("modify success!\n"); 
        }
    }
    if (sigh = 0)
    {
        printf("no find!\n");
    }

}
int cmp_name(const void* e1, const void* e2)
{
    return strcmp(((peo*)e1)->name, ((peo*)e2)->name);
}
void SortContact(contact* pc)
{
    assert(pc);
    qsort(pc->data, pc->count, sizeof(peo), cmp_name);
    printf("search over!\n");
}

void SaveContact(const contact* pc)
{
    assert(pc);
    FILE* pfwrite = fopen("contact.txt", "wb");
    if (pfwrite == NULL)
    {
        perror("SaveContact");
        return;
    }
    int i = 0;
    for (i; i < pc->count; i++)
    {
        fwrite(pc->data+i, sizeof(peo), 1, pfwrite);
    }
    fclose(pfwrite);
    pfwrite = NULL;
}


int main()
{
    int input = 0;
    contact con;
    InitContact(&con);
    do
    {

        menu();
        printf("choice:");
        scanf("%d", &input);
        switch (input)
        {
            case 1:
                AddContact(&con);
                break;
            case 2:
                DelContact(&con);
                break;
            case 3:
                SearchContact(&con);
                break;
            case 4:
                ModifyContact(&con);
                break;
            case 5:
                ShowContact(&con);
                break;
            case 6:
                SortContact(&con);
                break;
            case 0:
                SaveContact(&con);
                printf("over");
                break;
            default:
                printf("Error in selection.");
                break;
        }


    }while (input);
    getchar();
    getchar();
    return 0;
}