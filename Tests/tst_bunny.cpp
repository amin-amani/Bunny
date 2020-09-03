#include <QtTest>

// add necessary includes here

class Bunny : public QObject
{
    Q_OBJECT

public:
    Bunny();
    ~Bunny();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

Bunny::Bunny()
{

}

Bunny::~Bunny()
{

}

void Bunny::initTestCase()
{

}

void Bunny::cleanupTestCase()
{

}

void Bunny::test_case1()
{

}

QTEST_APPLESS_MAIN(Bunny)

#include "tst_bunny.moc"
