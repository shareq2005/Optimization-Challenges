//
//  fibonacci.cpp
//  fibonacci
//

//
//
//  Created by shareq on 2014-07-29.
//  Copyright (c) 2014 shareq. All rights reserved.
//


#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
typedef unsigned long long ll;

//vector structure implementation of matrix
typedef vector<vector<ll> > matrix;

// the matrix dimension
#define T 2

// CHange the following to the index you want
#define INDEX 41434767994

// Change the following to the last number of bits
// of the fibonacci number you need
// (zeros specify the number of bits)
#define MASK 100000


//function to multiply two 2x2 matrices
matrix multiply_two_by_two(matrix A, matrix B)
{
    matrix result(T, vector<ll>(T));
    
    result[0][0] =  (A[0][0]*B[0][0]) % MASK + (A[0][1]*B[1][0]) % MASK;
    result[0][1] =  (A[0][0]*B[0][1]) % MASK + (A[0][1]*B[1][1]) % MASK;
    result[1][0] =  (A[1][0]*B[0][0]) % MASK + (A[1][1]*B[1][0]) % MASK;
    result[1][1] =  (A[1][0]*B[0][1]) % MASK + (A[1][1]*B[1][1]) % MASK;
    
    return result;
}

//function returns the power of a 2x2 matrix A (A^n)
matrix power_two_by_two(matrix A, ll p)
{
    //identity matrix base case
    if(p == 0)
    {
        matrix identity(T, vector<ll>(T));
        identity[0][0] = 1;
        identity[0][1] = 0;
        identity[1][0] = 0;
        identity[1][1] = 1;
    }
    else if(p == 1)
    {
        return A;
    }
    else if(p % 2)  //if p is odd
    {
        return multiply_two_by_two(A, power_two_by_two(A, p-1));
    }
    
    matrix X = power_two_by_two(A,p/2);
    return multiply_two_by_two(X,X);
}


// calculates & returns the nth term of a fibonacci sequence
ll fibonacci_term(ll n)
{
    //base case - zero is actually an invalid index for our program
    if((n == 0)||(n == 1)||(n==2))  return 1;
    
    //initialize matrix
    matrix M(T, vector<ll>(T));
    M[0][0] = 1;
    M[0][1] = 1;
    M[1][0] = 1;
    M[1][1] = 0;

    matrix result = power_two_by_two(M,n);
    
    return (result[0][1] % MASK);
}

int main()
{
    //the index we want to find the nth fibonacci term for
    ll index = INDEX;
    
    //start the time
    const clock_t begin_time = clock();
    
    //get the nth term
    ll nth_term = fibonacci_term(index);
    
    //measure the elapsed time
    float elapsed_time = float(clock () - begin_time) / CLOCKS_PER_SEC;
    
    printf("The fibonacci sequence at index %llu is %llu, and the operation took %lf seconds\n", index, nth_term, elapsed_time);
    
    return 0;
}
