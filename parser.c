#include "parser.h"

char unwanted[BUF_SIZE]; // used by remove_chars
size_t unwanted_size;
char line[BUF_SIZE]; // buffer for the current line
char buf[BUF_SIZE]; // buffer for parse functions
char tmp[BUF_SIZE]; // temporary buffer for utils functions

// Source: ChatGPT
char* remove_chars(char* string) {
	if (string == NULL || unwanted == NULL) return NULL;
	size_t length = strlen(string);
	size_t i, j;
	for (i = 0; i < length; i++) {
		int remove = 0;
		for (j = 0; j < unwanted_size; j++) {
			if (string[i] == unwanted[j]) {
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

void substring(char* out, char* string, int start_index, int end_index) {
	int substring_length;
	if (end_index == -1){ substring_length = strlen(string) - start_index;}
	else 				{ substring_length = end_index - start_index; }
	if (substring_length <= 0) {
		printf("substring: substring_length negative or null\n");
		out = NULL;
		return;
	}
	if (out == string) {
		// In-place modification
		memmove(out, out + start_index, substring_length + 1);
	} else {
		// Transfer to a new memory location
		out = realloc(out, (substring_length + 1) * sizeof(char));
		strncpy(out, string + start_index, substring_length);
		out[substring_length] = '\0';
	}
	remove_chars(out);
}

void subint(int* out, char* string, int start_index, int end_index) {
	int substring_length;
	if (end_index == -1){ substring_length = strlen(string) - start_index;}
	else 				{ substring_length = end_index - start_index; }
	if (substring_length <= 0) {
		printf("subint: substring_length negative or null\n");
		return;
	}
	strncpy(tmp, string + start_index, substring_length);
	tmp[substring_length] = '\0';
	char* end_ptr;
	*out = strtol(remove_chars(tmp), &end_ptr, 10);
	if (*end_ptr != '\0') {
		printf("subint: strtol failed\n");
		exit(1);
	}
}

void subfloat(float* out, char* string, int start_index, int end_index) {
	int substring_length;
	if (end_index == -1){ substring_length = strlen(string) - start_index;}
	else 				{ substring_length = end_index - start_index; }
	if (substring_length <= 0) {
		printf("subfloat: substring_length negative or null\n");
		return;
	}
	strncpy(tmp, string + start_index, substring_length);
	tmp[substring_length] = '\0';
	char* end_ptr;
	*out = strtof(remove_chars(tmp), &end_ptr);
	if (*end_ptr != '\0'){
		printf("subfloat: subfloat failed\n");
		exit(1);
	}
}

void parse_general(General* general){
	if (strncmp(line, "AudioFilename", 13) == 0) substring(general->audioFilename, line, 15, -1);
	else if (strncmp(line, "AudioLeadIn", 11) == 0) subint(&general->audioLeadIn, line, 13, -1);
	else if (strncmp(line, "AudioHash", 9) == 0) substring(general->audioHash, line, 11, -1);
	else if (strncmp(line, "PreviewTime", 11) == 0) subint(&general->previewTime, line, 13, -1);
	else if (strncmp(line, "Countdown", 9) == 0) subint(&general->countdown, line, 11, -1);
	else if (strncmp(line, "SampleSet", 9) == 0) substring(general->sampleSet, line, 11, -1);
	else if (strncmp(line, "StackLeniency", 13) == 0) subfloat(&general->stackLeniency, line, 15, -1);
	else if (strncmp(line, "Mode", 4) == 0) subint(&general->mode, line, 6, -1);
	else if (strncmp(line, "LetterboxInBreaks", 17) == 0) subint(&general->letterboxInBreaks, line, 19, -1);
	else if (strncmp(line, "StoryFireInFront", 16) == 0) subint(&general->storyFireInFront, line, 18, -1);
	else if (strncmp(line, "UseSkinSprites", 14) == 0) subint(&general->useSkinSprites, line, 16, -1);
	else if (strncmp(line, "AlwaysShowPlayfield", 19) == 0) subint(&general->alwaysShowPlayfield, line, 21, -1);
	else if (strncmp(line, "OverlayPosition", 15) == 0) substring(general->overlayPosition, line, 17, -1);
	else if (strncmp(line, "SkinPreference", 14) == 0) substring(general->skinPreference, line, 16, -1);
	else if (strncmp(line, "EpilepsyWarning", 15) == 0) subint(&general->epilepsyWarning, line, 17, -1);
	else if (strncmp(line, "CountdownOffset", 15) == 0) subint(&general->countdownOffset, line, 17, -1);
	else if (strncmp(line, "SpecialStyle", 12) == 0) subint(&general->specialStyle, line, 14, -1);
	else if (strncmp(line, "WidescreenStoryboard", 20) == 0) subint(&general->widescreenStoryboard, line, 22, -1);
	else if (strncmp(line, "SamplesMatchPlaybackRate", 24) == 0) subint(&general->samplesMatchPlaybackRate, line, 26, -1);
	else{
		printf("parse_general: impossible case reached\n");
		exit(1);
	}
}

void parse_editor(Editor* editor){
	if (strncmp(line, "Bookmarks", 9) == 0) {
		substring(line, line, 11, -1);
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
	else if (strncmp(line, "DistanceSpacing", 15) == 0) subfloat(&editor->distanceSpacing, line, 17, -1);
	else if (strncmp(line, "BeatDivisor", 11) == 0) subint(&editor->beatDivisor, line, 13, -1);
	else if (strncmp(line, "GridSize", 8) == 0) subint(&editor->gridSize, line, 10, -1);
	else if (strncmp(line, "TimelineZoom", 12) == 0) subfloat(&editor->timelineZoom, line, 14, -1);
	else{
		printf("parse_editor: impossible case reached\n");
		exit(0);
	}
}

void parse_metadata(Metadata* metadata){
	if (strncmp(line, "Title", 5) == 0) substring(metadata->title, line, 6, -1);
	else if (strncmp(line, "TitleUnicode", 12) == 0) substring(metadata->titleUnicode, line, 13, -1);
	else if (strncmp(line, "Artist", 6) == 0) substring(metadata->artist, line, 7, -1);
	else if (strncmp(line, "ArtistUnicode", 13) == 0) substring(metadata->artistUnicode, line, 14, -1);
	else if (strncmp(line, "Creator", 7) == 0) substring(metadata->creator, line, 8, -1);
	else if (strncmp(line, "Version", 7) == 0) substring(metadata->version, line, 8, -1);
	else if (strncmp(line, "Source", 6) == 0) substring(metadata->source, line, 7, -1);
	else if (strncmp(line, "Tags", 4) == 0) {
		strcpy(unwanted, "\r\n"); unwanted_size = 2;
		substring(line, line, 5, -1);
		strcpy(unwanted, " \r\n"); unwanted_size = 3;
		char* tag;
		tag = strtok(line, " ");
		while (tag != NULL) {
			slist_add(metadata->tags, tag);
			tag = strtok(NULL, " ");
		}
	}
	else if (strncmp(line, "BeatmapID", 9) == 0) subint(&metadata->beatmapID, line, 10, -1);
	else if (strncmp(line, "BeatmapSetID", 12) == 0) subint(&metadata->beatmapSetID, line, 13, -1);
	else{
		printf("parse_metadata: impossible case reached\n");
		exit(0);
	}
}

void parse_difficulty(Difficulty* difficulty){
	if (strncmp(line, "HPDrainRate", 11) == 0) subfloat(&difficulty->hpDrainRate, line, 12, -1);
	else if (strncmp(line, "CircleSize", 10) == 0) subfloat(&difficulty->circleSize, line, 11, -1);
	else if (strncmp(line, "OverallDifficulty", 17) == 0) subfloat(&difficulty->overallDifficulty, line, 18, -1);
	else if (strncmp(line, "ApproachRate", 12) == 0) subfloat(&difficulty->approachRate, line, 13, -1);
	else if (strncmp(line, "SliderMultiplier", 16) == 0) subfloat(&difficulty->sliderMultiplier, line, 17, -1);
	else if (strncmp(line, "SliderTickRate", 14) == 0) subfloat(&difficulty->sliderTickRate, line, 15, -1);
	else{
		printf("parse_difficulty: impossible case reached\n");
		exit(0);
	}
	return;
}

void parse_backgroundEvent(Event* event){
	char* token;
	event->type = 0;
	event->event = new_backgroundEvent();
	BackgroundEvent* cur_event = (BackgroundEvent*)event->event;
	
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_backgroundEvent: incomplete event, missing filename\n");
		return;
	}
	strcpy(cur_event->filename, token);
	if (cur_event->filename[0] == '\"') {
		strcpy(unwanted, "\""); unwanted_size = 1;
		remove_chars(cur_event->filename);
		strcpy(unwanted, " \r\n"); unwanted_size = 3;
	}
	
	token = strtok(NULL, ",");
	if (token == NULL) {
		cur_event->xOffset = 0;
		cur_event->yOffset = 0;
		return;
	}
	subint(&cur_event->xOffset, token, 0, -1);
	
	token = strtok(NULL, ",");
	if (token == NULL) {
		cur_event->yOffset = 0;
		return;
	}
	subint(&cur_event->yOffset, token, 0, -1);
	
	token = strtok(NULL, ",");
	if (token == NULL) return;
	printf("parse_backgroundEvent: impossible case reached\n");
	exit(0);
}
void parse_videoEvent(Event* event){
	char* token;
	event->type = 1;
	event->event = new_videoEvent();
	VideoEvent* cur_event = (VideoEvent*)event->event;
	
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_videoEvent: incomplete event, missing filename\n");
		return;
	}
	strcpy(cur_event->filename, token);
	if (cur_event->filename[0] == '\"') {
		strcpy(unwanted, "\""); unwanted_size = 1;
		remove_chars(cur_event->filename);
		strcpy(unwanted, " \r\n"); unwanted_size = 3;
	}
	
	token = strtok(NULL, ",");
	if (token == NULL) {
		cur_event->xOffset = 0;
		cur_event->yOffset = 0;
		return;
	}
	subint(&cur_event->xOffset, token, 0, -1);
	
	token = strtok(NULL, ",");
	if (token == NULL) {
		cur_event->yOffset = 0;
		return;
	}
	subint(&cur_event->yOffset, token, 0, -1);
	
	token = strtok(NULL, ",");
	if (token == NULL) return;
	printf("parse_videoEvent: impossible case reached\n");
	exit(0);
}
void parse_breakEvent(Event* event){
	char* token;
	event->type = 2;
	event->event = new_breakEvent();
	BreakEvent* cur_event = (BreakEvent*)event->event;
	
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_breakEvent: incomplete event, missing endTime\n");
		return;
	}
	subint(&cur_event->endTime, token, 0, -1);
	
	token = strtok(NULL, ",");
	if (token == NULL) return;
	printf("parse_backgroundEvent: impossible case reached\n");
	exit(0);
}

void parse_events(List* events){
	char* token;
	strcpy(buf, strtok(line, ","));
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_events: incomplete event, missing startTime\n");
		return;
	}
	Event* event = new_event();
	subint(&event->startTime, token, 0, -1);
	if (strlen(buf) == 1){
		if (strncmp(buf, "0", 1) == 0) parse_backgroundEvent(event);
		else if (strncmp(buf, "1", 1) == 0) parse_videoEvent(event);
		else if (strncmp(buf, "2", 1) == 0) parse_breakEvent(event);
		else {
			printf("parse_events: impossible case1 reached (%s)\n", buf);
			exit(0);
		}
	} else {
		if (strncmp(buf, "Background", 10) == 0) parse_backgroundEvent(event);
		else if (strncmp(buf, "Video", 5) == 0) parse_videoEvent(event);
		else if (strncmp(buf, "Break", 5) == 0) parse_breakEvent(event);
		else {
			printf("parse_events: impossible case2 reached (%s)\n", buf);
			exit(0);
		}
	}
	list_add(events, event);
}

void parse_timingPoints(List* timingPoints){
	char* token;
	TimingPoint* timingPoint = new_timingPoint();
	token = strtok(line, ",");
	if (token == NULL) {
		printf("parse_timingPoints: incomplete timingPoint, missing time\n");
		return;
	}
	subint(&timingPoint->time, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_timingPoints: incomplete timingPoint, missing beatLength\n");
		return;
	}
	subfloat(&timingPoint->beatLength, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_timingPoints: incomplete timingPoint, missing meter\n");
		return;
	}
	subint(&timingPoint->meter, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_timingPoints: incomplete timingPoint, missing sampleSet\n");
		return;
	}
	subint(&timingPoint->sampleSet, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_timingPoints: incomplete timingPoint, missing sampleIndex\n");
		return;
	}
	subint(&timingPoint->sampleIndex, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_timingPoints: incomplete timingPoint, missing volume\n");
		return;
	}
	subint(&timingPoint->volume, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_timingPoints: incomplete timingPoint, missing uninherited\n");
		return;
	}
	subint(&timingPoint->uninherited, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_timingPoints: incomplete timingPoint, missing effects\n");
		return;
	}
	subint(&timingPoint->effects, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		list_add(timingPoints, timingPoint);
		return;
	}
	printf("parse_timingPoints: impossible case reached\n");
	exit(0);
}

void parse_colours(List* colours){
	char* token;
	Colour* colour = new_colour();
	int colour_start = 0;
	if (strncmp(line, "Combo", 5) == 0) {
		colour->type = 0;
		colour->object = new_comboColour();
		char* found = strchr(line, ':');
		if (found == NULL) {
			printf("parse_colours: impossible case reached\n");
			exit(0);
		}
		size_t end_index = found - line;
		subint(&((ComboColour*)colour->object)->combo, line, 5, end_index-1);
		colour_start = end_index+2;
	}
	else if (strncmp(line, "SliderTrackOverride", 19) == 0) {
		colour->type = 1;
		colour_start = 22;
	}
	else if (strncmp(line, "SliderBorder", 12) == 0) {
		colour->type = 2;
		colour_start = 15;
	}
	else{
		printf("parse_colours: impossible case reached\n");
		exit(0);
	}
	substring(line, line, colour_start, -1);
	token = strtok(line, ",");
	if (token == NULL) {
		printf("parse_colours: incomplete colour object, missing red\n");
		return;
	}
	subint(&colour->red, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_colours: incomplete colour object, missing green\n");
		return;
	}
	subint(&colour->green, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_colours: incomplete colour object, missing blue\n");
		return;
	}
	subint(&colour->blue, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		list_add(colours, colour);
		return;
	}
	printf("parse_colours: impossible case reached\n");
}

char* parse_curvePoint(Slider* slider, char* token){
	char* colon = strchr(token, ':');
	if (colon == NULL) {
		printf("parse_curvePoint: wrong CurvePoint format\n");
		exit(1);
	}
	CurvePoint* curvePoint = new_curvePoint();
	int end_index = colon - token;
	subint(&curvePoint->x, token, 0, end_index);
	subint(&curvePoint->y, token, end_index+1, -1);
	list_add(slider->curvePoints, curvePoint);
	return strtok(NULL, "|");
}

char* parse_edgeSound(Slider* slider, char* token){
	int edgeSound;
	subint(&edgeSound, token, 0, -1);
	ilist_add(slider->edgeSounds, edgeSound);
	return strtok(NULL, "|");
}

char* parse_edgeSet(Slider* slider, char* token){
	char* colon = strchr(token, ':');
	if (colon == NULL) {
		printf("parse_edgeSet: wrong EdgeSet format\n");
		exit(1);
	}
	EdgeSet* edgeSet = new_edgeSet();
	int end_index = colon - token;
	substring(edgeSet->normalSet, token, 0, end_index);
	substring(edgeSet->additionSet, token, end_index+1, -1);
	list_add(slider->edgeSets, edgeSet);
	return strtok(NULL, "|");
}

void parse_hitSample(HitObject* hitObject, char* token){
	token = strtok(token, ":"); if (token == NULL) return;
	subint(&hitObject->hitSample->normalSet, token, 0, -1);
	token = strtok(NULL, ":"); if (token == NULL) return;
	subint(&hitObject->hitSample->additionSet, token, 0, -1);
	token = strtok(NULL, ":"); if (token == NULL) return;
	subint(&hitObject->hitSample->index, token, 0, -1);
	token = strtok(NULL, ":"); if (token == NULL) return;
	subint(&hitObject->hitSample->volume, token, 0, -1);
	token = strtok(NULL, "");
	strcpy(hitObject->hitSample->filename, remove_chars(token));
}

char* parse_slider(HitObject* hitObject){
	char* token;
	char* next_token;
	Slider* slider = new_slider();
	hitObject->type = 1;
	hitObject->object = slider;
	token = strtok(NULL, "|");
	if (token == NULL) {
		printf("parse_slider: incomplete Slider, missing curveType\n");
		return NULL;
	}
	slider->curveType = token[0];
	token = strtok(NULL, ",");
	strcpy(buf, token);
	next_token = token+strlen(buf)+1;
	token = strtok(buf, "|");
	while (token != NULL) token = parse_curvePoint(slider, token);
	token = strtok(next_token, ",");
	if (token == NULL) {
		printf("parse_slider: incomplete Slider, missing slides\n");
		return NULL;
	}
	subint(&slider->slides, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_slider: incomplete Slider, missing length\n");
		return NULL;
	}
	subfloat(&slider->length, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) return NULL;
	strcpy(buf, token);
	next_token = token+strlen(buf)+1;
	token = strtok(buf, "|");
	while (token != NULL) token = parse_edgeSound(slider, token);
	token = strtok(next_token, ",");
	if (token == NULL) return NULL;
	strcpy(buf, token);
	next_token = token+strlen(buf)+1;
	token = strtok(buf, "|");
	while (token != NULL) token = parse_edgeSet(slider, token);
	return next_token;
}

char* parse_spinner(HitObject* hitObject){
	char* token;
	Spinner* spinner = new_spinner();
	hitObject->type = 2;
	hitObject->object = spinner;
	token = strtok(NULL, ",");
	subint(&spinner->endTime, token, 0, -1);
	return strtok(NULL, "");
}

char* parse_hold(HitObject* hitObject){
	char* token;
	Hold* hold = new_hold();
	hitObject->type = 3;
	hitObject->object = hold;
	token = strtok(NULL, ",");
	subint(&hold->endTime, token, 0, -1);
	return strtok(NULL, "");
}

void parse_hitObjects(List* hitObjects){
	char* token;
	HitObject* hitObject = new_hitObject();
	token = strtok(line, ",");
	if (token == NULL) {
		printf("parse_hitObjects: incomplete hitObject, missing x\n");
		return;
	}
	subint(&hitObject->x, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_hitObjects: incomplete hitObject, missing y\n");
		return;
	}
	subint(&hitObject->y, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_hitObjects: incomplete hitObject, missing time\n");
		return;
	}
	subint(&hitObject->time, token, 0, -1);
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_hitObjects: incomplete hitObject, missing type\n");
		return;
	}
	int type_flags;
	subint(&type_flags, token, 0, -1);
	hitObject->new_combo = (type_flags & 0b00000100) ? 1 : 0;
	hitObject->combo_skip = (type_flags & 0b01110000) >> 4;
	token = strtok(NULL, ",");
	if (token == NULL) {
		printf("parse_hitObjects: incomplete hitObject, missing hitSound\n");
		return;
	}
	int hitSound_flags;
	subint(&hitSound_flags, token, 0, -1);
	if (hitSound_flags != 0){
		hitObject->hitSound->normal = hitSound_flags & 0b0001;
		hitObject->hitSound->whistle = (hitSound_flags & 0b0010) ? 1 : 0;
		hitObject->hitSound->finish = (hitSound_flags & 0b0100) ? 1 : 0;
		hitObject->hitSound->clap = (hitSound_flags & 0b1000) ? 1 : 0;
	}
	char* next_token = NULL;
	int type = type_flags & 0b10001011;
	if (type == 1) next_token = strtok(NULL, "");
	else if (type == 2) next_token = parse_slider(hitObject);
	else if (type == 8) next_token = parse_spinner(hitObject);
	else if (type == 128) next_token = parse_hold(hitObject);
	else{
		printf("parse_hitObjects: unkown type (%i)\n", type);
		return;
	}
	parse_hitSample(hitObject, next_token);
	list_add(hitObjects, hitObject);
}

Beatmap* parse_beatmap(char* osuFile){
	strcpy(unwanted, " \r\n");
	unwanted_size = 3;
	FILE* file = fopen(osuFile, "r");
	if (file == NULL) {
		printf("parse_beatmap: failed to open the file\n");
		return NULL;
	}
	Beatmap* beatmap = new_beatmap();
	while (fgets(line, sizeof(line), file)) {
		if (line[1] == '\n' || (line[0] == '/' && line[1] == '/')) continue;
		else if (strncmp(line, "osu file format v", 17) == 0) {
			if (line[17] != '1' || line[18] != '4'){
				printf("parse_beatmap: does not support other osu file format than 14\n");
			}
		}
		else if (strncmp(line, "[General]", 9) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else if (line[0] != '/' && line[1] != '/')
					parse_general(beatmap->general);
			}
		}
		else if (strncmp(line, "[Editor]", 8) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else if (line[0] != '/' && line[1] != '/')
					parse_editor(beatmap->editor);
			}
		}
		else if (strncmp(line, "[Metadata]", 10) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else if (line[0] != '/' && line[1] != '/')
					parse_metadata(beatmap->metadata);
			}
		}
		else if (strncmp(line, "[Difficulty]", 12) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else if (line[0] != '/' && line[1] != '/')
					parse_difficulty(beatmap->difficulty);
			}
		}
		else if (strncmp(line, "[Events]", 8) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else if (line[0] != '/' && line[1] != '/')
					parse_events(beatmap->events);
			}
		}
		else if (strncmp(line, "[TimingPoints]", 14) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else if (line[0] != '/' && line[1] != '/')
					parse_timingPoints(beatmap->timingPoints);
			}
		}
		else if (strncmp(line, "[Colours]", 9) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else if (line[0] != '/' && line[1] != '/')
					parse_colours(beatmap->colours);
			}
		}
		else if (strncmp(line, "[HitObjects]", 12) == 0) {
			while (fgets(line, sizeof(line), file)) {
				if (line[1] == '\n')
					break;
				else if (line[0] != '/' && line[1] != '/')
					parse_hitObjects(beatmap->hitObjects);
			}
		}
	}
	fclose(file);
	return beatmap;
}