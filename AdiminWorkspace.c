#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "admin_members.h" 
#include "admin_events.h" 
#include "admin_utils.h"  
#include "AdiminWorkspace.h" 

void adminworkspace(const char *clubName) {
    int choice;
    enum admin_options { ADD_MEMBER = 1, VIEW_MEMBERS, REMOVE_MEMBER, CREATE_EVENT, VIEW_EVENTS, CANCEL_EVENT, EXIT };
    do {
        system("cls || clear");
        
        
        printf("========================================\n");
        printf("      Admin Menu for: %s\n", clubName);
        printf("========================================\n");
        showMenu();     
        
        printf("Enter your choice (0-6): ");
        
        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        clearInputBuffer();
        
        switch (choice) {
            case ADD_MEMBER:
                addMember(clubName);
                break;
            case VIEW_MEMBERS:
                viewAllMembers(clubName);
                break;
            case REMOVE_MEMBER:
                removeMember(clubName);
                break;
            case CREATE_EVENT:
                createEvent(clubName);
                break;
            case VIEW_EVENTS:
                viewAllEvents(clubName);
                break;
            case CANCEL_EVENT:
                cancelEvent(clubName);
                break;
            case EXIT:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        if (choice != 0) {
            printf("\nPress Enter to return to the menu...");
            getchar(); 
        }
    } while (choice != 0);
}