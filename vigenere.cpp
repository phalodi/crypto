
#include <iostream>
#include <string>

int main(int argc, char** argv) {

	if (argc==2) {
		std::string k(argv[1]);
		int d = k.size();
		for(int i=0;i<d;i++) {
			if(!((k[i]>='a' && k[i]<='z')||(k[i]>='A' && k[i]<='Z'))) {
				std::cout << "invalid key" << std::endl;
				return 1;
			}
		}

		std::string p;
		std::getline(std::cin, p);
		int j=0,c;
		for(int i=0;i<p.size();i++) {
			int k1 = k[j];
			if (k1>=97)
				c = (k1-97);
			else
				c = (k1-65);
			if (p[i]>='A' && p[i]<='Z') {
				p[i] = 'A' + ((p[i]-65)+c)%26;
				j++;
			} else if (p[i]>='a' && p[i] <= 'z') {
				p[i] = 'a' + ((p[i]-97)+c)%26;
				j++;
			}

			if (j>=d) {
				j = 0;
			}
		}

		std::cout << p << std::endl;
	} else {
		std::cout << "Number of agruments are less or more" << std::endl;
		return 1;
	}


	return 0;
}
