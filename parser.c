#include "parser.h"

// Source: ChatGPT
char* remove_chars(char* string, const char* characters) {
	if (string == NULL || characters == NULL) return NULL;
	size_t length = strlen(string);
	size_t char_length = strlen(characters);
	size_t i, j;
	for (i = 0; i < length; i++) {
		int remove = 0;
		for (j = 0; j < char_length; j++) {
			if (string[i] == characters[j]) {
				remove = 1;
				break;
			}
		}
		if (remove) {
			for (size_t k = i; k < length - 1; k++) {
				string[k] = string[k + 1];
			}
			string[length - 1] = '\0';
			length--;
			i--;
		}
	}
	return string;
}
char* replace(char* string, char characters[], char target) {
	if (string == NULL || characters == NULL) return NULL;
	size_t length = strlen(string);
	size_t char_length = strlen(characters);
	for (size_t i = 0; i < length; i++)
		for (size_t j = 0; j < char_length; j++)
			if (string[i] == characters[j])
				string[i] = target;
	return string;
}
char* strip(char* string) {
	size_t length = strlen(string);
	printf("length=%zu\n", length);
	if (length == 0) {
		printf("strip: null length\n");
		return string;
	}
	char* start = string;
	char* end = string + length - 1;
	while (start <= end && (*start == ' ' || *start == '\n' || *start == '\r')) start++;
	while (end >= start && (*end == ' ' || *end == '\n' || *end == '\r')) end--;
	size_t trimmed_length = (end - start) + 1;
	memmove(string, start, trimmed_length);
	string[trimmed_length] = '\0';
	return string;
}
void substring(char** out, char string[LINE_SIZE], int start_index, char* unwanted) {
	int length = strlen(string);
	int substring_length = length - start_index;
	if (substring_length <= 0) {
		printf("substring: substring_length negative or null\n");
		*out = NULL;
		return;
	}
	char* result = *out;
	if (result == string) {
		// In-place modification
		memmove(result, result + start_index, substring_length + 1);
	} else {
		// Transfer to a new memory location
		result = realloc(result, (substring_length + 1) * sizeof(char));
		strncpy(result, string + start_index, substring_length);
		result[substring_length] = '\0';
	}
	*out = remove_chars(result, unwanted);
}
void subint(int* out, char string[LINE_SIZE], int start_index, char* unwanted) {
	int length = strlen(string);
	int substring_length = length - start_index;
	if (substring_length <= 0) {
		printf("subint: substring_length negative or null\n");
		return;
	}
	char* tmp = malloc((substring_length + 1) * sizeof(char));
	strncpy(tmp, string + start_index, substring_length);
	tmp[substring_length] = '\0';
	char* end_ptr;
	*out = strtol(remove_chars(tmp, unwanted), &end_ptr, 10);
	if (*end_ptr != '\0') {
		printf("subint: strtol failed\n");
		exit(1);
	}
	free(tmp);
}
void subfloat(float* out, char string[LINE_SIZE], int start_index, char* unwanted) {
	int length = strlen(string);
	int substring_length = length - start_index;
	if (substring_length <= 0) {
		printf("subfloat: substring_length negative or null\n");
		return;
	}
	char* tmp = malloc((substring_length + 1) * sizeof(char));
	strncpy(tmp, string + start_index, substring_length);
	tmp[substring_length] = '\0';
	char* end_ptr;
	*out = strtof(remove_chars(tmp, unwanted), &end_ptr);
	if (*end_ptr != '\0'){
		printf("subfloat: subfloat failed\n");
		exit(1);
	}
	free(tmp);
}

void parse_general(char line[LINE_SIZE], General* general){
	char unwanted[3] = " \r\n";
	if (strncmp(line, "AudioFilename", 13) == 0) substring(&general->audioFilename, line, 15, unwanted);
	else if (strncmp(line, "AudioLeadIn", 11) == 0) subint(&general->audioLeadIn, line, 13, unwanted);
	else if (strncmp(line, "AudioHash", 9) == 0) substring(&general->audioHash, line, 11, unwanted);
	else if (strncmp(line, "PreviewTime", 11) == 0) subint(&general->previewTime, line, 13, unwanted);
	else if (strncmp(line, "Countdown", 9) == 0) subint(&general->countdown, line, 11, unwanted);
	else if (strncmp(line, "SampleSet", 9) == 0) substring(&general->sampleSet, line, 11, unwanted);
	else if (strncmp(line, "StackLeniency", 13) == 0) subfloat(&general->stackLeniency, line, 15, unwanted);
	else if (strncmp(line, "Mode", 4) == 0) subint(&general->mode, line, 6, unwanted);
	else if (strncmp(line, "LetterboxInBreaks", 17) == 0) subint(&general->letterboxInBreaks, line, 19, unwanted);
	else if (strncmp(line, "StoryFireInFront", 16) == 0) subint(&general->storyFireInFront, line, 18, unwanted);
	else if (strncmp(line, "UseSkinSprites", 14) == 0) subint(&general->useSkinSprites, line, 16, unwanted);
	else if (strncmp(line, "AlwaysShowPlayfield", 19) == 0) subint(&general->alwaysShowPlayfield, line, 21, unwanted);
	else if (strncmp(line, "OverlayPosition", 15) == 0) substring(&general->overlayPosition, line, 17, unwanted);
	else if (strncmp(line, "SkinPreference", 14) == 0) substring(&general->skinPreference, line, 16, unwanted);
	else if (strncmp(line, "EpilepsyWarning", 15) == 0) subint(&general->epilepsyWarning, line, 17, unwanted);
	else if (strncmp(line, "CountdownOffset", 15) == 0) subint(&general->countdownOffset, line, 17, unwanted);
	else if (strncmp(line, "SpecialStyle", 12) == 0) subint(&general->specialStyle, line, 14, unwanted);
	else if (strncmp(line, "WidescreenStoryboard", 20) == 0) subint(&general->widescreenStoryboard, line, 22, unwanted);
	else if (strncmp(line, "SamplesMatchPlaybackRate", 24) == 0) subint(&general->samplesMatchPlaybackRate, line, 26, unwanted);
	else{
		printf("parse_general: impossible case reached\n");
		exit(1);
	}
}

void parse_editor(char line[LINE_SIZE], Editor* editor){
	char unwanted[3] = " \r\n";
	if (strncmp(line, "Bookmarks", 9) == 0) {
		substring(&line, line, 11, unwanted);
		char* bookmark;
		bookmark = strtok(line, ",");
		while (bookmark != NULL) {
			char* end_ptr;
			long value = strtol(bookmark, &end_ptr, 10);
			if (*end_ptr != '\0'){
				printf("parse editor: strtol failed\n");
				exit(1);
			}
			ilist_add(editor->bookmarks, (int)value);
			bookmark = strtok(NULL, ",");	
		}
	}
	else if (strncmp(line, "DistanceSpacing", 15) == 0) subfloat(&editor->distanceSpacing, line, 17, unwanted);
	else if (strncmp(line, "BeatDivisor", 11) == 0) subint(&editor->beatDivisor, line, 13, unwanted);
	else if (strncmp(line, "GridSize", 8) == 0) subint(&editor->gridSize, line, 10, unwanted);
	else if (strncmp(line, "TimelineZoom", 12) == 0) subfloat(&editor->timelineZoom, line, 14, unwanted);
	else{
		printf("parse_editor: impossible case reached\n");
		exit(0);
	}
}

void parse_metadata(char line[LINE_SIZE], Metadata* metadata){
	char unwanted[3] = " \r\n";
	if (strncmp(line, "Title", 5) == 0) substring(&metadata->title, line, 6, unwanted);
	else if (strncmp(line, "TitleUnicode", 12) == 0) substring(&metadata->titleUnicode, line, 13, unwanted);
	else if (strncmp(line, "Artist", 6) == 0) substring(&metadata->artist, line, 7, unwanted);
	else if (strncmp(line, "ArtistUnicode", 13) == 0) substring(&metadata->artistUnicode, line, 14, unwanted);
	else if (strncmp(line, "Creator", 7) == 0) substring(&metadata->creator, line, 8, unwanted);
	else if (strncmp(line, "Version", 7) == 0) substring(&metadata->version, line, 8, unwanted);
	else if (strncmp(line, "Source", 6) == 0) substring(&metadata->source, line, 7, unwanted);
	else if (strncmp(line, "Tags", 4) == 0) {
		substring(&line, line, 5, "\r\n");
		char* tag;
		tag = strtok(line, " ");
		while (tag != NULL) {
			slist_add(metadata->tags, tag);
			tag = strtok(NULL, " ");
		}
	}
	else if (strncmp(line, "BeatmapID", 9) == 0) subint(&metadata->beatmapID, line, 10, unwanted);
	else if (strncmp(line, "BeatmapSetID", 12) == 0) subint(&metadata->beatmapSetID, line, 13, unwanted);
	else{
		printf("parse_metadata: impossible case reached\n");
		exit(0);
	}
}

void parse_difficulty(char line[LINE_SIZE], Difficulty* difficulty){
	char unwanted[3] = " \r\n";
	if (strncmp(line, "HPDrainRate", 11) == 0) subfloat(&difficulty->hpDrainRate, line, 12, unwanted);
	else if (strncmp(line, "CircleSize", 10) == 0) subfloat(&difficulty->circleSize, line, 11, unwanted);
	else if (strncmp(line, "OverallDifficulty", 17) == 0) subfloat(&difficulty->overallDifficulty, line, 18, unwanted);
	else if (strncmp(line, "ApproachRate", 12) == 0) subfloat(&difficulty->approachRate, line, 13, unwanted);
	else if (strncmp(line, "SliderMultiplier", 16) == 0) subfloat(&difficulty->sliderMultiplier, line, 17, unwanted);
	else if (strncmp(line, "SliderTickRate", 14) == 0) subfloat(&difficulty->sliderTickRate, line, 15, unwanted);
	else{
		printf("parse_difficulty: impossible case reached\n");
		exit(0);
	}
	return;
}

void parse_events(char line[LINE_SIZE], List* events){
	return;
}

void parse_timingPoints(char line[LINE_SIZE], List* timingPoints){
	return;
}

void parse_colours(char line[LINE_SIZE], List* colours){
	return;
}

void parse_hitObjects(char line[LINE_SIZE], List* hitObjects){
	return;
}

Beatmap* parse_beatmap(char* osuFile){
	FILE* file = fopen(osuFile, "r");
	if (file == NULL) {
		printf("parse_beatmap: failed to open the file\n");
		return NULL;
	}
	char line[LINE_SIZE];
	Beatmap* beatmap = new_beatmap();
	while (fgets(line, sizeof(line), file)) {
		if (strncmp(line, "osu file format v", 17) == 0) {
			if (line[17] != '1' || line[18] != '4'){
				printf("parse_beatmap: does not support other osu file format than 14\n");
				exit(0);
			}
		}
		else if (strncmp(line, "[General]", 9) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else 
					parse_general(line, beatmap->general);
			}
		}
		else if (strncmp(line, "[Editor]", 8) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else
					parse_editor(line, beatmap->editor);
			}
		}
		else if (strncmp(line, "[Metadata]", 10) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else
					parse_metadata(line, beatmap->metadata);
			}
		}
		else if (strncmp(line, "[Difficulty]", 12) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else
					parse_difficulty(line, beatmap->difficulty);
			}
		}
		else if (strncmp(line, "[Events]", 8) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else
					parse_events(line, beatmap->events);
			}
		}
		else if (strncmp(line, "[TimingPoints]", 14) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else
					parse_timingPoints(line, beatmap->timingPoints);
			}
		}
		else if (strncmp(line, "[Colours]", 9) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else
					parse_colours(line, beatmap->colours);
			}
		}
		else if (strncmp(line, "[HitObjects]", 12) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else
					parse_hitObjects(line, beatmap->hitObjects);
			}
		}
	}
	fclose(file);
	return beatmap;
}