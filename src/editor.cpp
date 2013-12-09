/*
 * editor.cpp
 *
 *  Created on: 10-nov.-2013
 *      Author: arno
 */

#include "QuestionList.h"
#include "Parser.h"
#include "Path.h"
#include <iostream>

int main(int argc, char * args[]) {
//	Path p1(1);
//	Path p2(2);
//	p1.push_front_number(3);
//	Path p3;
//	Path p4 =p3.cons(p1);
//	std::cout << p4.toString();
//
//	std::cout << "hihi";


	std::string fn (args[1]); //bestandsnaam nemen
	QuestionList ql = QuestionList(fn);
	Parser pa(&std::cin, &std::cout, &ql);
	return 0;
}
