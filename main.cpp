// I derived a formula for counting the number of bit strings
// that contain the substring "01" for Discrete Mathematics.
// This program will ensure that this algorithm does in fact 
// hold true.

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

// Calculate using recurrence relation a_n = a_(n-1) + 2^(n-1) - 1

long long calculateRecursive(int n) 
{
    // Base case

    if (n <= 1) 
    {
        return 0;
    }

    // Use array to avoid stack overflow with recursion

    vector<long long> a(n + 1, 0);
    a.at(1) = 0;  // Initial condition
    
    for (int i = 2; i <= n; i++) {
        a.at(i) = a.at(i - 1) + pow(2, i - 1) - 1;
    }
    
    return a.at(n); 
}

// Check if a bit string contains "01" substring

bool contains01(const string& s) 
{
    for (size_t i = 0; i < s.length() - 1; i++) 
    {
        if (s[i] == '0' && s[i+1] == '1')
        {
            return true;
        }
    }
    
    return false;
}

// Generate all bit strings of length n and count those containing "01"

long long countByGeneration(int n) 
{
    long long count = 0;
    
    // Generate all possible bit strings
    long long total = pow(2, n);
    for (long long i = 0; i < total; i++) {
        // Convert number to binary representation
        string bitString;
        long long num = i;
        
        // Ensure the bit string has length n by padding with 0s
        for (int j = 0; j < n; j++) {
            bitString = (num % 2 ? "1" : "0") + bitString;
            num /= 2;
        }
        
        // Check if the bit string contains "01"
        if (contains01(bitString)) {
            count++;
        }
    }
    
    return count;
}

int main() {
    cout << "Testing recurrence relation for bit strings containing '01'" << endl << endl;
    
    // Create nicely formatted table with column headers
    cout << left << setw(5) << "n" 
         << setw(15) << "Recursive" 
         << setw(15) << "Direct Count" 
         << "Match?" << endl;
    
    cout << setfill('-') << setw(45) << "" << setfill(' ') << endl;
    
    // Test for different values of n
    for (int n = 1; n <= 10; n++) {
        long long recursive = calculateRecursive(n);
        long long directCount = countByGeneration(n);
        
        cout << left << setw(5) << n 
             << setw(15) << recursive 
             << setw(15) << directCount 
             << (recursive == directCount ? "Yes" : "No") << endl;
    }
    
    // Allow user to test specific length
    int userInput;
    cout << "\nEnter a length to test (1-20): ";
    cin >> userInput;
    
    if (userInput >= 1 && userInput <= 20) 
    {
        long long recursive = calculateRecursive(userInput);
        long long directCount = countByGeneration(userInput);
        
        cout << "\nResults for n = " << userInput << ":" << endl;
        cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;
        cout << left << setw(20) << "Recursive formula:" << recursive << endl;
        cout << left << setw(20) << "Direct count:" << directCount << endl;
        cout << left << setw(20) << "Results match:" << (recursive == directCount ? "Yes" : "No") << endl;
    } 
    else 
    {
        cout << "Input out of range." << endl;
    }
    
    return 0;
}