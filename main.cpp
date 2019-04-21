#include <iostream>
#include <string.h>
#include "MinHeap.h"
#include "Encoder.h"
#include "Decoder.h"
#include <string>
using namespace std;

void printHelp(){
	cout << "Invalid arguments." << endl;
	cout << "Type \"huffman [mode] [arguments]\" where mode and its arguments are one of the following:" << endl;
	cout << "-e [src] [dest]: encode the source file and place the result into the specified destination" << endl;
	cout << "-d [src] [dest]: decode the source file and place the result into the specified destination" << endl;
	exit(1);
}


int main (int argc, char** argv){
	if (argc < 4) {
		printHelp();
	}
	if (strcmp(argv[1],"-e") == 0) {
		string src(argv[2]);
		string dest(argv[3]);
	//	cout << src << "\r\n";
	//	cout << dest << "\r\n";
		//src = src.substr(1,src.length()-2);
		//dest = dest.substr(1,dest.length()-2);
		Encoder * e = new Encoder(src);
		e->encode();
		e->writeEncodedFile(dest);
		delete e;
	}
	else if (strcmp(argv[1], "-d") ==0 ) {
		string src(argv[2]);
		string dest(argv[3]);
		Decoder * d = new Decoder(src);
		d->decode();
		d->writeUncompressedFile(dest);
		delete d;
	}
	else {
		printHelp();
	}
}
