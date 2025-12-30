#ifndef USER_PUBLIC_H
#define USER_PUBLIC_H

// The main menu for a specific club
void showClubMenu(const char *clubFilePrefix);

// Publicly viewable info
void showClubIntroduction(const char *clubFilePrefix);
void showClubAchievements(const char *clubFilePrefix);
void userViewEvents(const char *clubFilePrefix);

#endif