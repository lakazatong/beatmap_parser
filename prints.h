#ifndef BEATMAP_PARSER_PRINTS_H
#define BEATMAP_PARSER_PRINTS_H
#include "structs.h"

void print_int_list(int* list, int size);
void print_string_list(char** list, int size);
void printGeneral(const General* general);
void printEditor(const Editor* editor);
void printMetadata(const Metadata* metadata);
void printDifficulty(const Difficulty* difficulty);
void printEvent(const Event* event);
void printEvents(const List* events);
void printTimingPoint(const TimingPoint* timingPoint);
void printTimingPoints(const List* timingPoints);
void printColour(const Colour* colour);
void printColours(const List* colours);
void printHitSound(const HitSound* hitSound);
void printHitSample(const HitSample* hitSample);
void printSlider(const Slider* slider);
void printSpinner(const Spinner* spinner);
void printHold(const Hold* hold);
void printHitObject(const HitObject* hitObject);
void printHitObjects(const List* hitObjects);

#endif