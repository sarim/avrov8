#include <v8.h>
#include <iostream>
#include <vector>
void loadjs();
std::vector<std::string> recvlists(std::string banglatxt);
//char * avroparse(char * banglatxt);
std::string avroparse(std::string banglatxt);
void CommitString(const char* word,const char* candidate);
