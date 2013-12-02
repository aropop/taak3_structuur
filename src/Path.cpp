/*
 * Path.cpp
 *
 *  Created on: 30-nov.-2013
 *      Author: arno
 */


#include <sstream>
#include "Path.h"



Path::Path(const int initialNumber) {
	push_number(initialNumber);
}

void Path::push_number(const int num){
	numbers_.push_back(num);
}

int Path::pop_number(){
	std::vector<int>::reverse_iterator iter (numbers_.rbegin());
	int ret (*iter);
	numbers_.pop_back();
	return ret;
}

std::string Path::toString() const {
	std::stringstream return_strstr;
	for (std::vector<int>::const_iterator i = numbers_.begin(); i != numbers_.end(); ++i) {
		return_strstr << *i << ".";
	}
	std::string r(return_strstr.str());
	r= r.substr(0, r.length() - 1); //delete the last dot
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

Path Path::operator --(){
	int last(pop_number());
	last--;
	push_number(last);
	return *this;
}
std::ostream& operator << (std::ostream& out, Path p){
	out << p.toString();
	return out;
}



