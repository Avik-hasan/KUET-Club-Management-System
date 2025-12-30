#ifndef ADMIN_MEMBERS_H
#define ADMIN_MEMBERS_H

#include <stdio.h> 

void addMember(const char *clubName);
void viewAllMembers(const char *clubName);
void removeMember(const char *clubName);
void viewPendingApplicants(const char *clubName);

#endif