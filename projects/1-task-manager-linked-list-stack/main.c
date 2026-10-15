/* Mohammed Samara */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Reads a whole line safely (gets() was removed from C because it can overflow). */
void readLine(char buffer[], int size) {
    if (fgets(buffer, size, stdin) != NULL)
        buffer[strcspn(buffer, "\n")] = '\0';
}

typedef struct task* ptr;
typedef ptr list;
typedef ptr pos;

struct task{
    int id;
    char name[100];
    char date[15];
    float duration;
    ptr next;
};

typedef struct performedTask* stack;

struct performedTask{
    ptr task;
    stack next;
};

list MakeEmpty(list l);
int isEmpty(list l);
int isLast(pos p,list l);
ptr FindByID(int ID,list l);
ptr FindByName(char taskName[],list l);
ptr FindPrevious(int ID,list l);
void Delete(int ID,list l);
void Insert(int id,char name[],char date[],float duration,list l,pos p);
void InsertLast(int id,char name[],char date[],float duration,list l);
void PrintList(list l);
void DeleteList(list l);

stack createStack();
int isStackEmpty(stack s);
void makeStackEmpty(stack s);
void push(ptr x,stack s);
ptr pop(stack s);
ptr top(stack s);
void disposeStack(stack s);

void LoadTasksFile(list l);
void AddNewTask(list l);
void DeleteTask(list l);
void SearchTask(list l,stack perfomedStack);
void PerformTask(list l,stack s);
void UndoLastPerformed(list l,stack s,list undoneList);
void ViewTasks(list l);
void ViewPerformedTasks(stack s);
void ViewUndoneTasks(list l);
void GenerateReport(list taskList,stack performedStack,list undoneList);

int main(){
    list taskList=MakeEmpty(NULL);
    stack performedStack=createStack();
    list undoneList=MakeEmpty(NULL);
    printf("Welcome to Razan's Task Management System\n");
    int choice=-1;
    while(choice!=10){
        printf("\n------- Task Management Menu -------\n\n");
        printf("1. Load Tasks File\n2. Add a New Task\n3. Delete a Task\n4. Search for a Task\n5. View Unperformed Tasks\n6. Perform a Task\n7. Undo Last Performed Task\n8. View Performed Tasks\n9. Generate Summary Report\n10. Exit\n");
        printf("\nEnter your choice, please: ");
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1: LoadTasksFile(taskList);
                    break;
            case 2: AddNewTask(taskList);
                    break;
            case 3: DeleteTask(taskList);
                    break;
            case 4: SearchTask(taskList,performedStack);
                    break;
            case 5: ViewTasks(taskList);
                    break;
            case 6: PerformTask(taskList,performedStack);
                    break;
            case 7: UndoLastPerformed(taskList,performedStack,undoneList);
                    break;
            case 8: ViewPerformedTasks(performedStack);
                    break;
            case 9: GenerateReport(taskList,performedStack,undoneList);
                    break;
            case 10:printf("Thank you for using our system\nGoodBye!\n");
                    DeleteList(taskList);
                    while(!isStackEmpty(performedStack))
                        free(pop(performedStack)); /* free the performed tasks too */
                    disposeStack(performedStack);
                    DeleteList(undoneList);
                    exit(0);
            default: printf("Invalid choice!\nPlease try again:\n");
        }
    }
    return 0;
}

list MakeEmpty(list l){
    if(l!=NULL)
        DeleteList(l);
    l=(ptr)malloc(sizeof(struct task));
    if(l==NULL){
        printf("Out of memory!");
        return NULL;
    }
    l->next=NULL;
    return l;
}

int isEmpty(list l){
    if(l==NULL){
        printf("This list isn't created yet!\n");
        return 1;
    }
    return (l->next==NULL);
}

int isLast(pos p,list l){
    if(l==NULL){
        printf("This list isn't created yet!\n");
        return 1;
    }
    return (p->next==NULL);
}

ptr FindByID(int ID,list l){
    if(l==NULL){
        printf("This list isn't created yet!\n");
        return NULL;
    }
    ptr p=l->next;
    while(p!=NULL&&p->id!=ID)
        p=p->next;
    return p;
}

ptr FindByName(char taskName[],list l){
    if(l==NULL){
        printf("This list isn't created yet!\n");
        return NULL;
    }
    ptr p=l->next;
    while(p!=NULL&&strcmp(p->name,taskName)!=0)
        p=p->next;
    return p;
    }

ptr FindPrevious(int ID,list l){
    if(l==NULL){
        printf("This list isn't created yet!\n");
        return NULL;
    }
    ptr p=l;
    while(p->next!=NULL&&p->next->id!=ID)
        p=p->next;
    return p;
}

void Delete(int ID,list l){
    if(l==NULL){
        printf("This list isn't created yet!\n");
        return;
    }
    ptr prev=FindPrevious(ID,l);
    if(!isLast(prev,l)){
        ptr temp=prev->next;
        prev->next=temp->next;
        free(temp);
    }
}

void Insert(int id,char name[],char date[],float duration,list l,pos p){
    if(l==NULL){
        printf("This list isn't created yet!\n");
        return;
    }
    ptr temp=(ptr)malloc(sizeof(struct task));
    if(temp==NULL){
        printf("Out of memory!\n");
        return;
    }
    temp->id=id;
    strcpy(temp->name,name);
    strcpy(temp->date,date);
    temp->duration=duration;
    temp->next=p->next;
    p->next=temp;
}

void InsertLast(int id,char name[],char date[],float duration,list l){
    if(l==NULL){
        printf("This list isn't created yet!\n");
        return;
    }
    ptr p=l;
    while(p->next!=NULL)
        p=p->next;
    Insert(id,name,date,duration,l,p);
}

void PrintList(list l){
    if(l==NULL){
        printf("This list isn't created yet!\n");
        return;
    }
    if(isEmpty(l)){
        printf("This list is empty!\n");
        return;
     }
    ptr p=l->next;
    while(p!=NULL){
        printf("ID: %-4d | Name: %-25s | Date: %-12s | Duration: %.1f hours\n", p->id, p->name, p->date, p->duration);
        p=p->next;
    }
}

void DeleteList(list l){
    if(l==NULL){
        printf("This list isn't created yet!\n");
        return;
    }
    ptr p=l->next,temp;
    while(p!=NULL){
        temp=p->next;
        free(p);
        p=temp;
    }
    free(l);
}

stack createStack(){
    stack s=(stack)malloc(sizeof(struct performedTask));
    if(s==NULL){
        printf("The memory is full!\n");
        return NULL;
    }
    s->next=NULL;
    makeStackEmpty(s);
    return s;
}

void makeStackEmpty(stack s){
    if(s==NULL)printf("out of space!\n");
    else
        while(!isStackEmpty(s))
            pop(s);
}

int isStackEmpty(stack s){
    return s->next==NULL;
}

void push(ptr Task,stack s){
    stack temp=(stack)malloc(sizeof(struct performedTask));
    if(temp==NULL){
        printf("The memory is Full!\n");
        return;
    }
    temp->task=Task;
    temp->next=s->next;
    s->next=temp;
}

ptr pop(stack s){
    if(isStackEmpty(s))
        return NULL;
    stack temp=s->next;
    s->next=temp->next;
    ptr Task=temp->task;
    free(temp);
    return Task;
}

ptr top(stack s){
    if(isStackEmpty(s)){
        printf("Stack is empty.\n");
        return NULL;
    }
    return s->next->task;
}

void disposeStack(stack s){
    makeStackEmpty(s);
    free(s);
}

void LoadTasksFile(list l){
 FILE* f=fopen("tasks.txt","r");
    if(f==NULL){
        printf("Could not open file.\nPlease try again\n");
        return;
    }
    char line[300];
    while(fgets(line,sizeof(line),f)){
        for(int i=0;line[i]!='\0';i++){
            if (line[i]=='\n') {
                line[i]='\0';
                break;
            }
        }
        char* idText=strtok(line,"#");
        char* nameText=strtok(NULL,"#");
        char* dateText=strtok(NULL,"#");
        char* durationText=strtok(NULL,"#");
        if(idText==NULL||nameText==NULL||dateText==NULL||durationText==NULL)
            continue; /* skip empty or broken lines */
        int id=atoi(idText);
        char name[100];
        strncpy(name,nameText,sizeof(name)-1);
        name[sizeof(name)-1]='\0';
        char date[15];
        strncpy(date,dateText,sizeof(date)-1);
        date[sizeof(date)-1]='\0';
        float duration=atof(durationText);

        if(FindByID(id,l)==NULL){
            InsertLast(id,name,date,duration,l);
        }
    }
    fclose(f);
    printf("Tasks loaded successfully from the text file.\n");
}

void AddNewTask(list l){
    int id;
    char name[100],date[15];
    float dur;
    printf("Enter ID: ");
    scanf("%d",&id);
    getchar();
    if (FindByID(id,l)!=NULL){
        printf("A task with ID %d already exists. Task not added.\n",id);
        return;
    }
    printf("Enter Name: ");
    readLine(name, sizeof(name));
    printf("Enter Date(DD/MM/YYYY): ");
    readLine(date, sizeof(date));
    printf("Enter Duration: ");
    scanf("%f",&dur);
    getchar();
    InsertLast(id,name,date,dur,l);
    printf("Task added successfully to the list.\n");
}

void DeleteTask(list l){
    int id;
    printf("Enter ID to delete: ");
    scanf("%d",&id);
    if(FindByID(id,l)){
        Delete(id,l);
        printf("Task with ID %d was deleted successfully.\n",id);
    } else {
        printf("Task with ID %d not found. Nothing deleted.\n",id);
    }
}

void SearchTask(list l,stack performedStack){
    int choice;
    printf("1. By ID\n2. By Name\n");
    scanf("%d",&choice);
    if(choice==1){
        int id;
        printf("Enter ID: ");
        scanf("%d",&id);
        ptr p=FindByID(id,l);
        if(p!=NULL){
            printf("<Task Found: an Unperformed Task>\nTask Information:\nID: %d | Name: %s | Date: %s | Duration: %.1f hours\n",p->id,p->name,p->date,p->duration);
            return;
        }
        stack temp=createStack();
        ptr task;
        int flag=0;
        while(!isStackEmpty(performedStack)){
            task=pop(performedStack);
            if(task->id==id){
                printf("<Task Found: a Performed Task>\nTask Information:\nID: %d | Name: %s | Date: %s | Duration: %.1f hours\n",task->id,task->name,task->date,task->duration);
                flag=1;
            }
            push(task,temp);

        }
        while(!isStackEmpty(temp)){
            task=pop(temp);
            push(task,performedStack);
        }
        disposeStack(temp);
        if(flag)return;
        printf("Task with ID %d not found.\n",id);
    }
    else if(choice==2){
        getchar();
        char name[100];
        printf("Enter Name: ");
        readLine(name, sizeof(name));
        ptr p=FindByName(name,l);
        if(p!=NULL){
            printf("<Task Found: an Unperformed Task>\nTask Information:\nID: %d | Name: %s | Date: %s | Duration: %.1f hours\n",p->id,p->name,p->date,p->duration);
            return;
        }
        stack temp=createStack();
        ptr task;
        int flag=0;
        while(!isStackEmpty(performedStack)){
            task=pop(performedStack);
            if(strcmp(task->name,name)==0){
                printf("<Task Found: a Performed Task>\nTask Information:\nID: %d | Name: %s | Date: %s | Duration: %.1f hours\n",task->id,task->name,task->date,task->duration);
                flag=1;
            }
            push(task,temp);
        }
        while(!isStackEmpty(temp)){
            task=pop(temp);
            push(task,performedStack);
        }
        disposeStack(temp);
        if(flag)return;
        printf("Task with that name not found.\n");
    }
    else
        printf("Choice selected is not one of the options!\nTry again...\n");
}

void PerformTask(list l,stack s){
    int id;
    printf("Enter ID to perform: ");
    scanf("%d",&id);
    ptr prev=FindPrevious(id,l);
    if(prev!=NULL && prev->next!=NULL){
        ptr task=prev->next;
        prev->next=task->next;
        task->next=NULL;
        push(task,s);
        printf("Task performed successfully.\n");
    } else {
        printf("Task with ID %d not found.\n", id);
    }
}

void UndoLastPerformed(list l,stack s,list undoneList){
    ptr task=pop(s);
    if(task){
            if(!FindByID(task->id,l)){
                InsertLast(task->id,task->name,task->date,task->duration,l);
                printf("Last performed task has been undone and added back to the unperformed list.\n");
            }
            else {
            printf("Undo noted. Task with ID %d already exists in the unperformed list, so it wasn't added again.\n",task->id);
        }
            InsertLast(task->id,task->name,task->date,task->duration,undoneList);
            free(task); /* the lists above got copies, so the popped task can be freed */
    }else{
        printf("No performed task to undo.\n");
    }

/*
    I came across a case where the same task from the performed list might exist
    in the unperformed list (especially in the case when reloading from the same file again),
    so I added a check to avoid inserting it again.
    However, I still insert it into the undone list
    to keep track of undo operations, even if the task wasn't added back.
*/

}

void ViewPerformedTasks(stack s){
    if(isStackEmpty(s)){
        printf("No performed tasks.\n");
        return;
    }
    stack temp=createStack();
    ptr task;
    while(!isStackEmpty(s)){
        task=pop(s);
        push(task,temp);
    }
    printf("\nList of Performed Tasks (in the order they were completed):\n");
    while(!isStackEmpty(temp)){
        task=pop(temp);
        printf("Task ID: %-4d | Name: %-25s | Date: %-12s | Duration: %.1f hours\n",task->id,task->name,task->date,task->duration);
        push(task,s);
    }
    disposeStack(temp);
}


void ViewTasks(list l){ PrintList(l); }

void GenerateReport(list taskList,stack performedStack,list undoneList) {
    FILE* f=fopen("Report.txt","w");
    if(f==NULL){
        printf("Error opening Report file.\nPlease try again...\n");
        return;
    }
    fprintf(f,"----------< Unperformed Tasks >----------\n");
    fprintf(f,"%-5s %-50s %-15s %-10s\n","ID","Name","Date","Duration");
    ptr p=taskList->next;
    while(p!=NULL){
        fprintf(f,"%-5d %-50s %-15s %-6.1f hours\n",p->id,p->name,p->date,p->duration);
        p=p->next;
    }

    fprintf(f, "\n----------< Undone Tasks >----------\n");
    fprintf(f,"%-5s %-50s %-15s %-10s\n", "ID","Name","Date","Duration");
    p=undoneList->next;
    while(p!=NULL){
        fprintf(f,"%-5d %-50s %-15s %-6.1f hours\n",p->id,p->name,p->date,p->duration);
        p=p->next;
    }

    fprintf(f,"\n----------< Performed Tasks >----------\n");
    fprintf(f,"%-5s %-50s %-15s %-10s\n","ID","Name","Date","Duration");
    stack temp=createStack();
    ptr task;
    while(!isStackEmpty(performedStack)){
        task=pop(performedStack);
        push(task,temp);
    }
    while(!isStackEmpty(temp)){
        task=pop(temp);
        fprintf(f,"%-5d %-50s %-15s %-6.1f hours\n",task->id,task->name,task->date,task->duration);
        push(task,performedStack);
    }
    disposeStack(temp);

    fclose(f);
    printf("Report saved to Report text file\n");
}

