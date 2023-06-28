#include "names.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// Function to return a random number 0 to 5 inclusive simulating a roll of die
int roll(void) {
    return random() % 6;
}

// Function that returns the position of the player to the left
// pos: position of the current player
// players: the number of players in the game
int left(int pos, int players) {
    return (pos + players - 1) % players;
}

// Function that returns the position of the player to the right
// pos: position of the current player
// players: the number of players in the game
int right(int pos, int players) {
    return (pos + 1) % players;
}

int main(void) {
    // Grab user input for the number of players
    int numPlayers = 0;
    printf("Number of Players: ");
    scanf("%d", &numPlayers);

    // Error checking for number of players
    if (numPlayers >= 10 || numPlayers < 2) {
        fprintf(stderr, "Invalid number of players.\n");
        exit(1);
    }

    // Grab user input for the random seed
    int64_t seed = 0;
    printf("Random Seed: ");

    // Error checking for invalid random seed
    if (scanf("%" SCNd64, &seed) != 1) {
        fprintf(stderr, "Invalid random seed.\n");
    }
    if (seed < 0 || seed > UINT32_MAX) {
        fprintf(stderr, "Invalid random seed.\n");
        exit(1);
    }

    // Initialize all players lives in array to 3
    int lives[numPlayers];
    for (int i = 0; i < numPlayers; i++) {
        lives[i] = 3;
    }

    // Initialize an array that stores the current rolls for each player during each round
    int currentRoll[numPlayers];
    for (int i = 0; i < numPlayers; i++) {
        currentRoll[i] = 3;
    }

    // Initialize amount of alive players, a counter, and loop for the amount of rounds
    int currentNumPlayers = numPlayers;
    int counter = 1;
    while (currentNumPlayers > 1) {
        // Prints the current round
        printf("Round %d\n", counter);
        counter++;

        // Loop for each player's rolls
        for (int j = 0; j < numPlayers; j++) {
            int r1 = roll();
            int r2 = roll();
            if (lives[j] > 0) {

                // Check if the roll is a midnight
                if (r1 == 5 && r2 == 5) {
                    printf(" - %s rolls %s... ", names[j], rolls[r1][r2]);
                    int posLeft = left(j, numPlayers);
                    int posRight = right(j, numPlayers);

                    // If they have 0 lives, then resurrect the player, if > 0 lives, sparkles
                    if (lives[posLeft] > 0) {
                        printf("sparkles %s ", names[posLeft]);
                        lives[posLeft]++;
                    } else {
                        printf("resurrects %s ", names[posLeft]);
                        lives[posLeft]++;
                        currentNumPlayers++;
                    }
                    if (lives[posRight] > 0) {
                        printf("sparkles %s\n", names[posRight]);
                        lives[posRight]++;
                    } else {
                        printf("resurrects %s\n", names[posRight]);
                        lives[posRight]++;
                        currentNumPlayers++;
                        currentRoll[j + 1] = 12;
                    }

                } else {
                    printf(" - %s rolls %s...\n", names[j], rolls[r1][r2]);
                    // Store the current roll into array
                    currentRoll[j] = r1 + r2;
                }
            }
        }

        // Find the first minimum shown in the current roll array
        // Iterate through array, and print out the vampire that eats the garlic
        int min = currentRoll[0];
        int minPos;
        for (int j = 1; j < numPlayers; j++) {
            if (currentRoll[j] < min && lives[j] > 0) {
                min = currentRoll[j];
                minPos = j;
            }
        }

        printf("%s is forced to eat Garlic!\n", names[minPos]);

        // Deduct a life from the corresponding vampire that ate garlic
        if (lives[minPos] != 0) {
            lives[minPos]--;
        }

        // If their life is 0, deduct 1 from current amount of players alive
        if (lives[minPos] == 0) {
            currentNumPlayers--;
        }

        // If their life is 0, print that they died
        if (lives[minPos] == 0) {
            printf("%s has died.\n", names[minPos]);
        }

        // Otherwise, print out how many lives they have left
        if (lives[minPos] == 1) {
            printf("%s has %d life remaining.\n", names[minPos], lives[minPos]);
        } else if (lives[minPos] != 0) {
            printf("%s has %d lives remaining.\n", names[minPos], lives[minPos]);
        }
    }

    // At the end of the game, print out the winner that has >= 1 lives remaining
    int winner = 0;
    for (int i = 0; i < numPlayers; i++) {
        if (lives[i] >= 1) {
            winner = i;
        }
    }
    printf("%s wins the Garlic game!\n", names[winner]);
}
