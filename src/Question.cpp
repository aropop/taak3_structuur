/*
 * Question.cpp
 *
 *  Created on: 10-nov.-2013
 *      Author: arno
 */

#include "Question.h"
#include <iostream>


//Constructor meestal gebruikt voor type
Question::Question(Path id, std::string& question) :
		question_string(question), id_(id), type_(TEXT){

}

Question::Question() : id_(Path(0)){

}

//Destructor
Question::~Question(){

}
//verander de question string
void Question::set_question_string(std::string& new_question) {
	question_string = new_question;
}

//hulp functies voor het aanpassen van het id
Path Question::increase_id() {
	return ++id_;
}

Path Question::decrease_id() {
	return --id_;
}

//zorgt voor een gemakkelijk output
std::ostream& operator<<(std::ostream& out, Question& q) {
	out << q.get_string();
	return out;
}

std::string Question::get_question_file_string() const {
	return get_string();
}

std::string Question::get_string() const {
	std::stringstream ss;
	ss << id_.toString() << " " << Question::get_type_string(type_) << " " << question_string;
	return ss.str();
}

void Question::set_answers(std::string * answers, int amount) {
	throw std::string("Kan geen antwoorden toevoegen voor dit soort vraag!");
}


