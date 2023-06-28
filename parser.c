#include "parser.h"

void parse_general(char line[256], General* general){
	return;
}

void parse_editor(char line[256], Editor* editor){
	return;
}

void parse_metadata(char line[256], Metadata* metadata){
	return;
}

void parse_difficulty(char line[256], Difficulty* difficulty){
	return;
}

void parse_events(char line[256], List* events){
	return;
}

void parse_timingPoints(char line[256], List* timingPoints){
	return;
}

void parse_colours(char line[256], List* colours){
	return;
}

void parse_hitObjects(char line[256], List* hitObjects){
	return;
}

Beatmap* parse_beatmap(char* osuFile){
	FILE* file = fopen(osuFile, "r");
	if (file == NULL) {
		printf("Failed to open the file.\n");
		return NULL;
	}
	char line[256];
	General* general = new_general();
	Editor* editor = new_editor();
	Metadata* metadata = new_metadata();
	Difficulty* difficulty = new_difficulty();
	List events = new_list(1);
	List timingPoints = new_list(1);
	List colours = new_list(1);
	List hitObjects = new_list(1);
	while (fgets(line, sizeof(line), file)) {
		if (strncmp(line, "osu file format v", 17) == 0) {
			if (line[17] != '1' || line[18] != '4'){
				printf("Does not support other osu file format than 14\n");
				exit(0);
			}
		}
		else if (strncmp(line, "[General]", 9) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n') {
					// printf("Done reading General\n");
					break;
				} else 
					parse_general(line, general);
			}
		}
		else if (strncmp(line, "[Editor]", 8) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n') {
					// printf("Done reading Editor\n");
					break;
				} else
					parse_editor(line, editor);
			}
		}
		else if (strncmp(line, "[Metadata]", 10) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n') {
					// printf("Done reading Metadata\n");
					break;
				} else
					parse_metadata(line, metadata);
			}
		}
		else if (strncmp(line, "[Difficulty]", 12) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n') {
					// printf("Done reading Difficulty\n");
					break;
				} else
					parse_difficulty(line, difficulty);
			}
		}
		else if (strncmp(line, "[Events]", 8) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n') {
					// printf("Done reading Events\n");
					break;
				} else
					parse_events(line, &events);
			}
		}
		else if (strncmp(line, "[TimingPoints]", 14) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n') {
					// printf("Done reading TimingPoints\n");
					break;
				} else
					parse_timingPoints(line, &timingPoints);
			}
		}
		else if (strncmp(line, "[Colours]", 9) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n') {
					// printf("Done reading Colours\n");
					break;
				} else
					parse_colours(line, &colours);
			}
		}
		else if (strncmp(line, "[HitObjects]", 12) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n') {
					// printf("Done reading HitObjects\n");
					break;
				} else
					parse_hitObjects(line, &hitObjects);
			}
		}
	}
	fclose(file);
	Beatmap* beatmap = new_beatmap();
	beatmap->general = general;
	beatmap->editor = editor;
	beatmap->metadata = metadata;
	beatmap->difficulty = difficulty;
	beatmap->events = &events;
	beatmap->timingPoints = &timingPoints;
	beatmap->colours = &colours;
	beatmap->hitObjects = &hitObjects;
		
	return beatmap;
}