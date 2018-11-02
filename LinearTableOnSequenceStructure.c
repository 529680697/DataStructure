#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//有关常量的定义
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define ERROR1 -3
#define INFEASTABLE -1
#define OVERFLOW -2
//数据元素类型定义
typedef int status;
typedef int ElemType;

#define LIST_INIT_SIZE 100  //列表初始大小
#define LIST_INCREMENT 10  //列表增量

typedef struct {  //顺序表（顺序结构）的定义
    ElemType * elem;
    int length;
    int listSize;
}SqList;

typedef struct L_list{  //列表指针链表的定义
    SqList *l;
    char name[12];
    struct L_list *next;
}L_list;
//线性表的各种操作函数的声明
status InitList(SqList * L);
status DestroyList(SqList * L);
status ClearList(SqList * L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L, int i, ElemType * e);
status LocalElem(SqList L, ElemType e);  //简化过后的函数
status PriorElem(SqList L, ElemType cur_e, ElemType * pre_e);
status NextElem(SqList L, ElemType cur_e, ElemType * next_e);
status ListInsert(SqList * L, int i, ElemType e);
status ListDelete(SqList * L, int i, ElemType * e);
status ListTraverse(SqList L, void (* visit)(ElemType e));
void visit(ElemType e);

//其他函数的声明
status equal(ElemType x, ElemType y);
void display(ElemType e);
void menu(void);


void main(void){
//    SqList L1, L2;
//    L1.elem = L2.elem = NULL;
    L_list table_list, *head_list_point, *new_p;  //声明线性表指针链表(多表表头链表)
    table_list.next = NULL;
    head_list_point = &table_list;  //声明头指针指向线性表指针链表
//    p = &table_list;  //声明当前指针指向线性表指针链表(此时指向头节点)
    int option;
    do{
        system("cls");
        menu();
        printf("Please input your option[0-12]:");
        scanf("%d", &option);
        switch (option){
            case 0:
                break;
            case 1: {
                //printf("\n     here is InitList(),which  being realized\n");
                SqList *new_list=(SqList *)malloc(sizeof(SqList));  //创建新的线性表头指针节点
                new_list->elem = NULL;
                for (new_p = head_list_point; new_p->next != NULL; ) {  //找到列表头指针链表的尾节点
                    new_p = new_p->next;
                }
                new_p->l = new_list;  //把新创建的列表头指针赋给列表头指针链表的尾节点
                printf("Please enter a name for the new linear table:");  //初始化新的线性表并取名
                scanf("%s", new_p->name);
                L_list *p;  //判断线性表是否重名
                for (p = head_list_point; p->next != NULL && strcmp(p->name, new_p->name) != 0; p = p->next);
                if (p->next == NULL) {  //新线性表不重名
                    if (InitList(new_list)){
                        p->next = (struct L_list *)malloc(sizeof(L_list));
                        p->next->next = NULL;
                        printf("Linear table created successfully!\n");
                    }
                    else {  //新线性表重名
                        printf("Linear table created failed!\n");
                        free(new_list);
                    }
                }
                else {  //新线性表重名
                    printf("The name called [%s] for linear table has been used!\n", p->name);
                    free(new_list);
                }
                getchar();getchar();
                break;
            }
            case 2:
                //printf("\n     here is DestroyList(),which  being realized\n");
                if (head_list_point->next != NULL){  //判断是否有线性表指针存在
                    printf("Please enter the name of linear table which you want to destroy:");
                    char table_name[40];
                    scanf("%s", table_name);
                    L_list *cur_p, *pri_p;
                    pri_p = head_list_point;
                    if (!strcmp(pri_p->name, table_name)) {  //所删除的线性表表头指针位于链表头节点
                        if (DestroyList(pri_p->l)) {
                            printf("Linear table [%s] has been destroyed!\n", pri_p->name);
                            cur_p = pri_p;
                            pri_p = pri_p->next;
                            head_list_point = pri_p;
                            free(cur_p);
                        }
                        else
                            printf("Linear table [%s] can't be destroyed!\n", pri_p->name);
                    }
                    else {  //所删除的线性表表头指针不位于链表头节点
                        for (cur_p = pri_p->next; cur_p->next != NULL && strcmp(cur_p->name, table_name) != 0; ) {
                            pri_p = cur_p;
                            cur_p = cur_p->next;
                        }
                        if (cur_p->next == NULL) {  //要删除的线性表不存在
                            printf("The name called [%s] doesn't exist in our system.\n", table_name);
                        }
                        else {
                            if (DestroyList(pri_p->l)) {
                                printf("Linear table [%s] has been destroyed!\n", pri_p->name);
                                pri_p->next = cur_p->next;
                                free(cur_p);
                            }
                            else
                                printf("Linear table [%s] can't be destroyed!\n", pri_p->name);
                        }
                    }
                }
                else {
                    printf("There is no linear table existing in our system!\n");
                }
                getchar();getchar();
                break;
            case 3:
                //printf("\n     here is ClearList(),which  being realized\n");
                if (head_list_point->next != NULL){
                    printf("Please enter the name of linear table which you want to clear:");
                    char  table_name[40];
                    scanf("%s", table_name);
                    L_list *p;
                    for (p = head_list_point; p->next != NULL && strcmp(p->name, table_name) != 0; p = p->next);  //找到要清空的表位于的链表节点
                    if (p->next == NULL) {
                        printf("The name called [%s] doesn't exist in our system!\n", table_name);
                    }
                    else {
                        if (ClearList(p->l))
                            printf("Linear table [%s] has been cleaned!\n", p->name);
                        else
                            printf("Linear table [%s] can't be cleaned!\n", p->name);
                    }
                }
                else {
                    printf("There is no linear table existing in our system!\n");
                }
                getchar();getchar();
                break;
            case 4:
                //printf("\n     here is ListEmpty(),which  being realized\n");
                if (head_list_point->next != NULL){
                    printf("Please enter the name of linear table which you want to know whether is empty:");
                    char table_name[40];
                    scanf("%s", table_name);
                    L_list *p;
                    for (p = head_list_point; p->next != NULL && strcmp(p->name, table_name) != 0; p = p->next);
                    if (p->next == NULL) {
                        printf("The name called [%s] doesn't exist in our system!\n", table_name);
                    }
                    else {
                        if (ListEmpty(*p->l))
                            printf("Linear table [%s] is empty!\n", p->name);
                        else
                            printf("Linear table [%s] is not empty!\n", p->name);
                    }
                }
                else {
                    printf("There is no linear table existing in our system!\n");
                }
                getchar();getchar();
                break;
            case 5:
                //printf("\n     here is ListLength() ,which  being realized\n");
                if (head_list_point->next != NULL){
                    printf("Please enter the name of linear table which you want to know its length:");
                    char table_name[40];
                    scanf("%s", table_name);
                    L_list *p;
                    for (p = head_list_point; p->next != NULL && strcmp(p->name, table_name) != 0; p = p->next);
                    if (p->next == NULL) {
                        printf("The name called [%s] doesn't exist in our system!\n", table_name);
                    }
                    else {
                        printf("The length of linear table [%s] is [%d].\n", 
                                p->name, ListLength(*p->l));
                    }
                }
                else {
                    printf("There is no linear table existing in our system!\n");
                }
                getchar();getchar();
                break;
            case 6: {
                //printf("\n     here is GetElem(),which  being realized\n");
                if (head_list_point->next != NULL) {
                    printf("Please enter the name of linear table which you want to get its element:");
                    char table_name[40];
                    scanf("%s", table_name);
                    L_list *p;
                    for (p = head_list_point; p->next != NULL && strcmp(p->name, table_name) != 0; p = p->next);
                    if (p->next == NULL) {
                        printf("The name called [%s] doesn't exist in our system!\n", table_name);
                    }
                    else {
                        if (!ListEmpty(*p->l)) {
                            int num = -1;
                            ElemType e;
                            while (num == -1) {
                                printf("Please enter the number which you want to get [1-%d]:", p->l->length);
                                scanf("%d", &num);
                            }
                            while (num < 0 || num > p->l->length) {
                                printf("Please enter the right number [1-%d]:", p->l->length);
                                scanf("%d", &num);
                            }
                            if (GetElem(*p->l, num, &e))
                                printf("The value of Num.%d in linear table [%s] is [%d].",  num, p->name, e);
                        }
                        else {
                            printf("No element exists in linear table [%s] so you can't get any element!\n", p->name);
                        }
                    }
                }
                else {
                    printf("There is no linear table existing in our system!\n");
                }
                getchar();getchar();
                break;
            }
            case 7: {
                //printf("\n     here is LocalElem(),which  being realized\n");
                if (head_list_point->next != NULL){
                    printf("Please enter the name of linear table which you want to know the location of its element:");
                    char table_name[40];
                    scanf("%s", table_name);
                    L_list *p;
                    for (p = head_list_point; p->next != NULL && strcmp(p->name, table_name) != 0; p = p->next);
                    if (p->next == NULL) {
                        printf("The name called [%s] doesn't exist in our system!\n", table_name);
                    }
                    else {
                        if (!ListEmpty(*p->l)) {
                            ElemType e;
                            int i;
                            printf("Please enter the element which you want to know the order:");
                            scanf("%d", &e);
                            if ((i=LocalElem(*p->l, e)))
                                printf("The order of the element [%d] in linear table [%s] is [%d].\n", e, p->name, i);
                            else
                                printf("The element [%d] is not in linear table [%s]!\n", e, p->name);
                        }
                        else {
                            printf("No element exists in linear table [%s] so you can't get the order of any element!\n", p->name);
                        }
                    }
                }
                else {
                    printf("There is no linear table existing in our system!\n");
                }
                getchar();
                getchar();
                break;
            }
            case 8: {
                //printf("\n     here is PriorElem(),which  being realized\n");
                if (head_list_point->next != NULL){
                    printf("Please enter the name of linear table which you want to get its prior element:");
                    char table_name[40];
                    scanf("%s", table_name);
                    L_list *p;
                    for (p = head_list_point; p->next != NULL && strcmp(p->name, table_name) != 0; p = p->next);
                    if (p->next == NULL) {
                        printf("The name called [%s] doesn't exist in our system!\n", table_name);
                    }
                    else {
                        if (!ListEmpty(*p->l)) {
                            ElemType e, pre_e;
                            printf("Please enter the element which you want to know its pioneer:");
                            scanf("%d", &e);
                            ElemType result = PriorElem(*p->l, e, &pre_e);
                            if (result == ERROR)
                                printf("There is no element [%d] in linear table [%s]!\n", e, p->name);
                            else if (result == ERROR1)
                                printf("The element [%d] is the first element in linear table [%s], which has no pioneer!\n", e, p->name);
                            else
                                printf("The pioneer of element [%d] in linear table [%s] is [%d].\n", e, p->name, pre_e);
                        }
                        else {
                            printf("No pioneer exists because the linear table [%s] is empty!\n", p->name);
                        }
                    }
                }
                else {
                    printf("There is no linear table existing in our system!\n");
                }
                getchar();getchar();
                break;
            }
            case 9: {
                //printf("\n     here is NextElem(),which  being realized\n");
                if (head_list_point->next != NULL){
                    printf("Please enter the name of linear table which you want to get its next element:");
                    char table_name[40];
                    scanf("%s", table_name);
                    L_list *p;
                    for (p = head_list_point; p->next != NULL && strcmp(p->name, table_name) != 0; p = p->next);
                    if (p->next == NULL) {
                        printf("The name called [%s] doesn't exist in our system!\n", table_name);
                    }
                    else {
                        if (!ListEmpty(*p->l)) {
                            ElemType e, next_e, result;
                            printf("Please enter the element which you want to know its successor:");
                            scanf("%d", &e);
                            result = NextElem(*p->l, e, &next_e);
                            if (result == ERROR)
                                printf("There is no element [%d] in linear table [%s]!\n", e, p->name);
                            else if (result == ERROR1)
                                printf("The element [%d] id the last element in linear table [%s], which has no successor!\n",
                                       e, p->name);
                            else
                                printf("The successor of element [%d] in linear table [%s] is [%d].\n",
                                       e, p->name, next_e);
                        }
                        else {
                            printf("No successor exists because the linear table [%s] is empty!\n", p->name);
                        }
                    }
                }
                else {
                    printf("There is no linear table existing in our system!\n");
                }
                getchar();getchar();
                break;
            }
            case 10: {
                //printf("\n     here is ListInsert(),which  being realized\n");
                if (head_list_point->next != NULL){
                    printf("Please enter the name of linear table which you want to insert element to it:");
                    char table_name[40];
                    scanf("%s", table_name);
                    L_list *p;
                    for (p = head_list_point; p->next != NULL && strcmp(p->name, table_name) != 0; p = p->next);
                    if (p->next == NULL) {
                        printf("The name called [%s] doesn't exist in our system!\n", table_name);
                    }
                    else {
                        ElemType e, result;
                        int i;
                        printf("Please enter the element and its position[1-%d] which you want to insert:", p->l->length+1);
                        scanf("%d %d", &e, &i);
                        result = ListInsert(p->l, i, e);
                        if (result == ERROR)
                            printf("The position you want to insert is beyond the right range which is [1-%d]!\n", p->l->length+1);
                        else if (result == OVERFLOW)
                            printf("Memory overflow, can't insert the element!\n");
                        else
                            printf("The element [%d] had been inserted into linear table [%s] correctly!\n", e, p->name);
                    }
                }
                else {
                    printf("There is no linear table existing in our system!\n");
                }
                getchar();
                getchar();
                break;
            }
            case 11: {
                //printf("\n     here is ListDelete(),which  being realized\n");
                if (head_list_point->next != NULL){
                    printf("Please enter the name of linear table which you want to delete its element:");
                    char table_name[40];
                    scanf("%s", table_name);
                    L_list *p;
                    for (p = head_list_point; p->next != NULL && strcmp(p->name, table_name) != 0; p = p->next);
                    if (p->next == NULL) {
                        printf("The name called [%s] doesn't exist in our system!\n", table_name);
                    }
                    else {
                        if (!ListEmpty(*p->l)) {
                            ElemType e, result;
                            int i;
                            printf("Please enter the position[1-%d] of the element which you want to delete:", p->l->length);
                            scanf("%d", &i);
                            result = ListDelete(p->l, i, &e);
                            if (result == ERROR)
                                printf("The position you want to delete is beyond the right range which is [1-%d]!\n", p->l->length);
                            else
                                printf("The element [%d] in linear table [%s] had been deleted correctly!\n", e, p->name);
                        }
                        else {
                            printf("You can't delete any element because the linear table [%s] is empty!\n", p->name);
                        }
                    }
                }
                else {
                    printf("There is no linear table existing in our system!\n");
                }
                getchar();
                getchar();
                break;
            }
            case 12:
                //printf("\n     here is ListTraverse(),which  being realized\n");
                if (head_list_point->next != NULL){
                    printf("Please enter the name of linear table which you want to traverse its element:");
                    char table_name[40];
                    scanf("%s", table_name);
                    L_list *p;
                    for (p = head_list_point; p->next != NULL && strcmp(p->name, table_name) != 0; p = p->next);
                    if (p->next == NULL) {
                        printf("The name called [%s] doesn't exist in our system!\n", table_name);
                    }
                    else {
                        if (!ListEmpty(*p->l))
                            ListTraverse(*p->l, visit);
                        else
                            printf("There is no element in linear table [%s]!\n", p->name);
                    }
                }
                else {
                    printf("There is no linear table existing in our system!\n");
                }
                getchar();getchar();
                break;
            default: ;
        }
    }while (option);
    printf("\n--------------------Welcome again!--------------------\n");
    getchar();getchar();
}

void menu(void){
    printf("\n");
    printf("      Menu for Linear Table On Sequence Structure \n");
    printf("------------------------------------------------------\n");
    printf("    	  1. InitList        7. LocatElem\n");
    printf("    	  2. DestroyList     8. PriorElem\n");
    printf("    	  3. ClearList       9. NextElem \n");
    printf("    	  4. ListEmpty      10. ListInsert\n");
    printf("    	  5. ListLength     11. ListDelete\n");
    printf("    	  6. GetElem        12. ListTraverse\n");
    printf("    	  0. Exit\n");
    printf("------------------------------------------------------\n");
}

status InitList(SqList * L){
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listSize = LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList * L){
    free(L->elem);
    L->elem = NULL;
    return OK;
}

status ClearList(SqList * L){
    L->length = 0;
    return OK;
}

status ListEmpty(SqList L){
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}

int ListLength(SqList L){
    return L.length;
}

status GetElem(SqList L, int i, ElemType * e){
    *e = *(L.elem+i-1);
    return *e;
}

status LocalElem(SqList L, ElemType e){
    int i = 1;
    while (*L.elem != e){
        L.elem++;
        i++;
        if (i >L.length)
            return ERROR;  //ERROR表示线性表L中无e元素
    }
    return i;  //返回L中第1个与e相等的数据元素的位序
}//简化过后的函数

status PriorElem(SqList L, ElemType cur_e, ElemType * pre_e){
    int i = LocalElem(L, cur_e);
    if (i!=0 && i!=1){
        *pre_e = L.elem[i-2];
        return *pre_e;  //返回cur_e的前驱
    }
    else if (i==0)
        return ERROR;  //ERROR表示线性表L中无cur_e元素
    else
        return ERROR1;  //ERROR1代表当前元素为线性表L的第一个元素，无法获得前驱

}

status NextElem(SqList L, ElemType cur_e, ElemType * next_e){
    int i = LocalElem(L, cur_e);
    if (i!=0 && i!=L.length){
        *next_e = L.elem[i];
        return *next_e;  //返回cur_e的后继
    }
    else if (i==0)
        return ERROR;  //ERROR表示线性表L中无cur_e元素
    else
        return ERROR1;  //ERROR1代表当前元素为线性表L的最后一个元素，无法获得后继
}

status ListInsert(SqList * L, int i, ElemType e){
    ElemType *new_l = NULL, *t, *p;
    if (i < 1 || i > L->length + 1) return ERROR;  //ERROR表示想要插入的位置位于表外，无法插入
    if (L->length>=L->listSize){
        new_l = (ElemType *)realloc(L->elem, (L->listSize+LIST_INCREMENT)*sizeof(ElemType));
        if (!new_l) return OVERFLOW;  //表示表格创建失败(内存溢出)
        L->elem = new_l;
        L->listSize += LIST_INCREMENT;
    }
    t = &(L->elem[i-1]);
    for (p = &(L->elem[L->length-1]); p>=t; p--) {
        *(p+1) = *p;
    }
    *t = e;
    ++L->length;
    return OK;
}

status ListDelete(SqList * L, int i, ElemType * e){
    ElemType *t, *p;
    if (i<1 || i >L->length) return ERROR;
    p = &(L->elem[i-1]);
    *e = *p;
    t = &(L->elem[L->length-1]);
    for (p++; p <= t; ++p)
        *(p-1) = *p;
    --L->length;
    return OK;
}

status ListTraverse(SqList L, void (* visit)(ElemType e)){
    int i;
    for (i = 0; i < L.length; ++i) {
        visit(L.elem[i]);
    }
    return OK;
}

void visit(ElemType e){
    printf("%d ", e);
}