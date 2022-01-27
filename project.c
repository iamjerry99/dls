#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

struct node_rec
{
    int date;
    char cust_name[100];
    char status[50];
    struct node_rec *lptr;
    struct node_rec *rptr;
};

typedef struct node_rec *node;
node new, temp, prev;
typedef node header;

header createNode()
{
    header L;
    L = (struct node_rec *)malloc(sizeof(struct node_rec));
    L->lptr = NULL;
    L->rptr = NULL;
    return L;
}

int isEmpty(header L)
{
    if(L->rptr==NULL) {
        return 1;
    }
    else {
        return 0;
    }
}


int number_of_days()
{
    int month,year,  x;
    time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    month = current_time->tm_mon + 1;
    if(month == 2)
    {
        year = current_time->tm_year + 1900;
        if((year % 400 == 0 ) || (month % 100 != 0 && month % 4 == 0))
            return 29;
        return 28;
    }
    if(month == 1 || month == 3 ||  month == 5 || month ==  7  || month == 8 || month == 10 || month == 12)
        return 31;
    return 30;
}

void insertEnd(header L, int x)
{
    new = (struct node_rec *)malloc(sizeof(struct node_rec));
    new->date = x;
    strcpy(new->status,"Empty");
    strcpy(new->cust_name,"\0");
    if(isEmpty(L))
    {
        L->rptr = new;
        new->lptr = L;
        new->rptr = NULL;
    }
    else
    {
        temp = L->rptr;
        while(temp->rptr != NULL)
        {
            temp = temp->rptr;
        }
        temp->rptr = new;
        new->lptr = temp;
        new->rptr = NULL;
    }
}


int makeList(header L)
{
    int x = number_of_days();
    node new;
    for(int i = 1; i <= x; i++)
        insertEnd(L, i);

}



void display(header L)
{
    int month,year,century,day, w, z, noofdays, first, i, x = 0, y;
    node temp, prev;
    temp = L->rptr;
    time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    if(!isEmpty(L))
    {
        year = current_time->tm_year + 1900;
        month = current_time->tm_mon + 1;
        century = (year/100) +1;
        day = 1;
        year = year % 100;
        if(month == 1 || month == 2)
            year--;
        if(month == 1)
            month = 11;
        else if(month == 2)
            month = 12;
        else
            month = month - 2;
        w = (int)(day + floor(2.6*month - 0.2) - 2*century + year + floor(year/4) + floor(century/4)) % 7;
        if(w < 0)
            w = w + 7;
        w = (w + 2) % 7;
        noofdays = number_of_days();
        first = w;
        puts("");
        printf("=============================\n");
        switch(w)
        {
            case 0:
            {
                printf(" SU  MO  TU  WE  TH  FR  SA\n");
                break;
            }
            case 1:
            {
                printf(" MO  TU  WE  TH  FR  SA  SU\n");
                break;
            }
            case 2:
            {
                printf(" TU  WE  TH  FR  SA  SU  MO\n");
                break;
            }
            case 3:
            {
                printf(" WE  TH  FR  SA  SU  MO  TU\n");
                break;
            }
            case 4:
            {
                printf(" TH  FR  SA  SU  MO  TU  WE\n");
                break;
            }
            case 5:
            {
                printf(" FR  SA  SU  MO  TU  WE  TH\n");
                break;
            }
            case 6:
            {
                printf(" SA  SU  MO  TU  WE  TH  FR\n");
                break;
            }
        }
        printf("___________\n\n");
        while(temp != NULL)
        {
            printf(" %2d ",temp->date);
            prev = temp;
            temp = temp->rptr;
            x++;
            if(temp == NULL)
            {
                puts("");
                while(x != 1)
                {
                    prev = prev->lptr;
                    x--;
                }
                while(prev != NULL)
                {
                    if(!strcmp(prev->status, "Empty"))
                        printf("    ");
                    else
                        printf("  X "); 
                    prev = prev->rptr;
                }
                break;
            }
            if(temp->date > 1 && (temp->date - 1)%7 == 0)
            {
                puts("");
                y = temp->date;
                while(x!= 0)
                {
                    temp = temp->lptr;
                    x--;
                }
                while(temp->date != y)
                {
                    if(!strcmp(temp->status, "Empty"))
                        printf("    ");
                    else
                        printf("  X ");
                    temp = temp->rptr;
                    if(temp == NULL)
                        break;
                }
                puts("");
                puts("");
            }
        }
        puts("");
        printf("=============================\n\n");

    }
}

//SORRY, I NEEDED TO DISCARD THE LIST TO CHECK IF MY PART IS WORKING, YOU CAN REPLACE IT WIHT YOUR FUNCTION
void makeEmpty(header L)
{
    if(isEmpty(L))
    {
        printf("List is already empty\n");
    }
    else
    {
        temp = L->rptr;
        while(temp != NULL)
        {
            prev = temp;
            temp = temp->rptr;
            free(prev);
        }
        L->rptr = NULL;
    }
}

void deleteList(header L)
{
    if(!isEmpty(L))
    {
        makeEmpty(L);
    }
    free(L);
}

void remove_slot(int X,node L)
{
	int i=0;
	
	if(!isEmpty(L))
	{
		temp=L->rptr;
		while(temp!=NULL)
		{
			if(temp->date==X)
			{
				strcpy(temp->status,"Empty");
				strcpy(temp->cust_name,"\0");
			}

			temp=temp->rptr;
		}
	}
}

int count_slots(char name[100],node L)
{
	int i=0;
	
	if(!isEmpty(L))
	{
		temp=L->rptr;
		while(temp!=NULL)
		{
			if(strcmp(temp->cust_name,name) && strcmp(temp->status,"Booked"))
				i++;
			temp=temp->rptr;
		}
		return i;
	}
}


void findpos(header L)
{
int i=0;
int flag;
if(!isEmpty(L->rptr))
{
temp=L->rptr;
printf("\nenter the name u want to find date :");
char na[100];
scanf("%s",na);

while(temp!=NULL)
{
if(strcmp(temp->cust_name , na)==0)
{
printf("Date for the booked slot on:%d",i+1);
flag=0;
break;
}
else
{
flag=1;
}
i++;
temp=temp->rptr;
}
if(flag==1)
{
printf("\n date not found\n");
}
}
}



void add_slot(int X , node L)
{
int i=0;
if(!isEmpty(L))
{
temp=L->rptr;
while(temp != NULL)
{
if(temp->date==X)
 {
               { 
                   if(strcmp(temp->status,"Booked"))
                    {
                        printf("Slot already filled");
                          break;
                    }
                }

{
printf("\nenter your name :");
scanf("%s",temp->cust_name);
getchar();//comment
strcpy(temp->status,"Booked");
break;
}
temp = temp->rptr;
}
}
}
void dispose(header L)
{
    if(isEmpty(L))
    {
        printf("List is already empty\n");
    }
    else
    {
        temp = L->rptr;
        while(temp != NULL)
        {
            prev = temp;
            strcpy(prev->status ,"Empty");
            temp = temp->rptr;
            //free(prev);
        }
        //L->rptr = NULL;
    }
    
}
int main()
{
    int x,choice,i;
    char name[100];

    node L;
    L = createNode();
    makeList(L);

    do
    {
    printf("\n------------------Party Hall Booking System-----------------");
    printf("\n1.Display");
    printf("\n2.find date");
    printf("\n3.add booking slot ");
    printf("\n4.Remove Booking Slot");
    printf("\n5.Count the no. of slots booked by a person");
    printf("\n6.dispose");
    printf("\n7.Exit");
    printf("\nEnter your choice=");
    scanf("%d",&choice);
    getchar();//comment
    switch(choice)
    {
       case 1:
       {
		display(L);
		break;
       }
       case 2:
       {
          //findpos(L,name);
          findpos(L);
          break;
       }
        case 3:
        {
             printf("\nEnter the date:");
             scanf("%d", &x);
             getchar();//comment
             add_slot(x, L);
             break;
        }
       case 4:
       {
		printf("\nEnter the date=");
		scanf("%d",&x);
		remove_slot(x,L);
		break;
       }
       case 5:
       {
		printf("\nEnter the customer name=");
		scanf("%s",name);
		i=count_slots(name,L);
		printf("\nNo. of slots booked by the customer=%d",i);
		break;
       }
       case 6:
       {
          dispose(L);
           break;
       }
    }

    }while(choice!=7);
     deleteList(L);
 
    
 
    return 0;
}


