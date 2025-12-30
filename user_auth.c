#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user_auth.h"
#include "user_member.h" // For calling showMemberDashboard() on successful login
#include "user_types.h"  // For Member struct
#include "admin_utils.h" // For clearInputBuffer

void registerForClub(const char *clubFilePrefix) {
    Member newApplicant; // Member struct from common_structs.h
    char pendingFilePath[100];
    snprintf(pendingFilePath, sizeof(pendingFilePath), "%s_pending.txt", clubFilePrefix);

    printf("--- %s Registration Form ---\n", clubFilePrefix);
    printf("Please enter your details:\n");
    
    printf("Name: ");
    fgets(newApplicant.name, sizeof(newApplicant.name), stdin);
    clearNewline(newApplicant.name);

    printf("Roll: ");
    fgets(newApplicant.roll, sizeof(newApplicant.roll), stdin);
    clearNewline(newApplicant.roll);
    
    printf("Department (e.g., CSE): ");
    fgets(newApplicant.department, sizeof(newApplicant.department), stdin);
    clearNewline(newApplicant.department);
    
    printf("Phone: ");
    fgets(newApplicant.phone, sizeof(newApplicant.phone), stdin);
    clearNewline(newApplicant.phone);
    
    printf("Email: ");
    fgets(newApplicant.email, sizeof(newApplicant.email), stdin);
    clearNewline(newApplicant.email);
    
    printf("Semester (e.g., 2nd): ");
    fgets(newApplicant.semester, sizeof(newApplicant.semester), stdin);
    clearNewline(newApplicant.semester);
    
    printf("Create a Password: ");
    fgets(newApplicant.password, sizeof(newApplicant.password), stdin);
    clearNewline(newApplicant.password);

    FILE *file = fopen(pendingFilePath, "a");
    if (file == NULL) {
        printf("Error: Could not open registration file.\n");
        return;
    }

    fprintf(file, "%s|%s|%s|%s|%s|%s|%s\n",
            newApplicant.name, newApplicant.roll, newApplicant.department,
            newApplicant.phone, newApplicant.email, newApplicant.semester,
            newApplicant.password);
    
    fclose(file);
    printf("\nSuccess! Your application has been submitted to the admin for review.\n");
}

void memberLogin(const char *clubFilePrefix) {
    char roll[20];
    char password[50];
    char memberFilePath[100];
    snprintf(memberFilePath, sizeof(memberFilePath), "%s_members.txt", clubFilePrefix);

    printf("--- %s Member Login ---\n", clubFilePrefix);
    printf("Enter Roll: ");
    fgets(roll, sizeof(roll), stdin);
    clearNewline(roll);

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    clearNewline(password);

    FILE *file = fopen(memberFilePath, "r");
    if (!file) {
        printf("Error: Could not access member file. No members in this club yet?\n");
        return;
    }

    // SEARCHING ALGORITHM (Linear Search)
    char line[512];
    int loggedIn = 0;
    Member m;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
                m.name, m.roll, m.department, m.phone, m.email, m.semester, m.password) == 7) {
            
            if (strcmp(m.roll, roll) == 0 && strcmp(m.password, password) == 0) {
                loggedIn = 1;
                break; // Found the member, break the loop
            }
        }
    }
    fclose(file);

    if (loggedIn) {
        printf("\nWelcome, %s! Login successful.\n", m.name);
        printf("Press Enter to access the Member Dashboard...");
        getchar();
        showMemberDashboard(clubFilePrefix, &m); // Call the dashboard
    } else {
        printf("\nError: Invalid Roll Number or Password.\n");
    }
}