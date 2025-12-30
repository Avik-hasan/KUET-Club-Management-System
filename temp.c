// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define PENDING_FILE "pending.txt"
// #define MEMBERS_FILE "members.txt"
// #define EVENTS_FILE "events.txt"
// #define TEMP_FILE "temp.txt"

// typedef struct {
//     char name[100];
//     char roll[20];
//     char department[50];
//     char phone[20];
//     char email[50];
//     char semester[10];
// } Member;

// typedef struct {
//     char name[100];
//     char about[200];
//     char date[20];
//     char venue[100];
// } Event;

// void clearInputBuffer() {
//     int c;
//     while ((c = getchar()) != '\n' && c != EOF);
// }

// void clearNewline(char *str) {
//     str[strcspn(str, "\n")] = 0;
// }

// void printMember(Member m) {
//     printf("  Name: %s\n", m.name);
//     printf("  Roll: %s\n", m.roll);
//     printf("  Dept: %s\n", m.department);
//     printf("  Phone: %s\n", m.phone);
//     printf("  Email: %s\n", m.email);
//     printf("  Semester: %s\n", m.semester);
//     printf("----------------------------------------\n");
// }

// void printEvent(Event e) {
//     printf("  Event: %s\n", e.name);
//     printf("  About: %s\n", e.about);
//     printf("  Date: %s\n", e.date);
//     printf("  Venue: %s\n", e.venue);
//     printf("----------------------------------------\n");
// }

// void showMenu();
// void addMember();
// void viewAllMembers();
// void removeMember();
// void createEvent();
// void viewAllEvents();
// void cancelEvent();
// void viewPendingApplicants();

// int main() {
//     void (*menu_functions[])() = {
//         addMember,
//         viewAllMembers,
//         removeMember,
//         createEvent,
//         viewAllEvents,
//         cancelEvent
//     };

//     int choice;

//     do {
//         system("cls || clear");
//         showMenu();
//         printf("Enter your choice (0-6): ");
        
//         if (scanf("%d", &choice) != 1) {
//             choice = -1;
//         }
//         clearInputBuffer();

//         if (choice >= 1 && choice <= 6) {
//             menu_functions[choice - 1]();
//         } else if (choice == 0) {
//             printf("Thank you... Goodbye!\n");
//         } else {
//             printf("Invalid choice. Please try again.\n");
//         }
//         if (choice != 0) {
//             printf("\nPress Enter to return to the menu...");
//             getchar();
//         }
//     } while (choice != 0);
//     return 0;
// }

// void showMenu() {
//     printf("========================================\n");
//     printf("      Club Admin Management System\n");
//     printf("========================================\n");
//     printf("1. Add Member (from pending list)\n");
//     printf("2. View All Members\n");
//     printf("3. Remove Member\n");
//     printf("4. Create Event\n");
//     printf("5. View All Events\n");
//     printf("6. Cancel/Finish Event\n");
//     printf("0. Exit\n");
//     printf("----------------------------------------\n");
// }

// void addMember() {
//     char rollToApprove[20];
//     Member m;
//     char line[512];
//     int found = 0;

//     viewPendingApplicants();
//     printf("\n");
//     printf("Enter the Roll Number of the applicant to approve: ");
//     fgets(rollToApprove, sizeof(rollToApprove), stdin);
//     clearNewline(rollToApprove);

//     FILE *pendingFile = fopen(PENDING_FILE, "r");
//     FILE *memberFile = fopen(MEMBERS_FILE, "a");
//     FILE *tempFile = fopen(TEMP_FILE, "w");

//     if (!pendingFile || !memberFile || !tempFile) {
//         printf("Error: Could not open files for processing.\n");
//         if(pendingFile) fclose(pendingFile);
//         if(memberFile) fclose(memberFile);
//         if(tempFile) fclose(tempFile);
//         return;
//     }

//     while (fgets(line, sizeof(line), pendingFile)) {
//         sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
//                 m.name, m.roll, m.department, m.phone, m.email, m.semester);
//         if (strcmp(m.roll, rollToApprove) == 0) {
//             fprintf(memberFile, "%s|%s|%s|%s|%s|%s\n",
//                     m.name, m.roll, m.department, m.phone, m.email, m.semester);
//             found = 1;
//             printf("Success: Member '%s' (%s) has been added.\n", m.name, m.roll);
//         } else {
//             fprintf(tempFile, "%s", line);
//         }
//     }

//     fclose(pendingFile);
//     fclose(memberFile);
//     fclose(tempFile);

//     remove(PENDING_FILE);
//     rename(TEMP_FILE, PENDING_FILE);

//     if (!found) {
//         printf("Error: No applicant found with Roll Number '%s'.\n", rollToApprove);
//     }
// }

// void viewAllMembers() {
//     FILE *file = fopen(MEMBERS_FILE, "r");
//     if (file==NULL) {
//         printf("No members found or file cannot be opened.\n");
//         return;
//     }
//     printf("\n--- All Club Members ---\n");
//     char line[512];
//     int count = 0;
//     while (fgets(line, sizeof(line), file)) {
//         Member m;
//         char *token;
//         token = strtok(line, "|");
//         if (token) strcpy(m.name, token);
//         token = strtok(NULL, "|");
//         if (token) strcpy(m.roll, token);
//         token = strtok(NULL, "|");
//         if (token) strcpy(m.department, token);
//         token = strtok(NULL, "|");
//         if (token) strcpy(m.phone, token);
//         token = strtok(NULL, "|");
//         if (token) strcpy(m.email, token);
//         token = strtok(NULL, "|\n");
//         if (token) strcpy(m.semester, token);
//         printMember(m);
//         count++;
//     }
//     fclose(file);
//     if (count == 0) {
//         printf("The club currently has no members.\n");
//     }
//     printf("--- End of List ---\n");
// }

// void removeMember() {
//     char rollToRemove[20];
//     char line[512];
//     int found = 0;

//     viewAllMembers();
//     printf("\nEnter the Roll Number of the member to remove: ");
//     fgets(rollToRemove, sizeof(rollToRemove), stdin);
//     clearNewline(rollToRemove);

//     FILE *memberFile = fopen(MEMBERS_FILE, "r");
//     FILE *tempFile = fopen(TEMP_FILE, "w");

//     if (memberFile==NULL || tempFile==NULL) {
//         printf("Error: Could not open files for processing.\n");
//         if(memberFile) fclose(memberFile);
//         if(tempFile) fclose(tempFile);
//         return;
//     }

//     while (fgets(line, sizeof(line), memberFile)) {
//         char lineCopy[512];
//         strcpy(lineCopy, line);

//         char *name = strtok(lineCopy, "|");
//         char *roll = strtok(NULL, "|");

//         if (roll && strcmp(roll, rollToRemove) == 0) {
//             found = 1;
//             printf("Success: Member '%s' (%s) has been removed.\n", (name ? name : "Unknown"), roll);
//         } else {
//             fprintf(tempFile, "%s", line);
//         }
//     }

//     fclose(memberFile);
//     fclose(tempFile);

//     remove(MEMBERS_FILE);
//     rename(TEMP_FILE, MEMBERS_FILE);

//     if (!found) {
//         printf("Error: No member found with Roll Number '%s'.\n", rollToRemove);
//     }
// }

// void createEvent() {
//     Event newEvent;

//     printf("--- Create New Event ---\n");
//     printf("Enter Event Name: ");
//     fgets(newEvent.name, sizeof(newEvent.name), stdin);
//     clearNewline(newEvent.name);

//     printf("Enter 'About' (description): ");
//     fgets(newEvent.about, sizeof(newEvent.about), stdin);
//     clearNewline(newEvent.about);

//     printf("Enter Event Date (e.g., 25-Dec-2025): ");
//     fgets(newEvent.date, sizeof(newEvent.date), stdin);
//     clearNewline(newEvent.date);

//     printf("Enter Event Venue: ");
//     fgets(newEvent.venue, sizeof(newEvent.venue), stdin);
//     clearNewline(newEvent.venue);

//     FILE *file = fopen(EVENTS_FILE, "a");
//     if (file==NULL) {
//         printf("Error: Could not open events file.\n");
//         return;
//     }

//     fprintf(file, "%s|%s|%s|%s\n",
//             newEvent.name, newEvent.about, newEvent.date, newEvent.venue);

//     fclose(file);
//     printf("Success: Event '%s' has been created!\n", newEvent.name);
// }

// void viewAllEvents() {
//     FILE *file = fopen(EVENTS_FILE, "r");
//     if (file==NULL) {
//         printf("No events found or file cannot be opened.\n");
//         return;
//     }
//     printf("\n--- All Upcoming Events ---\n");
//     char line[512];
//     int count = 0;
//     Event e;
//     while (fgets(line, sizeof(line), file)) {
//         if (sscanf(line, "%[^|]|%[^|]|%[^|]|%[^\n]",
//                     e.name, e.about, e.date, e.venue) == 4) {
//             printEvent(e);
//             count++;
//         }
//     }

//     fclose(file);
//     if (count == 0) {
//         printf("There are no events scheduled.\n");
//     }
//     printf("--- End of List ---\n");
// }

// void cancelEvent() {
//     char nameToRemove[100];
//     char line[512];
//     int found = 0;
    
//     viewAllEvents();
//     printf("\nEnter the exact Event Name to cancel/finish: ");
//     fgets(nameToRemove, sizeof(nameToRemove), stdin);
//     clearNewline(nameToRemove);

//     FILE *eventFile = fopen(EVENTS_FILE, "r");
//     FILE *tempFile = fopen(TEMP_FILE, "w");

//     if (eventFile==NULL || tempFile==NULL) {
//         printf("Error: Could not open files for processing.\n");
//         if(eventFile) fclose(eventFile);
//         if(tempFile) fclose(tempFile);
//         return;
//     }
//     while (fgets(line, sizeof(line), eventFile)) {
//         char lineCopy[512];
//         strcpy(lineCopy, line);
//         char *eventName = strtok(lineCopy, "|");
//         if (eventName && strcmp(eventName, nameToRemove) == 0) {
//             found = 1;
//         } else {
//             fprintf(tempFile, "%s", line);
//         }
//     }
//     fclose(eventFile);
//     fclose(tempFile);
//     remove(EVENTS_FILE);
//     rename(TEMP_FILE, EVENTS_FILE);
//     if (found) {
//         printf("Success: Event '%s' has been removed.\n", nameToRemove);
//     } else {
//         printf("Error: No event found with the name '%s'.\n", nameToRemove);
//     }
// }

// void viewPendingApplicants() {
//     FILE *file = fopen(PENDING_FILE, "r");
//     if (!file) {
//         printf("There are no pending applications.\n");
//         return;
//     }
//     printf("\n--- Pending Applicants ---\n");
//     char line[512];
//     int count = 0;
//     Member m;
//     while (fgets(line, sizeof(line), file)) {
//         if (sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
//                     m.name, m.roll, m.department, m.phone, m.email, m.semester) == 6) {
//             printMember(m);
//             count++;
//         }
//     }
//     fclose(file);
//     if (count == 0) {
//         printf("There are no pending applications.\n");
//     }
//     printf("--- End of List ---\n");
// }#include <stdio.h>
// #include <stdlib.h>
// #include "main.h"

// int main() {
//     int option;
//     enum mode { ADMIN = 1, USER, EXIT };
//     do {
//         system("cls || clear");
//         printf("=============================================\n");
//         printf("       >> KUET Club Management Portal <<\n");
//         printf("=============================================\n");
//         printf("Access your club activities, events, and members\n");
//         printf("through an easy-to-use management system.\n\n");
//         printf("Empowering KUET clubs through smart management and collaboration.\n\n");
//         printf("1. Admin Login\n");
//         printf("2. User Mode\n");
//         printf("3. Exit\n");
//         printf("---------------------------------------------\n");
//         printf("Select Mode: ");
        
//         if (scanf("%d", &option) != 1) {
//             option = -1; 
//         }
//         getchar(); 

//         switch (option)
//         {
//             case ADMIN:
//                 adminmode();
//                 break; 
            
//             case USER:
//                 usermode();
//                 break; 
            
//             case EXIT:
//                 printf("Thanks for using the portal. Goodbye!\n");
//                 break;
            
//             default:
//                 printf("Invalid option. Please try again.\n");
//                 printf("Press Enter to continue...");
//                 getchar();
//                 break;
//         }

//     } while (option != 3); 

//     return 0;
// }