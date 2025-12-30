#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user_member.h"
#include "user_types.h"
#include "admin_utils.h"

// --- Static Helper Functions (for sorting) ---
// By making these 'static', they are private to this file.

static int compareMembersByName(const void *a, const void *b) {
    Member *memberA = (Member *)a;
    Member *memberB = (Member *)b;
    return strcmp(memberA->name, memberB->name);
}

static int compareAlumniByName(const void *a, const void *b) {
    Alumnus *alumnusA = (Alumnus *)a;
    Alumnus *alumnusB = (Alumnus *)b;
    return strcmp(alumnusA->name, alumnusB->name);
}

// --- Static Functions (Dashboard Features) ---
// These are also 'static' because they are only called by 
// showMemberDashboard() *within this same file*.

static void viewAllClubMembers(const char *clubFilePrefix) {
    char memberFilePath[100];
    snprintf(memberFilePath, sizeof(memberFilePath), "%s_members.txt", clubFilePrefix);
    
    FILE *file = fopen(memberFilePath, "r");
    if (!file) { /* ... error handling ... */ return; }

    // DYNAMIC MEMORY ALLOCATION & SORTING
    int count = 0;
    Member *memberList = NULL;
    char line[512];

    while (fgets(line, sizeof(line), file)) count++;
    rewind(file);

    if (count == 0) { /* ... handle no members ... */ fclose(file); return; }

    memberList = (Member *)malloc(count * sizeof(Member));
    if (memberList == NULL) { /* ... error handling ... */ fclose(file); return; }

    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
                memberList[i].name, memberList[i].roll, memberList[i].department,
                memberList[i].phone, memberList[i].email, memberList[i].semester,
                memberList[i].password) == 7) {
            i++;
        }
    }
    fclose(file);
    
    qsort(memberList, count, sizeof(Member), compareMembersByName);

    printf("\n--- All Members of %s (Sorted by Name) ---\n", clubFilePrefix);
    for (i = 0; i < count; i++) {
        printMember(memberList[i]); 
    }
    printf("--- End of List ---\n");
    free(memberList);
}


static void viewAlumni(const char *clubFilePrefix) {
    char alumniFilePath[100];
    snprintf(alumniFilePath, sizeof(alumniFilePath), "%s_alumni.txt", clubFilePrefix);
    
    FILE *file = fopen(alumniFilePath, "r");
    if (!file) { /* ... error handling ... */ return; }

    // DYNAMIC MEMORY ALLOCATION & SORTING
    int count = 0;
    Alumnus *alumniList = NULL;
    char line[512];
    
    while (fgets(line, sizeof(line), file)) count++;
    rewind(file);
    
    if (count == 0) { /* ... handle no alumni ... */ fclose(file); return; }

    alumniList = (Alumnus *)malloc(count * sizeof(Alumnus));
    if (alumniList == NULL) { /* ... error handling ... */ return; }

    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
                alumniList[i].name, alumniList[i].graduationYear,
                alumniList[i].company, alumniList[i].position,
                alumniList[i].email) == 5) {
            i++;
        }
    }
    fclose(file);

    qsort(alumniList, count, sizeof(Alumnus), compareAlumniByName);

    printf("\n--- %s Alumni Network (Sorted by Name) ---\n", clubFilePrefix);
    for (i = 0; i < count; i++) {
        printf("  Name: %s\n", alumniList[i].name);
        printf("  Graduated: %s\n", alumniList[i].graduationYear);
        printf("  Works at: %s\n", alumniList[i].company);
        printf("  Position: %s\n", alumniList[i].position);
        printf("  Contact: %s\n", alumniList[i].email);
        printf("----------------------------------------\n");
    }
    printf("--- End of List ---\n");
    free(alumniList);
}

static void viewResources(const char *clubFilePrefix) {
    char resourceFilePath[100];
    snprintf(resourceFilePath, sizeof(resourceFilePath), "%s_resources.txt", clubFilePrefix);
    
    FILE *file = fopen(resourceFilePath, "r");
    if (!file) { /* ... error handling ... */ return; }

    printf("\n--- %s Club Resources ---\n", clubFilePrefix);
    char line[512];
    Resource res;
    int typeInt;
    
    while (fgets(line, sizeof(line), file)) {
        char dataStr[200];
        if (sscanf(line, "%[^|]|%d|%[^|]|%[^\n]",
                res.title, &typeInt, dataStr, res.description) == 4) {
            
            res.type = (ResourceType)typeInt; 

            printf("  Title: %s\n", res.title);
            printf("  Desc: %s\n", res.description);
            
            switch (res.type) {
                case LINK:
                    strcpy(res.data.websiteUrl, dataStr);
                    printf("  Type: Web Link\n");
                    printf("  Link: %s\n", res.data.websiteUrl);
                    break;
                case BOOK:
                    strcpy(res.data.bookTitle, dataStr);
                    printf("  Type: Book\n");
                    printf("  Title: %s\n", res.data.bookTitle);
                    break;
                case VIDEO:
                    strcpy(res.data.videoId, dataStr);
                    printf("  Type: Video\n");
                    printf("  URL: https://youtube.com/watch?v=%s\n", res.data.videoId);
                    break;
            }
            printf("----------------------------------------\n");
        }
    }
    fclose(file);
    printf("--- End of List ---\n");
}


// --- Public Dashboard Function ---
// This is the only non-static function, called by memberLogin()

void showMemberDashboard(const char *clubFilePrefix, const Member *loggedInMember) {
    int choice;
    do {
        system("cls || clear");
        printf("=============================================\n");
        printf("      %s Member Dashboard\n", clubFilePrefix);
        printf("      Welcome, %s (%s)\n", loggedInMember->name, loggedInMember->roll);
        printf("=============================================\n");
        printf("1. View All Members (Sorted by Name)\n");
        printf("2. View Alumni Network (Sorted by Name)\n");
        printf("3. Access Club Resources\n");
        printf("0. Logout\n");
        printf("---------------------------------------------\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: viewAllClubMembers(clubFilePrefix); break;
            case 2: viewAlumni(clubFilePrefix); break;
            case 3: viewResources(clubFilePrefix); break;
            case 0: printf("Logging out...\n"); break;
            default: printf("Invalid choice. Try again.\n"); break;
        }
        if (choice != 0) {
            printf("\nPress Enter to return to the Dashboard...");
            getchar();
        }
    } while (choice != 0);
}