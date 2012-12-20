#First Install V8
	brew install v8

#compile the library
	c++ -shared -lv8 skv8.cpp -o libskv8.so

#compile the test code
	c++ -L. -lskv8 skv8test.cpp

#run the test code
	./a.out


NB: avrov8.cpp and avrov8.h is the skv8.cpp with the jni bridge included. Basically skv8.cpp is for testing, after test is done changes should to exported to avrov8.cpp.
