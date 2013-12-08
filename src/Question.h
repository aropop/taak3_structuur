/*
 * Question.h
 *
 *  Created on: 10-nov.-2013
 *      Author: arno
 */
#include <iostream>
#include <sstream>
#include "Path.h"

#ifndef QUESTION_H_
#define QUESTION_H_



class Question {
public:

	enum QuestionType {
		CHOICE,
		TEXT,
		BOOL,
		SCALE,
		GROUP
	};


	Question(Path id, std::string& question);
	Question();
	virtual ~Question();

	void set_question_string(std::string& new_question);

	virtual std::string get_question_file_string() const;
	virtual std::string get_string() const;

	virtual void set_answers(std::string * answers, int amount);

	static std::string get_type_string(QuestionType type);

	Path increase_id();
	Path decrease_id();

	void setId(Path id) {
		id_ = id;
	}

	QuestionType getType() const {
		return type_;
	}


	std::string question_string;

	bool copied;
protected:
	Path id_;
	QuestionType type_;


};



std::ostream& operator<< (std::ostream& out, Question& q);

#endif /* QUESTION_H_ */
