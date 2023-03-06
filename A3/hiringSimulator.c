#include <stdio.h>
#include<malloc.h> 
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SELECTED 15
typedef struct Applicant
{
  char gender; // 'M' or 'F'
  float height ;   // in feet as an float.
  int age; 
} Applicant;

typedef struct Hirer
{
  char *name; 
  int desiredAge ; //representing the minimum age of an applicantthat this person is willing to select
  float desiredHeight; // representing the minimum height of anapplicant that this person is willing to select
  Applicant applicantList[10];
  int numSelected; // representing the number of applicants currently in the selections list.
} Hirer;

typedef struct Pool
{
 
  Applicant applicantList[15];
  int numApplicant; // representing the number of applicants currently in the selections list.
} Pool;

int addApplicant(Pool *p, char gender, float height, unsigned char age){
    // lf p was already at capacity return 0
    if(p->numApplicant>=SELECTED){
        printf("pool full！\n");
        return 0;
    }
    
    p->applicantList[p->numApplicant].age=age;
    p->applicantList[p->numApplicant].gender=gender;
    p->applicantList[p->numApplicant].height=height;
    p->numApplicant+=1;
    
    return 0;
}

void listApplicants(Applicant *arrayOfApplicants, int n){
    char *Gender;
    for (int i=0; i<n; i++) {
        if (arrayOfApplicants[i].gender == 'M') {
            Gender="Male";
        }else if (arrayOfApplicants[i].gender == 'F') {
            Gender="Female";
        }else {
            Gender="?";
        }
        printf("%d year old %lf foot %s\n",arrayOfApplicants[i].age, arrayOfApplicants[i].height, Gender);
    }
}

char likes(Hirer *h, Applicant *a){
    //  A hirer likes an applicant if he/she is at least as tall (i.e., >=) as the hirer'sdesired height 
    // and if the applicant is within 1 year of the hirer's desired age.
    if(h->desiredAge-a->age>1 || h->desiredAge-a->age < -1){
        
        return 0;
    }
    if (h->desiredHeight>a->height) {
       
        return 0;
    }
    return 1;
}

int keep(Hirer *h, Applicant *a){
    // The capacity is full, return 0
    if (h->numSelected>=SELECTED) {
        printf("The capacity is full\n");
        return 0;
    }
    //printf("申请人 %d 岁 身高%lf 的人\n",a->age,a->height);
    // whether adding the applicant to the hirer's selection list
    //  cause the list to havemore than 50% (of capacity) of one type of gender in it. 
    int male=0;
    int female=0;
    if (a->gender == 'M') {
        male++;
    }else if (a->gender == 'F') {
        female++;
    }
    for (int i=0; i<h->numSelected; i++) {
        if (h->applicantList[i].gender == 'M') {
            male++;
        }else if (h->applicantList[i].gender == 'F') {
            female++;
        }
    }
    // if not add
    if(male <= SELECTED/2 && female <= SELECTED/2){
        
        h->applicantList[h->numSelected].age = a->age;
        h->applicantList[h->numSelected].gender = a->gender;
        h->applicantList[h->numSelected].height = a->height;
     
        h->numSelected+=1;
        return 1;
    }else {
        printf("gender over 50!\n");
        return 0;
    }
}

int selectApplicant(Hirer *h, Pool *p){
   
    // lf there are noapplicants left in the pool, 0 should be returned
    if(p->numApplicant <=0){
        return 0;
    }
    srand((unsigned)time(NULL));
    int num = rand()%p->numApplicant;
    //Applicant *a = (Applicant *)malloc(12);
    //printf("-------------%zu\n",sizeof(Applicant));
    
    if (likes(h, &p->applicantList[num])) {
        // keep the applicant if Hirer like the applicant
        if (keep(h, & p->applicantList[num]) == 1) {
            // remove the last applicant
            // exchange the value 
           /* printf("开始交换\n");
            printf("交换前申请人 %d 岁 身高%lf 的人\n",p->applicantList[num].age,p->applicantList[num].height);
            printf("预期申请人 %d 岁 身高%lf 的人\n",p->applicantList[p->numApplicant-1].age,p->applicantList[p->numApplicant-1].height);*/
            p->applicantList[num].age = p->applicantList[p->numApplicant-1].age;
            p->applicantList[num].gender = p->applicantList[p->numApplicant-1].gender;
            p->applicantList[num].height = p->applicantList[p->numApplicant-1].height;
            //printf("交换后申请人 %d 岁 身高%lf 的人\n",p->applicantList[num].age,p->applicantList[num].height);
            // the numApplicant -1
            p->numApplicant -=1;
        }
        
    }

    return 1;
}

void giveAwayApplicants (Hirer *h1, Hirer *h2, Pool *p){

    for (int i=0; i< h1->numSelected ; i++) {
        // if h2 if the applicant
        if (likes(h2, &h1->applicantList[i])>0) {
            // if h2 can not keep the applocant
            if (keep(h2, &h1->applicantList[i]) == 0) {
                // add the applicant to pool
                printf("1111\n");
                addApplicant(p, h1->applicantList[i].gender, h1->applicantList[i].height, h1->applicantList[i].age);
            }
            
        }
    }
    // Set the list of h1 to 0
    h1->numSelected=0;

}

int main(void) {
    
    Hirer h={"Fred",18,5.6,{}};
    h.applicantList[0].age=25;
    h.applicantList[0].gender='M';
    h.applicantList[0].height=175.0;

    Hirer Fred={"Fred",18,5.6,{}};
    Hirer Suzy={"Suzy",17,5.7,{}};

    Pool *p=(Pool*)malloc(sizeof(Pool));
    addApplicant(p, 'F', 5.33, 14);
    addApplicant(p, 'M', 6.12, 17);
    addApplicant(p, 'F', 5.20, 15);
    addApplicant(p, 'M', 5.82, 18);
    addApplicant(p, 'M', 5.39, 18);

    addApplicant(p, 'F', 5.25, 19);
    addApplicant(p, 'M', 6.04, 16);
    addApplicant(p, 'F', 5.96, 19);
    addApplicant(p, 'M', 5.75, 18);
    addApplicant(p, 'F', 5.37, 16);

    addApplicant(p, 'M', 5.28, 16);
    addApplicant(p, '?', 5.81, 16);
    addApplicant(p, 'F', 5.23, 18);
    addApplicant(p, 'M', 6.49, 17);
    addApplicant(p, 'F', 5.57, 18);
    
    //printf("Fred喜欢%lf:%d\n",p->applicantList[7].height,likes(&Fred, &p->applicantList[7]));
    listApplicants(p->applicantList, p->numApplicant);

    selectApplicant(&Fred, p);
    sleep(1);
    selectApplicant(&Fred, p);
    sleep(1);
    selectApplicant(&Fred, p);
    sleep(1);
    selectApplicant(&Fred, p);
    sleep(1);
    selectApplicant(&Fred, p);
    sleep(1);
    selectApplicant(&Fred, p);
    sleep(1);
    selectApplicant(&Fred, p);
    sleep(1);
    selectApplicant(&Fred, p);


    printf("--------------------------\n");
    printf("Fred's selectedd applicants: \n");
    listApplicants(Fred.applicantList, Fred.numSelected);

    printf("--------------------------\n");
    printf("Here is what is left of pool ... \n");
    listApplicants(p->applicantList, p->numApplicant);

    printf("--------------------------\n");
    printf("Suzy's selectedd applicants: \n");

    giveAwayApplicants(&Fred, &Suzy, p);
    listApplicants(Suzy.applicantList, Suzy.numSelected);
    printf("--------------------------\n");
    printf("Fred's selectedd applicants: \n");
    listApplicants(Fred.applicantList, Fred.numSelected);
    printf("--------------------------\n");
    printf("Here is what is left of pool ... \n");
    listApplicants(p->applicantList, p->numApplicant);
    

    return 0;
}