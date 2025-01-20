
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//design 
#define RESET_COLOR "\033[0m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[1;33m"
#define RED "\033[31m"

#define STUDENT_FILE "user143.txt"
#define TEACHER_FILE "user599.txt"
//define array size
//#define MAX_AMOUNT_LENGTH 20
    #define MAX_NAME_LENGTH 100
    #define MAX_DATE_LENGTH 15
    #define MAX_DEP_LENGTH 40
    #define MAX_ID_LENGTH 15
    #define MAX_SEMES_LENGTH 50
    //#define MAX_YEAR_LENGTH 15

    //define admin or password
    #define ADMIN_USERNAME "admin"
    #define ADMIN_PASSWORD "1234"

    //student details
    typedef struct{
        char name[MAX_NAME_LENGTH];
        char id[MAX_ID_LENGTH];
        char deperment[MAX_DEP_LENGTH];
        char semester[MAX_SEMES_LENGTH];//fall/spring/summer
        int year;
        char date[MAX_DATE_LENGTH];
        //double amount;
        double midfee;
        double Final;
        double Latefee;
        double Admissionfee;
    }Student;

    //teacher details
typedef struct{
    char Name[MAX_NAME_LENGTH];
    char role[MAX_DEP_LENGTH];
    char ID[MAX_ID_LENGTH];
    int experience;
    float base_salary;
    float total_salary;
}Teacher;

//Function Declartions
void adminLogin();
void displayMenu();
void displaySemester();
void displayAllMenu();
void displayAllMember();
void displayreg();
void displayregteacher();
//student info function
void Student_info();

void displayAllStudents();
void UniversityAllfee();
void AdmissionFormfee();
void latefee();
void Re_AdmissionFee();
void Certificatefee();
void Libraryfee();
void Labfee();
void Others();
void IDRe_issue();
void TuitionFee();
void SemesterFee();
void ImprovenentExam();
void displaySemesterFee();
void Mid();
void Final();

void Studentreg();
void AddRecord();
void DeleteRecord();
void ModifyRecord();
void SearchRecord();

//Teacher info Function
void Teacherinfo();
void displayteacher();
void Listteacher();
void Teacherreg();
void Add();
void Delete();
void Modify();

void display_logo()
{
    printf(BLUE " DDDD    AAAAA  FFFFF  FFFFF  OOOOO  DDDD    III  L      \n");
    printf(" D   D  A     A F      F      O   O  D   D    I   L      \n");
    printf(" D   D  AAAAAAA FFFFF  FFFFF  O   O  D   D    I   L      \n");
    printf(" D   D  A     A F      F      O   O  D   D    I   L      \n");
    printf(" DDDD   A     A F      F      OOOOO  DDDD    III  LLLLL  \n" RESET_COLOR);
    printf(GREEN "Daffodil International University\n" RESET_COLOR);
}

//Main Function
int main(){
    display_logo();
    adminLogin();
    int choice;
    do{
        displayMenu();
        printf("Enter Your Choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                Student_info();
                break;
            case 2:
                Teacherinfo();
                break;
            case 3:
                printf(BLUE"Exiting the system. Goodbye!\n"RESET_COLOR);
                break;
            default:
                printf(RED"Invalid choice. Please choose again.\n"RESET_COLOR);
        }

    }while(choice != 3);

    return 0;

}

void Teacherinfo(){
    int option;
    do{
        displayregteacher();
        printf("Enter Your Choice: ");
        scanf("%d",&option);
        switch(option){
            case 1:
                Teacherreg();
                break;
            case 2:
                displayteacher();
                break;
            case 3:
                Listteacher();
                break;
            case 4:
                printf(BLUE"Exiting the system. Goodbye!\n"RESET_COLOR);
                break;
            default:
                printf(RED"Invalid choice. Please choose again.\n"RESET_COLOR);
        }
    }while(option!=4);
}

void Teacherreg(){
    int option;
    do{
        displayAllMember();
        printf("Enter Your Choice: ");
        scanf("%d",&option);
        switch(option){
            case 1:
                Add();
                break;
            case 2:
                Delete();
                break;
            case 3:
                Modify();
                break;
            case 4:
                printf(BLUE"Exiting the system. Goodbye!\n"RESET_COLOR);
                break;
            default:
                printf(RED"Invalid choice. Please choose again.\n"RESET_COLOR);

        }

    }while(option != 4);

}

void Add(){
    Teacher tea;
    //save to file
    FILE *file=fopen(TEACHER_FILE,"ab");
    if(file == NULL){
        printf(RED"Error opening file!\n"RESET_COLOR);
        return;
    }

    printf("Enter Teacher Name: ");
    getchar();
    fgets(tea.Name,MAX_NAME_LENGTH,stdin);
    strtok(tea.Name,"\n");//remove new line

    printf("Enter Teacher ID: ");
    fgets(tea.ID,MAX_ID_LENGTH,stdin);
    strtok(tea.ID,"\n");//remove new line


    printf("Enter Role: ");
    fgets(tea.role,MAX_DEP_LENGTH,stdin);
    strtok(tea.role,"\n");//remove new line

    printf("Enter Experience (years): ");
    scanf("%d", &tea.experience);

    printf("Enter Base Salary: ");
    scanf("%f", &tea.base_salary);

    // Calculate total salary (example formula: base salary + 10% for every year of experience)
   tea.total_salary =tea.base_salary + (0.1 *tea.experience *tea.base_salary);

    fwrite(&tea,sizeof(Teacher),1,file);
    fclose(file);
    printf(GREEN"Teacher added successfully.\n"RESET_COLOR);
}

void Delete(){
    char searchkey[MAX_NAME_LENGTH];
    int found = 0;

    printf("\nEnter Teacher Name or ID to delete: ");
    getchar();
    fgets(searchkey,MAX_NAME_LENGTH,stdin);
    strtok(searchkey,"\n"); //remove newline

    FILE *file = fopen(TEACHER_FILE,"rb");
    if(file == NULL){
        printf(RED"No teacher data found.\n"RESET_COLOR);
        return;
    }

    FILE *temp = fopen("tempfile.txt","wb");
    if(temp == NULL){
        printf(RED"Error creating temporary file.\n"RESET_COLOR);
        fclose(file);
        return;
    }

    Teacher tea;
    while(fread(&tea,sizeof(Teacher),1,file)){
        if(strstr(tea.Name,searchkey) == NULL && strcmp(tea.ID,searchkey) != 0){
            fwrite(&tea,sizeof(Teacher),1,temp);
    }else{
        found = 1;
        printf("Deleted record: Name: %s, ID: %s\n",tea.Name,tea.ID);
    }

}
fclose(file);
fclose(temp);

if(found){
    remove(TEACHER_FILE);
    rename("tempfile.txt",TEACHER_FILE);
    printf(GREEN"Teacher Record deleted successfully.\n"RESET_COLOR);
}else{
    remove("tempfile.txt");
    printf(RED"No Teacher record found to delete.\n"RESET_COLOR);
}

}

//uodate function
void Modify() {
    char searchkey[MAX_NAME_LENGTH];
    int found = 0;

    printf("\nEnter Teacher Name or ID to delete: ");
    getchar();
    fgets(searchkey,MAX_NAME_LENGTH,stdin);
    strtok(searchkey,"\n"); //remove newline

     FILE *file = fopen(TEACHER_FILE,"rb");
    if(file == NULL){
        printf(RED"No teacher data found.\n"RESET_COLOR);
        return;
    }

    FILE *temp = fopen("tempfile.txt","wb");
    if(temp == NULL){
        printf(RED"Error creating temporary file.\n"RESET_COLOR);
        fclose(file);
        return;
    }

    Teacher tea;
    while (fread(&tea, sizeof(Teacher), 1, file)) {
        if (strstr(tea.Name, searchkey) != NULL || strcmp(tea.ID, searchkey) == 0) {
            found = 1;
            printf(YELLOW"\n----Current Record----\n"RESET_COLOR);
            printf("\nName: %s\n",tea.Name);
            printf("ID: %s\n",tea.ID);
            printf("Role: %s\n",tea.role);
            printf("Experience: %d\n",tea.experience);
            printf("Base Salary: %f\n",tea.base_salary);

            // Prompt for new details
            printf(YELLOW"\n\n---- Enter new details ----\n"RESET_COLOR);

            printf("Enter Teacher Name (current: %s): ", tea.Name);
            char newName[MAX_NAME_LENGTH];
            fgets(newName, MAX_NAME_LENGTH, stdin);
            if (strcmp(newName, "\n") != 0) {
                strtok(newName, "\n"); // Remove newline
                strcpy(tea.Name, newName);
            }

            printf("Enter Teacher ID (current: %s): ", tea.ID);
            char newID[MAX_ID_LENGTH];
            fgets(newID, MAX_ID_LENGTH, stdin);
            if (strcmp(newID, "\n") != 0) {
                strtok(newID, "\n"); // Remove newline
                strcpy(tea.ID, newID);
            }

            printf("Enter Role (current: %s): ", tea.role);
            char newRole[MAX_DEP_LENGTH];
            fgets(newRole, MAX_DEP_LENGTH, stdin);
            if (strcmp(newRole, "\n") != 0) {
                strtok(newRole, "\n"); // Remove newline
                strcpy(tea.role, newRole);
            }

            printf("Enter Experience (current: %d): ", tea.experience);
            int newexp;
            scanf("%d",&newexp);
            tea.experience = newexp;

            printf("Enter Base Salary (current: %f): ", tea.base_salary);
            float newbase;
            scanf("%f",&newbase);
            tea.base_salary = newbase;

            tea.total_salary =tea.base_salary + (0.1 *tea.experience *tea.base_salary);

            
        }
        fwrite(&tea, sizeof(Teacher), 1, temp);
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove(TEACHER_FILE);
        rename("tempfile.txt", TEACHER_FILE);
        printf(GREEN"teacher record updated successfully.\n"RESET_COLOR);
    } else {
        remove("tempfile.txt");
        printf(RED"No teacher record found to modify.\n"RESET_COLOR);
    }
}


void displayteacher(){
    char searchkey[MAX_NAME_LENGTH];

    int found = 0;


    printf("\nEnter Teacher Name or ID to search: ");
    getchar();
    fgets(searchkey,MAX_NAME_LENGTH,stdin);
    strtok(searchkey,"\n");//remove new line

    FILE *file = fopen(TEACHER_FILE,"rb");
    if(file == NULL){
        printf(RED"No teacher data found.\n"RESET_COLOR);
        return;
    }


    Teacher tea;

    while(fread(&tea,sizeof(Teacher),1,file)){
        if(strstr(tea.Name,searchkey)!=NULL || strcmp(tea.ID,searchkey)==0 ){
            printf("\n----Teacher Found----\n");
            printf("\nName: %s\n",tea.Name);
            printf("ID: %s\n",tea.ID);
            printf("Role: %s\n",tea.role);
            printf("Experience: %d\n",tea.experience);
            printf("Base Salary: %f\n",tea.base_salary);
            printf("Total Salary: %f\n",tea.total_salary);
            found = 1;
        }

    }

    fclose(file);
    if(found == 0){
        printf(RED"No teacher found with the given name or ID.\n"RESET_COLOR);
    }

}

void Listteacher(){

     //save to file
    FILE *file=fopen(TEACHER_FILE,"rb");
    if(file == NULL){
        printf(RED"No Teacher data found.\n"RESET_COLOR);
        return;
    }

    printf(YELLOW"\n---- All Teacher Details ----\n"RESET_COLOR);
   Teacher tea;


    while(fread(&tea,sizeof(Teacher),1,file)){
            printf("\nName: %s\n",tea.Name);
            printf("ID: %s\n",tea.ID);
            printf("Role: %s\n",tea.role);
            printf("Experience: %d\n",tea.experience);
            printf("Base Salary: %f\n",tea.base_salary);
            printf("Total Salary: %f\n",tea.total_salary);
    }

    fclose(file);
}

void Student_info(){
    
    int option;
    do{
        displayreg();
        printf("Enter Your Choice: ");
        scanf("%d",&option);
        switch(option){
            case 1:
                Studentreg();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                SearchRecord();
                break;
            case 4:
                UniversityAllfee();
                break;
            case 5:
                printf(BLUE"\nExiting the system. Goodbye!\n"RESET_COLOR);
                break;
            default:
                printf(RED"Invalid choice. Please choose again.\n"RESET_COLOR);

        }

    }while(option != 5);

}

//regestration of student

void Studentreg(){
    int option;
    do{
        displayAllMember();
        printf("Enter Your Choice: ");
        scanf("%d",&option);
        switch(option){
            case 1:
                AddRecord();
                break;
            case 2:
                DeleteRecord();
                break;
            case 3:
                ModifyRecord();
                break;
            case 4:
                printf(BLUE"Exiting the system. Goodbye!\n"RESET_COLOR);
                break;
            default:
                printf(RED"Invalid choice. Please choose again.\n"RESET_COLOR);

        }

    }while(option != 4);

}

//university all fee
void UniversityAllfee(){
    int option;
    do{
        displayAllMenu();
        printf("Enter Your Choice: ");
        scanf("%d",&option);
        switch(option){
        case 1:
            AdmissionFormfee();
            break;
        case 2:
            Re_AdmissionFee();
            break;
        case 3:
            TuitionFee();
            break;
        case 4:
            displaySemesterFee();
            break;
        case 5:
            Labfee();
            break;
        case 6:
            Libraryfee();
            break;
        case 7:
            ImprovenentExam();
            break;
        case 8:
            IDRe_issue();
            break;
        case 9:
            Certificatefee();
            break;
        case 10:
            latefee();
            break;
        case 11:
            Others();
            break;
        case 12:
            printf(BLUE"Exiting the system. Goodbye!\n"RESET_COLOR);
            break;
        default:
            printf(RED"Invalid choice. Please choose again.\n"RESET_COLOR);

        }
    }while(option != 12);
}

void displaySemesterFee(){
    int option;
    do{
        displaySemester();
        printf("Enter Your Choice: ");
        scanf("%d",&option);
        switch(option){
            case 1:
                Mid();
                break;
            case 2:
                Final();
                break;
            case 3:
                printf(BLUE"Exiting the system. Goodbye!\n"RESET_COLOR);
                break;
            default:
                printf(RED"Invalid choice. Please choose again.\n"RESET_COLOR);

        }

    }while(option != 3);

}

void AdmissionFormfee(){
    printf(YELLOW"\n\nAdmission Form fee is 1000\n"RESET_COLOR);
    char studentID[MAX_ID_LENGTH];
    double amount;

    printf("Enter student ID to record Admission fee: ");
    getchar();
    fgets(studentID,MAX_ID_LENGTH,stdin);
    strtok(studentID,"\n");

    printf("Enter Admission Fee amount: ");
    scanf("%lf",&amount);

    FILE *file=fopen(STUDENT_FILE,"rb+");
    if(file==NULL){
        printf(RED"Error opening file\n"RESET_COLOR);
        return;
    }

    Student s;
    int found=0;
    while(fread(&s,sizeof(Student),1,file)){
        if(strcmp(s.id,studentID)==0){
            s.Admissionfee=amount;
            fseek(file,-sizeof(Student),SEEK_CUR); //pointer change 
            fwrite(&s,sizeof(Student),1,file);
            found=1;
            printf(GREEN"Admission Form fee updated successfully for Student ID: %s\n"RESET_COLOR, studentID);
            break;
        }
    }
    fclose(file);
    if(found==0){
        printf(RED"No Student found with the given ID.\n"RESET_COLOR);
    }
}

void ImprovenentExam(){
    printf(RED"Not Working\n"RESET_COLOR);
}

void Re_AdmissionFee(){
    printf(RED"Not Working\n"RESET_COLOR);

}

void TuitionFee(){
    printf(RED"Not Working\n"RESET_COLOR);

}

void Labfee(){
    printf(RED"Not Working\n"RESET_COLOR);

}

void Libraryfee(){
    printf(RED"Not Working\n"RESET_COLOR);

}

void Others(){
    printf(RED"Not Working\n"RESET_COLOR);

}

void Certificatefee(){
    printf(RED"Not Working\n"RESET_COLOR);

}

void IDRe_issue(){
    printf(RED"Not Working\n"RESET_COLOR);

}


void latefee(){
    printf(YELLOW"\n\nLate fee is 200\n"RESET_COLOR);
    char studentID[MAX_ID_LENGTH];
    double amount;

    printf("Enter student ID to record Late fee: ");
    getchar();
    fgets(studentID,MAX_ID_LENGTH,stdin);
    strtok(studentID,"\n");

    printf("Enter Late fee Amount: ");
    scanf("%lf",&amount);

    FILE* file=fopen(STUDENT_FILE,"rb+");
    if(file==NULL){
        printf(RED"Error opening file\n"RESET_COLOR);
        return;
    }
    Student s;
    int found=0;

    while(fread(&s,sizeof(Student),1,file)){
        if(strcmp(s.id,studentID)==0){
            s.Latefee=amount;
            fseek(file,-sizeof(Student),SEEK_CUR);
            fwrite(&s,sizeof(Student),1,file);
            found=1;
            printf(GREEN"Late fee updated successfully for Student ID: %s\n"RESET_COLOR, studentID);
            break;
        }
    }

    fclose(file);
    if(found==0){
        printf(RED"No Student found with the given ID.\n"RESET_COLOR);
    }

}

void Final(){
    char studentID[MAX_ID_LENGTH];
    double finalamount;

    printf("Enter student ID to record Final fee: ");
    getchar();
    fgets(studentID, MAX_ID_LENGTH, stdin);
    strtok(studentID,"\n");

    printf("Enter the Final Exam Amount: ");
    scanf("%lf",&finalamount);

    FILE *file=fopen(STUDENT_FILE,"rb+");
    if(file == NULL){
        printf(RED"Error opening file\n"RESET_COLOR);
        return;
    }
    Student s;
    int found=0;
    while(fread(&s,sizeof(Student),1,file)){
        if(strcmp(s.id,studentID)==0){
            s.Final=finalamount;
            fseek(file,-sizeof(Student),SEEK_CUR);
            fwrite(&s,sizeof(Student),1,file);
            found=1;
            printf(GREEN"Final Exam fee updated successfully for Student ID: %s\n"RESET_COLOR, studentID);
            break;
    }
    }
    fclose(file);
    if(found==0){
        printf(RED"No Student found with the given ID.\n"RESET_COLOR);
    }
}

void Mid() {
    char studentID[MAX_ID_LENGTH];
    double midtermAmount;

    printf("Enter Student ID to record Midterm fee: ");
    getchar(); // to consume newline from previous input
    fgets(studentID, MAX_ID_LENGTH, stdin);
    strtok(studentID, "\n"); // remove newline

    printf("Enter the Midterm Amount: ");
    scanf("%lf", &midtermAmount);

    // Open the file to read and update the student's midterm fee
    FILE *file = fopen(STUDENT_FILE, "rb+");
    if (file == NULL) {
        printf(RED"Error opening file!\n"RESET_COLOR);
        return;
    }

    Student student;
    int found = 0;

    // Search for the student by ID and update the midterm fee
    while (fread(&student, sizeof(Student), 1, file)) {
        if (strcmp(student.id, studentID) == 0) {
            student.midfee = midtermAmount; // Update midterm fee
            fseek(file, -sizeof(Student), SEEK_CUR); // Move the file pointer back
            fwrite(&student, sizeof(Student), 1, file); // Write updated student record
            found = 1;
            printf(GREEN"Midterm fee updated successfully for Student ID: %s\n"RESET_COLOR, studentID);
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf(RED"No student found with the given ID.\n"RESET_COLOR);
    }
}

void adminLogin(){
    char username[20],password[20];
    printf(YELLOW"\n\n----Admin Login----\n"RESET_COLOR);

    printf("Enter Username: ");
    scanf("%s",username);

    printf("Enter Password: ");
    scanf("%s",password);

   // while(strcmp(username,ADMIN_USERNAME) != 0 || strcmp(password,ADMIN_PASSWORD) != 0)
    if(strcmp(username,ADMIN_USERNAME) != 0 || strcmp(password,ADMIN_PASSWORD) != 0)
{
    printf(RED"Access Denied! Incorrect username or password.\n"RESET_COLOR);
    //exit(0);
    adminLogin();
    }
    printf(GREEN"Login Successful!\n\n"RESET_COLOR);
}


void AddRecord(){
    Student student;
    //save to file
    FILE *file=fopen(STUDENT_FILE,"ab");
    if(file == NULL){
        printf(RED"Error opening file!\n"RESET_COLOR);
        return;
    }

    printf("Enter Student Name: ");
    getchar();
    fgets(student.name,MAX_NAME_LENGTH,stdin);
    strtok(student.name,"\n");//remove new line

    printf("Enter Student ID: ");
    fgets(student.id,MAX_ID_LENGTH,stdin);
    strtok(student.id,"\n");//remove new line
    
    printf("Enter Deperment Name: ");
    fgets(student.deperment,MAX_DEP_LENGTH,stdin);
    strtok(student.deperment,"\n");//remove new line

    printf("Enter Semester Name: ");
    fgets(student.semester,MAX_SEMES_LENGTH,stdin);
    strtok(student.semester,"\n");//remove new line
    
    printf("Enter Date: ");
    fgets(student.date,MAX_DATE_LENGTH,stdin);
    strtok(student.date,"\n");//remove new line

    printf("Enter Year: ");
    scanf("%d",&student.year);

    fwrite(&student,sizeof(Student),1,file);
    fclose(file);
    printf(GREEN"Record added successfully!\n"RESET_COLOR);
}

void SearchRecord(){
    char searchkey[MAX_NAME_LENGTH];

    int found = 0;


    printf("\nEnter Student Name or ID to search: ");
    getchar();
    fgets(searchkey,MAX_NAME_LENGTH,stdin);
    strtok(searchkey,"\n");//remove new line

    FILE *file = fopen(STUDENT_FILE,"rb");
    if(file == NULL){
        printf(RED"No student data found.\n"RESET_COLOR);
        return;
    }


    Student student;

    while(fread(&student,sizeof(Student),1,file)){

        if(strstr(student.name,searchkey)!=NULL || strcmp(student.id,searchkey)==0 ){
            printf(YELLOW"\n----Student Found----\n"RESET_COLOR);
            printf("Name: %s\n",student.name);
            printf("ID: %s\n",student.id);
            printf("Department: %s\n",student.deperment);
            printf("Semester: %s\n",student.semester);
            printf("Date: %s\n",student.date);
            printf("Year: %d\n",student.year);
            printf("Midterm Fee: %.2lf\n",student.midfee);
            printf("Final Fee: %.2lf\n",student.Final);
            printf("Admission Fee: %.2lf\n",student.Admissionfee);
            printf("Late Fee: %.2lf\n",student.Latefee);

            found = 1;
        }

    }

    fclose(file);
    if(found == 0){
        printf(RED"No student found with the given name or ID.\n"RESET_COLOR);
    }

}

void displayAllStudents(){
    FILE *file = fopen(STUDENT_FILE,"rb");
    if(file == NULL){
        printf(RED"No student data found.\n"RESET_COLOR);
        return;
    }

    printf(YELLOW"\n\n----All Student Details----\n"RESET_COLOR);
    Student student;


    while(fread(&student,sizeof(Student),1,file)){
            printf("\nName: %s\n",student.name);
            printf("ID: %s\n",student.id);
            printf("Department: %s\n",student.deperment);
            printf("Semester: %s\n",student.semester);
            printf("Date: %s\n",student.date);
            printf("Year: %d\n",student.year);
            printf("Midterm Fee: %.2f\n",student.midfee);
            printf("Final Fee: %.2lf\n",student.Final);
            printf("Admission Fee: %.2lf\n",student.Admissionfee);
            printf("Late Fee: %.2lf\n",student.Latefee);
            
    }

    fclose(file);
}

void DeleteRecord(){
    char searchkey[MAX_NAME_LENGTH];
    int found = 0;

    printf("\n\nEnter Student Name or ID to delete: ");
    getchar();
    fgets(searchkey,MAX_NAME_LENGTH,stdin);
    strtok(searchkey,"\n"); //remove newline

    FILE *file = fopen(STUDENT_FILE,"rb");
    if(file == NULL){
        printf(RED"No student data found.\n"RESET_COLOR);
        return;
    }

    FILE *tempfile = fopen("temp.txt","wb");
    if(tempfile == NULL){
        printf(RED"Error creating temporary file.\n"RESET_COLOR);
        fclose(file);
        return;
    }

    Student student;
    while(fread(&student,sizeof(Student),1,file)){
        if(strstr(student.name,searchkey) == NULL && strcmp(student.id,searchkey) != 0){
            fwrite(&student,sizeof(Student),1,tempfile);
    }else{
        found = 1;
        printf("Deleted record: Name: %s, ID: %s\n",student.name,student.id);
    }

}
fclose(file);
fclose(tempfile);

if(found){
    remove(STUDENT_FILE);
    rename("temp.txt",STUDENT_FILE);
    printf(GREEN"Student Record deleted successfully.\n"RESET_COLOR);
}else{
    remove("temp.txt");
    printf(RED"No student record found to delete.\n"RESET_COLOR);
}

}

void ModifyRecord() {
    char searchkey[MAX_NAME_LENGTH];
    int found = 0;

    printf("\nEnter Student Name or ID to modify: ");
    getchar();
    fgets(searchkey, MAX_NAME_LENGTH, stdin);
    strtok(searchkey, "\n"); // Remove newline

    FILE *file = fopen(STUDENT_FILE, "rb");
    if (file == NULL) {
        printf(RED"No student data found.\n"RESET_COLOR);
        return;
    }

    FILE *tempfile = fopen("temp.txt", "wb");
    if (tempfile == NULL) {
        printf(RED"Error creating temporary file.\n"RESET_COLOR);
        fclose(file);
        return;
    }

    Student student;
    while (fread(&student, sizeof(Student), 1, file)) {
        if (strstr(student.name, searchkey) != NULL || strcmp(student.id, searchkey) == 0) {
            found = 1;
            printf(YELLOW"\n\n----Current Record----\n"RESET_COLOR);
            printf("Name: %s\n", student.name);
            printf("ID: %s\n", student.id);
            printf("Department: %s\n", student.deperment);
            printf("Semester: %s\n", student.semester);

            // Prompt for new details
            printf(YELLOW"\n---- Enter new details ----\n"RESET_COLOR);

            printf("Enter Student Name (current: %s): ", student.name);
            char newName[MAX_NAME_LENGTH];
            fgets(newName, MAX_NAME_LENGTH, stdin);
            if (strcmp(newName, "\n") != 0) {
                strtok(newName, "\n"); // Remove newline
                strcpy(student.name, newName);
            }

            printf("Enter Student ID (current: %s): ", student.id);
            char newID[MAX_ID_LENGTH];
            fgets(newID, MAX_ID_LENGTH, stdin);
            if (strcmp(newID, "\n") != 0) {
                strtok(newID, "\n"); // Remove newline
                strcpy(student.id, newID);
            }

            printf("Enter Department Name (current: %s): ", student.deperment);
            char newDepartment[MAX_DEP_LENGTH];
            fgets(newDepartment, MAX_DEP_LENGTH, stdin);
            if (strcmp(newDepartment, "\n") != 0) {
                strtok(newDepartment, "\n"); // Remove newline
                strcpy(student.deperment, newDepartment);
            }

            printf("Enter Semester (current: %s): ", student.semester);
            char newSemester[MAX_SEMES_LENGTH];
            fgets(newSemester, MAX_SEMES_LENGTH, stdin);
            if (strcmp(newSemester, "\n") != 0) {
                strtok(newSemester, "\n"); // Remove newline
                strcpy(student.semester, newSemester);
            }
        }
        fwrite(&student, sizeof(Student), 1, tempfile);
    }

    fclose(file);
    fclose(tempfile);

    if (found) {
        remove(STUDENT_FILE);
        rename("temp.txt", STUDENT_FILE);
        printf(GREEN"Student record updated successfully.\n"RESET_COLOR);
    } else {
        remove("temp.txt");
        printf(RED"No student record found to modify.\n"RESET_COLOR);
    }
}


void displayMenu(){
    printf(YELLOW"\n---- University Billing System ----\n"RESET_COLOR);
    printf("1.Student\n");
    printf("2.Teacher\n");
    printf("3.Exit\n");
    
}

//semester
void displaySemester(){
    printf("\n1.Mid\n");
    printf("2.Final\n");
    printf("3.Exit\n");
}
//display all menu
void displayAllMenu(){
    printf("\n1.Admission Form/Financial fee\n");
    printf("2.Admission/Re-admission/Transfer fee\n");
    printf("3.Tuition fee for the course (s)/Previous Dues\n");
    printf("4.Semester fee\n");
    printf("5.Lab fee\n");
    printf("6.Library fee\n");
    printf("7.Incomplete/Improvenent Exam fee\n");
    printf("8.ID Re-issue/Duplicate admit card fee\n");
    printf("9.Certificate fee: Orginal / Provisional /Duplicate\n");
    printf("10.Late fee\n");
    printf("11.Others....\n");
    printf("12.Exit\n");
}
//student & teacher
void displayAllMember(){
    printf("\n1.Add Record\n");
    printf("2.Delete Record\n");
    printf("3.Modify Record\n");
    printf("4.Exit\n");
}

void displayreg(){
    printf("\n1.Regestration\n");
    printf("2.displayAllStudents\n");
    printf("3.Search Record\n");
    printf("4.University All Fee\n");
    printf("5.Exit\n");
}

void displayregteacher(){
    printf("\n1.Regestration\n");
    printf("2.SearchTeacher\n");
    printf("3.List All Teachers\n");
    printf("4.Exit\n");
}


