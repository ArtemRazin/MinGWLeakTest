// Copyright (c) Softanics

#include <windows.h>
#include <stdlib.h>
#include <new> // std::nothrow

void AllocateObject();

void OperatorNewTest();
void OperatorNewArrayTest();

void MallocTest();
void CallocTest();
void ReallocTest();

void HeapAllocTest();

void CallLambda(void (*lambda)());

#define ASSERT(expr) { if (!(expr)) DebugBreak(); }

int main(int argc, char** argv)
{
    CallLambda([]()-> void
    {
        CallLambda([]()-> void
        {
            new int; // DeleakerTest()
            new int; // DeleakerTest()
        });
    });

    AllocateObject();

    OperatorNewTest();
    OperatorNewArrayTest();

    MallocTest();
    CallocTest();
    ReallocTest();

    HeapAllocTest();

    // Mingw CRT doesn't free memory allocated for `argv`, so Deleaker shows the leak
    free(argv);

    return 0;
}

void OperatorNewTest()
{
    int* p = new int; // DeleakerTest()

    int* p1 = new int;
    delete p1;

    char* p2 = new(std::nothrow)char; // DeleakerTest()

    char* p3 = new(std::nothrow)char;
    operator delete(p3, std::nothrow);

    int* p4 = new(std::align_val_t { 64 }) int; // DeleakerTest()

    int* p5 = new(std::align_val_t { 64 }) int;
    operator delete(p5, std::align_val_t { 64 });

    void* p6 = operator new(10, std::align_val_t { 64 }, std::nothrow); // DeleakerTest()

    void* p7 = operator new(10, std::align_val_t { 64 }, std::nothrow);
    operator delete(p7, std::align_val_t { 64 }, std::nothrow);
}

void OperatorNewArrayTest()
{
    int* p = new int[56]; // DeleakerTest()

    int* p1 = new int[57];
    delete[] p1;

    char* p2 = new(std::nothrow) char[1]; // DeleakerTest()

    char* p3 = new(std::nothrow) char[1];
    operator delete[] (p3, std::nothrow);

    int* p4 = new(std::align_val_t { 64 }) int[10]; // DeleakerTest()

    int* p5 = new(std::align_val_t { 64 }) int[10];
    operator delete[](p5, std::align_val_t { 64 });

    void* p6 = operator new[](10, std::align_val_t { 64 }, std::nothrow); // DeleakerTest()

    void* p7 = operator new[](10, std::align_val_t { 64 }, std::nothrow);
    operator delete[](p7, std::align_val_t { 64 }, std::nothrow);
}

void MallocTest()
{
    void* p = malloc(123); // DeleakerTest()

    void* p1 = malloc(124);
    free(p1);
}

void CallocTest()
{
    void* p = calloc(125, 1); // DeleakerTest()

    void* p1 = calloc(126, 1);
    free(p1);
}

void ReallocTest()
{
    void* p = malloc(127);
    p = realloc(p, 128); // DeleakerTest()

    void* p1 = malloc(128);
    p1 = realloc(p1, 129);
    free(p1);
}

void HeapAllocTest()
{
    void* p = HeapAlloc(GetProcessHeap(), 0, 1134); // DeleakerTest()

    void* p1 = HeapAlloc(GetProcessHeap(), 0, 1135);
    HeapFree(GetProcessHeap(), 0, p1);
}

/// Test class
class CSomeClass {};

void AllocateObject()
{
    CSomeClass* someClassPtr = new CSomeClass(); // DeleakerTest()
}

void CallLambda(void (*lambda)())
{
    lambda();
}
