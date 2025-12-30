#ifndef COMMON_STRUCTS_H
#define COMMON_STRUCTS_H

// This struct uses BIT-FIELDS as requested
// It will be embedded inside the Member struct
// It's memory-efficient, packing 3 flags into a single 'unsigned int'
typedef struct {
    unsigned int is_active : 1;      // 1 bit = 1 (active) or 0 (inactive)
    unsigned int is_board_member : 1; // 1 bit = 1 (yes) or 0 (no)
    unsigned int has_paid_dues : 1;   // 1 bit = 1 (yes) or 0 (no)
} MemberStatus;


typedef struct {
    char name[100];
    char roll[20];
    char department[50];
    char phone[20];
    char email[50];
    char semester[10];
    char password[50]; // Added for member login
    MemberStatus status; // Embedded struct with bit-fields
} Member;

typedef struct {
    char name[100];
    char about[200];
    char date[20];
    char venue[100];
} Event;

#endif