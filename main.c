/*
 * File:   main.cpp
 * Author: j4-smith
 *N-Queens example in C
 * First Created on 25 April 2014, 18:42
 * Modified in light of student progress 
 
 * Rewritten Oct 2015 to use more generic solution structures 
 * and functions with NQueens-specific names that call the functions that modify the
 */


#include <stdio.h>
#include <stdlib.h>
#include "StructureDefinitions.h"
#include "SolutionListOperations.h"
#include "NQueensChecker.h"


candidateSolution workingCandidate;//this one will hold the soltion we arecurrently considering
candidateList  currentListOfCandidates; // this list will store all the soltion we;ve created but not examined yet
candidateList listOfExaminedCandidates; // this is where we will store all the ones we're done with



//************************ don't edit anything above this line***********************//


int main(int argc, const char * argv[])
{
    
    /* the next set of variables get used within our main function
     * but aren't declared globally becuase we don't want the other functions to change them inadvertently */
    int numberOfCompleteSolutionsFound = 0; //simple flag to let us know whether we have stopped
    int numberOfSolutionsExamined = 0; //simple counter
    int indexOfSolutionWeAreLookingAt; //index in list of current solution being examined
    int newLength, valueToAdd; // used when we extend the working candidate
	int i;

    //start off by emptying the lists of candidate solutions
    CleanListsOfSolutionsToStart();
	CleanWorkingCandidate();
    
    /* So now let's start by creating our first solution
     * which we do by filling the values into the variable we declared as the workingCandidate
     * We'll begin by putting the first queen into column ), or specified from the command line
   */
   //valueToAdd = 0;
   scanf("%d", &valueToAdd);
   if (valueToAdd > 7 || valueToAdd < 0) {
	   printf("Invalid input");
	   return 0;
   }

   if(argc==2)
     {
       valueToAdd = atoi(argv[1]);
       if (valueToAdd >=N || valueToAdd <0)
           PrintThisMessageAndExit("Invalid Input");
     }
	   
	
	AddQueenToNextRowInColumn(valueToAdd);
    CalculateNumberOfVulnerableQueensForWorkingCandidate(); //should return zero because there is only one queen:)
    numberOfSolutionsExamined=1;
    
    //and we can put this as our first item in the list to start the process
    AddWorkingCandidateToCurrentList();
    
    
    //Now we will go into a loop examining solutions until we find one that is full and has no vulnerable queens
	while (numberOfCompleteSolutionsFound == 0) {  //While the amount of complete solutions is NOT found loop around till we find one.
		indexOfSolutionWeAreLookingAt = currentListOfCandidates.indexOfLastEntryAdded; // This copies our next candidate into the working candidate
		CopySolutionFromCurrentListIntoWorkingCandidate(indexOfSolutionWeAreLookingAt); //Again does the same thing
		RemoveSolutionFromCurrentList(indexOfSolutionWeAreLookingAt); //Gets rid of it to stop examining the same index
		printf("Next Index of Solution: %d \n", indexOfSolutionWeAreLookingAt); // For debugging making sure I am actually changing the solution.
		PrintWorkingCandidate(); // For seeing if the working candidate has changed
		numberOfSolutionsExamined++; // to keep track of how many attempts
		CalculateNumberOfVulnerableQueensForWorkingCandidate(); // find number of queens that are vulnerable and change the working candidate score depending on the result.
		if ((workingCandidate.numberOfDefinedValues == N) && (workingCandidate.score == 0)) { // If it has reached the maximum number of queens placed and there are no vulnerable queens
			numberOfCompleteSolutionsFound++; //We do this to end the while loop			  // workingCandidate.numberOfDefinedValues == N means that we can't just place 1 queen and call it quits.
			printf("\n Solution found at: %d candidates\n", numberOfSolutionsExamined); // output total examined candidates
			PrintFinalSolutionAndExit(); // exit
		}
		else { // if no solution found
			AddWorkingCandidateToExaminedList(); // add it to examined list so we dont look through it again
			if (workingCandidate.score > 0) {
				//Dont do anything because we may as well get the next solution
			}

			else { 
				AddQueenToNextRowInColumn(0); // This all essentially generates a new candidate by constantly placing a queen in a column until the score is 0.
				newLength = workingCandidate.numberOfDefinedValues - 1; 
				for (valueToAdd = 0; valueToAdd < N; valueToAdd++) {
					MoveQueenInRowToNewCol(newLength, valueToAdd);
					AddWorkingCandidateToCurrentList(); // examine the new candidate in the loop again.
				}
			}

		}
	}

		
	
   // end of  statement dealing with search
    
    
    
    
    return 0;
}