/*
 * Path.cpp
 *
 *  Created on: 30-nov.-2013
 *      Author: arno
 */

#include <sstream>
#include <cctype>
#include "Path.h"

Path::Path(const int initialNumber) {
	push_number(initialNumber);
}

Path::Path() {
}

void Path::push_number(const int num) {
	numbers_.push_back(num);
}

int Path::pop_number() {
	std::vector<int>::reverse_iterator iter(numbers_.rbegin());
	int ret(*iter);
	numbers_.pop_back();
	return ret;
}

bool Path::at_end() const {
	return numbers_.empty();
}

std::string Path::toString() const {
	std::stringstream return_strstr;
	for (std::vector<int>::const_iterator i = numbers_.begin();
			i != numbers_.end(); ++i) {
		return_strstr << *i << ".";
	}
	std::string r(return_strstr.str());
	r = r.substr(0, r.length() - 1); //delete the last dot
	return r;
}

bool Path::operator ==(const Path& path2) const {
	return toString().compare(path2.toString()) == 0;
}

Path Path::operator ++() {
	int last(pop_number());
	last++;
	push_number(last);
	return *this;
}

Path Path::operator --() {
	int last(pop_number());
	last--;
	push_number(last);
	return *this;
}
std::ostream& operator <<(std::ostream& out, Path p) {
	out << p.toString();
	return out;
}

Path Path::cons(Path to_cons) {
	Path ret(*this);
	while (!to_cons.at_end()) {
		ret.push_number(to_cons.pop_front_number());
	}
	return ret;
}

bool Path::empty() const {
	return numbers_.empty();
}

int Path::length() const {
	return numbers_.size();
}

int Path::peek_number() {
	return numbers_.back();
}

int Path::pop_front_number() {
	std::vector<int> new_vect;
	//this can only be done when the size is bigger dan 1
	//which can be checked by length procedure
	for (std::vector<int>::iterator it = (1 + numbers_.begin());
			it != numbers_.end(); ++it) {
		new_vect.push_back(*it);
	}
	int ret(numbers_.front());
	numbers_ = new_vect;
	return ret;
}

std::istream& operator>>(std::istream& in, Path &p) {
	char cur;
	cur = in.get();
	while(cur == ' '){ //read till you find something else than " "
		cur = in.get();
	}
	bool last(false); //true is a number, false is a dot
	while ((cur != ' ') && (cur != '\n') && !in.eof()) {
		if (last) {
			if (cur == '.') { //skip and jump to next
				cur = in.get();
				last = false;
			} else {
				throw std::string("Invallid path");
			}
		} else {
			if (isdigit(cur)) {
				p.push_number(cur - 48);
				last = true;
				cur = in.get();
			} else {
				throw std::string("Invallid path");
			}
		}
	}
	return in;
}

int Path::peek_front() const {
	return numbers_.front();
}

void Path::push_front_number(int num) {
	numbers_.insert(numbers_.begin(), num);
}






