#include <stdio.h>
#include <string.h> 
#include "admin_utils.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearNewline(char *str) {
    str[strcspn(str, "\n")] = 0; 
}

void printMember(Member m) {
    printf("  Name: %s\n", m.name);
    printf("  Roll: %s\n", m.roll);
    printf("  Dept: %s\n", m.department);
    printf("  Phone: %s\n", m.phone);
    printf("  Email: %s\n", m.email);
    printf("  Semester: %s\n", m.semester);
    printf("----------------------------------------\n");
}

void printEvent(Event e) {
    printf("  Event: %s\n", e.name);
    printf("  About: %s\n", e.about);
    printf("  Date: %s\n", e.date);
    printf("  Venue: %s\n", e.venue);
    printf("----------------------------------------\n");
}

void showMenu() {
    printf("1. Add Member (from pending list)\n");
    printf("2. View All Members\n");
    printf("3. Remove Member\n");
    printf("4. Create Event\n");
    printf("5. View All Events\n");
    printf("6. Cancel/Finish Event\n");
    printf("0. Exit\n");
    printf("----------------------------------------\n");
}