#ifndef PARSER_H
#define PARSER_H
#include "structs.h"

#define LINE_SIZE 2048

char* remove_chars(char* string, const char* characters);
char* replace(char* string, char characters[], char target);
char* strip(char* string);
void substring(char** out, char string[LINE_SIZE], int start_index, char* unwanted);
void subint(int* out, char string[LINE_SIZE], int start_index, char* unwanted);
void subfloat(float* out, char string[LINE_SIZE], int start_index, char* unwanted);
void parse_general(char line[LINE_SIZE], General* general);
void parse_editor(char line[LINE_SIZE], Editor* editor);
void parse_metadata(char line[LINE_SIZE], Metadata* metadata);
void parse_difficulty(char line[LINE_SIZE], Difficulty* difficulty);
void parse_events(char line[LINE_SIZE], List* events);
void parse_timingPoints(char line[LINE_SIZE], List* timingPoints);
void parse_colours(char line[LINE_SIZE], List* colours);
void parse_hitObjects(char line[LINE_SIZE], List* hitObjects);
Beatmap* parse_beatmap(char* osuFile);

#endif