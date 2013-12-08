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
		Question* question2) :
		Question(id, theme_string) {
	question1->setId(id.cons(Path(1)));
	question2->setId(id.cons(Path(2)));
	ql_.add(question1);
	ql_.add(question2);
	ql_.setCurrentPath(id_);
	type_ = GROUP;
}

Path Group::add(Question* question) {
	return id_.cons(ql_.add(question));
}

void Group::ungroup(QuestionList& to_add) {
	//TODO implement
}

void Group::group_questions(Path q1, Path q2, std::string& theme_string) {
	ql_.group(q1, q2, theme_string);
}

std::string Group::get_question_file_string() const {
	std::stringstream ss;
	ss << id_.toString() << " " << Question::get_type_string(type_) << " "
			<< ql_.length() << " " << question_string << std::endl;
	ql_.save(ss);
	return std::string(" ");
}

std::string Group::get_string() const {
	std::stringstream ss;
	ss << id_.toString() << " " << Question::get_type_string(type_) << " "
			<< question_string << std::endl;
	ss << "-----" << std::endl;
	ql_.list(&ss);
	ss << "------" << std::endl;
	return ss.str();
}

Path Group::add(Question* question, Path& local_path) {
	return id_.cons(ql_.add(question, local_path));
}

Group::~Group() {
	//will call the destructor of the questionlist so that will handle the correct deletion
}

