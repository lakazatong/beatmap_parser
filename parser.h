#ifndef PARSER_H
#define PARSER_H
#include "structs.h"

#define BUF_SIZE 2048

char* remove_chars(char* string);
char* replace(char* string, char characters[], char target);
char* strip(char* string);
void substring(char* out, char* string, int start_index, int end_index);
void subint(int* out, char* string, int start_index, int end_index);
void subfloat(float* out, char* string, int start_index, int end_index);

void parse_general(General* general);
void parse_editor(Editor* editor);
void parse_metadata(Metadata* metadata);
void parse_difficulty(Difficulty* difficulty);
void parse_events(List* events);
void parse_timingPoints(List* timingPoints);
void parse_colours(List* colours);
void parse_hitObjects(List* hitObjects);
Beatmap* parse_beatmap(char* osuFile);

#endif