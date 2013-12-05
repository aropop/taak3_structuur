/*
 * Group.cpp
 *
 *  Created on: 2-dec.-2013
 *      Author: arno
 */

#include "Group.h"
#include "QuestionList.h"
#include "Question.h"

Group::Group() {
	type_ = GROUP;

}

Group::Group(Path id, std::string& theme_string, Question* question1,
		Question* question2):Question(id, theme_string) {
	ql_.add(question1);
	ql_.add(question2);
	type_ = GROUP;
}

Path Group::add(Question* question) {
	return id_.cons(ql_.add(question));
}

void Group::ungroup(QuestionList& to_add) {
	//TODO implement
}

Group::~Group() {
	//will call the destructor of the questionlist so that will handle the correct deletion
}

