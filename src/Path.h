/*
 * path.h
 *
 *  Created on: 30-nov.-2013
 *      Author: arno
 */

#include <iostream>
#include <vector>

#ifndef PATH_H_
#define PATH_H_

class Path {
public:
	Path(int initialNumber);
	std::string toString() const;
	void push_number(int num);
	int pop_number();
	bool operator==(const Path& path2) const;
	Path operator++();
	Path operator--();
private:
	std::vector<int> numbers_;

};

std::ostream& operator << (std::ostream& out, Path p);



#endif /* PATH_H_ */
