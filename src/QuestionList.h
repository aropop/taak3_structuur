/*
 * QuestionList.h
 *
 *  Created on: 10-nov.-2013
 *      Author: arno
 */
#include "Question.h"
#include <iostream>
#include <fstream>
#include <uuid/uuid.h>
#ifndef QUESTIONLIST_H_
#define QUESTIONLIST_H_

class QuestionList {
public:
	QuestionList(std::string& filename);
	QuestionList();
	~QuestionList();

	//commando's
	void list(std::ostream * out);

	int add(Question::QuestionType type, std::string& question_string,
			std::string *answers, int amount_of_answers);
	int add(Question::QuestionType type, std::string& question_string,
			std::string *answers, int amount_of_answers, int position);
	int add(Question::QuestionType type, std::string& question_string, int min,
			int max);
	int add(Question::QuestionType type, std::string& question_string, int min,
			int max, int position);

	void edit(int question_number, std::string& new_question_string);

	void edit_choice(int question_number, std::string* new_answers, int amount);

	void delete_question(int question_number);

	void save();

	//hulp
	bool dirty;
	bool in_range(int position);
	std::string get_question_string(int index);
	int amountOfQuestions() const;

private:
	std::string filename_;
	std::vector<Question*> questions_;
	uuid_t uuid_;

	//hulp
	void read_from_file(std::ifstream * input_file);

};

#endif /* QUESTIONLIST_H_ */
