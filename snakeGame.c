#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <poll.h>

void createSnakeBody();
void display();
void createFood();
int moveSnake();


int fx,fy;
int left=0, right=1, top=0, bottom=0;
int score = 0;

struct node
{
    int x, y;
    struct node *next;
};
struct node *head = NULL;
int main()
{
    char ch;
    createSnakeBody(2, 4);
    createSnakeBody(2, 3);
    createSnakeBody(2, 2);
    createSnakeBody(2, 1);
    createFood();
    display();
    while(1){
        struct pollfd mypoll = {STDIN_FILENO, POLLIN | POLLPRI};
        char key;
        if(poll(&mypoll, 1, 200)){
            scanf("%c",&key);
            if(key==27)
                break;
            if(key=='A' || key=='a'){ //left key
                if(right==0 && left==0){
                    left=1;
                    top=0;
                    bottom=0;
                    right=0;
                }
            }
            else if(key=='W' || key=='w'){ //top key
                if(top==0 && bottom==0){
                    left=0;
                    top=1;
                    bottom=0;
                    right=0;
                }
            }
            else if(key=='D' || key=='d'){ //right key
                if(right==0 && left==0){
                    left=0;
                    top=0;
                    bottom=0;
                    right=1;
                }
            }
            else if(key=='S' || key=='s'){ //bottom key
                if(top==0 && bottom==0){
                    left = 0;
                    top = 0;
                    bottom = 1;
                    right = 0;
                }
            }
        }
        if(moveSnake()==1){
            printf("\nGameOver\nScore = %d\n",score);
            break;
        }
        usleep(150000);
        system("clear");
        display();

    }
    return 0;
}
int moveSnake()
{
    int tx = head->x, ty = head->y;
    if(right==1){
        if(head->y!=48){
            head->y++;
            struct node *p=head->next;
            int stop=0;
            while(p!=NULL){
                if(p->x == head->x && p->y == head->y)
                    stop = 1;
                p=p->next;
            }
            if(stop == 1)
                return 1;
        }
        else
            head->y = 1;
        struct node *ptr;
        ptr = head->next;
        while(ptr!=NULL){
            int a=ptr->x;
            ptr->x = tx;
            tx=a;

            int b=ptr->y;
            ptr->y=ty;
            ty=b;
            ptr = ptr->next;
        }
    }
    else if(left==1){
        if(head->y!=1){
            head->y--;
            struct node *p = head->next;
            int stop=0;
            while(p!=NULL){
                if (p->x == head->x && p->y == head->y)
                    stop = 1;
                p = p->next;
            }
            if (stop == 1)
                return 1;
        }
        else
            head->y = 48;
        struct node *ptr;
        ptr = head->next;
        while (ptr != NULL)
        {

            int a = ptr->x;
            ptr->x = tx;
            tx = a;

            int b = ptr->y;
            ptr->y = ty;
            ty = b;

            ptr = ptr->next;
        }
    }
    else if (top == 1)
    {
        if (head->x != 1)
        {
            head->x--;
            struct node *p = head->next;
            int stop = 0;
            while (p != NULL)
            {
                if (p->x == head->x && p->y == head->y)
                    stop = 1;
                p = p->next;
            }
            if (stop == 1)
                return 1;
        }
        else
            head->x = 28;
        struct node *ptr;
        ptr = head->next;
        while (ptr != NULL){

            int a = ptr->x;
            ptr->x = tx;
            tx = a;

            int b = ptr->y;
            ptr->y = ty;
            ty = b;

            ptr = ptr->next;
        }
    }
    else if (bottom == 1){

        if (head->x != 28){
            head->x++;
            struct node *p = head->next;
            int stop = 0;
            while (p != NULL){
                if (p->x == head->x && p->y == head->y)
                    stop = 1;
                p = p->next;
            }
            if (stop == 1)
                return 1;
            
        }
        else
            head->x = 1;
        
        struct node *ptr;
        ptr = head->next;
        while (ptr != NULL){

            int a = ptr->x;
            ptr->x = tx;
            tx = a;

            int b = ptr->y;
            ptr->y = ty;
            ty = b;

            ptr = ptr->next;
        }
    }
    if (head->x == fx && head->y == fy)
    {
        createSnakeBody(tx,ty);
        score++;
        createFood();
    }
    return 0;
}
void createFood()
{
    fx= (rand()%48)+1;
    fy= (rand()%48)+1;
    struct node *ptr;
    ptr = head;
    while (1){
        int flag = 0;
        ptr = head;
        while (ptr != NULL){
            if (fx == ptr->x && fy == ptr->y){
                fx= (rand()%48)+1;
                fy= (rand()%48)+1;
                flag = 1;
            }
            ptr = ptr->next;
        }
        if (flag == 0)
            break;
        
    }
}
void createSnakeBody(int x_index, int y_index)
{
    struct node *temp, *ptr;
    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL)
        exit(0);
    
    temp->x = x_index;
    temp->y = y_index;
    temp->next = NULL;
    if (head == NULL)
        head = temp;
    else{
        ptr = head;
        while (ptr->next != NULL){
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
}
void display()
{
    for (int i = 0; i < 30; i++){
        for (int j = 0; j < 50; j++){
            struct node *ptr;
            ptr = head;
            int flag = 0;
            while (ptr != NULL){
                if (ptr->x == i && ptr->y == j){
                    if (ptr == head)
                        printf("O");
                    else
                        printf("o");
                    flag = 1;
                }
                ptr = ptr->next;
            }
            if (flag == 0){
                if (i == 0 || i == 29)
                    printf("-");
                else if (j == 0 || j == 49)
                    printf("|");
                else if (i == fx && j == fy)
                    printf("F");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
}