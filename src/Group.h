/*
 * Group.h
 *
 *  Created on: 2-dec.-2013
 *      Author: arno
 */

#ifndef GROUP_H_
#define GROUP_H_

#include "Question.h"
#include "QuestionList.h"

class Group: public Question {
public:
	Group();
	Group(Path id, std::string& theme_string, Question * question1, Question * question2);
	Path add(Question * question);
	Path add(Question * question, Path& local_path);
	void group_questions(Path q1, Path q2, std::string& theme_string);
	void ungroup(QuestionList& to_add);
	std::string get_question_file_string() const;
	std::string get_string() const;
	~Group();

private:
	QuestionList ql_;
};

#endif /* GROUP_H_ */
