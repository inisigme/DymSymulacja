#include "parsowanie.h"
using std::string;


GLuint parsowanie(std::string fileName) {

	GLfloat posTable[bufSize][3];
	GLfloat texCoord[bufSize][2];
	GLfloat normalVec[bufSize][3];
	GLfloat outPosTable[bufSize];
	GLfloat outTexCoord[bufSize];
	GLfloat outNormalVec[bufSize];

	string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open())
	{
		int licznik1, licznik2, licznik3;
		std::string pos1S, pos2S, pos3S, pos4S, pos5S;
		GLfloat pos2, pos3, pos4;
		licznik1 = licznik2 = licznik3 = 1;
		//4 linijki do ominiecia
		getline(myfile, line);
		getline(myfile, line);
		getline(myfile, line);
		getline(myfile, line);
		getline(myfile, line);
		std::stringstream ss(line);
		ss >> pos1S;
		while (pos1S.compare("v") == 0)
		{
			//std::stringstream ss(line);
			ss >> posTable[licznik1][0];
			ss >> posTable[licznik1][1];
			ss >> posTable[licznik1][2];
			std::cout << "v   " << posTable[licznik1][0] << "      " << posTable[licznik1][1] << "      " << posTable[licznik1][2] << "      " << std::endl;
			licznik1++;
			getline(myfile, line);
			ss.clear();
			ss.flush();
			ss.str( line );
			pos1S.clear();
			ss >> pos1S;
		}

		while (pos1S.compare("vt") == 0) {
			ss >> texCoord[licznik2][0];
			ss >> texCoord[licznik2][1];
			std::cout << "vt   " << texCoord[licznik2][0] << "      " << texCoord[licznik2][1] << "      " <<  std::endl;
			licznik2++;
			getline(myfile, line);
			ss.clear();
			ss.flush();
			ss.str(line);
			pos1S.clear();
			ss >> pos1S;
		}

		while (pos1S.compare("vn") == 0) {
			ss >> normalVec[licznik3][0];
			ss >> normalVec[licznik3][1];
			ss >> normalVec[licznik3][2];
			std::cout << "vn   " << normalVec[licznik3][0] << "      " << normalVec[licznik3][1] << "      " << normalVec[licznik3][2] << "      " << std::endl;
			licznik3++;
			getline(myfile, line);
			ss.clear();
			ss.flush();
			ss.str(line);
			pos1S.clear();
			ss >> pos1S;
		}

		getline(myfile, line);
		
		int tab[12];
		unsigned int koncowyLicznik = 0;
		while (!myfile.eof()) {
			tab[11] = tab[10] = tab[9] = 0;
			getline(myfile, line);
			ss.clear();
			ss.flush();
			ss.str(line);
			ss >> pos3S;
			unsigned int malyLicznik = 0;
			for (int i = 0; i < 4; i++) {
				pos1S.clear();
				ss >> pos1S;
				std::stringstream ss2(pos1S);
					while (getline(ss2, pos2S, '/'))
					{
						std::stringstream st(pos2S);
						st >> tab[malyLicznik];
						std::cout << tab[malyLicznik] << std::endl;
						malyLicznik++;
					}
					
			}
			std::cout << "sad       " << malyLicznik << std::endl;
			int ile = malyLicznik >> 10 ? 1 : 2;
			// ZMIENIC
			for (int przesuniecie = 0; przesuniecie < 1; przesuniecie++) {
				for (int wiercholek = 0; wiercholek < 3; wiercholek++) {
		//			for (int rodzaj = 0; rodzaj < 3; rodzaj++) {
						outPosTable[koncowyLicznik * 3 + 0] = posTable[tab[przesuniecie * 3 + wiercholek * 3 ]][0];
						outPosTable[koncowyLicznik * 3 + 1] = posTable[tab[przesuniecie * 3 + wiercholek * 3 ]][1];
						outPosTable[koncowyLicznik * 3 + 2] = posTable[tab[przesuniecie * 3 + wiercholek * 3 ]][2];
						std::cout << outPosTable[koncowyLicznik * 3 + 0] << "    " << outPosTable[koncowyLicznik * 3 + 1] << "     " << outPosTable[koncowyLicznik * 3 + 2] << std::endl;
						outTexCoord[koncowyLicznik * 2 + 0] = texCoord[tab[przesuniecie * 3 + wiercholek * 3 + 1]][0];
						outTexCoord[koncowyLicznik * 2 + 1] = texCoord[tab[przesuniecie * 3 + wiercholek * 3 + 1]][1];
						std::cout << outTexCoord[koncowyLicznik * 2 + 0] << "    " << outTexCoord[koncowyLicznik * 2 + 1] << std::endl;
						outNormalVec[koncowyLicznik * 3 + 0] = normalVec[tab[przesuniecie * 3 + wiercholek * 3 + 2]][0];
						outNormalVec[koncowyLicznik * 3 + 1] = normalVec[tab[przesuniecie * 3 + wiercholek * 3 + 2]][1];
						outNormalVec[koncowyLicznik * 3 + 2] = normalVec[tab[przesuniecie * 3 + wiercholek * 3 + 2]][2];
						std::cout << outNormalVec[koncowyLicznik * 3 + 0] << "     " << outNormalVec[koncowyLicznik * 3 + 1] << "     " << outNormalVec[koncowyLicznik * 3 + 2] << std::endl;
						koncowyLicznik++;
		//			}
				}
			}
			malyLicznik = 0;
		}
		GLuint vertexArray;
		GLuint vertexBuffer[3];
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer[0]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
		glBufferData(GL_ARRAY_BUFFER,  koncowyLicznik * sizeof(GLfloat)* 3, outPosTable, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glGenBuffers(1, &vertexBuffer[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[1]);
		glBufferData(GL_ARRAY_BUFFER, koncowyLicznik * sizeof(GLfloat) * 2, outTexCoord, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		glGenBuffers(1, &vertexBuffer[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[1]);
		glBufferData(GL_ARRAY_BUFFER, koncowyLicznik * sizeof(GLfloat) * 3, outNormalVec, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glFlush();
		//delete posTable;
		//delete texCoord;
		//delete normalVec;
		//delete outPosTable;
		//delete outTexCoord;
		//delete outNormalVec;
		glBindVertexArray(0);
		return vertexArray;
	}
	else {
		std::cout << "blad otwarcia pliku" << std::endl;
		getchar();
		return 0;
	}
}