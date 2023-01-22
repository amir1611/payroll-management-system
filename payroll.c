#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define Size 50

struct company // Main structure declaration
{
    char c_name[30];
    char c_add[30];
    int c_year;
};

struct employee // Main structure declaration
{
    char e_id[10];
    char e_name[30];
    int age;
    char e_gender[10];
    char e_email[30];
    char e_date[10];
    char position[100];
    int hour;
    float salary;
};

struct statutory
{
    int n_epf;
    float amount_epf;
    int n_socso;
    float amount_socso;
};

struct Salary
{
    float T_salary;
};

struct person
{
    char name[30];
    char email[30];
    int age;
    char gender[30];
    char ic[15];
    char dob[20];
    int maritial_s;
    struct employee e;  // Nested Structure declaration
    struct statutory s; // Nested Structure declaration
    struct Salary t;
    struct person *ptrnext; // for linked list, queue and sort
};
//////////////////////////////////////////////////////////////////////////////////
// functions to implement stack using linked list-below the main operations push and pop are implemented
/*The push function adds a new element to the top of the stack by creating a new Node and updating the top pointer.
 The pop function removes the top element and returns its value by updating
 the top pointer and freeing the memory allocated for the removed element.*/
struct Node
{
    struct person data;
    struct Node *next;
};

struct Node *top = NULL;

void push(struct person data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = top;
    top = newNode;
}

struct person pop()
{
    if (top == NULL)
    {
        printf("Error: Stack is empty\n");
        struct person empty = {"", "", 0, "", "", "", 0};
        return empty;
    }
    struct person data = top->data;
    struct Node *temp = top;
    top = top->next;
    free(temp);
    return data;
}
////////////////////////////////////////////////////////////////////////////////////////
struct search
{
    char id[30];
};

// linked list insert at the beginning
struct person *headptr, *newptr, *currentptr, *previousptr, *front = NULL, *rear = NULL;
struct person *start = NULL;
struct person *last = NULL;

struct person *temp;
struct company c_detail();        // return a structure to a calling function
struct person *enqueue_manager(); // enqueue //return a structure to a calling function
void dequeue_manager();           // dequeue
void add_employee();
void edit_employee(struct search);
void delete_employee(struct search);
void display_employee();                            // sorting
void print_slip(struct company);                    // using linear sequential search
void swapNode(struct person *x, struct person *y);  // swap the hours //
void swapNode2(struct person *x, struct person *y); // swap the total salary //
void addLast(struct person *);                      // Selection Sort //

void push_manager();

void pop_manager();
void main() // Main Menu//
{
    int menu, type, i, choice = TRUE, j = TRUE;
    struct person p;
    struct company c;
    struct search s;
    struct person *e;

    // localtime() uses the time pointed by t ,to fill a tm structure with the values that represent the corresponding local time.
    time_t t;
    struct tm *tmp;
    char MY_TIME[Size];
    time(&t);
    tmp = localtime(&t);

    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%d/%m/%Y - %I:%M %p", tmp);
    printf("\n\t\t\tAccessing the system on %s\n", MY_TIME);

    printf("\n\t\t\t----------------------------------------");
    printf("\n\t\t\t  WELCOME TO PAYROLL MANAGEMENT SYSTEM ");
    printf("\n\t\t\t----------------------------------------");
    c = c_detail();
    printf("\n\n\t\t\tData is Saving.......");
    printf("\n\n\t\t\t(Click [ENTER] To Proceed)");
    getch();
    system("cls");
    while (j == TRUE)
    {
        printf("\n\t\t\t\t\tMANAGER LIST"); // enqueue and dequeue
        printf("\n\t\t\t _________________");
        printf("\n\t\t\t| [1] ADD MANAGER                                   |"); // enqueue
        printf("\n\t\t\t|_________________|");
        printf("\n\t\t\t| [2] DELETE MANAGER                                |"); // linear search and dequeue
        printf("\n\t\t\t|_________________|");
        printf("\n\t\t\t| [3] CONTINUE                                      |");
        printf("\n\t\t\t|_________________|\n\t\t\t\t\t\t\t\t");
        printf("\n\t\t\t\tPLEASE CHOOSE A NUMBER IN THE BOX ABOVE");

        printf("\n\n\tEnter choice: ");
        scanf(" %d", &i);
        switch (i)
        {
        /*case 1:
            front = enqueue_manager();
            printf("\n\n\t\t***Manager Name*\n");
            struct person *temp_queue = front;
            printf("\n\t\t");
            while (temp_queue)
            {
                printf(" %s->", temp_queue->name);

                temp_queue = temp_queue->ptrnext;
            }
            printf("NULL");
            printf("\n\n\t\t(Data is Saving...)");
            printf("\n\n\t\t(Click [ENTER] To Proceed)");
            getch();
            system("cls");
            break;*/
        case 1:
            push_manager();
            printf("\n\n\t\t***Manager Name*\n");
            struct person data = top->data;
            printf("\n\t\t%s", data.name);
            printf("\n\n\t\t(Data is Saving...)");
            printf("\n\n\t\t(Click [ENTER] To Proceed)");
            getch();
            system("cls");
            break;

        case 2:
            pop_manager();
            break;

        case 3:
            j = FALSE;
            break;

        default:
            printf("\nEnter only one from the above");
        }
    }

    headptr = NULL;

    system("cls");
    while (choice == TRUE)
    {
        printf("\n\t\t\t\t\tPAYROLL MANAGEMENT MENU");
        printf("\n\t\t\t___________________");
        printf("\n\t\t\t| [1] MANAGE EMPLOYEES                            |");
        printf("\n\t\t\t|_________________|");
        printf("\n\t\t\t| [2] PRINT SLIP                                  |"); // implement linear search //
        printf("\n\t\t\t|_________________|");
        printf("\n\t\t\t| [3] EXIT                                        |");
        printf("\n\t\t\t|_________________|\n\t\t\t\t\t\t\t\t");

        printf("\n\t\t\t\tPLEASE CHOOSE A NUMBER IN THE BOX ABOVE");
        printf("\n\n\tEnter choice: ");
        scanf(" %d", &menu);
        system("cls");
        switch (menu)
        {
        case 1:
            printf("\n\t\t\t\t\tMANAGE EMPLOYEES");
            printf("\n\t\t\t__________________");
            printf("\n\t\t\t| [1] ADD EMPLOYEES                               |"); // implement enqueue//
            printf("\n\t\t\t|_________________|");
            printf("\n\t\t\t| [2] EDIT EMPLOYEES                              |"); // implement linear search
            printf("\n\t\t\t|_________________|");
            printf("\n\t\t\t| [3] DELETE EMPLOYEES                            |"); // implement dequeue//
            printf("\n\t\t\t|_________________|");
            printf("\n\t\t\t| [4] DISPLAY EMPLOYEES                           |"); // implement sorting
            printf("\n\t\t\t|_________________|");
            printf("\n\t\t\t| [5] EXIT                                        |");
            printf("\n\t\t\t|_________________|");

            printf("\n\n\t\t\t\tPLEASE CHOOSE A NUMBER IN THE BOX ABOVE");
            printf("\n\n\tEnter choice: ");
            scanf("%d", &type);
            switch (type)
            {
            case 1:
                add_employee();
                break;

            case 2:
                printf("\n\n\tEnter Employee ID You Want to Edit: ");
                fflush(stdin);
                scanf("%s", &s.id);
                edit_employee(s); // passing structure to a function //
                break;

            case 3:
                printf("\n\n\tEnter Employee ID You Want to Delete: ");
                fflush(stdin);
                scanf("%s", &s.id);
                delete_employee(s); // passing structure to a function //
                break;

            case 4:
                display_employee(); // implement sorting
                break;

            case 5:
                choice = FALSE;
                break;

            default:
                printf("\nEnter only one from the above");
            }
            break;

        // implement linear searching
        case 2:
            print_slip(c);
            break; // passing structure to function

        case 3:
            system("cls");
            choice = FALSE;
            printf("\n\n\t\t**Thank You For Using Payroll Management System, See You Again**\n\n");
            break;

        default:
            printf("\nEnter only one from the above");
        }
    }
}

struct company c_detail()
{
    struct company c;

    // company information
    printf("\n\n\t\t\t Company Name : ");
    scanf("%[^\n]s", &c.c_name);
    fflush(stdin);
    printf("\n\n\t\t\t Company Address : ");
    gets(c.c_add);
    printf("\n\n\t\t\t Company Organization Years: ");
    scanf(" %d", &c.c_year);

    return c;
}

struct person *enqueue_manager() // queue insert
{
    newptr = (struct person *)malloc(sizeof(struct person));

    system("cls");
    printf("\n\t\t\t***ADD MANAGER**");
    printf("\n\n\t Manager Name : ");
    fflush(stdin);
    scanf("%[^\n]s", &newptr->name);
    printf("\n\n\t No IC : ");
    scanf("%s", &newptr->ic);
    printf("\n\n\t Age : ");
    scanf("%d", &newptr->age);
    printf("\n\n\t Gender [FEMALE,MALE] : ");
    scanf("%s", &newptr->gender);
    printf("\n\n\t Date of Birth [DD/MM/YY] : ");
    scanf("%s", &newptr->dob);
    printf("\n\n\t E-mail : ");
    scanf("%s", &newptr->email);
    printf("\n\n\t Maritial Status [1-SINGLE, 2-MARRIED, 3-DIVORCED]: ");
    scanf("%d", &newptr->maritial_s);

    newptr->ptrnext = NULL;

    if (front == NULL && rear == NULL)
    {
        front = rear = newptr;
    }
    else
    {
        // add newnode in rear->next
        rear->ptrnext = newptr;

        // make the new node as the rear node
        rear = newptr;
    }
    return front;
}
/*You can see that, I have replaced the enqueue_manager function with a function named push_manager that takes no argument.
I have removed the front and rear pointers, as they are not needed for a stack implementation.
Instead, I have added a call to the push function at the end of the enqueue_manager function
to add the new element to the stack.*/
void push_manager()
{
    struct person *newptr = (struct person *)malloc(sizeof(struct person));

    system("cls");
    printf("\n\t\t\t***ADD MANAGER**");
    printf("\n\n\t Manager Name : ");
    fflush(stdin);
    scanf("%[^\n]s", &newptr->name);
    printf("\n\n\t No IC : ");
    scanf("%s", &newptr->ic);
    printf("\n\n\t Age : ");
    scanf("%d", &newptr->age);
    printf("\n\n\t Gender [FEMALE,MALE] : ");
    scanf("%s", &newptr->gender);
    printf("\n\n\t Date of Birth [DD/MM/YY] : ");
    scanf("%s", &newptr->dob);
    printf("\n\n\t E-mail : ");
    scanf("%s", &newptr->email);
    printf("\n\n\t Maritial Status [1-SINGLE, 2-MARRIED, 3-DIVORCED]: ");
    scanf("%d", &newptr->maritial_s);

    newptr->ptrnext = NULL;
    push(*newptr);
}

void dequeue_manager() // queue delete
{
    struct person *temp_queue;
    // used to free the first node after dequeue
    if (front == NULL)
    {
        printf("\n\n\t\tManager List is Empty. Unable to perform delete\n");
    }
    else
    {
        // take backup
        temp_queue = front;
        // make the front node points to the next node
        // logically removing the front element
        front = front->ptrnext;
        if (front == NULL)
        {
            rear = NULL;
        }
        // free the first node
        free(temp_queue);
        system("cls");
        printf("\n\n\t\tDelete Successful.");
        struct person *temp_queue = front;
        printf("\n\n\t\t***Manager Name*");
        printf("\n\n\t\t");
        while (temp_queue)
        {
            printf(" %s->", temp_queue->name);
            temp_queue = temp_queue->ptrnext;
        }
        printf("NULL\n\n");
    }
}
/*You can see that, I have replaced the dequeue_manager function with a function named pop_manager that takes no argument.
I have removed the front,rear and temp_queue pointers, as they are not needed for a stack implementation.
Instead, I have added a call to the pop function at the beginning of the pop_manager function to remove the top element from the stack.
*/
void pop_manager()
{
    if (top == NULL)
    {
        printf("Error: Stack is empty\n");
    }
    else
    {
        struct person data = pop();
        printf("\n\n\t\tDelete Successful.");
        printf("\n\n\t\t***Manager Name*\n\t\t%s", data.name);
    }
}

void add_employee() // linked list insert at the end
{
    newptr = (struct person *)malloc(sizeof(struct person));
    system("cls");
    printf("\n\t\t\t\tPLEASE ENTER EMPLOYEE'S DETAILS TO BE ADDED");
    printf("\n\t\t\t\t-------------------------------------------------");
    printf("\n\n\t\t\t Employee ID : ");
    scanf("%s", &newptr->e.e_id);
    printf("\n\t\t\t Name : ");
    fflush(stdin);
    scanf("%[^\n]s", &newptr->e.e_name);
    printf("\n\t\t\t Email : ");
    scanf("%s", &newptr->e.e_email);
    printf("\n\t\t\t Gender [FEMALE, MALE] : ");
    scanf("%s", &newptr->e.e_gender);
    printf("\n\t\t\t Age : ");
    scanf("%d", &newptr->e.age);
    printf("\n\t\t\t Employment Date [DD/MM/YYYY] : ");
    scanf("%s", &newptr->e.e_date);
    printf("\n\t\t\t Working Hours : ");
    scanf("%d", &newptr->e.hour);

    printf("\n\t\t\t Salary : RM");
    scanf("%f", &newptr->e.salary);
    printf("\n\t\t\t Position : ");
    fflush(stdin);
    scanf("%[^\n]s", &newptr->e.position);
    printf("\n\t\t\t No EPF : ");
    scanf("%d", &newptr->s.n_epf);
    printf("\n\t\t\t No Socso : ");
    scanf("%s", &newptr->s.n_socso);
    addLast(newptr);
    if (headptr == NULL)
    {
        headptr = newptr;
        newptr->ptrnext = NULL;
    }
    else
    {
        newptr->ptrnext = headptr;
        headptr = newptr;
    }
    printf("\n\n\t\t\tData is Saving........");
    printf("\n\n\t\t\t(Click [ENTER] To Proceed)");

    getch();
    printf("\n\n");
}
// Selection Sort For Employee Working hour and their Salary(newNode return to calling function) //
struct person *newNode(float i, int x)
{
    // create node to add Working hours and Salary in the other new node//
    struct person *newNode = (struct person *)malloc(sizeof(struct person));
    newNode->e.hour = x;
    newNode->e.salary = i;
    newNode->ptrnext = NULL;
    return newNode;
}
// For selection sort pass to the function //
void addLast(struct person *e)
{
    int x;
    char y[30];
    float i;
    x = e->e.hour;
    i = e->e.salary;
    struct person *hodor = newNode(i, x);
    if (start == NULL)
    {
        start = hodor;
        last = hodor;
    }
    else
    {
        last->ptrnext = hodor;
        last = hodor;
    }
}
void edit_employee(struct search s) // linked list update data
{
    int editdata;

    system("cls");
    // using delete in the middle techniques/linear search to search employee ID
    if (headptr == NULL) // node is empty?
    {
        printf("\n\n\tThe list is empty. Cannot delete!!!\n\n"); // the list is empty
    }
    else
    {
        currentptr = headptr;
        while (currentptr->ptrnext != NULL)
        {
            if (strcasecmp(currentptr->e.e_id, s.id) == 0) // found the location
            {
                break;
            }
            else
            {
                previousptr = currentptr;         // save the previous current address
                currentptr = currentptr->ptrnext; // point to next node
            }
        }
        if (strcasecmp(currentptr->e.e_id, s.id) == 0)
        {
            printf("\n\t\t1. Position");
            printf("\n\t\t2. Working Hours per Day");
            printf("\n\t\t3. Salary");
            printf("\n\n\t\tEnter data you want to Edit: ");
            scanf(" %d", &editdata);
            if (editdata == 1) // overwrite data
            {
                printf("\n\n\t\tEnter your new position :");
                fflush(stdin);
                scanf("%[^\n]s", &currentptr->e.position);
            }
            else if (editdata == 2) // overwrite data
            {
                printf("\n\n\t\tEnter your new working hours :");
                scanf(" %d", &currentptr->e.hour);
            }
            else // overwrite data
            {
                printf("\n\n\t\tEnter your new salary :");
                scanf(" %f", &currentptr->e.salary);
            }
            printf("\n\n\t\tEdit Successful, Data is Saving......\n\n");
            printf("\t\t(Click [ENTER] To Proceed)\n");
        }
        else
        {
            printf("\n\n\tSorry, no match Employee ID found");
            return;
        }
    }
}
void delete_employee(struct search s) // linked list delete data
{
    int number;
    system("cls");
    // using delete in the middle list/linear search to search employee id
    if (headptr == NULL)
    {
        printf("\n\n\tThe list is empty. Cannot delete!!!\n"); // the list is empty
    }
    else
    {
        currentptr = headptr;
        while (currentptr->ptrnext != NULL)
        {
            if (strcasecmp(currentptr->e.e_id, s.id) == 0)
            {
                break;
            }
            else
            {
                previousptr = currentptr;
                currentptr = currentptr->ptrnext;
            }
        }
        if (strcasecmp(currentptr->e.e_id, s.id) == 0)
        {
            if (currentptr == headptr)
            {
                headptr = currentptr->ptrnext;
                free(currentptr);
            }
            else
            {
                previousptr->ptrnext = currentptr->ptrnext;
                free(currentptr);
            }
        }
        else
        {
            printf("\n\tEmployee ID to be deleted is not in the list!!!\n\n"); // no match
        }
    }
    printf("\n\n\t\tEmployee %s Successful Deleted....\n\n", s.id);
}
void display_employee() // sorting salary and working hours from low to high
{
    int i = 1, sort, choice = TRUE;
    struct person *key;
    system("cls");
    if (headptr == NULL)
    {
        printf("\n\tEmpty list...\n\n");
    }
    else
    {
        currentptr = headptr;
        system("cls");
        printf("\n\n\tEmployee List");
        printf("\n\t--------------------------------");
        do
        {
            printf("\n\n\tEmployee No %d", i);
            printf("\n\tEmployee ID : %s", currentptr->e.e_id);
            printf("\n\tName : %s", currentptr->e.e_name);
            printf("\n\tPosition : %s", currentptr->e.position);
            printf("\n\tDate Employment : %s", currentptr->e.e_date);
            printf("\n\tTotal Hours for work : %d", currentptr->e.hour);
            printf("\n\tTotal Salary for work : RM%.2f", currentptr->e.salary);
            printf("\n\t--------------------------------");
            printf("\n\n\t(Click [ENTER] To Proceed)");
            currentptr = currentptr->ptrnext; // point to next node
            i++;
        } while (currentptr != NULL);
        getch();

        while (choice == TRUE)
        {
            printf("\n\n\t\t\tItem");
            printf("\n\t______________");
            printf("\n\t| [1] Total Hours Work               |");
            printf("\n\t| [2] Salary                         |");
            printf("\n\t| [3] Exit                           |");
            printf("\n\t--------------------------------------");

            printf("\n\n\tSelect What Item To Sort : ");
            scanf(" %d", &sort);
            system("cls");
            switch (sort)
            {
            case 1:
                key = start;
                while (key != NULL)
                {
                    temp = key->ptrnext;
                    while (temp != NULL)
                    {
                        if (key->e.hour > temp->e.hour)
                        {
                            swapNode(key, temp); // swap the hours //
                        }
                        temp = temp->ptrnext;
                    }
                    key = key->ptrnext;
                }

                if (headptr == NULL)
                {
                    printf("\nEmpty list");
                    return;
                }
                printf("\n\n\t**Sorted List Working Hours For Employee from Low to High**");
                printf("\n\n\t\t------Hour-----\n");
                temp = start;
                while (temp->ptrnext != NULL)
                {
                    printf("\n\t\t\t%d", temp->e.hour);

                    temp = temp->ptrnext;
                }
                printf("\n\t\t\t%d", temp->e.hour);
                break;

            case 2:
                key = start;

                while (key != NULL)
                {
                    temp = key->ptrnext;
                    while (temp != NULL)
                    {
                        if (key->e.salary > temp->e.salary)
                        {
                            swapNode2(key, temp); // swap the salary //
                        }
                        temp = temp->ptrnext;
                    }
                    key = key->ptrnext;
                }

                if (headptr == NULL)

                {
                    printf("\nEmpty list");
                    return;
                }
                printf("\n\n\t\t**Sorted List For Employee Salary From Low to High**");
                printf("\n\n\t\t------Total Salary-----\n");
                temp = start;
                while (temp->ptrnext != NULL)
                {
                    printf("\n\t\t\t RM%.2f", temp->e.salary);
                    temp = temp->ptrnext;
                }
                printf("\n\t\t\t RM%.2f", temp->e.salary);
                break;
            case 3:
                choice = FALSE;
                break;
            default:
                printf("\n\n\t\tEnter only one from the above");
            }
        }
    }
}
// swap the employee working hour //
void swapNode(struct person *x, struct person *y)
{
    int temp = x->e.hour;
    x->e.hour = y->e.hour;
    y->e.hour = temp;
}
// swap the total salary //
void swapNode2(struct person *x, struct person *y)
{
    int temp = x->e.salary;
    x->e.salary = y->e.salary;
    y->e.salary = temp;
}
void print_slip(struct company c) // display company info and selected employees payroll slip
{
    float amount_epf, amount_socso;
    int t_salary, number = 0;
    char searchKeyword[10];
    // implement linear search //
    if (headptr == NULL)
    {
        printf("\n\t\tEmpty Employee List, Can't Print Slip.");
        printf(" Please Add Employee before Print Slip....\n\n");
    }
    else
    {
        printf("\n\tEnter Employee ID Your Want to Print: ");
        fflush(stdin);
        scanf(" %s", &searchKeyword);
        system("cls");
        currentptr = headptr;
        do
        {
            printf("\n\t\t\t***Company Details*\n");
            printf("\n\t\tName : %s", c.c_name);
            printf("\n\t\tAddress : %s", c.c_add);
            printf("\n\t\tYears : %d", c.c_year);

            printf("\n\n");
            if (strcasecmp(currentptr->e.e_id, searchKeyword) == 0)
            {
                if (front == NULL)
                {
                    printf("\n\t\t\t***Manager List*\n");
                    printf("\n\t\t Empty\n");
                }
                else
                {
                    printf("\n\t\t\t***Manager Details*\n");
                    struct person *temp_queue = front;
                    while (temp_queue)
                    {
                        printf("\n\t\tManager No %d", number + 1);
                        printf("\n\t\tName : %s", temp_queue->name);
                        printf("\n\t\tIC : %s", temp_queue->ic);
                        printf("\n\t\tEmail : %s", temp_queue->email);
                        printf("\n\t\tGender : %s", temp_queue->gender);
                        printf("\n\t\tDate of Birth : %s", temp_queue->dob);
                        printf("\n\t\tMartial Status: %d", temp_queue->maritial_s);
                        printf("\n");
                        temp_queue = temp_queue->ptrnext;
                        number++;
                    }
                }
                printf("\n\n\t\t\t***Employee Details*\n");
                printf("\n\t\tName : %s", currentptr->e.e_name);
                printf("\n\t\tID : %s", currentptr->e.e_id);
                printf("\n\t\tAge : %d", currentptr->e.age);
                printf("\n\t\tGender : %s", currentptr->e.e_gender);
                printf("\n\t\tEmail : %s", currentptr->e.e_email);
                printf("\n\t\tEmployment Date : %s", currentptr->e.e_date);
                printf("\n\t\tWorking Hours : %d", currentptr->e.hour);
                printf("\n\t\tPosition : %s", currentptr->e.position);
                printf("\n\t\tSalary : RM%.2f", currentptr->e.salary);
                t_salary = currentptr->e.salary;
                if (currentptr->e.age >= 60) // amount epf and socso contribution rate
                {
                    amount_epf = t_salary * 0;
                    amount_socso = t_salary * 0;
                }
                else
                {
                    amount_epf = t_salary * 0.09;
                    amount_socso = t_salary * 0.05;
                }
                currentptr->t.T_salary = t_salary - amount_epf - amount_socso;
                printf("\n\n\t\t**No EPF : %d \t\t**EPF Amount : RM%.2f", currentptr->s.n_epf, amount_epf);
                printf("\n\t\t**No Socso : %d\t\t**Socso Amount : RM%.2f", currentptr->s.n_socso, amount_socso);
                printf("\n\n\t\tTotal Salary : RM%.2f", currentptr->t.T_salary);
                printf("\n\n\n");
                return;
            }
            currentptr = currentptr->ptrnext;
        } while (currentptr != NULL);
        printf("\n\n\t\tSorry, %s not found", searchKeyword);
    }
}