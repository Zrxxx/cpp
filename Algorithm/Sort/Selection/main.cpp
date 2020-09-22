#include "Selection.h"
#include <iostream>
#include <vector>
int main(){
	std::vector<int> arr= {1,9,4,100,50,1,45};

	/*	std::vector<int>::iterator iter = arr.begin();
		std::vector<int>::iterator::value_type a =*begin;
		std::cout << a << std::endl;
	*/
	Selection<std::vector<int>::iterator> s(arr.begin(),arr.end(),arr.size());
	s.print(std::cout);
	s.sort();
	s.print(std::cout);
}
