//
//  main.cpp
//  CSCI 2421 Homework 7
//
//  Created by Bradley Ruck on 4/1/16.
//  Copyright © 2016 Bradley Ruck. All rights reserved.
//  Latest modification date 10/26/16.
//
//  Program that recursively finds all solutions for making change from
//  a user entered amount in US cents.  The user is asked if only the unique
//  solutions are to be printed (in ascending order - based on total coins
//  required to make the change). Otherwise, all recursive solutions are
//  printed in ascending order. Coins available to make change are a
//  penny(1), nickel(5), dime(10) and quarter(25).
//
#include <iostream>
#include <vector>
#include <iomanip>      // std::setw

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::vector;

// Global constants
const int COUNTS = 5;   // 1,2,3,4 - number of each coin denomination in solution,
                        // 5 - number of total coins in solution

// Function declarations
int coins(int denomination);
void ways(int amount, int startcoins, vector<vector<int> > &solutions, vector<int> &coin, int &totalways, char answer);
bool wayToSort(vector<int> i, vector<int> j);

int main() {
    vector<int> coin(COUNTS, 0);                // Set of coin solution counts
    vector<vector<int> > solutions(0, coin);    // Master set of solutions
    int totalways = 0;                          // Total number of solutions
    int amount;                                 // User entered amount to change
    char answer;                                // User entered for unique solutions preference

    cout << "Please enter the amount in US currency (in cents) to change: ";
    cin  >> amount;
    cout << endl;

    cout << "Do you want only unique solutions?\n" << "Please enter 'Y' for yes or 'N' for no: ";
    cin >> answer;
    cout << endl;

    if (amount > 0) {
        cout << "Optimal Combination:";
        int startcoins = 0;                                             // starting number of coins in solution
        ways(amount, startcoins, solutions, coin, totalways, answer);   // Recursively solve for solutions
        sort(solutions.begin(), solutions.end(), wayToSort);            // Sort solution vector by total # of coins
        for(int i = 0; i < solutions.size(); i++)                       // Print all saved solutions to screen
            cout << "   {" << setw(2) << solutions[i][0] << " Quarters, " << setw(2) << solutions[i][1] << " Dimes, " << setw(2) << solutions[i][2] << " Nickels, " << setw(2) << solutions[i][3] << " Pennies" << " } " << "   Total: " << setw(2) << solutions[i][4] << " coins" << endl;
        if (answer == 'Y' || answer == 'y')
            cout << endl << "Total unique coin combinations: " << totalways << endl << endl;
        else
            cout << endl << "Total recursive coin combinations: " << totalways << endl << endl;
    }
        // No change to be made if no initial amount
    else if (amount == 0)
        cout << "You have entered no value, there is no change to be made." << endl << endl;
        // Cannot make change from a negative amount
    else
        cout << "You have entered a negative value, please try again." << endl << endl;

    return 0;
}
// Function to return the denomination of each coin available
int coins(int denomination) {
    if (denomination == 1)      // Returns value of a penny
        return 1;
    else if (denomination == 2) // Returns value of a nickel
        return 5;
    else if (denomination == 3) // Returns value of a dime
        return 10;
    else // (denomination == 4) // Returns value of a quarter
        return 25;
}
// Function to define sort algorithm for vector of solutions based
// on total number of coins in solution, ASCENDING order
bool wayToSort(vector<int> i, vector<int> j) {
    return i[4] < j[4];
}
// Function to recursively solve for all change solutions, returns total number of unique solutions
void ways(int amount, int i, vector<vector<int> > &solutions, vector<int> &coin, int &totalways, char answer) {
    if (i != amount) {
        if (i + coins(4) <= amount) {
            coin[0]++;
            ways(amount, i + coins(4), solutions, coin, totalways, answer);
            coin[0]--;
        }
        if (i + coins(3) <= amount) {
            coin[1]++;
            ways(amount, i + coins(3), solutions, coin, totalways, answer);
            coin[1]--;
        }
        if (i + coins(2) <= amount) {
            coin[2]++;
            ways(amount, i + coins(2), solutions, coin, totalways, answer);
            coin[2]--;
        }
        if (i + coins(1) <= amount) {
            coin[3]++;
            ways(amount, i + coins(1), solutions, coin, totalways, answer);
            coin[3]--;
        }
    }
    else {
        // Total number of coins in solution
        coin[4] = coin[0] + coin[1] + coin[2] + coin[3];
        // Test to see if solution already exits, and if user opts for unique solutions
        if (find(solutions.begin(), solutions.end(), coin) != solutions.end() && (answer == 'Y' || answer == 'y'))
            return;                     // Return if solution already exits or user wants to print all recursive solutions
        else
            solutions.push_back(coin);  // Add to solution list if not found or all solutions to be printed

        totalways++;                    // Increment total number of solutions
    }
    return;
}