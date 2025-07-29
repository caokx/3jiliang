#include <stdio.h>

#include "CuTest.h"

CuSuite *MemoryGetSuite();
CuSuite *ASN1GetSuite();
//CuSuite* CuStringGetSuite();

void RunAllTests(void)
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    CuSuiteAddSuite(suite, MemoryGetSuite());
    CuSuiteAddSuite(suite, ASN1GetSuite());
    //CuSuiteAddSuite(suite, CuStringGetSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}

int main(void)
{
    RunAllTests();
    getchar();
}
