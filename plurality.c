#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void swap(candidate *x, candidate *y);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Iterate candidates array to find if any existing candidate was voted
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++; // Update candidate votes
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Array to store winners
    candidate winners[MAX];

    // Sort the array using selection sort
    for (int j = 0; j < candidate_count - 1; j++)
    {
        int max = candidates[j].votes;
        for (int k = j + 1; k < candidate_count; k++)
        {
            if (max < candidates[k].votes)
            {
                max = candidates[k].votes;
                swap(&candidates[j], &candidates[k]);
            }
        }
    }

    // Check if there is a legit winner
    if (!candidates[0].votes)
    {
        printf("No winner\n");
        return;
    }
    else
    {
        winners[0] = candidates[0];
    }

    // Linear Search to create a winners array
    for (int l = 1; l < candidate_count; l++)
    {
        if (winners[0].votes == candidates[l].votes)
        {
            winners[l] = candidates[l];
        }
    }

    // Print all winners
    int m = 0;
    do
    {
        printf("%s\n", winners[m].name);
        m++;
    }
    while (winners[m].name);

    return;
}

void swap(candidate *x, candidate *y)
{
    candidate temp = *x;
    *x = *y;
    *y = temp;
    return;
}