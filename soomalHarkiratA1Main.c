/*
Harkirat Soomal 
hsoomal@uoguelph.ca 1232181
*/
#include "givenA1.h"
/*cAllocation
This program prompts the user for four different options displayed on a menu. Each of these options represents a task/function regarding
professors and courses at the university. The user will be continously prompted until they enter an invalid input
*/
int main(int argc, char * argv[]){

    int userChoice; //variable will hold integer from 4-8 that stores users choice for which task they would like to perform
    //these next two variables will be used to test whether task 2 and task 3 work succesfully and make sure neither return -1
    int checkTask2;
    int checkTask3;
    int locate; //variable used to hold the return value from multiple task functions and is used to confirm if the task was successful
    int courseNum; //variable used to store course ID that is entered by the user and used in task 5 and task 7
    int cNumFound; //variable used in task 6 to store the course ID of the corresponding inputed course name
    char cNameFound[MAX_STR]; //string used to hold course name for task 5
    char profsNCourses[NUMBER_PROFS][MAX_STR]; //2d string used to store all professors teaching a specific course used in task 4
    char cName[MAX_STR]; //string used to store user input for course name used in task 6
    char taughtBy[NUMBER_PROFS][MAX_STR]; //2d string to store courses all prof names that taught a specific course in task 7
 
    struct courseStruct courseInfo[NUMBER_COURSES]; //struct datatype for courseStruct used for course names and course ID's
    struct profStruct profInfo[NUMBER_PROFS]; //struct datatype for profInfo used for professor names and the courses taught
    /*
    before prompting the user check if task 2 can be run correctly using the first command line argument and check
    if there is the correct amount of lines along with a working file pointer
    */
    checkTask2 = readCourse(argv[1], courseInfo);
    if(checkTask2 == -1){
        printf("Unsuccessful operation for task 2\n");
    }
    /*
    before prompting the user check if task 3 can be run correctly using the first command line argument and check
    if there is the correct amount of lines along with a working file pointer
    */
    checkTask3 = readProfAndCoursesTaught(argv[2], profInfo, courseInfo);
    if(checkTask3 == -1){
        printf("Unsuccessful operation for task 3\n");
    }
    //if either one of the tasks returns -1 (indicating a unsuccessful operation) than the program must stop
    if(checkTask2 == -1 || checkTask3 == -1){
        return 0;
    }
    //Use a do-while loop to prompt user atleast once before they the inputted value is tested. The loop will continously run until a value <4 or >8 is inputted
    do{
        //output display for menu and options user can select
        printf("***********************\nMenu Options: \n");
        printf("\nTask 4 - nCourses\nTask 5 - getCourseName\nTask 6 - getCourseNum\nTask 7 - profsTeachingCourse\nTask 8 - avgNumCourses\n\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);
        printf("***********************\n");
        /*
        since scanf leaves a newline character in the input stream it can mess up the input for fgets used in task 6 
        so getchar is used here to clear the input stream and removes the newline character allowing fgets to successfully work
        */
        getchar(); 
        //user input for task 4
        if(userChoice == 4){
            int total; //variable used to store all amount of professors who teach n or more courses
            int n; //variable used to store user input for how many professors teach a specific amount of courses
            //do-while loop to prompt until user enters a valid amount of courses (>0)
            do{
                printf("Enter value for n: ");
                scanf("%d", &n);
            }while(n<0);
            total = nCourses(n, profInfo, profsNCourses); //total stores the return value from task 4
            printf("There is %d professor(s) that teach %d amount courses or more: \n", total, n);
            //print all professor names who teach the particular amount of courses
            for(int i=0; i<total; i++){
                printf("%s\n", profsNCourses[i]);
            }
        }
        //user input for task 5
        else if(userChoice == 5){
            printf("Enter a course ID: ");
            scanf("%d", &courseNum);
            locate = getCourseName(courseNum, cNameFound, courseInfo); //locate stores return value from task 5
            //check if task 5 runs succesfully and make sure the course ID is present
            if(locate==0){
                printf("Course ID is not located\n");
            }else{ //if course ID is located print that ID's corresponding course name
                printf("The course name is: %s\n", cNameFound);
            }
        }
        //user input for task 6
        else if(userChoice == 6){
            printf("Enter a course name: ");
            fgets(cName, MAX_STR, stdin); //obtain user input for the course (fgets since some names have spaces)
            cName[strlen(cName)-1] = '\0'; //remove the trailing newline character
            locate = getCourseNum(cName, &cNumFound, courseInfo); //locate stores return value from task 6
            //check if task 6 runs succesfully and make sure course name is found
            if(locate==0){
                printf("The course is not located\n");
            }else{ //if course name is found print the corresponding course ID
                printf("%d\n", cNumFound);
            }
        }
        //user input for task 7
        else if(userChoice == 7){
            printf("Enter a course ID: ");
            scanf("%d", &courseNum);
            locate = profsTeachingCourse(courseNum, profInfo, taughtBy); //locate stores return value task 7
            //check if task 7 runs succesfully 
            if(locate==0){
                printf("There is no professor teaching this course\n");
            }else{ //if the ID is found print all professor names that teach it
                printf("There are %d profs that teach the course %d: \n", locate, courseNum);
                for(int j=0; j<locate; j++){
                    printf("%s\n", taughtBy[j]); //print each professor name
                }
            }
        }
        //user input for task 8
        else if(userChoice == 8){
            float average; //float variable used to store average of all courses taught
            average = avgNumCourses(profInfo); //average hold return value from task 8
            printf("The average courses taught by a professor is %.1f courses\n", average); //print average to one decimal places
        }
    }while(userChoice >=4 && userChoice <=8); //check if the user input is between 4 and 8 and continously run program till invalid input is entered
    //if input value is invalid end the program
    if (userChoice <4 || userChoice >8){
        printf("This is an invalid option");
        return 0;
    }
}

