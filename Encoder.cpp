#include <iostream>

#include "Encoder.h"

#include <string>

#include <stdio.h>


Encoder::Encoder(string file) {
	file_path  = file;		
}


//the frequency_table array where frequency_table[i] 
//will contain the frequency of char with ASCII code i          
void Encoder::buildFrequencyTable() {
	for (int i = 0; i < 256; i++) {
		frequency_table[i] = 0;
	}
	FILE * fd = fopen(file_path.c_str(), "r");
	int c;
	while ((c = fgetc(fd)) != EOF) {
		frequency_table[c]++;
	}
	fclose(fd);
}

//Builds the min head and run the encoding algorithm
void Encoder::encode() {
	buildFrequencyTable();
	int i;
	TreeNode * e;
	for (i = 0; i < 256; i++) {	
		if (frequency_table[i] > 0) {
			e = new TreeNode((char) i, frequency_table[i]);
  			mh->insert(e);
		}			
	}	
	t->buildTree(mh);
	t->generateCodes();
	
}

//Generates the encoded file and save it as output_file_path
void Encoder::writeEncodedFile(string output_file_path) {
	int count = 0;
	int i;
	for (i = 0; i < 256; i++) {
		if (frequency_table[i] > 0) {
			count++;	
		}
	}
	FILE * fd = fopen(output_file_path.c_str(), "w");
	unsigned char c;
	short int k;
	k = count;
	fwrite(&k,sizeof(short int),1,fd);
	for (i = 0; i < 256; i++) {
		if (frequency_table[i] > 0) {
			c = i;
			fwrite(&c,sizeof(char),1,fd);
			int x = frequency_table[i];
			/*int valueShifted = (x << 24) |                // Move 4th byte 
						((x << 8) & 0x00ff0000) |  // Move 2nd byte to 3rd
    						((x >> 8) & 0x0000ff00) |  // Move 3rd byte to 2nd
    						( x >> 24);*/
			fwrite(&x, sizeof(int),1,fd);		
			
		}
	}
	FILE * fs = fopen(file_path.c_str(), "r");
	string bit;
	int d;
	while ((d = fgetc(fs)) != EOF) {
                bit = bit.append(t->getCharCode(d));
        }
	fclose(fs);
	int length = bit.length();
        for (int n = 0; n < 8-(length %  8); n++) {
                bit = bit + '0';
        }
        unsigned char  code;
        int m = 0;
        while (m < bit.length()) {
                code = 0;
                int factor = 1;
                for (int k = 0; k < 8; k++) {
                        int x = m / 8;
                        code = code + (bit[7+16*x-m]-48) * factor;
                        m++;
                        factor = factor * 2;
                }
                fwrite(&code,sizeof(char),1,fd);
        }
	fclose(fd);
}

Encoder::~Encoder() {
	delete t;
	delete mh;
}	
