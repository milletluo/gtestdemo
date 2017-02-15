// gtestdemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <limits.h>
#include <gtest\gtest.h>
#include <iostream>


// Returns true iff n is a prime number.
bool IsPrime(int n) {
	// Trivial case 1: small numbers
	if (n <= 1) return false;

	// Trivial case 2: even numbers
	if (n % 2 == 0) return n == 2;

	// Now, we have that n is odd and n >= 3.

	// Try to divide n by every odd number i, starting from 3
	for (int i = 3; ; i += 2) {
		// We only have to try i up to the squre root of n
		if (i > n/i) break;

		// Now, we have i <= n/i < n.
		// If n is divisible by i, n is not prime.
		if (n % i == 0) return false;
	}

	// n has no integer factor in the range (1, n), and thus is prime.
	return true;
}

// Tests IsPrime()

// Tests negative input.
TEST(IsPrimeTest, Negative) {
	// This test belongs to the IsPrimeTest test case.

	EXPECT_FALSE(IsPrime(-1));
	EXPECT_FALSE(IsPrime(-2));
	EXPECT_FALSE(IsPrime(INT_MIN));
}

// Tests some trivial cases.
TEST(IsPrimeTest, Trivial) {
	EXPECT_FALSE(IsPrime(0));
	EXPECT_FALSE(IsPrime(1));
	EXPECT_TRUE(IsPrime(2));
	EXPECT_TRUE(IsPrime(3));
}

// Tests positive input.
TEST(IsPrimeTest, Positive) {
	EXPECT_FALSE(IsPrime(4));
	EXPECT_TRUE(IsPrime(5));
	EXPECT_FALSE(IsPrime(6));
	EXPECT_TRUE(IsPrime(23));
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);

	RUN_ALL_TESTS();
	system("pause");//暂停控制台，便于调试观察；也可在cmd中运行生成的exe
	return 0;
	//return RUN_ALL_TESTS();
}

// int _tmain(int argc, _TCHAR* argv[])
// {
// 	return 0;
// }

