//////////////////////////
// constants.h
// Autor: Areg Kalantaryan
//////////////////////////

#include "notes.h"
#pragma once

typedef void (*function_ptr)(void);

const char* str_moreop[][4]		= {{"\x01 Stopwatch", "\x02 Tune", "\03 Language", "\04 Credits"},
									  {"\x01 Stoppuhr", "\x02 Melodie", "\x03 Sprache", "\x04 Credits"},
									  {"\x01 \xBD\xC4\xAF\xCC\xDF\xB3\xAB\xAF\xC1", "\x02 \xB7\xAE\xB8", "\x03 \xB9\xDE\xDD\xBA\xDE", "\x04 \xB8\xDA\xBC\xDE\xAF\xC4"}};
const char* str_lang[]			= {"English", "Deutsch", "\xC6\xCE\xDD\xBA\xDE"};
const char* str_tune[]			= {"No tune", "Siren", "Ring", "Tumbler", "Three Tankmen"};
const char* str_credits[][2]	= {{"Smart Clock", "Made by Areg K."},
								   {"Smart Uhr", "Gemacht von Areg"},
								   {"\xBD\xCF\xB0\xC4\xB8\xDB\xAF\xB8", "\xB1\xDA\xB8\xDE\xA5\xB6\xD7\xDD\xC0\xD8\xB1\xDD\xC9\xBB\xB8"}};
const char* str_other[][4]	= {{"===Set timer====", "Set date & time", "==More options==", "   Time is up   "},
							   {"Timer einstellen", "Zeit einstellen", "Weitere Optionen", " Die Zeit ist um"},
							   {"====\xC0\xB2\xCF\xB0\xA6\xBE\xAF\xC3\xB2===", "=\xCB\xC2\xDE\xB9\xC4\xBC\xDE\xBA\xB8\xA6\xBE\xAF\xC3\xB2=", "===\xBF\xC9\xC0\xC9\xB5\xCC\xDF\xBC\xAE\xDD===", "     \xBC\xDE\xB6\xDD\xB7\xDE\xDA    "}};

Note tumbler_bass[] = {
    Note(NOTE_F3,2),
    Note(NOTE_C4,2),
    Note(NOTE_F3,2),
    Note(NOTE_C4,2),
    Note(NOTE_F3,2),
    Note(NOTE_C4,2),
    Note(NOTE_F3,2),
    Note(NOTE_C4,2),
    Note(NOTE_C4,2),
    Note(NOTE_C5,2),
    Note(NOTE_C4,2),
    Note(NOTE_C5,2),
    Note(NOTE_C4,2),
    Note(NOTE_C5,2),
    Note(NOTE_C4,2),
    Note(NOTE_C5,2),
    
    Note(NOTE_F3,2),
    Note(NOTE_C4,2),
    Note(NOTE_F3,2),
    Note(NOTE_C4,2),
    Note(NOTE_F3,2),
    Note(NOTE_C4,2),
    Note(NOTE_F3,2),
    Note(NOTE_C4,2),
    Note(NOTE_C4,2),
    Note(NOTE_C5,2),
    Note(NOTE_C4,2),
    Note(NOTE_C5,2),
    Note(NOTE_C4,2),
    Note(NOTE_C5,2),
    Note(NOTE_C4,2),
    Note(NOTE_C5,2),

    Note(NOTE_CS4,2),
    Note(NOTE_CS5,2),
    Note(NOTE_CS4,2),
    Note(NOTE_CS5,2),
    Note(NOTE_CS4,2),
    Note(NOTE_CS5,2),
    Note(NOTE_CS4,2),
    Note(NOTE_CS5,2),
    Note(NOTE_DS4,2),
    Note(NOTE_DS5,2),
    Note(NOTE_DS4,2),
    Note(NOTE_DS5,2),
    Note(NOTE_DS4,2),
    Note(NOTE_DS5,2),
    Note(NOTE_DS4,2),
    Note(NOTE_DS5,2),

    Note(NOTE_AS3,2),
    Note(NOTE_AS4,2),
    Note(NOTE_AS3,2),
    Note(NOTE_AS4,2),
    Note(NOTE_AS3,2),
    Note(NOTE_AS4,2),
    Note(NOTE_AS3,2),
    Note(NOTE_AS4,2),
    Note(NOTE_GS3,2),
    Note(NOTE_GS4,2),
    Note(NOTE_GS3,2),
    Note(NOTE_GS4,2),
    Note(NOTE_GS3,2),
    Note(NOTE_GS4,2),
    Note(NOTE_GS3,2),
    Note(NOTE_GS4,2),
    Note(SHEET_END, 0)
};

Note tumbler_solo[] = {
    Note(NOTE_F4,2),
    Note(NOTE_C5, 4),
    Note(NOTE_F4,2),
    Note(NOTE_C5, 4),
    Note(NOTE_F4,2),
    Note(NOTE_CS5,2),
    Note(NOTE_DS5, 4),
    Note(NOTE_C5, 4),
    Note(NOTE_AS4, 4),
    Note(NOTE_C5, 4),
    Note(NOTE_F4,2),
    Note(NOTE_C5, 4),
    Note(NOTE_F4,2),
    Note(NOTE_C5, 4),
    Note(NOTE_F4,2),
    Note(NOTE_CS5,2),
    Note(NOTE_DS5, 4),
    Note(NOTE_C5, 4),
    Note(NOTE_AS4, 4),
    Note(NOTE_C5, 4),
    
    Note(NOTE_GS4,2),
    Note(NOTE_F5, 4),
    Note(NOTE_GS4,2),
    Note(NOTE_F5, 4),
    Note(NOTE_GS4,2),
    Note(NOTE_DS5,2),
    Note(NOTE_DS5, 4),
    Note(NOTE_DS5, 4),
    Note(NOTE_CS5, 4),
    Note(NOTE_C5, 4),
    Note(NOTE_AS4,2),
    Note(NOTE_CS5, 4),
    Note(NOTE_AS4,2),
    Note(NOTE_CS5, 4),
    Note(NOTE_AS4,2),
    Note(NOTE_GS4,2),
    Note(NOTE_DS4, 4),
    Note(NOTE_GS4, 4),
    Note(NOTE_G4, 4),
    Note(NOTE_GS4, 4),
    Note(SHEET_END, 0)
};

Note three_tankmen_sheet[] = {
    Note(NOTE_G4, 6),
    Note(NOTE_A4, 2),
    Note(NOTE_B4, 12),
    Note(NOTE_B4, 4),
    Note(NOTE_C5, 4),
    Note(NOTE_A4, 4),
    Note(NOTE_E5, 4),
    Note(NOTE_C5, 4),
    Note(NOTE_B4, 8),
    Note(NOTE_B4, 16),
    Note(NOTE_E5, 6),
    Note(NOTE_FS5, 2),
    Note(NOTE_G5, 12),
    Note(NOTE_E5, 4),
    Note(NOTE_FS5, 6),
    Note(NOTE_FS5, 2),
    Note(NOTE_E5, 4),
    Note(NOTE_DS5, 4),
    Note(NOTE_E5, 24),

    Note(NOTE_G5, 6),
    Note(NOTE_E5, 2),
    Note(NOTE_D5, 8),
    Note(NOTE_B4, 8),
    Note(NOTE_E5, 6),
    Note(NOTE_E5, 2),
    Note(NOTE_D5, 4),
    Note(NOTE_E5, 4),
    Note(NOTE_C5, 8),
    Note(NOTE_A4, 16),
    Note(NOTE_G4, 6),
    Note(NOTE_A4, 2),
    Note(NOTE_B4, 12),
    Note(NOTE_B4, 4),
    Note(NOTE_FS5, 6),
    Note(NOTE_FS5, 2),
    Note(NOTE_E5, 4),
    Note(NOTE_DS5, 4),
    Note(NOTE_E5, 24),
    
    Note(NOTE_G5, 6),
    Note(NOTE_E5, 2),
    Note(NOTE_D5, 8),
    Note(NOTE_B4, 8),
    Note(NOTE_E5, 6),
    Note(NOTE_E5, 2),
    Note(NOTE_D5, 4),
    Note(NOTE_E5, 4),
    Note(NOTE_C5, 8),
    Note(NOTE_A4, 16),
    Note(NOTE_G4, 6),
    Note(NOTE_A4, 2),
    Note(NOTE_B4, 12),
    Note(NOTE_B4, 4),
    Note(NOTE_FS5, 6),
    Note(NOTE_FS5, 2),
    Note(NOTE_E5, 4),
    Note(NOTE_DS5, 4),
    Note(NOTE_E5, 24),
    Note(SHEET_END, 0)
};

Note tune_ring_melody[] = {
    Note(NOTE_C5, 1),
    Note(NOTE_G5, 1),
    Note(NOTE_C5, 1),
    Note(NOTE_G5, 1),
    Note(NOTE_C5, 1),
    Note(NOTE_G5, 1),
    Note(NOTE_C5, 1),
    Note(NOTE_G5, 1),
    Note(REST, 16),
    Note(SHEET_END, 0)
};

Note* tune_ring[] = {tune_ring_melody, 0, 0};

Note tune_siren_melody[] = {
    Note(NOTE_C5, 2),
    Note(NOTE_FS5, 2),
    Note(SHEET_END, 0)
};
Note* tune_siren[] = {tune_siren_melody, 0, 0};

Note* tune_tumbler[] = {tumbler_solo, tumbler_bass, 0};
Note* tune_three_tankmen[] = {three_tankmen_sheet, 0, 0};

Note** list_tunes[] = {nullptr, tune_siren, tune_ring, tune_tumbler, tune_three_tankmen};

unsigned char custom_chars[8][8] = {
	{}, //0 wird weggelassen, da sie auch dem Nullterminator entspricht
	{0x0E, 0x04, 0x0E, 0x13, 0x15, 0x15, 0x11, 0x0E}, //Stoppuhr
	{0x01, 0x07, 0x09, 0x09, 0x09, 0x0B, 0x1B, 0x18}, //Melodie
	{0x0E, 0x1F, 0x15, 0x15, 0x15, 0x15, 0x1F, 0x0E}, //Sprache
	{0x1F, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x1F, 0x00}, //Credits
	{0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00}, //Grad
	{0x04, 0x0E, 0x0A, 0x0A, 0x0A, 0x1F, 0x04, 0x00}, //Minuten Timer
	{0x04, 0x0E, 0x0E, 0x0E, 0x0E, 0x1F, 0x04, 0x00}, //Stunden Timer
};