#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 10

typedef struct {
  char name[50];
  int age;
  char class[3];
  float grades[3];
} Student;

Student add_student(char name[50], int age, char class[3], float grades[3]);
int confirmation(char operation[6]);
void foreach_float(float receiver[3], float source[3]);
void foreach_grade(float array[3]);
void foreach_student(Student students[10], int length);
int get_student(char operation[6]);
Student get_student_info_input();
void remove_student(Student student);
Student update_student(Student student, Student updatedInfo);
int view_student(Student student, int id);

int main() {
  Student students[MAX_LENGTH];
  int keep = 1;
  int option = 0;
  int id = 0;
  int length = 0;
  int current_id = 0;

  while (keep) {
    printf("---   New Age High School   ---\n");
    printf("---   Students system       ---\n");
    printf("---   1 - Add Student       ---\n");
    printf("---   2 - View Students     ---\n");
    printf("---   3 - Update Student    ---\n");
    printf("---   4 - Delete Student    ---\n");
    printf("---   0 - Exit              ---\n");

    printf("Enter the operation: ");
    scanf_s("%d", &option);
    getchar();

    switch (option) {
    case 1:
      // Add student option
      printf("Enter the student's information\n");
      if (length >= MAX_LENGTH) {
        printf("Number of students cannot exceed maximum. Try again.\n");
        system("pause");
        system("cls");
        break;
      }

      Student info = get_student_info_input();
      Student new_student =
          add_student(info.name, info.age, info.class, info.grades);
      students[current_id] = new_student;
      system("cls");

      view_student(new_student, current_id);

      current_id++;
      length++;
      system("pause");
      system("cls");
      break;
    case 2:
      // View all students' option
      if (length == 0) {
        printf("There are no students to display.\n");
        system("pause");
        system("cls");
        break;
      }

      printf("All student's information\n");
      foreach_student(students, length);
      system("pause");
      system("cls");
      break;
    case 3:
      // Update a student's information option
      system("cls");
      if (length == 0) {
        printf("There are no students to display.\n");
        system("pause");
        system("cls");
        break;
      }

      id = get_student("update");

      if (id >= current_id) {
        printf("Chosen ID does not exist. Try again.\n");
        system("pause");
        system("cls");
        break;
      }

      view_student(students[id], id);

      if (confirmation("update") == 0)
        break;

      printf("Enter new information (press Enter or -1 to keep current "
             "values):\n");
      Student updatedInfo = get_student_info_input();
      Student updatedStudent = update_student(updatedStudent, updatedInfo);
      students[id] = updatedStudent;

      printf("Student successfully updated!\n");
      printf("Check out the information:\n");
      view_student(students[id], id);

      system("pause");
      system("cls");

      break;
    case 4:
      // Delete a student's information option
      system("cls");
      if (length == 0) {
        printf("There are no students to display.\n");
        system("pause");
        system("cls");
        break;
      }

      id = get_student("delete");
      if (id >= current_id) {
        printf("Chosen ID does not exist. Try again.\n");
        system("pause");
        system("cls");
        break;
      }

      view_student(students[id], id);

      if (confirmation("remove") == 0)
        break;

      remove_student(students[id]);
      --length;
      break;
    case 0:
      keep = 0;
      printf("Thank you for using our system!!\n");
      break;
    default:
      printf("Invalid option, try again.\n");
      system("pause");
      system("cls");
    }
  }

  return 0;
}

/*
Function to add a student.
Input:
  name Student's name.
  age Student's age.
  class Student's class.
  grades Student's grades.
Output:
  new New student.
*/
Student add_student(char name[50], int age, char class[3], float grades[3]) {
  Student new;
  new.age = age;
  strcpy_s(new.name, 50, name);
  strcpy_s(new.class, 3, class);
  foreach_float(new.grades, grades);
  return new;
}

/*
Function to confirm update/remove operation.
Input:
  operation Operation to be confirmed.
Output:
  1 if confirmed, 0 otherwise.
*/
int confirmation(char operation[6]) {
  int confirmation;
  printf("Is that the student you want to %s? [1 -- Yes | 0 -- No]\n",
         operation);
  scanf_s("%d", &confirmation);
  getchar();

  if (!confirmation) {
    printf("Try again later.\n");
    system("pause");
    system("cls");
    return 0;
  }

  return 1;
}

/*
Function to exchange values between two arrays.
Input:
  receiver Array to receive values.
  source Array to provide values.
Output:
  There is no return, but the function exchanges values between two arrays.
*/
void foreach_float(float receiver[3], float source[3]) {
  for (int i = 0; i < 3; i++) {
    receiver[i] = source[i];
  }
}

/*
Function to show each grade in the array.
Input:
  grades Array of grades.
Output:
  There is no return, but the function prints each grade in the array.
*/
void foreach_grade(float grades[3]) {
  for (int i = 0; i < 3; i++) {
    printf("Grade N %d: %.2f\n", i + 1, grades[i]);
  }
}

/*
Function to show all students' information.
Input:
  students Array of students.
  length Length of the array.
Output:
  There is no return, but the function prints all students' information.
 */
void foreach_student(Student students[10], int length) {
  for (int i = 0; i < length; i++) {
    if (view_student(students[i], i) == 0) {
      continue;
    }
  }
}

/*
Function to get the desired student's ID.
Input:
  operation Name of the operation that will appear in the prompt.
Output:
  id The student's ID.
*/
int get_student(char operation[6]) {
  int id;

  printf("Enter the student's ID you want to %s: ", operation);
  scanf_s("%d", &id);
  getchar();

  return id - 1;
}

/*
Function to get the student's information.
Input:
  There is no input, since the input is done inside the function.
Output:
  info The student's information.
*/
Student get_student_info_input() {
  Student info;

  // Student's name
  printf("Enter the student's name: ");
  fgets(info.name, sizeof(info.name), stdin);
  info.name[strcspn(info.name, "\n")] = '\0';

  // Student's age
  printf("Enter the student's age: ");
  scanf_s("%d", &info.age);
  getchar();

  // Student's class
  printf("Enter the student's class: ");
  fgets(info.class, sizeof(info.class), stdin);
  info.class[strcspn(info.class, "\n")] = '\0';

  // Student's grades
  for (int i = 0; i < 3; i++) {
    printf("Enter the student's N %d grade: ", i + 1);
    scanf_s("%f", &info.grades[i]);
  }
  getchar();

  return info;
}

/*
Function to remove a student from the array.
Input:
  student Student to be removed.
Output:
  There is no output, but the function removes a student's information.
*/
void remove_student(Student student) {
  strcpy_s(student.name, sizeof(student.name), "");
  strcpy_s(student.class, sizeof(student.class), "");
  student.age = 0;
  float grades[3] = {0, 0, 0};
  foreach_float(student.grades, grades);

  printf("Student successfully removed.\n");
  system("pause");
  system("cls");
}

/*
Function to update a student's information.
Input:
  student Student to be updated.
  updatedInfo Updated information of the student.
Output:
  student Student with updated information.
*/
Student update_student(Student student, Student updatedInfo) {

  if (strcmp(updatedInfo.name, "") != 0) {
    strcpy_s(student.name, 50, updatedInfo.name);
  }

  if (strcmp(updatedInfo.class, "") != 0) {
    strcpy_s(student.class, 3, updatedInfo.class);
  }

  if (updatedInfo.age != -1) {
    student.age = updatedInfo.age;
  }

  for (int i = 0; i < 3; i++) {
    if (updatedInfo.grades[i] != -1) {
      student.grades[i] = updatedInfo.grades[i];
    }
  }

  return student;
}

/*
Function to display the desired student's information.
Input:
  student Chosen student to display information.
  id The id of the student.
Output:
  There is no output, but the function displays the student's information.
*/
int view_student(Student student, int id) {
  if (strcmp(student.name, "") == 0 || strcmp(student.class, "") == 0) {
    return 0;
  }
  printf("ID: %d\n", id + 1);
  printf("Name: %s\n", student.name);
  printf("Age: %d\n", student.age);
  printf("Class: %s\n", student.class);
  foreach_grade(student.grades);
  return 1;
}
