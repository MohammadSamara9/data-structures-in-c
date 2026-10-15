/* Mohammed Samara */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Reads a whole line safely (gets() was removed from C because it can overflow). */
void readLine(char buffer[], int size) {
    if (fgets(buffer, size, stdin) != NULL)
        buffer[strcspn(buffer, "\n")] = '\0';
}
typedef struct Node* ptr;
typedef struct Node* root;
struct Node{
    int ID;
    char name[100];
    char date[15];
    float duration;
    ptr left;
    ptr right;
    int flag;//0 for unperformed and 1 for performed
    char key[10];//to know which attribute is being used to build the tree

};

ptr MakeEmpty(root T);
ptr InsertByID(ptr T,int id,char name[],char date[],float duration,int flag);
ptr InsertByName(ptr T,int id,char name[],char date[],float duration,int flag);
ptr InsertByDate(ptr T,int id,char name[],char date[],float duration,int flag);
ptr InsertByDuration(ptr T,int id,char name[],char date[],float duration,int flag);
int dateCmp(char date1[],char date2[]);
ptr FindByID(root T,int id);
ptr FindByName(root T,char name[]);
ptr FindByDate(root T,char date[]);
ptr FindByDuration(root T,float duration);
ptr FindByIDLinear(root T,int id);
ptr FindByNameLinear(root T,char name[]);
ptr FindByDateLinear(root T,char date[]);
ptr FindByDurationLinear(root T,float duration);
ptr FindMin(ptr T);
ptr FindMax(ptr T);
ptr DeleteByID(ptr T,int id);
ptr DeleteByName(ptr T,char name[]);
ptr DeleteByDate(ptr T,char date[]);
ptr DeleteByDuration(ptr T,float duration);

root LoadTasksFile(root T);
root AddNewTask(root T);
root DeleteTask(root T);
void SearchTask(root T);
void SearchInOrder(root T,char target[],int* found);
ptr BinarySearchByName(ptr T,char name[]);
root PerformTask(root T);
void MarkPerformedInOrder(root T, int id,int* found);
root ViewUnperformedTasks(root T);
void PrintUnperformedTasks(root T,int* count);
root ViewPerformedTasks(root T);
void PrintPerformedTasks(root T,int* count);
root RestructureTasksBST(root T,char key[]);
root InsertAllNodes(ptr current,root newTree,char key[]);
int size(root T);
int height(root T);
int leavesCounter(root T);
int internalNodes(root T);
void TreeInfo(root T);
int main()
{
    root t=NULL;
    printf("Welcome to Razan's Task Management System\n");
    int choice=-1;
    while(choice!=10){
        printf("\n------- Task Management Menu -------\n\n");
        printf("1. Load Tasks File\n2. Add a New Task\n3. Delete a Task\n4. Search for a Task\n5. Perform a Task\n6. View Unperformed Tasks\n7. View Performed Tasks\n8. Restructure the Tasks BST\n9. View the Tasks BST Information\n10. Exit\n");
        printf("\nEnter your choice, please: ");
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1: t=LoadTasksFile(t);
                    break;
            case 2: t=AddNewTask(t);
                    break;
            case 3: t=DeleteTask(t);
                    break;
            case 4: SearchTask(t);;
                    break;
            case 5: t=PerformTask(t);
                    break;
            case 6: t=ViewUnperformedTasks(t);
                    break;
            case 7: t=ViewPerformedTasks(t);
                    break;
            case 8: {
                if (t == NULL) {
                    printf("Tree is empty.\n");
                    break;
                }
                char key[10];
                printf("Enter the attribute to restructure the BST by (id/name/date/duration): ");
                scanf("%s",key);
                if(strcmp(key,"id")!=0&&strcmp(key,"name")!=0&&strcmp(key,"date")!=0&&strcmp(key,"duration")!=0){
                    printf("Invalid attribute. Please enter one of: id, name, date, duration.\n");
                }else{
                    t=RestructureTasksBST(t,key);
                    printf("Tree restructured successfully by %s.\n",key);
                }
                break;
            }

            case 9:TreeInfo(t);
                    break;
            case 10:printf("Thank you for using our system\nGoodBye!\n");
                    t=MakeEmpty(t);
                    exit(0);
            default: printf("Invalid choice!\nPlease try again:\n");
        }
    }

}
ptr MakeEmpty(root T){
    if(T!=NULL){
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
    return NULL;
}

ptr InsertByID(ptr T,int id,char name[],char date[],float duration,int flag){
    if(T==NULL){
        T=(ptr)malloc(sizeof(struct Node));
        if(T==NULL){
            printf("Memory out of space!\n");
            return NULL;
        }
        else{
            T->ID=id;
            strcpy(T->name,name);
            strcpy(T->date,date);
            T->duration=duration;
            T->left=T->right=NULL;
            T->flag=flag;
            strcpy(T->key,"id");
            return T;
        }
    }
    else if(id<T->ID)
        T->left=InsertByID(T->left,id,name,date,duration,flag);
    else if(id>T->ID)
        T->right=InsertByID(T->right,id,name,date,duration,flag);
    else
        printf("Task with id '%d' already exists!\n",id);
    return T;
}

ptr InsertByName(ptr T,int id,char name[],char date[],float duration,int flag){
    if(T==NULL){
        T=(ptr)malloc(sizeof(struct Node));
        if(T==NULL){
            printf("Memory out of space!\n");
            return NULL;
        }
        else{
            T->ID=id;
            strcpy(T->name,name);
            strcpy(T->date,date);
            T->duration=duration;
            T->left=T->right=NULL;
            T->flag=flag;
            strcpy(T->key,"name");
            return T;
        }
    }
    else if(strcmp(name,T->name)>0)
        T->right=InsertByName(T->right,id,name,date,duration,flag);
    else if(strcmp(name,T->name)<0)
        T->left=InsertByName(T->left,id,name,date,duration,flag);
     else
        printf("Task with name '%s' already exists!\n",name);
    return T;

}

ptr InsertByDate(ptr T,int id,char name[],char date[],float duration,int flag){
    if(T==NULL){
        T=(ptr)malloc(sizeof(struct Node));
        if(T==NULL) {
            printf("Memory out of space!\n");
            return NULL;
        }else{
            T->ID=id;
            strcpy(T->name,name);
            strcpy(T->date,date);
            T->duration=duration;
            T->left=T->right = NULL;
            T->flag=flag;
            strcpy(T->key,"date");
            return T;
        }
    }

    int cmp=dateCmp(date,T->date);
    if(cmp<0)
        T->left=InsertByDate(T->left,id,name,date,duration,flag);
    else if(cmp>0)
        T->right=InsertByDate(T->right,id,name,date,duration,flag);
     else
        printf("Task with date '%s' already exists!\n",date);
    return T;
}

int dateCmp(char date1[],char date2[]){
    char temp1[15],temp2[15];
    strcpy(temp1,date1);
    strcpy(temp2,date2);
    char *token1=strtok(temp1,"/");
    int d1=atoi(token1);
    token1=strtok(NULL,"/");
    int m1=atoi(token1);
    token1=strtok(NULL,"/");
    int y1=atoi(token1);
    char *token2=strtok(temp2,"/");
    int d2=atoi(token2);
    token2=strtok(NULL,"/");
    int m2=atoi(token2);
    token2=strtok(NULL,"/");
    int y2=atoi(token2);
    if(y1!=y2){
        return(y1<y2)?-1:1;
    }
    if(m1!=m2){
        return(m1<m2)?-1:1;
    }
    if(d1!=d2){
        return(d1<d2)?-1:1;
    }

    return 0;
}//I considered that earlier tasks are greater than the others

ptr InsertByDuration(ptr T,int id,char name[],char date[],float duration,int flag){
    if(T==NULL){
        T=(ptr)malloc(sizeof(struct Node));
        if(T==NULL){
            printf("Out of memory!\n");
            return NULL;
        }else{
            T->ID=id;
            strcpy(T->name,name);
            strcpy(T->date,date);
            T->duration=duration;
            T->left=T->right=NULL;
            T->flag=flag;
            strcpy(T->key,"duration");
            return T;
        }
    }
    if(duration<T->duration)
        T->left=InsertByDuration(T->left,id,name,date,duration,flag);
    else if(duration>T->duration)
        T->right=InsertByDuration(T->right,id,name,date,duration,flag);
     else
        printf("Task with duration '%.1f' already exists!\n",duration);
    return T;
}

ptr FindByID(root T,int id){
    if(T==NULL)
        return NULL;
    else if(id>T->ID)
        return FindByID(T->right,id);
    else if(id<T->ID)
        return FindByID(T->left,id);
    else
        return T;
}

ptr FindByName(root T,char name[]){
    if(T==NULL)
        return NULL;
    else if(strcmp(name,T->name)>0)
        return FindByName(T->right,name);
    else if(strcmp(name,T->name)<0)
        return FindByName(T->left,name);
    else
        return T;
}

ptr FindByDate(root T,char date[]){
    if(T==NULL)
        return NULL;
    if(dateCmp(date,T->date)>0)
        return FindByDate(T->right,date);
    else if(dateCmp(date,T->date)<0)
        return FindByDate(T->left,date);
    else
        return T;
}

ptr FindByDuration(root T,float duration){
    if(T==NULL)
        return NULL;
    else if(duration>T->duration)
        return FindByDuration(T->right,duration);
    else if(duration<T->duration)
        return FindByDuration(T->left,duration);
    else
        return T;
}

ptr FindByIDLinear(root T,int id){
    if(T==NULL)
        return NULL;
    if(T->ID==id)
        return T;
    ptr left=FindByIDLinear(T->left,id);
    if(left!=NULL)
        return left;
    return FindByIDLinear(T->right,id);
}

ptr FindByNameLinear(root T,char name[]){
    if(T==NULL)
        return NULL;
    if(strcmp(T->name,name)==0)
        return T;
    ptr left=FindByNameLinear(T->left,name);
    if(left!=NULL)
        return left;
    return FindByNameLinear(T->right,name);
}

ptr FindByDateLinear(root T,char date[]){
    if(T==NULL)
        return NULL;
    if(dateCmp(T->date,date)==0)
        return T;
    ptr left=FindByDateLinear(T->left,date);
    if(left!=NULL)
        return left;
    return FindByDateLinear(T->right,date);
}

ptr FindByDurationLinear(root T,float duration){
    if(T==NULL)
        return NULL;
    if(T->duration==duration)
        return T;
    ptr left=FindByDurationLinear(T->left,duration);
    if(left!=NULL)
        return left;
    return FindByDurationLinear(T->right,duration);
}

ptr FindMin(ptr T){
    if(T!=NULL){
        while(T->left!=NULL)
            T=T->left;
    }
    return T;
}

ptr FindMax(ptr T){
    if(T!=NULL)
        while(T->right!=NULL)
            T=T->right;
    return T;
}

ptr DeleteByID(ptr T,int id){
    ptr temp;
    if(T==NULL)
        printf("Element not found!\n");
    else if(id<T->ID)
        T->left=DeleteByID(T->left,id);
    else if(id>T->ID)
        T->right=DeleteByID(T->right,id);
    else if(T->left && T->right){
            temp=FindMin(T->right);
            T->ID=temp->ID;
            strcpy(T->name,temp->name);
            strcpy(T->date,temp->date);
            T->duration=temp->duration;
            T->flag=temp->flag;
            strcpy(T->key,temp->key);
            T->right=DeleteByID(T->right,T->ID);
        }
        else{
            temp=T;
            if(T->left==NULL)
                T=T->right;
            else if(T->right==NULL)
                T=T->left;
            free(temp);
        }
        return T;

}

ptr DeleteByName(ptr T,char name[]){
    ptr temp;
    if(T==NULL)
        printf("Element not found!\n");
    else if(strcmp(name,T->name)<0)
        T->left=DeleteByName(T->left,name);
    else if(strcmp(name,T->name)>0)
        T->right=DeleteByName(T->right,name);
    else
        if(T->left && T->right){
            temp=FindMin(T->right);
            T->ID=temp->ID;
            strcpy(T->name,temp->name);
            strcpy(T->date,temp->date);
            T->duration=temp->duration;
            T->flag=temp->flag;
            strcpy(T->key,temp->key);
            T->right=DeleteByName(T->right,temp->name);
        }
        else{
            temp=T;
            if(T->left==NULL)
                T=T->right;
            else if(T->right==NULL)
                T=T->left;
            free(temp);
        }
    return T;
}

ptr DeleteByDate(ptr T,char date[]){
    ptr temp;
    if(T==NULL)
        printf("Element not found!\n");
    else if(dateCmp(date,T->date)<0)
        T->left=DeleteByDate(T->left,date);
    else if(dateCmp(date,T->date)>0)
        T->right=DeleteByDate(T->right,date);
    else
        if(T->left && T->right){
            temp=FindMin(T->right);
            T->ID=temp->ID;
            strcpy(T->name,temp->name);
            strcpy(T->date,temp->date);
            T->duration=temp->duration;
            T->flag=temp->flag;
            strcpy(T->key,temp->key);
            T->right=DeleteByDate(T->right,temp->date);
        }
        else{
            temp=T;
            if(T->left==NULL)
                T=T->right;
            else if(T->right==NULL)
                T=T->left;
            free(temp);
        }
    return T;
}

ptr DeleteByDuration(ptr T,float duration){
    ptr temp;
    if(T==NULL)
        printf("Element not found!\n");
    else if(duration<T->duration)
        T->left=DeleteByDuration(T->left,duration);
    else if(duration>T->duration)
        T->right=DeleteByDuration(T->right,duration);
    else
        if(T->left && T->right){
            temp=FindMin(T->right);
            T->ID=temp->ID;
            strcpy(T->name,temp->name);
            strcpy(T->date,temp->date);
            T->duration=temp->duration;
            T->flag=temp->flag;
            strcpy(T->key,temp->key);
            T->right=DeleteByDuration(T->right,temp->duration);
        }
        else{
            temp=T;
            if(T->left==NULL)
                T=T->right;
            else if(T->right==NULL)
                T=T->left;
            free(temp);
        }
    return T;
}

root LoadTasksFile(root T){
    FILE* f=fopen("tasks.txt","r");
    if(f==NULL) {
        printf("Could not open file.\nPlease try again\n");
        return T;
    }
    int loadedCount=0;
    char line[300];
    while(fgets(line,sizeof(line),f)){
        for(int i=0;line[i]!='\0';i++){
            if(line[i]=='\n'){
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

        if(T==NULL){
            T=InsertByID(T,id,name,date,duration,0);
            loadedCount++;
        }else{
        // I used linear search here because checking each attribute ID, Name, Date, Duration
        // would otherwise require restructuring the entire tree based on that attribute,
        // then restoring the original structure after each check. This would be highly inefficient
        // and time consuming (O(n log n) for each restructure), so linear traversal (O(n)) is more optimal here.
            if((FindByIDLinear(T,id)==NULL)&&(FindByNameLinear(T,name)==NULL)&&(FindByDateLinear(T,date)==NULL)&&(FindByDurationLinear(T,duration)==NULL)) {
                if (strcmp(T->key,"id")==0)
                    T=InsertByID(T,id,name,date,duration,0);
                else if(strcmp(T->key,"name")==0)
                    T=InsertByName(T,id,name,date,duration,0);
                else if(strcmp(T->key,"date")==0)
                    T=InsertByDate(T,id,name,date,duration,0);
                else if(strcmp(T->key,"duration")==0)
                    T=InsertByDuration(T, id,name,date,duration,0);
                 loadedCount++;
            }else{
                printf("Skipped duplicate for task with id '%d'\n",id);
            }
        }
    }
    fclose(f);
    printf("Tasks loaded successfully from the text file.\n");
    printf("Total tasks loaded: %d\n",loadedCount);
    return T;
}

root AddNewTask(root T){
    int id;
    char name[100],date[15];
    float duration;

    printf("Enter Task ID: ");
    scanf("%d",&id);
    getchar();
    printf("Enter Task Name: ");
    readLine(name, sizeof(name));
    printf("Enter Task Date (DD/MM/YYYY): ");
    readLine(date, sizeof(date));
    printf("Enter Task Duration (in hours): ");
    scanf("%f",&duration);
    getchar();
    if(T==NULL){
        T=InsertByID(T,id,name,date,duration,0);
        printf("Task added successfully as the root.\n");
        return T;
    }
    if(FindByIDLinear(T,id)!=NULL){
    printf("Conflict: A task with the same ID (%d) already exists.\n",id);
    return T;
    }
    if(FindByNameLinear(T,name)!=NULL){
    printf("Conflict: A task with the same Name (%s) already exists.\n",name);
    return T;
    }
    if(FindByDateLinear(T,date)!=NULL){
    printf("Conflict: A task with the same Date (%s) already exists.\n",date);
    return T;
    }
    if(FindByDurationLinear(T, duration)!=NULL){
    printf("Conflict: A task with the same Duration (%.1f hours) already exists.\n",duration);
    return T;
    }

    if(strcmp(T->key,"id")==0)
        T=InsertByID(T,id,name,date,duration,0);
    else if(strcmp(T->key,"name")==0)
        T=InsertByName(T,id,name,date,duration,0);
    else if(strcmp(T->key,"date")==0)
        T=InsertByDate(T,id,name,date,duration,0);
    else if(strcmp(T->key,"duration")==0)
        T=InsertByDuration(T,id,name,date,duration,0);

    printf("Task added successfully!\n");
    return T;
}

void SearchInOrder(root T,char target[],int* found){
    if (T==NULL)
        return;
    SearchInOrder(T->left,target,found);
    if(strcmp(T->name,target)==0){
        printf("\nTask Found:\n");
        printf("ID       : %d\n",T->ID);
        printf("Name     : %s\n",T->name);
        printf("Date     : %s\n",T->date);
        printf("Duration : %.1f hours\n",T->duration);
        printf("Status   : %s\n",T->flag?"Performed":"Unperformed");
        *found = 1;
    }
    SearchInOrder(T->right,target,found);
}

ptr BinarySearchByName(root T,char name[]){
    if (T==NULL)
        return NULL;
    int cmp=strcmp(name,T->name);
    if (cmp<0)
        return BinarySearchByName(T->left,name);
    else if(cmp>0)
        return BinarySearchByName(T->right,name);
    else
        return T;
}

// What I did here is: I first check if the tree is sorted by Names, then I use binary search (which costs O(log n)).
// But if the key isn't Name, I go with a linear in order search (O(n)) instead.
// I could restructure the whole tree temporarily, but that would cost O(n log n),
// which is actually worse than just doing a linear search.

void SearchTask(root T){
    if(T==NULL){
        printf("The tree is empty!\n");
        return;
    }
    char name[100];
    printf("Enter the Task Name to search: ");
    readLine(name, sizeof(name));
    int found=0;
    if(strcmp(T->key,"name")==0){
        ptr result=BinarySearchByName(T,name);
        if(result!=NULL){
            printf("\nTask Found:\n");
            printf("ID       : %d\n", result->ID);
            printf("Name     : %s\n", result->name);
            printf("Date     : %s\n", result->date);
            printf("Duration : %.1f hours\n", result->duration);
            printf("Status   : %s\n",result->flag?"Performed":"Unperformed");
        }else{
            printf("\nTask with name \"%s\" not found.\n",name);
        }
    }else{
        SearchInOrder(T,name,&found);
        if(found==0)
            printf("\nTask with name \"%s\" not found.\n",name);
    }
}

root DeleteTask(root T){
    if(T==NULL){
        printf("Tree is empty.\n");
        return NULL;
    }
    int choice;
    printf("Choose the attribute to delete by:\n");
    printf("1. ID\n2. Name\n3. Date\n4. Duration\n");
    printf("Enter your choice (1-4): ");
    scanf("%d",&choice);
    char originalKey[10];
    strcpy(originalKey,T->key);
    char attribute[10];
    if(choice==1) strcpy(attribute,"id");
    else if(choice==2) strcpy(attribute,"name");
    else if(choice==3) strcpy(attribute,"date");
    else if(choice==4) strcpy(attribute,"duration");
    else {
        printf("Invalid choice.\n");
        return T;
    }
    if(strcmp(attribute,T->key)!=0){
        T=RestructureTasksBST(T,attribute);
    }
    int id;
    char name[100],date[15];
    float duration;
    if(strcmp(attribute,"id")==0) {
        printf("Enter the Task ID to delete: ");
        scanf("%d",&id);
        if(FindByID(T,id)==NULL){
            printf("Task with ID %d not found.\n",id);
        }else{
            T=DeleteByID(T,id);
            printf("Task with ID %d deleted successfully.\n",id);
        }
    }else if(strcmp(attribute,"name")==0){
        printf("Enter the Task Name to delete: ");
        getchar();
        readLine(name, sizeof(name));
        if(FindByName(T,name)==NULL){
            printf("Task with Name '%s' not found.\n",name);
        }else{
            T=DeleteByName(T,name);
            printf("Task with Name '%s' deleted successfully.\n",name);
        }
    }else if(strcmp(attribute,"date")==0){
        printf("Enter the Task Date (DD/MM/YYYY) to delete: ");
        getchar();
        readLine(date, sizeof(date));

      if(FindByDate(T,date)==NULL){
            printf("Task with Date '%s' not found.\n",date);
        }else{
            T=DeleteByDate(T,date);
            printf("Task with Date '%s' deleted successfully.\n",date);
        }
    }else if(strcmp(attribute,"duration")==0){
        printf("Enter the Task Duration to delete: ");
        scanf("%f",&duration);
        if(FindByDuration(T,duration)==NULL){
            printf("Task with Duration %.1f not found.\n",duration);
        }else{
            T=DeleteByDuration(T,duration);
            printf("Task with Duration %.1f deleted successfully.\n",duration);
        }
    }
    if(strcmp(attribute,originalKey)!=0){
        T=RestructureTasksBST(T,originalKey);
    }

    return T;
}

void MarkPerformedInOrder(root T,int id,int* found){
    if (T==NULL)
        return;
    MarkPerformedInOrder(T->left,id,found);
    if (T->ID==id){
        T->flag=1;
        printf("Task with ID %d marked as performed.\n",id);
        *found=1;
        return;
    }
    MarkPerformedInOrder(T->right,id,found);
}
// What I did here is: I first check if the tree is sorted by ID, then I use binary search (which costs O(log n)).
// But if the key isn't ID, I go with a linear in-order search (O(n)) instead.
// I could restructure the whole tree temporarily, but that would cost O(n log n),
// which is actually worse than just doing a linear search, so I preferred the simpler and faster way.

root PerformTask(root T){
    if(T==NULL){
        printf("Tree is empty.\n");
        return T;
    }
    int id;
    printf("Enter the Task ID to mark as performed: ");
    scanf("%d",&id);
    int found=0;
    if(strcmp(T->key,"id")==0){
        ptr task=FindByID(T,id);
        if(task==NULL) {
            printf("Task with ID %d not found.\n",id);
        }else{
            task->flag=1;
            printf("Task with ID %d marked as performed.\n",id);
        }
    }else{
        MarkPerformedInOrder(T,id,&found);
        if(found==0)
            printf("Task with ID %d not found.\n",id);
    }
    return T;
}

root ViewUnperformedTasks(root T){
    int count=0;
    if (T==NULL) {
        printf("The tree is empty.\n");
        return T;
    }
    char originalKey[10];
    strcpy(originalKey,T->key);
    if(strcmp(T->key,"name")!=0) {
        T=RestructureTasksBST(T,"name");
    }
    printf("\nUnperformed Tasks (Sorted by Name):\n");
    PrintUnperformedTasks(T,&count);
    if(strcmp(originalKey,"name")!=0) {
        T=RestructureTasksBST(T,originalKey);
    }
    if(count==0){
        printf("No Unperformed Tasks found!\n");
    }
    return T;
}

void PrintUnperformedTasks(root T,int* count){
    if (T==NULL)
        return;
    PrintUnperformedTasks(T->left,count);
    if (T->flag==0) {
        printf("Name: %-25s, ",T->name);
        printf("ID: %-5d, ",T->ID);
        printf("Date: %-12s, ",T->date);
        printf("Duration: %-6.1f hours, ",T->duration);
        printf("Status: Unperformed\n");
        (*count)++;
    }
    PrintUnperformedTasks(T->right,count);
}

root ViewPerformedTasks(root T){
    int count=0;
    if (T==NULL){
        printf("Tree is empty.\n");
        return T;
    }
    char originalKey[10];
    strcpy(originalKey,T->key);
    if(strcmp(T->key,"id")!= 0){
        T=RestructureTasksBST(T,"id");
    }
    printf("\nPerformed Tasks (Sorted by ID):\n");
    PrintPerformedTasks(T,&count);
    if (strcmp(originalKey,"id")!=0){
        T=RestructureTasksBST(T,originalKey);
    }
    if(count==0){
        printf("No Performed Tasks found!\n");
    }
    return T;
}

void PrintPerformedTasks(root T,int* count){
    if(T==NULL)
        return;

    PrintPerformedTasks(T->left,count);
    if(T->flag==1) {
        printf("ID: %-5d, ",T->ID);
        printf("Name: %-25s, ",T->name);
        printf("Date: %-12s, ",T->date);
        printf("Duration: %-6.1f hours, ",T->duration);
        printf("Status: Performed\n");
        (*count)++;
    }
    PrintPerformedTasks(T->right,count);
}

root RestructureTasksBST(root T,char key[]){
    if(T==NULL)
        return NULL;
    root newTree=NULL;
    newTree=InsertAllNodes(T,newTree,key);
    MakeEmpty(T); /* free the old tree, all its tasks were copied to newTree */
    return newTree;
}

root InsertAllNodes(ptr current,root newTree,char key[]){
    if(current==NULL)
        return newTree;
    newTree=InsertAllNodes(current->left,newTree,key);
    if(strcmp(key,"id")==0)
        newTree=InsertByID(newTree,current->ID,current->name,current->date,current->duration,current->flag);
    else if(strcmp(key,"name")==0)
        newTree=InsertByName(newTree,current->ID,current->name,current->date,current->duration,current->flag);
    else if(strcmp(key,"date")==0)
        newTree=InsertByDate(newTree,current->ID,current->name,current->date,current->duration,current->flag);
    else if(strcmp(key,"duration")==0)
        newTree=InsertByDuration(newTree,current->ID,current->name,current->date,current->duration,current->flag);
    newTree=InsertAllNodes(current->right,newTree,key);
    return newTree;
}

int size(root T){
    if(T==NULL)
        return 0;
    else
        return 1+size(T->left)+size(T->right);
}

int height(root T){
    if(T==NULL){
        return -1;
    }
    else{
        int left=height(T->left);
        int right=height(T->right);
        if(right>left)return right+1;
        else return left+1;
    }

}

int leavesCounter(root T){
    if(T==NULL)return 0;
    else if(T->left==NULL && T->right==NULL)return 1;
    else return leavesCounter(T->left)+leavesCounter(T->right);
}

int internalNodes(root T){
    return size(T)-leavesCounter(T);
}

void TreeInfo(root T){
    printf("Size: %d\n",size(T));
    printf("Height: %d\n",height(T));
    printf("Leaves: %d\n",leavesCounter(T));
    printf("Internal Nodes: %d\n",internalNodes(T));
}
