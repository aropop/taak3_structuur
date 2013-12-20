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


	std::string fn (args[1]); //bestandsnaam nemen
	QuestionList ql = QuestionList(fn);
//	std::cout << ql.getQuestion(p)->get_asking_string() << std::endl;
	Parser pa(&std::cin, &std::cout, &ql);
	return 0;
}
