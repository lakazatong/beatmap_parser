#ifndef STRUCTS_H
#define STRUCTS_H
#include "list.h"

typedef struct {
	char* audioFilename;
	int audioLeadIn;
	char* audioHash;
	int previewTime;
	int countdown;
	char* sampleSet;
	float stackLeniency;
	int mode;
	int letterboxInBreaks;
	int storyFireInFront;
	int useSkinSprites;
	int alwaysShowPlayfield;
	char* overlayPosition;
	char* skinPreference;
	int epilepsyWarning;
	int countdownOffset;
	int specialStyle;
	int widescreenStoryboard;
	int samplesMatchPlaybackRate;
} General;

typedef struct {
	iList* bookmarks;
	float distanceSpacing;
	int beatDivisor;
	int gridSize;
	float timelineZoom;
} Editor;

typedef struct {
	char* title;
	char* titleUnicode;
	char* artist;
	char* artistUnicode;
	char* creator;
	char* version;
	char* source;
	sList* tags; // char*
	int beatmapID;
	int beatmapSetID;
} Metadata;

typedef struct {
	float hpDrainRate;
	float circleSize;
	float overallDifficulty;
	float approachRate;
	float sliderMultiplier;
	float sliderTickRate;
} Difficulty;

// ...,filename,xOffset,yOffset
typedef struct {
	char* filename;
	int xOffset;
	int yOffset;
} BackgroundEvent;

// ...,filename,xOffset,yOffset
typedef struct {
	char* filename;
	int xOffset;
	int yOffset;
} VideoEvent;

// ...,endTime
typedef struct {
	int endTime;
} BreakEvent;

// eventType,startTime,eventParams
typedef struct {
	int type; 
	int startTime;
	void* event; // 0 BackgroundEvent 1 VideoEvent 2 BreakEvent
} Event;

// time,beatLength,meter,sampleSet,sampleIndex,volume,uninherited,effects
typedef struct {
	int time;
	float beatLength;
	int meter;
	int sampleSet;
	int sampleIndex;
	int volume;
	int uninherited;
	int effects;
} TimingPoint;

typedef struct {
	int combo;
	int SliderTrackOverride;
	int SliderBorder;
} Colour;

// normalSet:additionSet:index:volume:filename
typedef struct {
	int normalSet;
	int additionSet;
	int index;
	int volume;
	// <sampleSet>-hit<hitSound><index>.wav
	char* filename;
} HitSample;
/*
// no additional params
typedef struct {

} HitCircle;
*/
// ...,curveType|curvePoints,slides,length,edgeSounds,edgeSets,...
typedef struct {
	// B = bézier, C = centripetal catmull-rom, L = linear, P = perfect circle
	char curveType;
	// x1:y1|x2:y2|... (?)
	List* curvePoints; // char*
	int slides;
	float length;
	// integer1|interger2|... (?)
	iList* edgeSounds;
	// normalSet1:additionSet1|normalSet2:additionSet2|... (?)
	List* edgeSets; // char*
} Slider;

// ...,endTime,...
typedef struct {
	// x = 256
	// y = 192
	int endTime;
} Spinner;

// ...,endTime:...
typedef struct {
	// y = 192
	int endTime;
} Hold;

// x,y,time,type,hitSound,objectParams,hitSample
typedef struct {
	int x;
	int y;
	int type; 
	int hitSound;
	void* object; // 0 HitCircle 1 Slider 2 Spinner 3 Hold
	HitSample* hitSample;
} HitObject;

typedef struct {
	General* general;
	Editor* editor;
	Metadata* metadata;
	Difficulty* difficulty;
	List* events; // Event*
	List* timingPoints; // TimingPoint*
	List* colours; // Colour*
	List* hitObjects; // HitObject*
} Beatmap;

// generated prototypes

General* new_general();
Editor* new_editor();
Metadata* new_metadata();
Difficulty* new_difficulty();
BackgroundEvent* new_backgroundEvent();
VideoEvent* new_videoEvent();
BreakEvent* new_breakEvent();
Event* new_event();
TimingPoint* new_timingPoint();
Colour* new_colour();
HitSample* new_hitSample();
Slider* new_slider();
Spinner* new_spinner();
Hold* new_hold();
HitObject* new_hitObject();
Beatmap* new_beatmap();
void free_general(General* general);
void free_editor(Editor* editor);
void free_metadata(Metadata* metadata);
void free_difficulty(Difficulty* difficulty);
void free_backgroundEvent(BackgroundEvent* backgroundEvent);
void free_videoEvent(VideoEvent* videoEvent);
void free_breakEvent(BreakEvent* breakEvent);
void free_event(Event* event);
void free_timingPoint(TimingPoint* timingPoint);
void free_colour(Colour* colour);
void free_hitSample(HitSample* hitSample);
void free_slider(Slider* slider);
void free_spinner(Spinner* spinner);
void free_hold(Hold* hold);
void free_hitObject(HitObject* hitObject);
void free_beatmap(Beatmap* beatmap);

#endif