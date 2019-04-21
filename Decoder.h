#ifndef DECODER_H
#define DECODER_H

#include <string>
#include "MinHeap.h"
#include "HuffTree.h"
using namespace std;



class Decoder
{
	private:
		unsigned frequency_table[256];
		// You need to add more class memeber and methods
		string file_open;
		MinHeap * mh = new MinHeap();
                HuffTree * t = new HuffTree();
	public:
		//huff_file_path is the input (encoded) file that we 
		//want to decode
		bool getbit(char c, int n ) {
			return (c >> (7-n)) & 1;
		}
		Decoder(string huff_file_path);

		//Fills up the frequency_table array where frequency_table[i] 
		//will contain the frequency of char with ASCII code i			
		//This method will read the header of the encoded file to 
		//extract the chars and their frequency
		void buildFrequencyTableFromFile();

		//Creates a min-heap and builds the Huffman tree
		void decode();

		//Writes the uncompressed file and save it as file_path
		void writeUncompressedFile(string file_path);

		~Decoder();

};

#endif
