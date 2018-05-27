
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include"file_treatment.h"

using namespace std;

int main(int argc, char const *argv[])
{
	//std::string pass = argv[0];
	//std::string flag = argv[1];
	srand(time(NULL));
	string a = argv[2];

	if (a == "enc") {
		//cout << "i am encrypting";
		std::vector<Site> v = output_temp_to_vector();
		vector_to_file(v, argv[1]);
		return 1;
	}
	if (a == "dec") {
		std::vector<Site> v = file_to_vector(argv[1]);
		vector_to_temp_output(v);
		return 1;
		//cout << "i am decrypting";
	}
	else
		return 0;

}