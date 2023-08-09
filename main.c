#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LIMIT 40

typedef struct Student {
    int successRank;
    int orderOfPreference;
    float highSchoolGrade;
    char *highSchoolType;
} Student;

typedef struct StudentArray {
    Student **studentList;
    size_t size;
} StudentArray;

typedef struct HighSchoolTypesArray {
    char **highSchoolTypes;
    size_t size;
} HighSchoolTypesArray;

void clearMemory(StudentArray *studentArray, HighSchoolTypesArray *typesArray);

void addHighSchoolType(HighSchoolTypesArray *typesArray, char *type);

float calculateStudentRatio(StudentArray studentArray, char *type);

float calculateAvgGrade(StudentArray studentArray, char *type);

char *spaceAlignment();

char *stringAlignment(char *str);

void printGraduateInfo(StudentArray studentArray, HighSchoolTypesArray typesArray);

void printPercentiles(StudentArray studentArray);

int main() {
    StudentArray *studentArray = (StudentArray *) malloc(sizeof(StudentArray));
    if (studentArray == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }
    studentArray->size = 0;

    HighSchoolTypesArray *highSchoolTypesArray = (HighSchoolTypesArray *) malloc(sizeof(HighSchoolTypesArray));
    if (highSchoolTypesArray == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }
    highSchoolTypesArray->size = 0;

    studentArray->studentList = (Student **) malloc(sizeof(Student *));
    if (studentArray->studentList == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(studentArray);
        return 1;
    }

    highSchoolTypesArray->highSchoolTypes = (char **) malloc(sizeof(char *));
    if (highSchoolTypesArray->highSchoolTypes == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(highSchoolTypesArray);
        free(studentArray);
        return 1;
    }

    while (1) {
        int successRank;
        do {
            printf("Enter student %zu's success rank number: ", studentArray->size + 1);
            scanf("%d", &successRank);

            if (successRank < 0)
                printf("Invalid success rank number!\n");
        } while (successRank < 0);

        if (successRank == 0)
            break;

        Student *newStudent = (Student *) malloc(sizeof(Student));

        newStudent->highSchoolType = (char *) malloc(sizeof(char) * (STR_LIMIT + 1));
        if (newStudent->highSchoolType == NULL) {
            fprintf(stderr, "Memory allocation failed!\n");
            free(studentArray->studentList);
            free(studentArray);
            return 1;
        }

        studentArray->studentList = (Student **) realloc(studentArray->studentList,
                                                         sizeof(Student *) * (studentArray->size + 2));
        newStudent->successRank = successRank;
        do {
            printf("Enter student %zu's order of preference number: ", studentArray->size + 1);
            scanf("%d", &newStudent->orderOfPreference);

            if (newStudent->orderOfPreference < 1 || newStudent->orderOfPreference > 24)
                printf("Invalid order of preference number!\n");
        } while (newStudent->orderOfPreference < 1 || newStudent->orderOfPreference > 24);

        do {
            printf("Enter student %zu's high school graduation grade number: ", studentArray->size + 1);
            scanf("%f", &newStudent->highSchoolGrade);

            if (newStudent->highSchoolGrade < 0 || newStudent->highSchoolGrade > 100)
                printf("Invalid high school graduation grade number!\n");
        } while (newStudent->highSchoolGrade < 0 || newStudent->highSchoolGrade > 100);

        fflush(stdin);

        char *type = (char *) malloc(sizeof(char) * (STR_LIMIT + 1));
        do {
            printf("Enter student %zu's high school type: ", studentArray->size + 1);
            gets(type);
            if (strlen(type) > STR_LIMIT)
                printf("Maximum string length exceeded! Enter shorter string!\n");
        } while (strlen(type) > STR_LIMIT);

        strcpy(newStudent->highSchoolType, type);
        addHighSchoolType(highSchoolTypesArray, type);

        studentArray->studentList[studentArray->size++] = newStudent;
    }

    printGraduateInfo(*studentArray, *highSchoolTypesArray);
    printPercentiles(*studentArray);

    clearMemory(studentArray, highSchoolTypesArray);
    return 0;
}

void clearMemory(StudentArray *studentArray, HighSchoolTypesArray *typesArray) {
    for (size_t i = 0; i < studentArray->size; i++)
        free(studentArray->studentList[i]->highSchoolType);
    free(studentArray->studentList);
    free(studentArray);

    for (size_t i = 0; i < typesArray->size; i++)
        free(typesArray->highSchoolTypes[i]);
    free(typesArray);
}

void addHighSchoolType(HighSchoolTypesArray *typesArray, char *type) {
    for (size_t i = 0; i < typesArray->size; i++) {
        if (strcmp(typesArray->highSchoolTypes[i], type) == 0)
            return;
    }

    typesArray->highSchoolTypes = (char **) realloc(typesArray->highSchoolTypes,
                                                    sizeof(char *) * (typesArray->size + 2));
    typesArray->highSchoolTypes[typesArray->size] = (char *) malloc(sizeof(char) * STR_LIMIT);
    strcpy(typesArray->highSchoolTypes[typesArray->size++], type);
}

float calculateStudentRatio(StudentArray studentArray, char *type) {
    size_t count = 0;
    for (size_t i = 0; i < studentArray.size; i++) {
        if (strcmp(studentArray.studentList[i]->highSchoolType, type) == 0)
            count++;
    }

    return (float) count * 100 / studentArray.size;
}

float calculateAvgGrade(StudentArray studentArray, char *type) {
    float totalGrade = 0.0f;
    size_t count = 0;
    for (size_t i = 0; i < studentArray.size; i++) {
        if (strcmp(studentArray.studentList[i]->highSchoolType, type) == 0) {
            totalGrade += studentArray.studentList[i]->highSchoolGrade;
            count++;
        }
    }

    return (float) totalGrade / count;
}

char *spaceAlignment() {
    size_t len = STR_LIMIT - strlen("Graduated High School Type");
    char *spaces = (char *) malloc(sizeof(char) * (len - 3));

    for (size_t i = 0; i < len - 4; i++)
        spaces[i] = ' ';
    spaces[len - 4] = '\0';

    return spaces;
}

char *stringAlignment(char *str) {
    if (strlen(str) + strlen(" High School") >= STR_LIMIT + 3) {
        fprintf(stderr, "Error: String length exceeds limit\n");
        return NULL;
    }

    strcat(str, " High School");
    for (size_t i = strlen(str); i < STR_LIMIT - 1; i++)
        str[i] = ' ';
    str[STR_LIMIT - 1] = '\0';

    return str;
}

void printGraduateInfo(StudentArray studentArray, HighSchoolTypesArray typesArray) {
    printf("\nGraduated High School Type%sStudent Ratio          Average High School Grade\n", spaceAlignment());
    printf("--------------------------%s-------------          -------------------------\n", spaceAlignment());

    for (size_t i = 0; i < typesArray.size; i++) {
        printf("%s%.2f %%                      %.2f\n",
               stringAlignment(typesArray.highSchoolTypes[i]),
               calculateStudentRatio(studentArray, typesArray.highSchoolTypes[i]),
               calculateAvgGrade(studentArray, typesArray.highSchoolTypes[i]));
    }
}

void printPercentiles(StudentArray studentArray) {
    printf("\nPreference Order   P1   P2   P3   P4   P5   P6   P7   P8\n");
    printf("----------------   --   --   --   --   --   --   --   --\n");

    for (size_t i = 1; i <= 24; i++) {
        size_t first = 0, second = 0, third = 0, fourth = 0, fifth = 0, sixth = 0, seventh = 0, eighth = 0;
        for (size_t j = 0; j < studentArray.size; j++) {
            if (studentArray.studentList[j]->orderOfPreference == i) {
                int percentile = (studentArray.studentList[j]->successRank - 1) / 5000 + 1;

                if (percentile == 1) first++;
                else if (percentile == 2) second++;
                else if (percentile == 3) third++;
                else if (percentile == 4) fourth++;
                else if (percentile == 5) fifth++;
                else if (percentile == 6) sixth++;
                else if (percentile == 7) seventh++;
                else eighth++;
            }
        }
        if (i < 10) printf(" ");
        printf("       %zu           %zu    %zu    %zu    %zu    %zu    %zu    %zu    %zu\n",
               i, first, second, third, fourth, fifth, sixth, seventh, eighth);
    }
    printf("\n");
}
