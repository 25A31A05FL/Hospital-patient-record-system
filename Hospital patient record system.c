#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    char doctor[50];
    int room_no;
};

void addPatient();
void viewPatients();
void searchPatient();
void deletePatient();

int main() {
    int choice;

    do {
        printf("\n=== Hospital Patient Record System ===\n");
        printf("1. Add Patient Record\n");
        printf("2. View All Patients (Tabular)\n");
        printf("3. Search Patient by ID\n");
        printf("4. Delete Patient Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: printf("Exiting program...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}

/* Add Patient */
void addPatient() {
    struct patient p;
    FILE *fp = fopen("patients.dat", "ab");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &p.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("Enter Gender: ");
    scanf("%9s", p.gender);

    printf("Enter Disease: ");
    scanf(" %[^\n]", p.disease);

    printf("Enter Room No: ");
    scanf("%d", &p.room_no);

    printf("Enter Doctor Name: ");
    scanf(" %[^\n]", p.doctor);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf("Patient record added successfully.\n");
}

/* View Patients in Tabular Form */
void viewPatients() {
    struct patient p;
    FILE *fp = fopen("patients.dat", "rb");

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n========================== Patient List ==========================\n");
    printf("%-5s %-20s %-5s %-8s %-15s %-8s %-15s\n",
           "ID", "Name", "Age", "Gender", "Disease", "Room", "Doctor");
    printf("-----------------------------------------------------------------\n");

    while (fread(&p, sizeof(p), 1, fp)) {
        printf("%-5d %-20s %-5d %-8s %-15s %-8d %-15s\n",
               p.id,
               p.name,
               p.age,
               p.gender,
               p.disease,
               p.room_no,
               p.doctor);
    }

    printf("=================================================================\n");

    fclose(fp);
}

/* Search Patient */
void searchPatient() {
    struct patient p;
    int id, found = 0;
    FILE *fp = fopen("patients.dat", "rb");

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("\nPatient Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nRoom No: %d\nDoctor: %s\n",
                   p.id, p.name, p.age, p.gender, p.disease, p.room_no, p.doctor);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Patient not found.\n");
    }

    fclose(fp);
}

/* Delete Patient */
void deletePatient() {
    struct patient p;
    int id, found = 0;

    FILE *fp = fopen("patients.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            found = 1;
        } else {
            fwrite(&p, sizeof(p), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("patients.dat");
    rename("temp.dat", "patients.dat");

    if (found)
        printf("Patient record deleted successfully.\n");
    else
        printf("Patient ID not found.\n");
}
