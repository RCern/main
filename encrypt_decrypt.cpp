// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "encryption.h"

class Site
{
private:
	std::string _username;
	std::string _password;
	std::string _site_name;
public:

	Site(std::string username, std::string password, std::string site_name) :_username(username), _password(password), _site_name(site_name) {}
	std::string getSiteName() { return _site_name; }
	std::string getPassword() { return _password; }
	std::string getUsername() { return _username; }
	void changeUsername(const std::string &changed) { _username = changed; }
	void changeSiteName(const std::string &changed) { _site_name = changed; }
	void changePassword(const std::string &changed) { _password = changed; }

	~Site() {}

};

int get_file_lines(std::ifstream &file) {
	unsigned int i = 0;
	std::string line;
	while (std::getline(file, line)) {
		i++;
	}
	return i;
}


bool vector_to_file(std::vector<Site> &vect, const std::string &pass) {
	std::ofstream us_k;
	us_k.open("us_k.txt");
	std::ofstream us_v;
	us_v.open("us_v.txt");
	std::ofstream us_c;
	us_c.open("us_c.txt");

	std::ofstream p_k;
	p_k.open("p_k.txt");
	std::ofstream p_v;
	p_v.open("p_v.txt");
	std::ofstream p_c;
	p_c.open("p_c.txt");
	
	std::ofstream s_k;
	s_k.open("s_k.txt");
	std::ofstream s_v;
	s_v.open("s_v.txt");
	std::ofstream s_c;
	s_c.open("s_c.txt");

	std::ofstream ivs;
	ivs.open("iv.txt");

	for (auto i = vect.begin(); i != vect.end(); ++i) {
		encrypt_key(pass, i->getUsername(), us_k, us_v, us_c, ivs);

		encrypt_key(pass, i->getPassword(), p_k, p_v, p_c, ivs);
	
		encrypt_key(pass, i->getSiteName(), s_k, s_v, s_c, ivs);
		
	}
	us_k.close();
	us_v.close();
	us_c.close();
	
	p_k.close();
	p_v.close();
	p_c.close();
	
	s_k.close();
	s_v.close();
	s_c.close();

	ivs.close();

	return 1;
}
std::vector<std::string> return_from_path(const std::string &path) {
	std::vector<std::string> to_return;
	std::ifstream file;
	unsigned int file_size = 0;
	std::string line;

	file.open(path);
		while (std::getline(file, line)) {
			to_return.push_back(line);
		}
	file.close();
	return to_return;
}
unsigned int min(unsigned int a, unsigned int b, unsigned int c) {

	unsigned int min = 0;
	for (unsigned int i = 0; i < 3; i++) {
		if (a < b)
		{
			min = a;
			b = c;
		}
		else {
			min = b;
			a = c;
		}
	}

	return min;
}
std::vector<Site> file_to_vector(const std::string &password) {
	std::vector<Site> vector;
	std::vector<std::string> user_ciphers, user_keys, user_ivs;
	std::vector<std::string> pass_ciphers, pass_keys, pass_ivs;
	std::vector<std::string> sname_ciphers, sname_keys, sname_ivs;
	std::vector<std::string> ivs;
	std::string pass, username, sname;
	user_ciphers = return_from_path("us_c.txt");
	user_keys = return_from_path("us_k.txt");
	user_ivs = return_from_path("us_v.txt");

	pass_ciphers = return_from_path("p_c.txt");
	pass_keys = return_from_path("p_k.txt");
	pass_ivs = return_from_path("p_v.txt");

	sname_ciphers = return_from_path("s_c.txt");
	sname_keys = return_from_path("s_k.txt");
	sname_ivs = return_from_path("s_v.txt");

	ivs = return_from_path("iv.txt");

	if (user_ciphers.size() == pass_ciphers.size() && pass_ciphers.size() == sname_ciphers.size()) {
		unsigned int x = 0, y = 1, z = 2;
		for (unsigned int i = 0; i < user_ciphers.size(); ++i) {
			username = decrypt_key(user_ciphers[i], user_keys[i], user_ivs[i], password, ivs[x]);
			pass = decrypt_key(pass_ciphers[i], pass_keys[i], pass_ivs[i], password, ivs[y]);
			sname = decrypt_key(sname_ciphers[i], sname_keys[i], sname_ivs[i], password, ivs[z]);

			cout << username << " " << pass << " " << sname << "\n";
			Site a(username, pass, sname);
			vector.push_back(a);
			x += 3;
			y += 3;
			z += 3;
		}

		return vector;
	}
	else
	{
		// error pop-out 
		unsigned int x = 0, y = 1, z = 2;
		unsigned int min_size = min(user_ciphers.size(), pass_ciphers.size(), sname_ciphers.size());
		for (unsigned int i = 0; i < min_size; ++i) {
			username = decrypt_key(user_ciphers[i], user_keys[i], user_ivs[i], password, ivs[x]);
			pass = decrypt_key(pass_ciphers[i], pass_keys[i], pass_ivs[i], password, ivs[y]);
			sname = decrypt_key(sname_ciphers[i], sname_keys[i], sname_ivs[i], password, ivs[z]);

			//cout << username << " " << pass << " " << sname << "\n";
			Site a(username, pass, sname);
			vector.push_back(a);
			x += 3;
			y += 3;
			z += 3;
		}

		return vector;
		
	}
}

int main(int argc, char const *argv[])
{	
	std::string username = "Rko", password = "123485", name = "Facebook", pass = "muie1324";
	std::vector<Site> v;
	
	Site a(username, password, name);
	v.push_back(a);
	Site b("Jel", "def", "ghi");
	v.push_back(b);

	Site c("15", "123", "85");
	v.push_back(c);
	Site d("aze", "fds", "qsd");
	v.push_back(d);
	Site e("zazeaze", "dafaef", "ghfafzazfi");
	v.push_back(e);

	vector_to_file(v, pass);
	std::vector<Site> k;
	k = file_to_vector(pass);
	
	
	/*e.changePassword("xzef");
	cout << e.getPassword() << std::endl;
	*/std::cout << "The End"<<"\n";
	std::getchar();
	return 0;
}
