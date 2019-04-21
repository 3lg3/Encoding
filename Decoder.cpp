#include <iostream>
#include "Decoder.h"
#include <string>

#include <stdio.h>


Decoder::Decoder(string huff_file_path) {
	file_open = huff_file_path;
}

void Decoder::buildFrequencyTableFromFile() {
	for (int i = 0; i < 256; i++) {
        	frequency_table[i] = 0;
        }
	FILE * fd = fopen(file_open.c_str(), "r");
	short int num;
	fread(&num, sizeof(short int),1,fd);
	for (int i = 0; i < num; i++) {
		unsigned char val;
		fread(&val,sizeof(char),1,fd);
		int freq;
		fread(&freq,sizeof(int),1,fd);
		frequency_table[val] = freq;
	}
}

//Creates a min-heap and builds the Huffman tree
void Decoder::decode() {
	buildFrequencyTableFromFile();
	int i;
	TreeNode *e;
	for (i = 0; i < 256; i++) {
		if (frequency_table[i] > 0) {
			e = new TreeNode((char) i, frequency_table[i]);
			mh->insert(e);
		}
	}
	t->buildTree(mh);
	t->generateCodes();
}

//Writes the uncompressed file and save it as file_path
void Decoder::writeUncompressedFile(string file_path) {
	unsigned char code;
	FILE * fd = fopen(file_open.c_str(), "r");
	short int num;
        fread(&num, sizeof(short int),1,fd);
	int total = 0;
        for (int i = 0; i < num; i++) {
                char val;
                fread(&val,sizeof(char),1,fd);
                int freq;
                fread(&freq,sizeof(int),1,fd);
		total = total + freq;
        }
	FILE * fs = fopen(file_path.c_str(),"w");
	int c;
	int n;
	int count = 0;
	TreeNode * root = t->getRoot();
	while ((c = fgetc(fd)) != EOF) {
		for (n = 0; n < 8; n++) {
			/*if (root->isLeafNode()) {
				code = root->getVal();
				fwrite(&code,sizeof(char),1,fs);
				root = t->getRoot();
			}*/
			
			if (getbit((char)c,n) == true) {
				if (root->isLeafNode()) {
                                	code = root->getVal();
					if (count < total) {
                                		fwrite(&code,sizeof(char),1,fs);
						count ++;
					}
					root = t->getRoot();
				}
				root = root->getLeft();
                        }
			
			else if (getbit((char)c,n) == false) {
				if (root->isLeafNode()) {
                                        code = root->getVal();
                                        if (count < total) {
						fwrite(&code,sizeof(char),1,fs);
						count++;
					}
					root = t->getRoot();	
                                }
				root = root->getRight();
			}
		}
	}
	fclose(fd);
	fclose(fs);
}

Decoder::~Decoder() {
	delete t;
	delete mh;
}

