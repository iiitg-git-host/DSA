#include <stdio.h>
#include <stdlib.h>

struct student
{
    int rollNumber;
    int defenceAgainstTheDarkArts;
    int charms;
    int potions;
};
struct PDE 
{
    int rollNumber;
    int defenceAgainstTheDarkArts;
    int charms;
};
struct student generateStudentData(int rollNo, int defenceAgainstTheDarkArts, int charms, int potions)
{
    struct student newStudent;
    newStudent.rollNumber = rollNo;
    newStudent.defenceAgainstTheDarkArts = defenceAgainstTheDarkArts;
    newStudent.charms = charms;
    newStudent.potions = potions;
    return newStudent;
}
struct PDE generatePDEData(struct student student)
{
    struct PDE newPDEStudent;
    newPDEStudent.rollNumber = student.rollNumber;
    newPDEStudent.defenceAgainstTheDarkArts = student.defenceAgainstTheDarkArts;
    newPDEStudent.charms = student.charms;
    return newPDEStudent;
}

//              Utilities
int checkPDE(struct student student)
{
    if (student.defenceAgainstTheDarkArts < 40 && student.charms > 70)
    {
        
        return 1;
    }
    return 0;
}
int checkValidRollNo(int roll)
{
    int validRoll[] = {10, 11, 12, 13};
    int flag = 0;
    for (int i = 0; i < 4; i++)
    {
        if (validRoll[i] == roll)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}
int getSize(FILE *records)
{
    if (records == NULL)
    {
        printf("File doesn't exist\n");
        return 0;
    }
    else
    {
        char ch;
        char number[100];
        int c = 0;
        fscanf(records, "%s", number);
        return atoi(number);
    }
}
char *getHouse(int houseCode)
{
    char *house;
    if (houseCode == 10)
    {
        house = "Gryffindor";
    }
    else if (houseCode == 11)
    {
        house = "HufflePuff";
    }
    else if (houseCode == 12)
    {
        house = "Ravenclaw ";
    }
    else if (houseCode == 13)
    {
        house = "Slytherine";
    }
    return house;
}
//              Printing
void printStudent(struct student student)
{
    char *house = getHouse((student.rollNumber) / 10000);
    printf("%d %s %d(001) %d(002) %d(003)\n", student.rollNumber, house, student.defenceAgainstTheDarkArts, student.charms, student.potions);
}
void printPDE(struct PDE student)
{
    char *house = getHouse((student.rollNumber) / 10000);
    printf("PDE  %d %s %d(001) %d(002)\n", student.rollNumber, house, student.defenceAgainstTheDarkArts, student.charms);
}
void printStudentRecord(struct student studentRecord[], int size)
{
    for (int i = 0; i < size; i++)
    {
        //     char *house = getHouse((studentRecord[i].rollNumber) / 10000);
        //     printf("%d %s %d(001) %d(002) %d(003)\n", studentRecord[i].rollNumber, house, studentRecord[i].defenceAgainstTheDarkArts, studentRecord[i].charms, studentRecord[i].potions);
        printStudent(studentRecord[i]);
    }
}
void printPDERecord(struct PDE PDERecord[], int size)
{
    for (int i = 0; i < size; i++)
    {
        char *house = getHouse((PDERecord[i].rollNumber) / 10000);
        printf("PDE  %d %s %d(001) %d(002)\n", PDERecord[i].rollNumber, house, PDERecord[i].defenceAgainstTheDarkArts, PDERecord[i].charms);
    }
}
void print(struct student studentRecord[], int studentCount, struct PDE PDERecord[], int PDECount)
{
    printf("-###############################-\n");
    printf("| 1.printStudentDatabase()\t|\n| 2.printPDEDatabase()\t\t|\n| 3.exitToMainMenu()\t\t|\n");
    printf("-###############################-\n");
    int pch;
    scanf("%d", &pch);
    if (pch == 1)
    {
        printStudentRecord(studentRecord, studentCount);
    }
    else if (pch == 2)
    {
        printPDERecord(PDERecord, PDECount);
    }
    else if (pch == 3)
    {
    }
    else
    {
        printf("Invalid Choice!\n");
    }
}
//              Sorting

//          Swapping
void studentSwap(struct student studentRecord[], int first, int second)
{
    struct student temp = studentRecord[first];
    studentRecord[first] = studentRecord[second];
    studentRecord[second] = temp; 
}
void PDESwap(struct PDE studentRecord[], int first, int second)
{
    struct PDE  temp = studentRecord[first];
    studentRecord[first] = studentRecord[second];
    studentRecord[second] = temp; 
}

//          QuickSort
int partition(struct student studentRecord[], int lowerBound, int upperBound)
{
    int pivot = studentRecord[lowerBound].rollNumber;
    int left = lowerBound + 1;
    int right = upperBound;
    while (left < right)
    {
        while (studentRecord[right].rollNumber > pivot)
        {
            right--;
        }
        while (studentRecord[left].rollNumber <= pivot)
        {
            left++;
        }
        if (left < right)
        {
            studentSwap(studentRecord, left, right);
        }
    }
    studentSwap(studentRecord, lowerBound, right);
    return right;
}
void quickSort(struct student studentRecord[], int lowerBound, int upperBound)
{
    if (lowerBound < upperBound)
    {
        int pivot = partition(studentRecord, lowerBound, upperBound);
        quickSort(studentRecord, lowerBound, pivot - 1);
        quickSort(studentRecord, pivot + 1, upperBound);
    }
}

//          InsertionSort
void studentInsertionSort(struct student studentRecord[], int size)
{
    for (int m = 1; m < size; m++)
    {
        int j = m;
        int i = m - 1;
        while (i >= 0 && studentRecord[i].rollNumber > studentRecord[j].rollNumber)
        {
            studentSwap(studentRecord, i--, j--);
        }
    }
}
void PDEInsertionSort(struct PDE studentRecord[], int size)
{
    for (int m = 1; m < size; m++)
    {
        int j = m;
        int i = m - 1;
        while (i >= 0 && studentRecord[i].rollNumber > studentRecord[j].rollNumber)
        {
            PDESwap(studentRecord, i--, j--);
        }
    }
}

//          BinarySearch
struct student binarySearch(struct student studentRecord[], int left, int right, int keyRollNumber)
{
    if (right < left)
    {   
        struct student empty;
        return empty;
    }

    int mid = left + (right - left) / 2;

    if (studentRecord[mid].rollNumber == keyRollNumber)
    {
        return studentRecord[mid];
    }

    if (studentRecord[mid].rollNumber < keyRollNumber)
    {
        return binarySearch(studentRecord, mid + 1, right, keyRollNumber);
    }

    return binarySearch(studentRecord, left, mid - 1, keyRollNumber);
}

//          Adding New Students
struct student addRecord(struct student studentRecord[], int size, int *flag)
{
    int rollNo, datda, potions, charms;
    printf("\nEnter Roll No.(Enter -1 to exit and go back to main menu) :");
    scanf("%d", &rollNo);
    if (rollNo == -1)
    {
        *flag = 1;
        struct student empty;
        return empty;
    }
    if (checkValidRollNo(rollNo / 10000) == 0)
    {
        printf("Invalid Roll No.\n");
        struct student empty;
        return empty;
    }
    struct student found = binarySearch(studentRecord, 0, size - 1, rollNo);

    if (found.rollNumber!=0)
    {
        printf("Roll no. already present in database!\n");
        struct student empty;
        return empty;
    }
    printf("\nMarks in Defence againt the Dark Arts :");
    scanf("%d", &datda);
    printf("\nMarks in potions :");
    scanf("%d", &potions);
    printf("\nMarks in Charms:");
    scanf("%d", &charms);
    struct student newStudent = generateStudentData(rollNo, datda, charms, potions);
    return newStudent;
}

int main()
{
    FILE *records = fopen("records.txt", "r");
    int studentCount = getSize(records);
    struct student studentRecord[100];
    struct PDE PDERecord[100];
    
    int count = 0;
    int PDECount = 0;

    while (count < studentCount)
    {
        char rollChar[6], datda[3], charmsStr[3], potionsStr[3];
        fscanf(records, "%s %s %s %s", rollChar, datda, charmsStr, potionsStr);
        int rollNo = atoi(rollChar);
        if (checkValidRollNo(rollNo / 10000))
        {
            struct student newStudent = generateStudentData(rollNo, atoi(datda), atoi(charmsStr), atoi(potionsStr));
            if (checkPDE(newStudent))
            {
                struct PDE newPDEStudent = generatePDEData(newStudent);
                PDERecord[PDECount++] = newPDEStudent;
            }
            studentRecord[count++] = newStudent;
        }
        else
        {
            printf("Invalid Roll no. %d\n", rollNo);
            studentCount--;
        }
    }

    quickSort(studentRecord, 0, studentCount - 1);
    PDEInsertionSort(PDERecord, PDECount);
    printStudentRecord(studentRecord, studentCount);

    while (1)
    {
        printf("-###############################################-\n");
        printf("|\t\t 1.Sort()\t\t\t|\n|\t\t 2.add3Students()\t\t|\n|\t\t 3.searchByRollNo()\t\t|\n|\t\t 4.print()\t\t\t|\n|\t\t 5.exit()\t\t\t|\n");
        printf("-###############################################-\n");
        int q;
        scanf("%d", &q);
        if (q == 1)
        {
            quickSort(studentRecord, 0, studentCount - 1);
        }
        else if (q == 2)
        {
            int flag = 0;
            for (int i = 1; i <= 3; i++)
            {
                struct student newStudent = addRecord(studentRecord, studentCount, &flag);
                if (flag)
                {
                    break;
                }
                if (newStudent.rollNumber!=0)
                {   
                    if (checkPDE(newStudent))
                    {   
                        struct PDE newPDEStudent = generatePDEData(newStudent);
                        PDERecord[PDECount++] = newPDEStudent;
                        printf("Potential Death Eater detected... adding to PDERecord\n");
                    }
                    studentRecord[studentCount++] = newStudent;
                }
                else
                {
                    i--;
                }
            }
            studentInsertionSort(studentRecord, studentCount);
            PDEInsertionSort(PDERecord, PDECount);
        }
        else if (q == 3)
        {
            int roll;
            printf("Enter roll Number:\n");
            scanf("%d", &roll);
            struct student queriedStudent = binarySearch(studentRecord, 0, studentCount - 1, roll);
            if (queriedStudent.rollNumber!=0)
            {
                printStudent(queriedStudent);
            }
            else
            {
                printf("No such student in database!\n");
            }
        }
        else if (q == 4)
        {
            print(studentRecord, studentCount, PDERecord, PDECount);
        }
        else if (q == 5)
        {
            exit(0);
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}
