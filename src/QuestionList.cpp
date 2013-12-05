/*
 * QuestionList.cpp
 *
 *  Created on: 10-nov.-2013
 *      Author: arno
 */

#include "QuestionList.h"
#include "Question.h"
#include "ChoiceQuestion.h"
#include "ScaleQuestion.h"
#include "BoolQuestion.h"
#include <iostream>
#include <fstream>
#include <uuid/uuid.h>

QuestionList::QuestionList(std::string& filename) :
		filename_(filename) {
	//ifstream opbouwen
	std::ifstream input_file(filename_.c_str());
	dirty = false;
	//verschil tussen een bestaand bestand en een niet bestaand bestand
	if (!input_file) {
		//bestand bestaat niet
		uuid_generate(uuid_);
	} else {
		//probeer te lezen van bestand
		try {
			read_from_file(&input_file);
		} catch (std::string& e) {
			//fout in bestand
			std::cout << e << std::endl;
		}
		//file sluiten
		input_file.close();
	}
}

//mostly used for groups
QuestionList::QuestionList() :
		dirty(false) {
}

QuestionList::~QuestionList(void) {
	//verwijder de questions
	for (std::vector<Question *>::iterator i = questions_.begin();
			i != questions_.end(); i++) {
		delete *i;
	}
}

//list commando
void QuestionList::list(std::ostream * out) {
	//over vragen lopen en ze uitprinten
	for (std::vector<Question*>::iterator i = questions_.begin();
			i != questions_.end(); ++i) {
		*out << **i;
	}
}

//add commando met een positie
Path QuestionList::add(Question::QuestionType type,
		std::string& question_string, std::string *answers,
		int amount_of_answers, int position) {
	Question * q;
	if (type == Question::TEXT) {
		q = new Question(current_path_.cons(Path(position)), question_string);
	} else if (type == Question::CHOICE) {
		q = new ChoiceQuestion(current_path_.cons(Path(position)), question_string, answers,
				amount_of_answers);
	} else if (type == Question::BOOL) {
		q = new BoolQuestion(current_path_.cons(Path(position)), question_string);
	} else {
		throw std::string(
				"You have to specify more for these type of questions");
	}
	return add(q, position);
}

//overloaden om add zonder positie mogelijk te maken
Path QuestionList::add(Question::QuestionType type,
		std::string& question_string, std::string *answers,
		int amount_of_answers) {
	return add(type, question_string, answers, amount_of_answers,
			amountOfQuestions() + 1);
}

//hulp functie die uuid omzet
std::string uuid_to_string(char * character_array) {
	std::string uuid_string;
	uuid_string.append(character_array, 36);
	return uuid_string;
}

//save commando
void QuestionList::save() {
	//output file openen
	std::fstream output_file(filename_.c_str(), std::ofstream::out);
	char uuid_str[36];
	uuid_unparse(uuid_, uuid_str);
	//header wegschrijven
	output_file << "VERSION 2" << std::endl << "ID " << uuid_to_string(uuid_str)
			<< std::endl << "STEPS " << amountOfQuestions() << std::endl;
	//vragen wegschrijven
	for (std::vector<Question *>::iterator i = questions_.begin();
			i != questions_.end(); i++) {
		output_file << (**i).get_question_file_string();
	}
	//sluiten
	output_file.close();
	//ql is niet meer dirty want is juist weggeschreven
	dirty = false;
}

//hulp functie die zegt of een bepaalde positie binnen het bereik ligt
bool QuestionList::in_range(int position) {
	return ((0 < position) && (position < (amountOfQuestions() + 1)));
}

//geeft de question string door
std::string QuestionList::get_question_string(int index) {
	return questions_.at(index)->question_string;
}

//edit commando voor question strings
void QuestionList::edit(int question_number, std::string& new_question_string) {
	questions_.at(question_number)->set_question_string(new_question_string);
	dirty = true;
}

//edit commando voor choices
void QuestionList::edit_choice(int question_number, std::string* new_answers,
		int amount) {
	questions_.at(question_number)->set_answers(new_answers, amount);
	dirty = true;
}

//getter voor amount of questions
int QuestionList::amountOfQuestions() const {
	return questions_.size();
}

//delete commando
void QuestionList::delete_question(int question_number) {
	//avoid memory leaks
	delete questions_.at(question_number);
	questions_.erase(questions_.begin() + question_number);
}

//functie die het bestand uitleest en het object invult
void QuestionList::read_from_file(std::ifstream * input_file) {
	std::stringstream ss;
	std::string current_line, current_identifier;
	getline(*input_file, current_line);
	//bekijk de versie
	if (current_line.compare("VERSION 2") == 0
			|| current_line.compare("VERSION 1") == 0) {
		getline(*input_file, current_line);
		ss.clear();
		ss.str(current_line);
		ss >> current_identifier;
		//bekijk het id
		if (current_identifier.compare("ID") == 0) {
			//uuid van tekst naar uuid_t omzetten
			char uuid_txt[36];
			ss >> uuid_txt;
			uuid_parse(uuid_txt, uuid_);

			//size van de lijst uitlezen

			getline(*input_file, current_line);
			ss.clear();
			ss.str(current_line);
			ss >> current_identifier;
			int total_questions(0);
			ss >> total_questions;

			int counter(1);
			//deze dan verder invullen
			while (total_questions >= counter) {

				getline(*input_file, current_line);
				ss.clear();
				ss.str(current_line);

				int question_number;
				std::string question_string, question_type;

				ss >> question_number;
				ss >> question_type;

				//verschil tussen choice en text questions
				if (question_type.compare(
						Question::get_type_string(Question::CHOICE)) == 0) {

					int amount_of_answers;
					ss >> amount_of_answers;
					ss.ignore();
					getline(ss, question_string);
					std::string* answers = new std::string[amount_of_answers];
					ss.clear();

					//lees de choices uit
					for (int i = 0; i < amount_of_answers; ++i) {
						getline(*input_file, answers[i]);
					}
					//maak de vraag aan
					ChoiceQuestion * current_question = new ChoiceQuestion(
							Path(question_number), question_string, answers,
							amount_of_answers);
					questions_.push_back(current_question);
					//scope zal de current_question destructen maar we hebben ze gekopieerd naar het geheugen
					current_question->copied = true;
				} else if (question_type.compare(
						Question::get_type_string(Question::TEXT)) == 0) {
					ss.ignore();
					getline(ss, question_string);
					//moet alleen vraag uitlezen en question object aanmaken
					Question* current_question = new Question(question_number,
							question_string);

					questions_.push_back(current_question);

					ss.clear();

				} else if (question_type.compare(
						Question::get_type_string(Question::BOOL)) == 0) {
					ss.ignore();
					getline(ss, question_string);
					Question* current_question = new BoolQuestion(
							Path(question_number), question_string);
					questions_.push_back(current_question);
					ss.clear();

				} else if (question_type.compare(
						Question::get_type_string(Question::SCALE)) == 0) {
					int min, max;
					ss >> min;
					ss >> max;
					ss.ignore();
					getline(ss, question_string);
					Question* current_question = new ScaleQuestion(
							Path(question_number), question_string, min, max);
					questions_.push_back(current_question);
					ss.clear();
				} else {
					//kent het question type niet
					throw std::string("Unknown question type");
				}
				counter++;

			}

		} else {
			throw std::string("Corrupt file");
		}
	} else {
		throw std::string("Corrupt file");
	}

}

Path QuestionList::add(Question::QuestionType type,
		std::string& question_string, int min, int max) {
	int p = amountOfQuestions() + 1;
	return add(type, question_string, min, max, p);

}

Path QuestionList::add(Question::QuestionType type,
		std::string& question_string, int min, int max, int position) {
	return add(new ScaleQuestion(current_path_.cons(Path(position)), question_string, min,max), position);
}

Path QuestionList::add(Question* question) {
	return add(question, amountOfQuestions() + 1);
}

Path QuestionList::add(Question* question, int position) {
	questions_.insert(questions_.begin() + position - 1, question);
	for (std::vector<Question*>::iterator it = questions_.begin() + position;
			it != questions_.end(); it++) {
		(**it).increase_id();
	}
	dirty = true;
	return Path(position);
}

Path QuestionList::add(Question::QuestionType type,
		std::string& question_string) {
	return add(type, question_string, amountOfQuestions() + 1);
}

Path QuestionList::add(Question::QuestionType type,
		std::string& question_string, int position) {
	Path p(0);
	if (type == Question::TEXT) {
		p = add(new Question(current_path_.cons(Path(position)), question_string), position);
	} else if (type == Question::BOOL) {
		p = add(new BoolQuestion(current_path_.cons(Path(position)), question_string), position);
	} else {
		throw std::string("You have to specify more for this type of question");
	}
	return p;
}

