#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin_members.h" 
#include "admin_utils.h"   

void addMember(const char *clubName) {
    char rollToApprove[20];
    Member m;
    char line[512];
    int found = 0;

    char pendingFilePath[100];
    char memberFilePath[100];
    char tempFilePath[100];
    snprintf(pendingFilePath, sizeof(pendingFilePath), "%s_pending.txt", clubName);
    snprintf(memberFilePath, sizeof(memberFilePath), "%s_members.txt", clubName);
    snprintf(tempFilePath, sizeof(tempFilePath), "%s_temp.txt", clubName);

    viewPendingApplicants(clubName); 
    printf("\n");
    printf("Enter the Roll Number of the applicant to approve: ");
    fgets(rollToApprove, sizeof(rollToApprove), stdin);
    clearNewline(rollToApprove);

    FILE *pendingFile = fopen(pendingFilePath, "r");
    FILE *memberFile = fopen(memberFilePath, "a");
    FILE *tempFile = fopen(tempFilePath, "w");

    if (!pendingFile) {
        printf("Error: No pending applications for %s.\n", clubName);
        if(memberFile) fclose(memberFile);
        if(tempFile) fclose(tempFile);
        return;
    }
    if (!memberFile || !tempFile) {
        printf("Error: Could not open files for processing.\n");
        fclose(pendingFile);
        if(memberFile) fclose(memberFile);
        if(tempFile) fclose(tempFile);
        return;
    }

    while (fgets(line, sizeof(line), pendingFile)) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
                m.name, m.roll, m.department, m.phone, m.email, m.semester);
        if (strcmp(m.roll, rollToApprove) == 0) {
            fprintf(memberFile, "%s|%s|%s|%s|%s|%s\n",
                    m.name, m.roll, m.department, m.phone, m.email, m.semester);
            found = 1;
            printf("Success: Member '%s' (%s) has been added to %s.\n", m.name, m.roll, clubName);
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(pendingFile);
    fclose(memberFile);
    fclose(tempFile);

    remove(pendingFilePath);
    rename(tempFilePath, pendingFilePath);

    if (!found) {
        printf("Error: No applicant found with Roll Number '%s'.\n", rollToApprove);
    }
}

void viewAllMembers(const char *clubName) {
    char memberFilePath[100];
    snprintf(memberFilePath, sizeof(memberFilePath), "%s_members.txt", clubName);

    FILE *file = fopen(memberFilePath, "r");
    if (file == NULL) {
        printf("No members found for %s or file cannot be opened.\n", clubName);
        return;
    }
    printf("\n--- All Members of %s ---\n", clubName);
    char line[512];
    int count = 0;
    Member m;
    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, "|");
        if (token) strcpy(m.name, token);
        token = strtok(NULL, "|");
        if (token) strcpy(m.roll, token);
        token = strtok(NULL, "|");
        if (token) strcpy(m.department, token);
        token = strtok(NULL, "|");
        if (token) strcpy(m.phone, token);
        token = strtok(NULL, "|");
        if (token) strcpy(m.email, token);
        token = strtok(NULL, "|\n");
        if (token) strcpy(m.semester, token);
        printMember(m);
        count++;
    }
    fclose(file);
    if (count == 0) {
        printf("%s currently has no members.\n", clubName);
    }
    printf("--- End of List ---\n");
}

void removeMember(const char *clubName) {
    char rollToRemove[20];
    char line[512];
    int found = 0;

    char memberFilePath[100];
    char tempFilePath[100];
    snprintf(memberFilePath, sizeof(memberFilePath), "%s_members.txt", clubName);
    snprintf(tempFilePath, sizeof(tempFilePath), "%s_temp.txt", clubName);

    viewAllMembers(clubName); 
    
    printf("\nEnter the Roll Number of the member to remove: ");
    fgets(rollToRemove, sizeof(rollToRemove), stdin);
    clearNewline(rollToRemove);

    FILE *memberFile = fopen(memberFilePath, "r");
    FILE *tempFile = fopen(tempFilePath, "w");

    if (memberFile == NULL || tempFile == NULL) {
        printf("Error: Could not open files for processing.\n");
        if(memberFile) fclose(memberFile);
        if(tempFile) fclose(tempFile);
        return;
    }

    while (fgets(line, sizeof(line), memberFile)) {
        char lineCopy[512];
        strcpy(lineCopy, line);
        char *name = strtok(lineCopy, "|");
        char *roll = strtok(NULL, "|");

        if (roll && strcmp(roll, rollToRemove) == 0) {
            found = 1;
            printf("Success: Member '%s' (%s) has been removed from %s.\n", (name ? name : "Unknown"), roll, clubName);
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(memberFile);
    fclose(tempFile);

    remove(memberFilePath);
    rename(tempFilePath, memberFilePath);

    if (!found) {
        printf("Error: No member found with Roll Number '%s' in %s.\n", rollToRemove, clubName);
    }
}

void viewPendingApplicants(const char *clubName) {
    char pendingFilePath[100];
    snprintf(pendingFilePath, sizeof(pendingFilePath), "%s_pending.txt", clubName);

    FILE *file = fopen(pendingFilePath, "r");
    if (!file) {
        printf("There are no pending applications for %s.\n", clubName);
        return;
    }
    printf("\n--- Pending Applicants for %s ---\n", clubName);
    char line[512];
    int count = 0;
    Member m;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
                    m.name, m.roll, m.department, m.phone, m.email, m.semester) == 6) {
            printMember(m);
            count++;
        }
    }
    fclose(file);
    if (count == 0) {
        printf("There are no pending applications for %s.\n", clubName);
    }
    printf("--- End of List ---\n");
}