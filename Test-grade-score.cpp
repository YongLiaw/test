#include <iostream>
#include <string>
#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
 
#include "grade-score.h"
 
using namespace std;
 
class Test_grade_score : public CppUnit::TestFixture {
public:
 
	static CppUnit::Test *suite() {
		::TestSuite *suiteOfTests = new CppUnit::TestSuite("Test_grade_score");
 
		suiteOfTests->addTest(new CppUnit::TestCaller<Test_grade_score>("Test1 - Tokenizer with valid input string",
				&Test_grade_score::testTokenizer_valid ));
		suiteOfTests->addTest(new CppUnit::TestCaller<Test_grade_score>("Test2 - Tokenizer with blank string",
				&Test_grade_score::testTokenizer_blank ));
 
		suiteOfTests->addTest(new CppUnit::TestCaller<Test_grade_score>("Test3 - Person constructor",
				&Test_grade_score::testPerson));
		suiteOfTests->addTest(new CppUnit::TestCaller<Test_grade_score>("Test4 - Person operator >",
				&Test_grade_score::testPerson_operator_greater ));
 
		return suiteOfTests;
	}
 
	/// Setup method
	void setUp() {}
 
	/// Teardown method
	void tearDown() {}
 
protected:
	void testTokenizer_valid() {
          	Tokenizer tokens("Smith, Paul, 67");
		CPPUNIT_ASSERT(tokens.Size() == 3);
		CPPUNIT_ASSERT(tokens.GetToken() == string("Smith"));
		CPPUNIT_ASSERT(tokens.GetToken() == string("Paul"));
		CPPUNIT_ASSERT(tokens.GetToken() == string("67"));
	}
 
	void testTokenizer_blank() {
          	Tokenizer tokens("    ");
		CPPUNIT_ASSERT(tokens.Size() == 1);
		CPPUNIT_ASSERT(tokens.GetToken() == string.empty());
	}
 
	void testPerson() {
          	Person p("Smith", "Paul", 67);
		CPPUNIT_ASSERT(p.FirstName() == string("Paul");
		CPPUNIT_ASSERT(p.LastName() == string("Smith");
		CPPUNIT_ASSERT(p.Score() == 67);
		CPPUNIT_ASSERT(p.AsString() == string("Smith, Paul, 67"));
	}

	void testPerson_operator_greater() {
          	Person p1("Smith", "Paul", 67);
          	Person p2("Smith", "Paul2", 67);
          	Person p3("King", "John", 89);
          	Person p4("Queen", "Mary", 67);
		CPPUNIT_ASSERT(p1.AsString() == string("Smith, Paul, 67"));
		CPPUNIT_ASSERT(p1.AsString() == string("Smith, Paul2, 67"));
		CPPUNIT_ASSERT(p1.AsString() == string("King, John, 89"));
		CPPUNIT_ASSERT(p1.AsString() == string("Queen, Mary, 67"));
		CPPUNIT_ASSERT(p3 > p1);
		CPPUNIT_ASSERT(p3 > p2);
		CPPUNIT_ASSERT(p3 > p4);
		CPPUNIT_ASSERT(p4 > p1);
		CPPUNIT_ASSERT(p4 > p2);
		CPPUNIT_ASSERT(p1 > p2);
	}
};
