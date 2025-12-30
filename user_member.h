#ifndef USER_MEMBER_H
#define USER_MEMBER_H

#include "common_structs.h" // For the Member struct

// This is the only function that needs to be "public"
// It's called by memberLogin()
void showMemberDashboard(const char *clubFilePrefix, const Member *loggedInMember);

#endif