#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <crtdbg.h>
#define Q_MAX 50


typedef struct human {
    char id;
    int ta;
    int ts;
}human;

struct queue {
    human data[Q_MAX];
    int end;
    int begin;
};

typedef struct list {
    human data;
    struct list* next;
}list;

typedef struct que {
    list* begin;
    list* end;
}que;


int getInt(int* a);
human gethuman();


void initialization(que* initq);
int isempty(que* empty);
void add(que* new_slot, human* new_member);
list* get_list(list* next, human* data);
human remove_human(que* removing);
void output(struct que* x);
int time_sum(que* queue);
int len_que(que* queue);


//void initialization(struct queue* initq); //�� �������
//int isempty(struct queue* empty);           
//void add(struct queue* new_slot,  human* new_member);
//human remove_human(struct queue* removing);
//void output(struct queue* x);
//int time_sum(queue* queue);
//int len_que(queue* queue);




int main()
{   
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    int i;
    char warning[31] = "\nIvalid number of passengers\n\0";
    char s[31] = "\0";
    srand(time(NULL));
    printf("Entfer registration stands quantity:");
    int n;
    do
    {
        printf("%s", s);
        strcpy_s(s, 31 * sizeof(char), warning);
        getInt(&n);
    } while (n < 1);
    printf("Enter the number of passengers:");
    int q;
    *s = '\0';
    do
    {
        printf("%s", s);
        strcpy_s(s, 31 * sizeof(char), warning);
        getInt(&q);
    } while (q < 1);

    /*
    struct queue* queue = (struct queue*)malloc(sizeof(struct queue) * n);;         //�� �������
    for (i = 0; i < n; i++)
        initialization(queue + i);
*/

    struct que* queue = (struct que*)malloc(sizeof(struct que) * n);;               //�� ������
    for (i = 0; i < n; i++)
        initialization(queue + i);




    human* humen = (human*)malloc(sizeof(human) * q);

    for (i = 0; i < q; i++)
    {
        humen[i] = gethuman();


    }

    int tmax = 0;
    for (i = 0; i < q; i++)
        if (tmax < humen[i].ta + humen[i].ts)
            tmax = humen[i].ta + humen[i].ts;

    //������������ �� ��������
    int t = 0;
    int j;
    for (t = 0; t <= tmax + 1; t++)
    {
        int changes = 0;
        //������� ������

        for (i = 0; i < n; i++)
            while (isempty(queue + i) == 0 && time_sum(queue + i) < t)
            {
                remove_human(queue + i);
                changes++;
            }

        //��������� �����


        for (i = 0; i < q; i++)
            if (humen[i].ta == t)
            {
                int p1 = rand() % n;
                int p2;
                do
                    p2 = rand() % n;
                while (p2 == p1);
                human tmp = humen[i];
                if (isempty(queue + p1))
                {
                    changes++;
                    add(queue + p1, &tmp);
                }
                else if (isempty(queue + p2))
                {
                    changes++;
                    add(queue + p2, &tmp);
                }
                else if (len_que(queue + p1) <= len_que(queue + p2))
                {
                    changes++;
                    add(queue + p1, &tmp);
                }
                else
                {
                    changes++;
                    add(queue + p2, &tmp);
                }
            }
        //������� ���������

        if (changes || t == 0 || t == tmax + 1)
        {
            printf("\n\nT = %d", t);
            for (i = 0; i < n; i++)
            {
                printf("\n%d: ", i + 1);
                output(queue + i);
            }
        }

    }


    return 0;
};





int getInt(int* a)
{
    int n;
    do
    {
        n = scanf("%d", a);
        if (n < 0)
            return 0;
        if (n == 0)
        {
            printf("%s\n", "Error! Repeat input");
            scanf("%*c", 0);
        }
    } while (n == 0);
    char c = 0;     //������� ������ �������� ������
    scanf("%c", &c);
    if (((c != ' ') && (c != '\n')))
    {
        scanf("%*[^\n]");
        scanf("%*c");
    }
    return 1;
}



human gethuman() {
    int ta, ts;
    human tmp;
    char id;
    printf("Enter passenger info\n");
    scanf("%c/%d/%d", &id, &ta, &ts);

    char c = 0;     //������� ������ �������� ������
    scanf("%c", &c);
    if (((c != ' ') && (c != '\n')))
    {
        scanf("%*[^\n]");
        scanf("%*c");
    }
    tmp.id = id;
    tmp.ta = ta;
    tmp.ts = ts;
    return tmp;
}







void initialization(que* initq) {                          //�� ������
    initq->begin = NULL;
    initq->end = NULL;
    return;
}

int isempty(que* empty) {
    if (!(empty->begin)) return 1;
    return 0;
}

void add(que* new_slot, human* new_member)
{
    if (isempty(new_slot))
    {
        new_slot->end = get_list(NULL, new_member);
        new_slot->begin = new_slot->end;
    }
    else
    {
        new_slot->end->next = get_list(NULL, new_member);
        new_slot->end = new_slot->end->next;
    }

    return;
}

list* get_list(list* l_next, human* h_data)
{
    list* tmp = (list*)malloc(sizeof(list));
    tmp->data = *h_data;
    tmp->next = l_next;
    return tmp;
}

human remove_human(que* removing) {
    human hum;
    hum.id = '0';
    hum.ta = 0;
    hum.ts = 0;
    if (isempty(removing) == 1)
    {
        printf("\nQueue is empty\n");
        return hum;
    };

    hum = removing->begin->data;
    list* tmp = removing->begin;
    removing->begin = removing->begin->next;
    free(tmp);

    return hum;
}

void output(struct que* x)
{
    if (isempty(x) == 1) {
        printf("Queue is empty"); return;
    }
    for (list* h = x->begin; h != NULL; h = h->next)
        printf("%c ", h->data.id);

    return;
}


int time_sum(que* queue)
{
    return queue->begin->data.ts + queue->begin->data.ta;
}

int len_que(que* queue)
{
    int i = 0;
    for (list* h = queue->begin; h != NULL; h = h->next, i++);
    return i;
}

/*void initialization(struct queue* initq) {                        //�� �������
    initq->begin = 1;
    initq->end = 0;
    return;
}



int isempty(struct queue* empty) {                                //�� �������
    if (empty->end < empty->begin) return 1;
    else return 0;
}




void add(struct queue* new_slot, human* new_member)
{
    if (new_slot->end < Q_MAX - 1) {
        new_slot->end += 1;
        new_slot->data[new_slot->end] = *new_member;
    }
    else printf("\nNo more space in queue!\n");
    return;
}


human remove_human(struct queue* removing) {
    human tmp;
    tmp.id = '0';
    tmp.ta = 0;
    tmp.ts = 0;
    if (isempty(removing) == 1) { printf("\nQueue is empty\n");  return tmp; };
    tmp = removing->data[removing->begin];
    removing->begin += 1;
    return tmp;
}


void output(struct queue* x)
{
    int i;
    if (isempty(x) == 1) {
        printf("Queue is empty"); return;
    }
    for (i = x->begin; i <= x->end; i++)
    {
        printf("%c ", x->data[i]);

    }

    return;
}


int time_sum(queue* queue)
{
    return (queue[i].data[queue[i].begin].ta + queue[i].data[queue[i].begin].ts);
}

int len_que(queue* queue)
{
    return queue->end - queue->begin;
}
*/
