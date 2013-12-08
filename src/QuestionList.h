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
	void list(std::ostream * out) const;

	Path add(Question::QuestionType type, std::string& question_string,
			std::string *answers, int amount_of_answers);
	Path add(Question::QuestionType type, std::string& question_string,
			std::string *answers, int amount_of_answers, Path position);
	Path add(Question::QuestionType type, std::string& question_string, int min,
			int max);
	Path add(Question::QuestionType type, std::string& question_string, int min,
			int max, int position);
	Path add(Question::QuestionType type, std::string& question_string);
	Path add(Question::QuestionType type, std::string& question_string, Path position);
	Path add(Question * question);
	Path add(Question * question, Path position);

	void edit(int question_number, std::string& new_question_string);

	void edit_choice(int question_number, std::string* new_answers, int amount);

	void delete_question(int question_number);

	void save();
	void save(std::ostream& out) const;

	void group(Path& question1, Path& question2, std::string& theme_string);

	//hulp
	bool dirty;
	bool in_range(Path position);
	std::string get_question_string(int index);
	int amountOfQuestions() const;
	Path getCurrentPath() const;
	void setCurrentPath(Path currentPath);
	int length() const;

private:
	std::string filename_;
	std::vector<Question*> questions_;
	uuid_t uuid_;

	Path current_path_;

	//hulp
	void read_from_file(std::ifstream * input_file);

};

#endif /* QUESTIONLIST_H_ */
