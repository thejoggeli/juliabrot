#include <QtTest>
#include <QCoreApplication>

#include "../JuliabrotApp/vec2.h"

// add necessary includes here

class TestVec2 : public QObject
{
	Q_OBJECT

public:
	TestVec2();
	~TestVec2();

private slots:
	void initTestCase();
	void cleanupTestCase();
	void test_case1();

};

TestVec2::TestVec2()
{

}

TestVec2::~TestVec2()
{

}

void TestVec2::initTestCase()
{

}

void TestVec2::cleanupTestCase()
{

}

void TestVec2::test_case1()
{
	// (3,3) + (1,2) = (4,5)
	Vec2 v1, v2;
	v1 = Vec2(3,3);
	v1.add(1,2);
	v2 = Vec2(4,5);
	QCOMPARE(v1.x, v2.x);
	QCOMPARE(v1.y, v2.y);

	// (3,3) + (-3,-3) = (0,0)
	v1 = Vec2(3,3);
	v1.add(-3,-3);
	v2 = Vec2(0, 0);
	QCOMPARE(v1.y, v2.y);
	QCOMPARE(v1.y, v2.y);

	// (1,1) + (-7,-5) = (-6,-4)
	v1 = Vec2(1,1);
	v1.add(-7,-5);
	v2 = Vec2(-6, -4);
	QCOMPARE(v1.y, v2.y);
	QCOMPARE(v1.y, v2.y);

	// (0,0) + (1, 0) = (1,0)
	v1 = Vec2(0,0);
	v1.add(1,0);
	v2 = Vec2(1,0);
	QCOMPARE(v1.y, v2.y);
	QCOMPARE(v1.y, v2.y);
}

QTEST_MAIN(TestVec2)

#include "tst_testvec2.moc"
