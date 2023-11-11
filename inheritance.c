// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person

    person *newperson = malloc(sizeof(person));

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // TODO: Set parent pointers for current person

        //write parent* adress in the parents array of pointers

        newperson->parents[0] = parent0;
        newperson->parents[1] = parent1;


        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        //assign the new person the alleles their parents have using a random number that gets the allele in the position of the random number

        newperson->alleles[0] = parent0->alleles[rand() % 2];
        newperson->alleles[1] = parent1->alleles[rand() % 2];

    }

    // If there are no generations left to create
    else
    {
        // TODO: Set parent pointers to NULL

        //declaring that there isn't a parent to track

        person *parent0 = NULL;
        person *parent1 = NULL;

        // TODO: Randomly assign alleles

        //setting the alles using the random allele function because the person doesn't have parents

        newperson->alleles[0] = random_allele();
        newperson->alleles[1] = random_allele();

        newperson->parents[0] = parent0;
        newperson->parents[1] = parent1;

    }

    // TODO: Return newly created person
    return newperson;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case

    if (p == NULL)
    {
        return;
    }

    printf("%c%c\n", p->alleles[0], p->alleles[1]);

    // TODO: Free parents recursively

    //parent0 of parent0 of parent0... until it doesn't have any parent0

    free_family(p->parents[0]);

    //same procces

    free_family(p->parents[1]);

    // TODO: Free child

    //frees current p and then it returns to the p before (previous step)

    printf("Person freed: %c%c\n", p->alleles[0], p->alleles[1]);

    free(p);


}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
