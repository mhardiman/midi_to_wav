// midi_to_wav.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <MidiFile.h>
#include <Options.h>
#include "midi_to_wav.h"
#include <math.h>

using namespace std;
using namespace smf;


void keep_window_open() { char c; cin >> c; }


int sample_wav_list::add_sample(string filename, char key_number) {
	// Open file and get audio size.
	AudioFile<double> *audio_file = new AudioFile<double>;
	audio_file->load(filename);

	// Add sample to list.
	if (list[key_number] != NULL) {
		cout << "ERROR: Key number already taken." << endl;
		return 1;
	}
	list[key_number] = audio_file;

	return 0;
}


void setup_audio_file_out(AudioFile<double>* file_out, AudioFile<double>* sample_file) {
	// Get parameters of this audio sample. This program assumes all audio samples have the same parameters.
	int sampleRate = sample_file->getSampleRate();
	int bitDepth = sample_file->getBitDepth();
	int numChannels = sample_file->getNumChannels();

	// Condition the output buffer to match the input samples.
	file_out->setNumChannels(numChannels);
	file_out->setNumSamplesPerChannel(NUM_SECONDS_OF_AUDIO_TO_ALLOCATE * sampleRate);
	file_out->setBitDepth(bitDepth);
	file_out->setSampleRate(sampleRate);
}


int main()
{
	// Read in MIDI file.
	MidiFile midifile;
	midifile.read(midi_fn);
	if (!midifile.status()) {
		cerr << "Error reading MIDI file " << midi_fn << endl;
		exit(1);
	}
	midifile.joinTracks();	
	midifile.doTimeAnalysis();

	// Setup audio samples.
	sample_wav_list sample_list("music_box");

	/*sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_E4.wav", (char)64);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_F#4.wav", (char)66);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_G4.wav", (char)67);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_A4.wav", (char)69);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_B4.wav", (char)71);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_C5.wav", (char)72);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_D5.wav", (char)74);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_E5.wav", (char)76);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_F#5.wav", (char)78);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_G5.wav", (char)79);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_A5.wav", (char)81);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_B5.wav", (char)83);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_C6.wav", (char)84);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_D6.wav", (char)86);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_E6.wav", (char)88);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_F#6.wav", (char)90);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_G6.wav", (char)91);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_A6.wav", (char)93);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_B6.wav", (char)95);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_C7.wav", (char)96);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_D7.wav", (char)98);*/

	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_E4.wav", (char)52);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_F#4.wav", (char)54);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_G4.wav", (char)55);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_A4.wav", (char)57);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_B4.wav", (char)59);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_C5.wav", (char)60);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_D5.wav", (char)62);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_E5.wav", (char)64);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_F#5.wav", (char)66);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_G5.wav", (char)67);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_A5.wav", (char)69);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_B5.wav", (char)71);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_C6.wav", (char)72);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_D6.wav", (char)74);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_E6.wav", (char)76);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_F#6.wav", (char)78);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_G6.wav", (char)79);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_A6.wav", (char)81);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_B6.wav", (char)83);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_C7.wav", (char)84);
	sample_list.add_sample("D:\\Music\\Composing\\Samples\\Music Box\\mb_D7.wav", (char)86);

	// Create an AudioFile for storing the output that contains the song.

	AudioFile<double> *audio_file_out = new AudioFile<double>;
	setup_audio_file_out(audio_file_out, sample_list.list[FIRST_SAMPLE_KEYNUMBER]);


	// Fill the audio output buffer.
	int track = 0;
	for (int i = 0; i<midifile[track].size(); i++) {
		if (!midifile[track][i].isNoteOn()) {
			continue;
		}
		cout << midifile[track][i].seconds
			<< '\t' << midifile[track][i].getKeyNumber()
			<< endl;
		double sample_offset = midifile[track][i].seconds * sample_list.list[FIRST_SAMPLE_KEYNUMBER]->getSampleRate();
		char keynum = midifile[track][i].getKeyNumber();// - 2 for converting Amaj to Gmaj
		double mul = keynum < 78 ? 0.75 : 1; // Adjust for lack of volume in highest notes.
		if (sample_list.list[keynum] == NULL) {
			cout << "ERROR: no sample was loaded for keynum = " << (char)keynum << endl;
			keep_window_open();
			return(1);
		}
		for (int j = 0; j < sample_list.list[keynum]->getNumSamplesPerChannel(); j++) {
			audio_file_out->samples[0][sample_offset + j] += sample_list.list[keynum]->samples[0][j]*mul;
			audio_file_out->samples[1][sample_offset + j] += sample_list.list[keynum]->samples[1][j]*mul;
		}
	}

	// Trim output buffer to reduce end silence.
	for (int i = audio_file_out->getNumSamplesPerChannel() - 1; i >= 0; i--) {
		if ((audio_file_out->samples[0][i] != 0) || (audio_file_out->samples[1][i] != 0)) {
			audio_file_out->setNumSamplesPerChannel(i + 1);
			break;
		}
	}
	
	/*
	for (int offset = 0; offset < 3; offset++) {
		for (int i = 0; i < sample_list.list[FIRST_SAMPLE_KEYNUMBER]->getNumSamplesPerChannel(); i++)
		{
			audio_file_out->samples[0][i + offset*10000] += sample_list.list[FIRST_SAMPLE_KEYNUMBER+2*offset]->samples[0][i];
			audio_file_out->samples[1][i + offset*10000] += sample_list.list[FIRST_SAMPLE_KEYNUMBER+2*offset]->samples[1][i];
		}
	}*/

	// Save the audio file to disk

	// Wave file (explicit)
	audio_file_out->save("D:\\Music\\Composing\\wav_out\\audio_file.wav", AudioFileFormat::Wave);

	//keep_window_open();
    return 0;
}

