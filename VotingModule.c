#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Voter {
    int id;
    char name[50];
    int hasVoted; // 0 = not voted, 1 = voted
};

struct Candidate {
    char name[50];
    int voteCount;
};

// Function Prototypes
int loadVotersFromFile(const char *filename, struct Voter **voters);
int loadCandidatesFromFile(const char *filename, struct Candidate **candidates);
void saveVotersToFile(const char *filename, struct Voter *voters, int voterCount);
void saveCandidatesToFile(const char *filename, struct Candidate *candidates, int candidateCount);
void displayCandidates(struct Candidate *candidates, int candidateCount);
void displayVoters(struct Voter *voters, int voterCount);
void addCandidate(struct Candidate **candidates, int *candidateCount);
void removeCandidate(struct Candidate **candidates, int *candidateCount);
void addVoter(struct Voter **voters, int *voterCount);
void removeVoter(struct Voter **voters, int *voterCount);
void voteForCandidate(struct Voter *voters, int voterCount, struct Candidate *candidates, int candidateCount);
void displayResults(struct Candidate *candidates, int candidateCount);
void adminMenu(struct Voter **voters, int *voterCount, struct Candidate **candidates, int *candidateCount);
void voterMenu(struct Voter *voters, int voterCount, struct Candidate *candidates, int candidateCount);

int main() {
    struct Voter *voters = NULL;
    struct Candidate *candidates = NULL;
    int voterCount = loadVotersFromFile("voters.txt", &voters);
    int candidateCount = loadCandidatesFromFile("candidates.txt", &candidates);

    if (voterCount == 0 || candidateCount == 0) {
        printf("Warning: Voters or candidates list is empty.\n");
    }
    int choice;
    do {
        printf("\n--- Voting System ---\n");
        printf("1. Admin Mode\n");
        printf("2. Voter Mode\n");
        printf("3. Display Results\n"); // Added this line
        printf("4. Exit\n"); // Adjusted exit option to 4
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                adminMenu(&voters, &voterCount, &candidates, &candidateCount);
                break;
            case 2:
                voterMenu(voters, voterCount, candidates, candidateCount);
                break;
            case 3: // New case for displaying results
                displayResults(candidates, candidateCount);
                break;
            case 4:
                saveVotersToFile("voters.txt", voters, voterCount);
                saveCandidatesToFile("candidates.txt", candidates, candidateCount);
                printf("Data saved. Exiting system.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    free(voters);
    free(candidates);
    return 0;
}

// Function Definitions

// Load voters from file
int loadVotersFromFile(const char *filename, struct Voter **voters) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return 0;
    int count = 0;
    struct Voter temp;
    while (fscanf(file, "%d,%49[^,],%d\n", &temp.id, temp.name, &temp.hasVoted) != EOF) {
        *voters = realloc(*voters, (count + 1) * sizeof(struct Voter));
        (*voters)[count++] = temp;
    }
    fclose(file);
    return count;
}

// Load candidates from file
int loadCandidatesFromFile(const char *filename, struct Candidate **candidates) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return 0;
    int count = 0;
    struct Candidate temp;
    while (fscanf(file, "%49[^,],%d\n", temp.name, &temp.voteCount) != EOF) {
        *candidates = realloc(*candidates, (count + 1) * sizeof(struct Candidate));
        (*candidates)[count++] = temp;
    }
    fclose(file);
    return count;
}

// Save voters to file
void saveVotersToFile(const char *filename, struct Voter *voters, int voterCount) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < voterCount; i++) {
        fprintf(file, "%d,%s,%d\n", voters[i].id, voters[i].name, voters[i].hasVoted);
    }
    fclose(file);
}

// Save candidates to file
void saveCandidatesToFile(const char *filename, struct Candidate *candidates, int candidateCount) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < candidateCount; i++) {
        fprintf(file, "%s,%d\n", candidates[i].name, candidates[i].voteCount);
    }
    fclose(file);
}

// Display candidates
void displayCandidates(struct Candidate *candidates, int candidateCount) {
    printf("\n%-10s%-20s%-10s\n", "No.", "Name", "Votes");
    printf("========================================\n");

    for (int i = 0; i < candidateCount; i++) {
        printf("%-10d%-20s%-10d\n", 
               i + 1, 
               candidates[i].name, 
               candidates[i].voteCount);
    }
}

// Display voters
void displayVoters(struct Voter *voters, int voterCount) {
    printf("\n%-10s%-20s%-15s\n", "ID", "Name", "Has Voted");
    printf("===============================================\n");

    for (int i = 0; i < voterCount; i++) {
        printf("%-10d%-20s%-15s\n", 
               voters[i].id, 
               voters[i].name, 
               voters[i].hasVoted ? "Yes" : "No");
    }
}

void displayResults(struct Candidate *candidates, int candidateCount) {
    printf("\n--- Voting Results ---\n");
    if (candidateCount == 0) {
        printf("No candidates available.\n");
        return;
    }

    printf("%-20s%-10s\n", "Candidate Name", "Votes");
    printf("============================\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%-20s%-10d\n", candidates[i].name, candidates[i].voteCount);
    }

    // Find the candidate with the highest votes
    int maxVotes = 0;
    int maxIndex = -1;
    for (int i = 0; i < candidateCount; i++) {
        if (candidates[i].voteCount > maxVotes) {
            maxVotes = candidates[i].voteCount;
            maxIndex = i;
        }
    }

    // Display the winner
    if (maxIndex != -1) {
        printf("\nThe candidate with the highest votes is: %s with %d votes!\n",
               candidates[maxIndex].name, candidates[maxIndex].voteCount);
    }
}

// Admin operations
void adminMenu(struct Voter **voters, int *voterCount, struct Candidate **candidates, int *candidateCount) {
    int passkey;
    int choice;
    int attempts = 3; // Maximum allowed attempts

    while (attempts > 0) {
        printf("Enter the Admin passkey: ");
        scanf("%d", &passkey);

        if (passkey == 233536) {
            do {
                printf("\n--- Admin Menu ---\n");
                printf("1. Add Candidate\n");
                printf("2. Remove Candidate\n");
                printf("3. Add Voter\n");
                printf("4. Remove Voter\n");
                printf("5. Display Candidates\n");
                printf("6. Display Voters\n");
                printf("7. Exit Admin Menu\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        addCandidate(candidates, candidateCount);
                        break;
                    case 2:
                        removeCandidate(candidates, candidateCount);
                        break;
                    case 3:
                        addVoter(voters, voterCount);
                        break;
                    case 4:
                        removeVoter(voters, voterCount);
                        break;
                    case 5:
                        displayCandidates(*candidates, *candidateCount);
                        break;
                    case 6:
                        displayVoters(*voters, *voterCount);
                        break;
                    case 7:
                        printf("Exiting Admin Menu.\n");
                        break;
                    default:
                        printf("Invalid choice. Try again.\n");
                }
            } while (choice != 7);
            return; // Exit function after successful login and menu operations
        } else {
            attempts--;
            if (attempts > 0) {
                printf("Invalid passkey! You have %d attempt(s) remaining.\n", attempts);
            } else {
                printf("Invalid passkey! No attempts left. Terminating program.\n");
                exit(0); // Terminate the program
            }
        }
    }
}

// Voter operations
void voterMenu(struct Voter *voters, int voterCount, struct Candidate *candidates, int candidateCount) {
    voteForCandidate(voters, voterCount, candidates, candidateCount);
}

// Add candidate
void addCandidate(struct Candidate **candidates, int *candidateCount) {

    displayCandidates(*candidates, *candidateCount);
    printf("\n");

    char askUser;
    struct Candidate newCandidate;
    printf("Enter candidate name: ");
    scanf("%s", newCandidate.name);
    newCandidate.voteCount = 0;

    *candidates = realloc(*candidates, (*candidateCount + 1) * sizeof(struct Candidate));
    (*candidates)[*candidateCount] = newCandidate;
    (*candidateCount)++;
    printf("Candidate added successfully to the above candidate list.\n");
}  

// Remove candidate
void removeCandidate(struct Candidate **candidates, int *candidateCount) {

    displayCandidates(*candidates, *candidateCount);
    printf("\n");

    int index;
    printf("Enter candidate number to remove: ");
    scanf("%d", &index);
    if (index < 1 || index > *candidateCount) {
        printf("Invalid candidate number.\n");
        return;
    }
    for (int i = index - 1; i < *candidateCount - 1; i++) {
        (*candidates)[i] = (*candidates)[i + 1];
    }
    *candidates = realloc(*candidates, (*candidateCount - 1) * sizeof(struct Candidate));
    (*candidateCount)--;
    printf("Candidate removed successfully.\n");
}

// Add voter
void addVoter(struct Voter **voters, int *voterCount) {
    struct Voter newVoter;
    int isDuplicate = 0;

    // Input voter ID and check constraints
    do {
        printf("Enter voter ID (must be > 1200): ");
        scanf("%d", &newVoter.id);
        if (newVoter.id <= 1200) {
            printf("Invalid ID! Voter ID must be greater than 1200.\n");
        }
    } while (newVoter.id <= 1200);

    // Check for duplicate ID
    for (int i = 0; i < *voterCount; i++) {
        if ((*voters)[i].id == newVoter.id) {
            isDuplicate = 1;
            break;
        }
    }

    if (isDuplicate) {
        printf("Duplicate ID detected! A voter with ID %d already exists.\n", newVoter.id);
        return;
    }

    // Input voter name
    printf("Enter voter name: ");
    scanf("%s", newVoter.name);
    newVoter.hasVoted = 0;

    // Add the new voter to the list
    *voters = realloc(*voters, (*voterCount + 1) * sizeof(struct Voter));
    (*voters)[*voterCount] = newVoter;
    (*voterCount)++;
    printf("Voter added successfully.\n");
}

// Remove voter
void removeVoter(struct Voter **voters, int *voterCount) {
    int id;
    printf("Enter voter ID to remove: ");
    scanf("%d", &id);
    int index = -1;
    for (int i = 0; i < *voterCount; i++) {
        if ((*voters)[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Voter not found.\n");
        return;
    }
    for (int i = index; i < *voterCount - 1; i++) {
        (*voters)[i] = (*voters)[i + 1];
    }
    *voters = realloc(*voters, (*voterCount - 1) * sizeof(struct Voter));
    (*voterCount)--;
    printf("Voter removed successfully.\n");
}

// Cast vote
void voteForCandidate(struct Voter *voters, int voterCount, struct Candidate *candidates, int candidateCount) {
    int voterID;
    printf("Enter your voter ID: ");
    scanf("%d", &voterID);
    int voterIndex = -1;
    for (int i = 0; i < voterCount; i++) {
        if (voters[i].id == voterID) {
            if (voters[i].hasVoted) {
                printf("You have already voted.\n");
                return;
            }
            voterIndex = i;
            break;
        }
    }
    if (voterIndex == -1) {
        printf("Invalid voter ID.\n");
        return;
    }

    displayCandidates(candidates, candidateCount);
    int choice;
    printf("Enter the number of the candidate you want to vote for: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > candidateCount) {
        printf("Invalid candidate number.\n");
        return;
    }

    voters[voterIndex].hasVoted = 1;
    candidates[choice - 1].voteCount++;
    printf("Vote successfully cast for %s.\n", candidates[choice - 1].name);
}

//End of the voting module