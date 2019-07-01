#pragma once

#include <iostream>
#include <AudioFile.h>

using namespace std;

#define NUM_KEYNUMBERS (128)
#define NUM_SECONDS_OF_AUDIO_TO_ALLOCATE (60)
#define FIRST_SAMPLE_KEYNUMBER (64)

//string midi_fn = "D:\\Music\\Composing\\My Heart Will Go On beginning.mid";//"D:\\Music\\Composing\\A Million Dreams experimentation.mid";
string midi_fn = "D:\\Music\\Composing\\A Million Dreams experimentation samples.mid";

/*class sample_wav {
	public:
		sample_wav(string filename_in, unsigned int size_in, signed short *buffer_in, char key_number_in)
			:filename(filename_in), size(size_in), audio_buffer(buffer_in), key_number(key_number_in) {}
		string filename = "";
		unsigned int size = 0;
		short *audio_buffer = NULL;
		char key_number = (char)0;
};*/

class sample_wav_list {
	public:
		sample_wav_list(string name_in);
		string name = "";
		AudioFile<double>* list[NUM_KEYNUMBERS]; // Holds pointers to the sample sounds for each keynumber, which are stored as AudioFiles.
		int add_sample(string filename, char key_number);
};

sample_wav_list::sample_wav_list(string name_in) {
	name = name_in;

	for (int i = 0; i < NUM_KEYNUMBERS; i++) {
		list[i] = NULL;
	}
}



