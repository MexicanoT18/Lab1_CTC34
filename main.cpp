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

void testExpression(string test,string expre){
    Automaton automaton;
    automaton.addExpression(test);
    automaton.possibleStates(expre);
    automaton.print();
    automaton.printStates();
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

void testEClosure(string test){
    Automaton automaton;
    automaton.addExpression(test);
    automaton.print();
    automaton.deleteETransitions();
    automaton.print();
}

void testAutomata2RegExp(string test){
    Automaton automaton;
    automaton.addExpression(test);
    automaton.print();
    automaton.deleteETransitions();
    automaton.print();
    printf("Converted regular expression: |%s|\n", automaton.getRegExpression().c_str());
}

int main()
{
    //testPlus();
    //testConcatenation();
    //testPlusConcat();
    //testKleener();
    //testExpression("a*ba*b","aaaaabaaa");
    /*testAutomata2RegExp("(a+b)*bb(a+b)*");
    int n;
    scanf("%d",&n);
    testAutomata2RegExp("(a(b+c))*");
    scanf("%d",&n);
    testAutomata2RegExp("a*b+b*a");
    scanf("%d",&n);
    testAutomata2RegExp("a*b*c*");
    scanf("%d",&n);*/

    testAutomata2RegExp("(a(b+c))*");

    return 0;
}
