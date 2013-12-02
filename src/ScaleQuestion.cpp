/*
 * ScaleQuestion.cpp
 *
 *  Created on: 1-dec.-2013
 *      Author: arno
 */

#include "ScaleQuestion.h"

ScaleQuestion::ScaleQuestion() {
	type_ = SCALE;
}

ScaleQuestion::~ScaleQuestion() {
}

int ScaleQuestion::getMin() const {
	return min_;
}

ScaleQuestion::ScaleQuestion(Path id, std::string& question_string, int min,
		int max) : Question(id, question_string),  min_(min), max_(max) {
	type_ = SCALE;
}

bool ScaleQuestion::in_range(int possible_answer) const {
	return (min_ <= possible_answer) && (max_ >= possible_answer);
}

int ScaleQuestion::getMax() const {
	return max_;
}



