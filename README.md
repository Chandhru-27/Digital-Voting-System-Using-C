# Digital-Voting-System-Using-C
This Voting Module is a simple C-based voting system that allows users to cast votes, view results, and store voting data in a text file for persistence. The program features a menu-driven interface, making it easy to navigate. It ensures that all votes are recorded and counted accurately by reading and writing data to a text file.

# Voting Module

## Overview
This project implements a simple voting system in C that allows users to cast votes, view results, and manage voting data. The voting data is stored in a text file for persistence.

## Features
- **User-friendly interface:** The program provides an easy-to-use menu-driven interface.
- **Casting votes:** Users can vote for their preferred candidates.
- **Displaying results:** The program calculates and displays vote counts for each candidate.
- **Data storage:** Votes are saved in a text file to ensure data persistence between runs.

## How It Works
1. **Menu Selection:** The user is presented with a menu to either cast a vote, view results, or exit.
2. **Voting:** Users select their preferred candidate, and the vote is recorded.
3. **Data Persistence:** Votes are written to a text file to maintain records.
4. **Result Computation:** The program reads the text file to calculate and display the results.

## File Handling
- The program uses a text file to store voting data.
- Every vote cast is appended to this file.
- During result computation, the program reads and processes the file data.

## Prerequisites
- A C compiler (GCC, Clang, or MSVC)
- Basic knowledge of C programming

## Compilation and Execution
To compile the program, use:
```sh
gcc VotingModule.c -o VotingModule
```
To run the program, use:
```sh
./VotingModule
```

## Notes
- Ensure the text file used for storage is accessible and writable.
- Deleting the text file will reset the vote counts.

## Future Enhancements
- Implement authentication for secure voting.
- Improve the file handling mechanism to enhance security.
- Add a graphical user interface (GUI) for better usability.

## Author
Chandhru Loganathan

