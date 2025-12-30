// #include <stdlib.h>
// #include <stdio.h>
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // <-- ADD THIS for strcmp()
#include "main.h"

// The signature is changed to accept argc and argv
int main(int argc, char *argv[]) {
    
    // --- New Argument Handling Logic ---
    if (argc > 1) {
        // Check what the first argument (argv[1]) is
        
        if (strcmp(argv[1], "--admin") == 0) {
            // If it's "--admin", run admin mode and exit
            printf("Launching directly into Admin Mode...\n");
            adminmode();
            return 0; // Skip the menu
            
        } else if (strcmp(argv[1], "--user") == 0) {
            // If it's "--user", run user mode and exit
            printf("Launching directly into User Mode...\n");
            usermode();
            return 0; // Skip the menu
            
        } else {
            // If the argument is unrecognized, show help
            printf("Unknown argument: %s\n", argv[1]);
            printf("Usage: %s [--admin | --user]\n", argv[0]);
            return 1; // Exit with an error
        }
    }
    // --- End of New Logic ---

    // If no arguments were given (argc == 1),
    // run the normal menu-driven program.
    
    int option;
    enum mode { ADMIN = 1, USER, EXIT };
    do {
        system("cls || clear");
        printf("=============================================\n");
        printf("       >> KUET Club Management Portal <<\n");
        printf("=============================================\n");
        // (Rest of your menu printf statements...)
        printf("1. Admin Login\n");
        printf("2. User Mode\n");
        printf("3. Exit\n");
        printf("---------------------------------------------\n");
        printf("Select Mode: ");
        
        if (scanf("%d", &option) != 1) {
            option = -1; 
        }
        getchar(); 

        switch (option)
        {
            case ADMIN:
                adminmode();
                break; 
            
            case USER:
                usermode();
                break; 
            
            case EXIT:
                printf("Thanks for using the portal. Goodbye!\n");
                break;
            
            default:
                printf("Invalid option. Please try again.\n");
                printf("Press Enter to continue...");
                getchar();
                break;
        }

    } while (option != 3); 

    return 0;
}