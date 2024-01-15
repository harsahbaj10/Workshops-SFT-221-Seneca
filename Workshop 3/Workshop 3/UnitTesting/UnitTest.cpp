#include "pch.h"
#include "CppUnitTest.h"
//#include "coustomer_r.h"
#include "customer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace harsahbajSft3;

namespace PostalCodeTest
{
	TEST_CLASS(PostalCodeTest)
	{
	public:

		/******* Black-box ********/

		//This test aims to verify if a normal input
		//can yield an uppercase string of a postal code, 
		//and if the function will return true.
		TEST_METHOD(BlackboxTest1)
		{
			char test[] = "A1B 3C4";
			bool result = testPostalCode(test);
			Assert::AreEqual("A1B 3C4", test);
			Assert::AreEqual(true, result);
		}

		//This test aims to verify if a normal input with
		//several spaces in the string can yield an uppercase string of a postal code,
		//and if the function will return true.
		TEST_METHOD(BlackboxTest2)
		{
			char test[] = "a1b       3c4";
			bool result = testPostalCode(test);
			Assert::AreEqual("A1B 3C4", test);
			Assert::AreEqual(true, result);
		}

		//This test aims to verify 
		//if an invalid input without any tabs or spaces within the string will not be modified,
		//and if the function will return false.
		TEST_METHOD(BlackboxTest3)
		{
			char test[] = "a1b3C4";
			bool result = testPostalCode(test);
			Assert::AreEqual("a1b3C4", test);
			Assert::AreEqual(false, result);
		}

		//Test to see if an invalid input without several spaces 
		//in front of the string will not be modified, and if the function will return false.
		TEST_METHOD(BlackboxTest4)
		{
			char test[] = "    a1b 3C4";
			bool result = testPostalCode(test);
			Assert::AreEqual("    a1b 3C4", test);
			Assert::AreEqual(false, result);

		}

		//Test to see if an invalid input with several tabs and spaces
		//at the end of the string will not be modified, and if the function will return false.
		TEST_METHOD(BlackboxTest5)
		{
			char test[] = "a1b 3C4					";
			bool result = testPostalCode(test);
			Assert::AreEqual("a1b 3C4					", test);
			Assert::AreEqual(false, result);
		}

		//This test aims to verify if an invalid input with a space
		//at the 0st index of the string will not be modified, and if the function will return false.
		TEST_METHOD(BlackboxTest6)
		{
			char test[] = " 1b 3C4";
			bool result = testPostalCode(test);
			Assert::AreEqual(" 1b 3C4", test);
			Assert::AreEqual(false, result);
		}

		//This test aims to verify if an invalid input with a space
		//at the 1st index of the string will not be modified, and if the function will return false.
		TEST_METHOD(BlackboxTest7)
		{
			char test[] = "a b 3C4";
			bool result = testPostalCode(test);
			Assert::AreEqual("a b 3C4", test);
			Assert::AreEqual(false, result);
		}

		//This test aims to verify if an invalid input with a space
		//at the 2ed index of the string will not be modified, and if the function will return false.
		TEST_METHOD(BlackboxTest8)
		{
			char test[] = "a1  3C4";
			bool result = testPostalCode(test);
			Assert::AreEqual("a1  3C4", test);
			Assert::AreEqual(false, result);
		}

		//This test aims to verify if an invalid input with a space
		//at the 4th index of the string will not be modified, and if the function will return false.
		TEST_METHOD(BlackboxTest9)
		{
			char test[] = "a1b  C4";
			bool result = testPostalCode(test);
			Assert::AreEqual("a1b  C4", test);
			Assert::AreEqual(false, result);
		}

		//This test aims to verify if an invalid input with a space
		//at the 5th index of the string will not be modified, and if the function will return false.
		TEST_METHOD(BlackboxTest10)
		{
			char test[] = "a1b 3 4";
			bool result = testPostalCode(test);
			Assert::AreEqual("a1b 3 4", test);
			Assert::AreEqual(false, result);
		}



		/*******   White-box   *******/

		//Test to see if an invalid input with more than 50 characters
		//in the string will not cause a crash and the function will return false.
		TEST_METHOD(WhiteboxTest1)
		{
			char test[] = "0123456789012345678901234567890123456789012345678901234567890123456789";
			bool result = testPostalCode(test);
			Assert::AreEqual("0123456789012345678901234567890123456789012345678901234567890123456789", test);
			Assert::AreEqual(false, result);
		}

		//Test to see if an invalid input with a newline character in the string
		//will not cause a crash and the function will return false.
		TEST_METHOD(WhiteboxTest2)
		{
			char test[] = "\n";
			bool result = testPostalCode(test);
			Assert::AreEqual("\n", test);
			Assert::AreEqual(false, result);
		}

		//Test to see if an invalid input with just a space in the string will
		//not cause a crash and the function will return false.
		TEST_METHOD(WhiteboxTest3)
		{
			char test[] = " ";
			bool result = testPostalCode(test);
			Assert::AreEqual(" ", test);
			Assert::AreEqual(false, result);
		}

		//Test to verify that if an invalid input is NULL, 
		//the function will not result in a crash and will return false.
		TEST_METHOD(WhiteboxTest4)
		{
			char test[] = { 0 };
			bool result = testPostalCode(test);
			Assert::AreEqual("", test);
			Assert::AreEqual(false, result);
		}


	};
}
