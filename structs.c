#include "structs.h"

General* new_general(){
	General* r = malloc(sizeof(General));
	r->audioFilename = malloc(1*sizeof(char));
	r->audioLeadIn = 0;
	r->audioHash = malloc(1*sizeof(char));
	r->previewTime = -1;
	r->countdown = 1;
	r->sampleSet = malloc(1*sizeof(char));
	r->stackLeniency = 0.7;
	r->mode = 0;
	r->letterboxInBreaks = 0;
	r->storyFireInFront = 1;
	r->useSkinSprites = 0;
	r->alwaysShowPlayfield = 0;
	r->overlayPosition = malloc(1*sizeof(char));
	r->skinPreference = malloc(1*sizeof(char));
	r->epilepsyWarning = 0;
	r->countdownOffset = 0;
	r->specialStyle = 0;
	r->widescreenStoryboard = 0;
	r->samplesMatchPlaybackRate = 0;
	return r;
}

Editor* new_editor(){
	Editor* r = malloc(sizeof(Editor));
	r->bookmarks = new_ilist(0);
	r->distanceSpacing = 0.0;
	r->beatDivisor = 0;
	r->gridSize = 0;
	r->timelineZoom = 0.0;
	return r;
}

Metadata* new_metadata(){
	Metadata* r = malloc(sizeof(Metadata));
	r->title = malloc(1*sizeof(char));
	r->titleUnicode = malloc(1*sizeof(char));
	r->artist = malloc(1*sizeof(char));
	r->artistUnicode = malloc(1*sizeof(char));
	r->creator = malloc(1*sizeof(char));
	r->version = malloc(1*sizeof(char));
	r->source = malloc(1*sizeof(char));
	r->tags = new_slist(0);
	r->beatmapID = 0;
	r->beatmapSetID = 0;
	return r;
}

Difficulty* new_difficulty(){
	Difficulty* r = malloc(sizeof(Difficulty));
	r->hpDrainRate = 0.0;
	r->circleSize = 0.0;
	r->overallDifficulty = 0.0;
	r->approachRate = 0.0;
	r->sliderMultiplier = 0.0;
	r->sliderTickRate = 0.0;
	return r;
}

BackgroundEvent* new_backgroundEvent(){
	BackgroundEvent* r = malloc(sizeof(BackgroundEvent));
	r->filename = malloc(1*sizeof(char));
	r->xOffset = 0;
	r->yOffset = 0;
	return r;
}

VideoEvent* new_videoEvent(){
	VideoEvent* r = malloc(sizeof(VideoEvent));
	r->filename = malloc(1*sizeof(char));
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
	r->event = NULL;
	return r;
}

TimingPoint* new_timingPoint(){
	TimingPoint* r = malloc(sizeof(TimingPoint));
	r->time = 0;
	r->beatLength = 0.0;
	r->meter = 0;
	r->sampleSet = 0;
	r->sampleIndex = 0;
	r->volume = 0;
	r->uninherited = 0;
	r->effects = 0;
	return r;
}

ComboColour* new_comboColour(){
	ComboColour* r = malloc(sizeof(ComboColour));
	r->combo = 0;
	return r;
}

Colour* new_colour(){
	Colour* r = malloc(sizeof(Colour));
	r->type = 0;
	r->red = 0;
	r->green = 0;
	r->blue = 0;
	r->object = NULL;
	return r;
}

HitSample* new_hitSample(){
	HitSample* r = malloc(sizeof(HitSample));
	r->normalSet = 0;
	r->additionSet = 0;
	r->index = 0;
	r->volume = 0;
	r->filename = malloc(1*sizeof(char));
	return r;
}

Slider* new_slider(){
	Slider* r = malloc(sizeof(Slider));
	r->curveType = 0;
	r->curvePoints = new_slist(0);
	r->slides = 0;
	r->length = 0.0;
	r->edgeSounds = new_ilist(0);
	r->edgeSets = new_slist(0);
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
	r->object = NULL;
	r->hitSample = new_hitSample();
	return r;
}

Beatmap* new_beatmap(){
	Beatmap* r = malloc(sizeof(Beatmap));
	r->general = new_general();
	r->editor = new_editor();
	r->metadata = new_metadata();
	r->difficulty = new_difficulty();
	r->events = new_list(0);
	r->timingPoints = new_list(0);
	r->colours = new_list(0);
	r->hitObjects = new_list(0);
	return r;
}

void free_general(General* general){
	free(general->audioFilename);
	free(general->audioHash);
	free(general->sampleSet);
	free(general->overlayPosition);
	free(general->skinPreference);
	free(general);
}

void free_editor(Editor* editor){
	free_ilist(editor->bookmarks);
	free(editor);
}

void free_metadata(Metadata* metadata){
	free(metadata->title);
	free(metadata->titleUnicode);
	free(metadata->artist);
	free(metadata->artistUnicode);
	free(metadata->creator);
	free(metadata->version);
	free(metadata->source);
	free_slist(metadata->tags);
	free(metadata);
}

void free_difficulty(Difficulty* difficulty){
	free(difficulty);
}

void free_backgroundEvent(BackgroundEvent* backgroundEvent){
	free(backgroundEvent->filename);
	free(backgroundEvent);
}

void free_videoEvent(VideoEvent* videoEvent){
	free(videoEvent->filename);
	free(videoEvent);
}

void free_event(Event* event){
	if (event->type == 0) free_backgroundEvent((BackgroundEvent*)event->event);
	else if (event->type == 1) free_videoEvent((VideoEvent*)event->event);
	else
		free(event->event);
	free(event);
}

void free_timingPoint(TimingPoint* timingPoint){
	free(timingPoint);
}

void free_colour(Colour* colour){
	if (colour->type == 0) free(colour->object);
	free(colour);
}

void free_hitSample(HitSample* hitSample){
	free(hitSample->filename);
	free(hitSample);
}

void free_slider(Slider* slider){
	free_slist(slider->curvePoints);
	free_ilist(slider->edgeSounds);
	free_slist(slider->edgeSets);
	free(slider);
}

void free_hitObject(HitObject* hitObject){
	if (hitObject->type == 1)
		free_slider((Slider*)hitObject->object);
	else if (hitObject->type != 0)
		free(hitObject->object);
	free_hitSample(hitObject->hitSample);
	free(hitObject);
}

void free_beatmap(Beatmap* beatmap){
	free_general(beatmap->general);
	free_editor(beatmap->editor);
	free_metadata(beatmap->metadata);
	free_difficulty(beatmap->difficulty);
	int i = 0;
	while (i < beatmap->events->size) free_event(beatmap->events->elements[i++]);
	free(beatmap->events);
	i = 0;
	while (i < beatmap->timingPoints->size) free_timingPoint(beatmap->timingPoints->elements[i++]);
	free(beatmap->timingPoints);
	i = 0;
	while (i < beatmap->colours->size) free_colour(beatmap->colours->elements[i++]);
	free(beatmap->colours);
	i = 0;
	while (i < beatmap->hitObjects->size) free_hitObject(beatmap->hitObjects->elements[i++]);
	free(beatmap->hitObjects);
	free(beatmap);
}
