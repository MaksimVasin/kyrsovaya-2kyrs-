#include "pch.h"
#include "CppUnitTest.h"
#include "../Potok/AdjacencyMatrix.h"
#include "../Potok/AdjacencyMatrix.cpp"
#include "../Potok/LinkedList.h"
#include "../Potok/LinkedList.cpp"

#include <string>
#define TEST_CASE_DIRECTORT GetDirectoryName(__FILE__)
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

string GetDirectoryName(string path)
{
	const size_t last_slash_idx = path.rfind('\\');
	if (std::string::npos != last_slash_idx)
	{
		return path.substr(0, last_slash_idx + 1);
	}
	return "";
}

namespace TestGraphs
{
	TEST_CLASS(TestGraphs)
	{
	public:
		TEST_METHOD(OPEN_FILE)
		{
			string fileName = string(TEST_CASE_DIRECTORT) + "test1.txt";
			AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
			Matrix->createMatrix(fileName);
		}
		TEST_METHOD(not_find_file)
		{
			string fileName = string(TEST_CASE_DIRECTORT) + "netytakogo.txt";
			try
			{
				AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
			}
			catch (std::out_of_range error)
			{
				Assert::AreEqual("file is empty", error.what());
			}
		}
		TEST_METHOD(incorrect_input) // no sourse or drain
		{
			string fileName = string(TEST_CASE_DIRECTORT) + "test0.txt";
			AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
			try
			{
				Matrix->Edmonds_Karp();
			}
			catch (std::out_of_range error)
			{
				Assert::AreEqual("incorrect input", error.what());
			}
		}
		TEST_METHOD(test1)
		{
			string fileName = string(TEST_CASE_DIRECTORT) + "test1.txt";
			AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
			Matrix->createMatrix(fileName);
			Assert::AreEqual((int)5, (int)Matrix->Edmonds_Karp());
		}
		TEST_METHOD(test2)
		{
			string fileName = string(TEST_CASE_DIRECTORT) + "test2.txt";
			AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
			Matrix->createMatrix(fileName);
			Assert::AreEqual((int)5, (int)Matrix->Edmonds_Karp());
		}
		TEST_METHOD(test3)
		{
			string fileName = string(TEST_CASE_DIRECTORT) + "test3.txt";
			AdjacencyMatrix* Matrix = new AdjacencyMatrix(fileName);
			Matrix->createMatrix(fileName);
			Assert::AreEqual((int)10, (int)Matrix->Edmonds_Karp());
		}
	};
}
