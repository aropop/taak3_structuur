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
//	Path p1;
//	Path p2;
//	std::cin >> p1;
//	std::cin >> p2;
//	std::cout << p1.toString() << p2.toString();
//
//	std::cout << "hihi";


	std::string fn (args[1]); //bestandsnaam nemen
	QuestionList ql = QuestionList(fn);
	Parser pa(&std::cin, &std::cout, &ql);
	return 0;
}
