# KUET-Club-Management-System
This is our first project of KUET. The primary objective of this project is to build a system for KUET.
Club-Management-System-for-KUET
KUET Club Management System (KUET-CMS)

A console-based application built in C for managing student clubs at Khulna University of Engineering and Technology (KUET). This project is developed as part of our first-year C programming course.

2.Project Objective
The primary goal of the KUET Club Management System is to create a simple, efficient, and robust console-based tool to digitize and streamline the administrative tasks of various student clubs at KUET. This system moves away from traditional paper-based or scattered spreadsheet methods to a centralized C-based application, focusing on fundamental programming concepts like data structures, file handling, and memory management.

2.Key Features
This system provides a menu-driven interface for easy navigation. The core functionalities include:

Member Management:

Add New Member: Register a new student with details like Student ID, Name, Department, Phone, and Email.

View All Members: Display a complete list of all registered club members.

Search for Member: Quickly find a member's details using their Student ID or Name.

Update Member Info: Edit the details of an existing member.

Remove Member: Delete a member's record from the system.

Event Management:

Create New Event: Add upcoming events with details like Event Name, Date, and Venue.

View All Events: List all scheduled events.

Manage Event Registration: Register members for an event and view the participant list.

Finance Management (Basic):

Track Membership Fees: Update and check the fee payment status (Paid/Unpaid) for each member.

Log Basic Expenses: Keep a simple log of club expenses for budgeting.

Data Persistence:

All member and event data is saved locally to text files (.txt or .dat).

The system reads from these files on startup and saves all changes back to the files before exiting, ensuring no data is lost between sessions.

Admin/User Roles:

A simple password-protected Admin Mode allows access to all features (adding, deleting, updating).

A General User Mode might have read-only access (viewing members and events).

3.Technology & Concepts
Language: C (Standard C)

Core Concepts:

Data Structures: Using struct to model members, events, and other entities.

File Handling (File I/O): Reading from and writing to text files (fopen, fwrite, fread, fclose) for data persistence.

Pointers & Dynamic Memory: Using malloc and free for managing data (e.g., in linked lists, if implemented).

Functions & Modular Programming: Organizing code into separate, reusable functions for each feature.

Console UI Design: Creating a user-friendly, menu-driven interface in the console.

4.Team Members
[Avik Hasan] - 2407021 - (Department of Computer Science and Engineering)

[Bismoy Sarkar] - 2407008 - (Department of Computer Science and Engineering)

[Ohona Rahman] - 2407014 - (Department of Computer Science and Engineering)

(Project for [CSE-1101,1102], Khulna University of Engineering and Technology)
