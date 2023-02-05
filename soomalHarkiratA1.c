#include "givenA1.h"

//command for makefile: ./soomalHarkiratA1 courses.txt data.txt

/*
task 1
This function will take in a filename as a string and create a FILE pointer out of it.
If the file opens successfully, a FILE pointer will be returned. Otherwise, NULL. The file will
only be opened for reading, not writing

Function name: openFileForReading
Inputs: string, struct
Returns: file pointer
*/
FILE *openFileForReading(char fileName[MAX_STR]){

    FILE *fptr;
    fptr = fopen(fileName, "r"); //create file pointer for reading

    //check if the file is empty, if so return NULL
    if(fptr==NULL){
        return NULL;
    }
    //if not empty return the file pointer
    else{
        return fptr;
    }
}

/*
task 2
This function must read struct data types from a text file to
populate the array of structs called courseInfo with course names and corresponding course
ids. The file must be read from the command line. The first 10 lines of this file store 10 course names, and the next 10
lines store 10 course ID's. Function will return 1 if successful operation or -1 if null pointer, 
file has 2 times more NUMBER_COURSES or file has 2 times less than NUMBER_COURSES

Function name: readCourse
Inputs: string, struct
Returns: int
*/
int readCourse (char filename [MAX_STR], struct courseStruct courseInfo [NUMBER_COURSES]){

    FILE *fp =  openFileForReading(filename); //using function above create file pointer for reading
    //the filename given in the parameter is set as the first command-line argument

    int i = 0; //integer used to loop through file content and set index values
    char temp[MAX_STR]; //temporary string used tot store name of course to easily transfer data to struct 
    int line = 0; //used to count how many lines are in the file

    //check if file is empty 
    if(fp==NULL){
        return -1;
    }
    //if file not empty loop through contents
    else{
        //loop will repeat 10 times 
        while (i<NUMBER_COURSES){
            fgets(temp, MAX_STR, fp); //store the content of the first line to temp string
            line++; //since fgets include newline character, increment line to keep track of lines
            temp[strlen(temp)-1] = '\0'; //since fgets include newline character it must be removed to ensure the correct data is stored
            strcpy(courseInfo[i].courseName, temp); //copy temp to courseName
            i++; //increase i by 1 so all courseNames are filled
            //after reading NUMBER_COURSES amount of lines the data changes to courseID's
            if(i==NUMBER_COURSES){
                //loop will repeat 10 times, storing all course ID values
                for(int j=0; j<NUMBER_COURSES; j++){
                    fscanf(fp, "%d", &courseInfo[j].courseID); //fscanf does not add newline character
                    line++; //add 1 after scanning each line
                }
            }
        }
        //check if amount of lines is greater than or less than 2 times NUMBER_COURSES
        if(line<(2*NUMBER_COURSES) || line>(2*NUMBER_COURSES)){
            //if so, return -1
            return -1;
        }
        else{
            //returning 1 indicates successful operation
            return 1;
        }
        //close the file to prevent issues 
        fclose(fp);
    }
}

/*
task 3
The prof names and course assignments must be read from second command line argument file. The first 6 lines of the file contain the prof names. 
The next 6 lines will consist of characters y or n, indicating whether a course is taught by a prof or not. Assume that the order of the course IDs used in
this function is the same as that used in function readCourse. This function will store the courseID's
of the courses taught by the different professors in coursesTaught in the profInfo struct

Function name: readProfAndCoursesTaught
Input: string, 2 structs
Returns: int
*/
int readProfAndCoursesTaught (char filename [MAX_STR], struct profStruct profInfo [NUMBER_PROFS], struct courseStruct courseInfo [NUMBER_COURSES]){
    
    FILE *fp =  openFileForReading(filename); //create file pointer for reading
    //the filename given in the parameter is set as the second command-line argument

    int i = 0; //integer used to loop through file content and set index values
    char temp[MAX_STR]; //temporary string to hold professor name 
    char yesOrNo[NUMBER_PROFS][NUMBER_COURSES]; //2d array to store each line of 'yynn....' which signify courses taught as y represent a course

    //check if file empty 
    if(fp==NULL){
        return -1;
    }
    //if not empty loop through data
    else{
        //loop will repeat NUMBER_PROFS amount of times
        while(i<NUMBER_PROFS){
            fgets(temp, MAX_STR, fp); //store the content of the first line to temp string
            temp[strlen(temp)-1] = '\0'; //since fgets include newline character it must be removed to ensure the correct data is stored
            strcpy(profInfo[i].profName, temp); //copy temporary string to prof Name index in the struct profInfo
            i++; //increase i by 1 so all profName are filled
            //after number professors is read, collect the courses taught data
            if(i==NUMBER_PROFS){
                //loop will run NUMBER_PROFS amount of times
                for(int j=0; j<NUMBER_PROFS; j++){
                    fscanf(fp, "%s", yesOrNo[j]); //read all the courses taught line by line
                }
            }
        }
        //nested loop will fill coursesTaught with its corresponding courseID
        //outer loop runs NUMBER_PROFS amount of times
        for(int i=0; i<NUMBER_PROFS; i++){
            //inner loop runs NUMBER_COURSES amount of times
            for(int j=0; j<NUMBER_COURSES; j++){
                //check if each index is either yes or no (y with or without lower/uppercase)
                if(yesOrNo[i][j] == 'y' || yesOrNo[i][j] == 'Y'){
                    profInfo[i].coursesTaught[j] = courseInfo[j].courseID; 
                }
                //if the course is not taught by that professor set by index i, then set index to -1
                else{
                    profInfo[i].coursesTaught[j] = -1;
                }
            }
        }
    }
    //close the file to prevent issues
    fclose(fp);
    return 1;
}
/*
task 4
This function populates an array called profsNCourses with names of all professors who
teach n or more courses. It then returns the total number of professors who teach n
or more courses.

Function name: nCourses
Input: int, struct, 2d string
Returns: int
*/
int nCourses (int n, struct profStruct profInfo [NUMBER_PROFS], char profsNCourses [NUMBER_PROFS][MAX_STR]){

    int amount = 0; //number profs who teach n or more courses
    int count; //number courses taught by each professor

    //outer loop will run NUMBER_PROFS amount of times
    for(int i=0; i<NUMBER_PROFS; i++){
        count = 0; //after inner loop runs NUMBER_COURSES amount of times, count is reinitalized to 0 so each profs data is checked
        for(int j=0; j<NUMBER_COURSES; j++){
            //check if the course is taught by the professor for the index by checking if its not -1 
            if(profInfo[i].coursesTaught[j] != -1){
                count++; //increase courses by 1 for that index
            }
        }
        //check if count is greater or equal to n for the specific professor and save that prof name to profsNCourses
        if(count>=n){
            strcpy(profsNCourses[amount], profInfo[i].profName); //copy that specific professor to the 2d array
            amount++; //increase num to ensure all the professors teaching n or more courses are added to the 2d array
        }
    }
    //return the number of professors who teach n or more courses
    return amount;
}
/*
task 5
This function, takes a course number as input, searches for its course name and stores it in
a string parameter (e.g. cNameFound). It returns 1 if the course is found, 0 otherwise. For
example, if the course number is 1300, it will return 1 and store “Programming” in cNameFound.

Function name: getCourseName 
Input: int, string, struct
Returns: int
*/
int getCourseName (int courseNum, char cNameFound [MAX_STR], struct courseStruct courseInfo [NUMBER_COURSES]){

    //loop will repeat NUMBER_COURSES amount of times
    for(int i=0; i<NUMBER_COURSES; i++){
        //checks if the specific courseID is equal to the course number passed in
        if(courseInfo[i].courseID == courseNum){
            strcpy(cNameFound, courseInfo[i].courseName); //if true copy that course name to array cNameFound
            return 1; //return 1 if course ID is found
        }
    }
    return 0; //otherwise return 0 if course ID not found
}

/*
task 6
This function, takes a course name as input, searches for its course number and stores it in
an output int parameter (e.g. cNumFound). It returns 1 if the course is found, 0 otherwise.
If the course number is 1300, it will return 1 and store 1300 in *cNumFound.

Function name: getCourseNum
Input: string, int pointer, struct
Returns: int
*/
int getCourseNum (char cName [MAX_STR], int * cNumFound, struct courseStruct courseInfo [NUMBER_COURSES]){

    //loop repeats NUMBER_COURSES amount of times
    for(int i=0; i<NUMBER_COURSES; i++){
        //check if the course name passed in is equal to the specifc course name
        if(strcmp(cName, courseInfo[i].courseName)==0){
            *cNumFound = courseInfo[i].courseID; //if they are equal set int pointer to that specfic course ID 
            return 1;
        }
    }
    return 0;
}
/*
task 7
This function, takes a course number as input, searches for the profs teaching it, and
populates array taughtBy with these prof names. It returns the total number of profs
teaching the course courseNum if the course is found, 0 otherwise. It also returns 0 if the
course is not taught by any prof. If the course number is 1300, it will populate
taughtBy with “Ritu”, “Ben” and “Sooraj”. The function returns 3 in this case

Function name: profsTeachingCourse 
Input: int, struct, 2d string
Returns: int
*/
int profsTeachingCourse (int courseNum, struct profStruct profInfo [NUMBER_PROFS], char taughtBy [NUMBER_PROFS][MAX_STR]){

    int num = 0; //number of professors teaching the course
    //outer loop will repeat NUMBER_PROFS amount of times
    for(int i=0; i<NUMBER_PROFS; i++){
        //inner loop will repeat NUMBER_COURSES amount of times
        for(int j=0; j<NUMBER_COURSES; j++){
            //check if the course ID passed in is equal to coursesTaught and copy that specific profs name to the the 2d array
            if(profInfo[i].coursesTaught[j] == courseNum){
                strcpy(taughtBy[num], profInfo[i].profName); //copy prof name to 2d array taughtBy
                num++; //increase num to add all the profs teaching the course ID passed in
            }
        }
    }
    //return the total amount of professors teaching the specific course
    return num;
}
/*
task 8
This function returns the average number of courses taught by a professor. The returned value
will be rounded to the nearest digit

Function name: avgNumCourses
Input: struct
Returns: float
*/
float avgNumCourses (struct profStruct profInfo [NUMBER_PROFS]){

    float average = 0; //variable used to hold the average amount of courses taught throughout all professors
    //outer loop repeats NUMBER_PROFS amount of times
    for(int i=0; i<NUMBER_PROFS; i++){
        //innerloop repeats NUMBER_COURSES amount of times
        for(int j=0; j<NUMBER_COURSES; j++){
            //check if the course is being taught by the specific professor
            if(profInfo[i].coursesTaught[j] != -1){
                average++; //add 1 to the total amount of courses taught
            }
        }
    }
    average = (average/NUMBER_PROFS); //divide the total by amount of professors
    average = (int)average + 1; //cast the float type into an integer and add 1 to round 
    average = (float)average; //cast back to a float datatype (since math.h and ceil can cause issues in terminal)
    return average;
}
