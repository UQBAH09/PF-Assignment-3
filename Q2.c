#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store player details and performance
struct Player
{
    int ballScores[12];
    char playerName[50];
    int totalScore;
};

// Validates the score for a ball (should be between 0 and 6)
int validateScore(int score)
{
    if (score >= 0 && score <= 6)
    {
        return score;
    }
    return 0;
}

// Captures the scores for a player's game and calculates the total score
void playGame(struct Player *player)
{
    player->totalScore = 0;

    for (int i = 0; i < 12; i++)
    {
        int score;
        printf("Enter score for ball %d: ", i + 1);
        scanf("%d", &score);

        player->ballScores[i] = validateScore(score);

        player->totalScore += player->ballScores[i];
    }
}

// Determines the winner between two players
int findWinner(struct Player player1, struct Player player2)
{
    if (player1.totalScore > player2.totalScore)
    {
        return 1;
    }
    else if (player1.totalScore < player2.totalScore)
    {
        return 2;
    }
    return 0;
}

// Displays the performance and scores for both players
void displayMatchScoreboard(struct Player player1, struct Player player2)
{
    printf("\nPlayer 1 Performance:\n");
    for (int i = 0; i < 12; i++)
    {
        printf("Ball %d score: %d\n", i + 1, player1.ballScores[i]);
    }
    printf("Average score: %.2f\n", player1.totalScore / 12.0);
    printf("Total score: %d\n", player1.totalScore);

    printf("\nPlayer 2 Performance:\n");
    for (int i = 0; i < 12; i++)
    {
        printf("Ball %d score: %d\n", i + 1, player2.ballScores[i]);
    }
    printf("Average score: %.2f\n", player2.totalScore / 12.0);
    printf("Total score: %d\n", player2.totalScore);
}

int main(void)
{
    struct Player player1, player2;

    // Input scores for Player 1
    printf("Enter scores for Player 1:\n");
    playGame(&player1);

    // Input scores for Player 2
    printf("\nEnter scores for Player 2:\n");
    playGame(&player2);

    // Determine and announce the winner
    int winner = findWinner(player1, player2);

    if (winner == 1)
    {
        printf("\nPlayer 1 is the winner!\n");
    }
    else if (winner == 2)
    {
        printf("\nPlayer 2 is the winner!\n");
    }
    else
    {
        printf("\nThe match is a tie!\n");
    }

    // Display the match scoreboard
    displayMatchScoreboard(player1, player2);

    return 0;
}
