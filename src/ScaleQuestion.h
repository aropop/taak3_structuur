/*
 * ScaleQuestion.h
 *
 *  Created on: 1-dec.-2013
 *      Author: arno
 */

#ifndef SCALEQUESTION_H_
#define SCALEQUESTION_H_

#include "Question.h"

class ScaleQuestion: public Question {
public:
	ScaleQuestion();
    ScaleQuestion(Path id, std::string& question_string, int min, int max);
    ~ScaleQuestion();
    bool in_range(int possible_answer) const;
    int getMin() const;
	int getMax() const;

private:
    int min_;
    int max_;
};

#endif /* SCALEQUESTION_H_ */
