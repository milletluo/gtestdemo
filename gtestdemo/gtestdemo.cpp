// gtestdemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <gtest\gtest.h>
#include <iostream>

int Foo(int a, int b) // ��a��b�����Լ��
{
	if (a == 0 || b == 0)
	{
		throw "don't do that";
	}
	int c = a % b;
	if (c == 0)
		return b;
	return Foo(b, c);
}

class FooEnvironment : public testing::Environment
{
public:
	virtual void SetUp()
	{
		std::cout << "Foo FooEnvironment SetUP" << std::endl;
	}
	virtual void TearDown()
	{
		std::cout << "Foo FooEnvironment TearDown" << std::endl;
	}
};

// class FooTest : public testing::Test {
// protected:
// 	static void SetUpTestCase() {
// 		shared_resource_ = new;
// 	}
// 	static void TearDownTestCase() {
// 		delete shared_resource_;
// 		shared_resource_ = NULL;
// 	}
// 	// Some expensive resource shared by all tests.
// 	static T* shared_resource_;
// };

// class FooCalcTest:public testing::Test
// {
// protected:
// 	virtual void SetUp()
// 	{
// 		m_foo.Init();
// 	}
// 	virtual void TearDown()
// 	{
// 		m_foo.Finalize();
// 	}
// 
// 	FooCalc m_foo;
// };
// 
// TEST_F(FooCalcTest, HandleNoneZeroInput)
// {
// 	EXPECT_EQ(4, m_foo.Calc(12, 16));
// }
// 
// TEST_F(FooCalcTest, HandleNoneZeroInput_Error)
// {
// 	EXPECT_EQ(5, m_foo.Calc(12, 16));
// }

TEST(FooTest, HandleNoneZeroInput)
{
	EXPECT_EQ(2, Foo(4, 10)) << "Vectors x and y differ at index ";  // ʧ��ʱ����������ִ��
	//EXPECT_EQ(6, Foo(30, 18)); 
	//ASSERT_EQ(5, Foo(25, 5));// ʧ��ʱ����ǰ��������
	//EXPECT_EQ(2, Foo(16, 18)); 
}

TEST(FooTest, HandleZeroInput)
{
	EXPECT_ANY_THROW(Foo(10, 0));
	EXPECT_THROW(Foo(0, 5), char*);
}

bool MutuallyPrime(int m, int n)
{
	return Foo(m , n) > 1;
}

TEST(PredicateAssertionTest, Demo)
{
	int m = 3, n = 6;
	EXPECT_PRED2(MutuallyPrime, m, n);//MutuallyPrime����ֵ��falseʱ�������m,n
}

testing::AssertionResult AssertFoo(const char* m_expr, const char* n_expr, const char* k_expr, int m, int n, int k) {
	if (Foo(m, n) == k)
		return testing::AssertionSuccess();
	testing::Message msg;
	msg << m_expr << " �� " << n_expr << " �����Լ��Ӧ���ǣ�" << Foo(m, n) << " �����ǣ�" << k_expr;
	return testing::AssertionFailure(msg);
}

TEST(AssertFooTest, HandleFail)
{
	EXPECT_PRED_FORMAT3(AssertFoo, 3, 9, 2);
}

TEST(StringCmpTest, Demo)
{
	char* pszCoderZh = "CoderZh";
	wchar_t* wszCoderZh = L"CoderZh";
	std::string strCoderZh = "CoderZh";
	std::wstring wstrCoderZh = L"CoderZh";

	EXPECT_STREQ("CoderZh", pszCoderZh);
	EXPECT_STREQ(L"CoderZh", wszCoderZh);

	EXPECT_STRNE("CnBlogs", pszCoderZh);
	EXPECT_STRNE(L"CnBlogs", wszCoderZh);

	EXPECT_STRCASEEQ("coderzh", pszCoderZh);
	//EXPECT_STRCASEEQ(L"coderzh", wszCoderZh);    ��֧��

	EXPECT_STREQ("CoderZh", strCoderZh.c_str());
	EXPECT_STREQ(L"CoderZh", wstrCoderZh.c_str());
}

TEST(ExplicitTest, Demo)
{
	//ADD_FAILURE() << "Sorry"; // None Fatal Asserton����������ִ�С�

	//FAIL(); // Fatal Assertion��������ִ�иð�����

	SUCCEED();
}

int main(int argc, char* argv[])
{
	testing::AddGlobalTestEnvironment(new FooEnvironment);
	testing::InitGoogleTest(&argc, argv);

	RUN_ALL_TESTS();
	system("pause");//��ͣ����̨�����ڵ��Թ۲죻Ҳ����cmd���������ɵ�exe
	return 0;
	//return RUN_ALL_TESTS();
}

// int _tmain(int argc, _TCHAR* argv[])
// {
// 	return 0;
// }

