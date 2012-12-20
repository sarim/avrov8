#include <iostream>
#include <v8.h>
#include "skv8.h"
using namespace v8;

int main(){
loadjs();
//avroparse();
std::cout << avroparse("sari");

std::cout << "\n";

CommitString("সাড়ী","sari");

std::cout << avroparse("sari");

//std::cout << avroparse("sh");
//std::cout << avroparse("sh");
return 0;
}
