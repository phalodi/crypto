#include <iostream>
#include <string>
#include <cstdlib>

int main(int argc, char** argv) {

	if (argc==2) {
		int k = atoi(argv[1]);
	
		std::string s;
		std::getline(std::cin, s);

		for(int i=0,n=s.size();i<n;i++) {
			int c = s[i] + k;
			if (s[i]>='A' && s[i] <= 'Z') {
				if (c<='Z')
					s[i] = c;
				else
					s[i] = 'A' +(c-65)%26;
			} else if (s[i]>='a' && s[i]<='z') {
				if (c<='z')
					s[i] = c;
				else
					s[i] = 'a'+(c-97)%26;
			}
		}

		std::cout << s << std::endl;
			
	} else {

		std::cout << "not as per required arguments" << std::endl;
		return 1;
	}



	return 0;

}
