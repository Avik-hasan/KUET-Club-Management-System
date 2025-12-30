#ifndef USER_TYPES_H
#define USER_TYPES_H

#include "common_structs.h" // For Member and Event

// ENUM for resource type
typedef enum {
    LINK,
    BOOK,
    VIDEO
} ResourceType;

// UNION for resource data
typedef union {
    char websiteUrl[200];
    char bookTitle[150];
    char videoId[50];
} ResourceData;

// STRUCT for a resource
typedef struct {
    char title[100];
    char description[200];
    ResourceType type; // Using the enum
    ResourceData data; // Using the union
} Resource;

// STRUCT for an alumnus
typedef struct {
    char name[100];
    char graduationYear[10];
    char company[100];
    char position[100];
    char email[50];
} Alumnus;

#endif