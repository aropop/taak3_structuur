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
	Path();
	Path(int initialNumber);
	std::string toString() const;
	void push_number(int num);
	int pop_number();
	bool operator==(const Path& path2) const;
	bool at_end() const;
	Path operator++();
	Path operator--();
	Path cons(Path to_cons);
	bool empty() const;
private:
	std::vector<int> numbers_;

};

std::ostream& operator << (std::ostream& out, Path p);



#endif /* PATH_H_ */
