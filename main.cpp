#include <iostream>
#include "Automaton.h"
#include <cstdio>
using namespace std;

void testString(string test){
    printf("Testing %s:\n", test.c_str());
    Automaton automaton;
    automaton.addExpression(test);
    automaton.print();
}

void testConcatenation(){
    string test = "ab";
    testString(test);
    test = "abc";
    testString(test);
    test = "abcd";
    testString(test);
}

void testPlus(){
    string test = "a+b";
    testString(test);
    test = "a+b+c";
    testString(test);
    test = "a+b+c+d";
    testString(test);
}

void testPlusConcat(){
    string test = "ab(c+de)";
    testString(test);
}

void testKleener(){
    string test = "ab+(b+c)*";
    testString(test);
    /*test = "(0+(1(01*(00)*0)*1)*)*";
    testString(test);*/
    test = "(a+(ba(c+a)*))*";
    testString(test);
}

int main()
{
    //testPlus();
    //testConcatenation();
    //testPlusConcat();
    testKleener();
    return 0;
}
