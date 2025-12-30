#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "user_public.h" 
#include "admin_utils.h" 

char *clubs[] = {
    "SGIPC", "DREAM", "HACK", "DHRUPODI", "KCC", "SPECTRUM",
    "KBEC", "ABOHO", "KRADIO", "KDC", "TRY", "KMC",
    "KPS", "KFS", "KSC", "KRC"
};

int num_of_clubs = sizeof(clubs) / sizeof(clubs[0]);

void usermode()
{
    int choice;
    do {
        system("cls || clear");
        printf("   >> Welcome to KUET User Page <<\n");
        printf("Explore the clubs and choose one to view details.\n\n");
        printf("------------ Club Menu ------------\n");
        for(int i = 0; i < num_of_clubs; i++){
            printf("%d. %s\n", i + 1, clubs[i]);
        }
        printf("0. Return to Home Menu\n");
        printf("---------------------------------------------\n");
        printf("Enter your choice (0-%d): ", num_of_clubs);

        if (scanf("%d", &choice) != 1) {
            choice = -1; 
        }
        clearInputBuffer();

        if (choice > 0 && choice <= num_of_clubs) {

            showClubMenu(clubs[choice - 1]); 
        } else if (choice == 0) {
            printf("Returning to Home Menu...\n");
        } else {
            printf("Invalid choice. Please try again.\n");
            printf("Press Enter to continue...");
            getchar();
        }

    } while (choice != 0);
}