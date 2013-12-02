/*
 * BoolQuestion.cpp
 *
 *  Created on: 1-dec.-2013
 *      Author: arno
 */

#include "BoolQuestion.h"

BoolQuestion::BoolQuestion() :
		Question() {
	type_ = BOOL;
}

BoolQuestion::~BoolQuestion() {
}

BoolQuestion::BoolQuestion(Path id, std::string& question_string):Question(id, question_string) {
	type_ = BOOL;
}

bool BoolQuestion::accepts_character(char ch) {
	return (ch == 'j') || (ch == 'y') || (ch == '1') || (ch == 'n') || (ch == 0);
}

