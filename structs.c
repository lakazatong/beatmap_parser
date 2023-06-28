#include "structs.h"

General* new_general(){
	General* r = malloc(sizeof(General));
	r->audioFilename = NULL;
	r->audioLeadIn = 0;
	r->audioHash = NULL;
	r->previewTime = 0;
	r->countdown = 0;
	r->sampleSet = NULL;
	r->stackLeniency = 0;
	r->mode = 0;
	r->letterboxInBreaks = 0;
	r->storyFireInFront = 0;
	r->useSkinSprites = 0;
	r->alwaysShowPlayfield = 0;
	r->overlayPosition = NULL;
	r->skinPreference = NULL;
	r->epilepsyWarning = 0;
	r->countdownOffset = 0;
	r->specialStyle = 0;
	r->widescreenStoryboard = 0;
	r->samplesMatchPlaybackRate = 0;
	return r;
}

Editor* new_editor(){
	Editor* r = malloc(sizeof(Editor));
	r->bookmarks = NULL;
	r->distanceSpacing = 0;
	r->beatDivisor = 0;
	r->gridSize = 0;
	r->timelineZoom = 0;
	return r;
}

Metadata* new_metadata(){
	Metadata* r = malloc(sizeof(Metadata));
	r->title = NULL;
	r->titleUnicode = NULL;
	r->artist = NULL;
	r->artistUnicode = NULL;
	r->creator = NULL;
	r->version = NULL;
	r->source = NULL;
	r->tags = NULL;
	r->beatmapID = 0;
	r->beatmapsetID = 0;
	return r;
}

Difficulty* new_difficulty(){
	Difficulty* r = malloc(sizeof(Difficulty));
	r->hpDrainRate = 0;
	r->circleSize = 0;
	r->overallDifficulty = 0;
	r->approachRate = 0;
	r->sliderMultiplier = 0;
	r->sliderTickRate = 0;
	return r;
}

BackgroundEvent* new_backgroundEvent(){
	BackgroundEvent* r = malloc(sizeof(BackgroundEvent));
	r->filename = NULL;
	r->xOffset = 0;
	r->yOffset = 0;
	return r;
}

VideoEvent* new_videoEvent(){
	VideoEvent* r = malloc(sizeof(VideoEvent));
	r->filename = NULL;
	r->xOffset = 0;
	r->yOffset = 0;
	return r;
}

BreakEvent* new_breakEvent(){
	BreakEvent* r = malloc(sizeof(BreakEvent));
	r->endTime = 0;
	return r;
}

Event* new_event(){
	Event* r = malloc(sizeof(Event));
	r->type = 0;
	r->startTime = 0;
	return r;
}

TimingPoint* new_timingPoint(){
	TimingPoint* r = malloc(sizeof(TimingPoint));
	r->time = 0;
	r->beatLength = 0;
	r->meter = 0;
	r->sampleSet = 0;
	r->sampleIndex = 0;
	r->volume = 0;
	r->uninherited = 0;
	r->effects = 0;
	return r;
}

Colour* new_colour(){
	Colour* r = malloc(sizeof(Colour));
	r->combo = 0;
	r->SliderTrackOverride = 0;
	r->SliderBorder = 0;
	return r;
}

HitSample* new_hitSample(){
	HitSample* r = malloc(sizeof(HitSample));
	r->normalSet = 0;
	r->additionSet = 0;
	r->index = 0;
	r->volume = 0;
	r->filename = NULL;
	return r;
}

Slider* new_slider(){
	Slider* r = malloc(sizeof(Slider));
	r->curveType = 0;
	r->curvePoints = NULL;
	r->slides = 0;
	r->length = 0;
	r->edgeSounds = NULL;
	r->edgeSets = NULL;
	return r;
}

Spinner* new_spinner(){
	Spinner* r = malloc(sizeof(Spinner));
	r->endTime = 0;
	return r;
}

Hold* new_hold(){
	Hold* r = malloc(sizeof(Hold));
	r->endTime = 0;
	return r;
}

HitObject* new_hitObject(){
	HitObject* r = malloc(sizeof(HitObject));
	r->x = 0;
	r->y = 0;
	r->type = 0;
	r->hitSound = 0;
	r->hitSample = NULL;
	return r;
}

Beatmap* new_beatmap(){
	Beatmap* r = malloc(sizeof(Beatmap));
	r->general = NULL;
	r->editor = NULL;
	r->metadata = NULL;
	r->difficulty = NULL;
	r->events = NULL;
	r->timingPoints = NULL;
	r->colours = NULL;
	r->hitObjects = NULL;
	return r;
}

void free_general(General* general){
	free(general);
}

void free_editor(Editor* editor){
	free(editor);
}

void free_metadata(Metadata* metadata){
	free(metadata);
}

void free_difficulty(Difficulty* difficulty){
	free(difficulty);
}

void free_backgroundEvent(BackgroundEvent* backgroundEvent){
	free(backgroundEvent);
}

void free_videoEvent(VideoEvent* videoEvent){
	free(videoEvent);
}

void free_breakEvent(BreakEvent* breakEvent){
	free(breakEvent);
}

void free_event(Event* event){
	switch (event->type){
		case 0:
			free_backgroundEvent((BackgroundEvent*)event->event);
			break;
		case 1:
			free_videoEvent((VideoEvent*)event->event);
			break;
		case 2:
			free_breakEvent((BreakEvent*)event->event);
			break;
	}
	free(event);
}

void free_timingPoint(TimingPoint* timingPoint){
	free(timingPoint);
}

void free_colour(Colour* colour){
	free(colour);
}

void free_hitSample(HitSample* hitSample){
	free(hitSample);
}

void free_slider(Slider* slider){
	free(slider);
}

void free_spinner(Spinner* spinner){
	free(spinner);
}

void free_hold(Hold* hold){
	free(hold);
}

void free_hitObject(HitObject* hitObject){
	switch (hitObject->type){
		case 0:
			break;
		case 1:
			free_slider((Slider*)hitObject->object);
			break;
		case 2:
			free_spinner((Spinner*)hitObject->object);
			break;
		case 3:
			free_hold((Hold*)hitObject->object);
			break;
	}
	free_hitSample(hitObject->hitSample);
	free(hitObject);
}

void free_beatmap(Beatmap* beatmap){
	free_general(beatmap->general);
	free_editor(beatmap->editor);
	free_metadata(beatmap->metadata);
	free_difficulty(beatmap->difficulty);
	int i = 0;
	while (beatmap->events->elements[i] != NULL){
		free_event(beatmap->events->elements[i]);
		i += 1;
	}
	i = 0;
	while (beatmap->timingPoints->elements[i] != NULL){
		free_timingPoint(beatmap->timingPoints->elements[i]);
		i += 1;
	}
	i = 0;
	while (beatmap->colours->elements[i] != NULL){
		free_colour(beatmap->colours->elements[i]);
		i += 1;
	}
	i = 0;
	while (beatmap->hitObjects->elements[i] != NULL){
		free_hitObject(beatmap->hitObjects->elements[i]);
		i += 1;
	}
	free(beatmap);
}

