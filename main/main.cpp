#include <iostream>
#include <numeric> // For std::accumulate (optional, but a good practice)

// Function to calculate factorial of a number
long long calculateFactorial(int n) {
    if (n < 0) {
        return -1; // Indicate error for negative input
    }
    long long factorial = 1;
    // Loop from 1 to n to multiply numbers
    for (int i = 1; i <= n; ++i) {
        factorial *= i;
    }
    return factorial;
}

int main() {
    int number;

    std::cout << "Enter a positive integer: ";

    // Take input from the user
    if (!(std::cin >> number)) {
        std::cerr << "Invalid input. Please enter an integer." << std::endl;
        return 1; // Exit with error
    }

    // Check if the number is positive
    if (number < 0) {
        std::cout << "Factorial is not defined for negative numbers." << std::endl;
    }
    else {
        // Call the function to calculate factorial
        long long result = calculateFactorial(number);
        if (result == -1) {
            // This case should ideally not be reached due to the check above
            std::cerr << "An unexpected error occurred during calculation." << std::endl;
        }
        else {
            // Display the result
            std::cout << "Factorial of " << number << " is " << result << std::endl;
        }
    }

    return 0; // Successful execution
}
