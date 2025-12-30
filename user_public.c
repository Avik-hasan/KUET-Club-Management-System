#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include all the function prototypes we need
#include "user_public.h"
#include "user_auth.h"
#include "user_member.h"

// Include all the type definitions
#include "user_types.h"
#include "admin_utils.h" // For clearInputBuffer, printEvent

// Main Club Menu
void showClubMenu(const char *clubFilePrefix) {
    int choice;
    do {
        system("cls || clear");
        printf("=============================================\n");
        printf("         Welcome to %s\n", clubFilePrefix);
        printf("=============================================\n");
        printf("1. Introduction\n");
        printf("2. Achievements\n");
        printf("3. View Upcoming Events\n");
        printf("4. Register for this Club\n");
        printf("5. Member Login\n");
        printf("0. Return to Club List\n");
        printf("---------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: showClubIntroduction(clubFilePrefix); break;
            case 2: showClubAchievements(clubFilePrefix); break;
            case 3: userViewEvents(clubFilePrefix); break;
            case 4: registerForClub(clubFilePrefix); break; // From user_auth.h
            case 5: memberLogin(clubFilePrefix); break;     // From user_auth.h
            case 0: printf("Returning to club list...\n"); break;
            default: printf("Invalid choice. Try again.\n"); break;
        }
        if (choice != 0) {
            printf("\nPress Enter to return to the %s menu...", clubFilePrefix);
            getchar();
        }
    } while (choice != 0);
}

// --- Public Functions ---

void showClubIntroduction(const char *clubFilePrefix) {
    char filename[100];
    snprintf(filename, sizeof(filename), "%s_intro.txt", clubFilePrefix);
    
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Sorry, no introduction is available for %s.\n", clubFilePrefix);
        return;
    }
    printf("\n--- Introduction to %s ---\n", clubFilePrefix);
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }
    printf("\n--- End of Introduction ---\n");
    fclose(f);
}

void showClubAchievements(const char *clubFilePrefix) {
    char filename[100];
    snprintf(filename, sizeof(filename), "%s_achievements.txt", clubFilePrefix);
    
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Sorry, no achievements are listed for %s.\n", clubFilePrefix);
        return;
    }
    printf("\n--- Achievements of %s ---\n", clubFilePrefix);
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        printf("* %s", line);
    }
    printf("--- End of List ---\n");
    fclose(f);
}

void userViewEvents(const char *clubFilePrefix) {
    char eventFilePath[100];
    snprintf(eventFilePath, sizeof(eventFilePath), "%s_events.txt", clubFilePrefix);
    
    FILE *file = fopen(eventFilePath, "r");
    if (file == NULL) {
        printf("No events found for %s.\n", clubFilePrefix);
        return;
    }
    printf("\n--- All Upcoming Events for %s ---\n", clubFilePrefix);
    char line[512];
    int count = 0;
    Event e; // Event struct from common_structs.h
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^|]|%[^|]|%[^|]|%[^\n]",
                    e.name, e.about, e.date, e.venue) == 4) {
            printEvent(e); // Re-using admin helper function
            count++;
        }
    }
    fclose(file);
    if (count == 0) {
        printf("There are no events scheduled for %s.\n", clubFilePrefix);
    }
    printf("--- End of List ---\n");
}