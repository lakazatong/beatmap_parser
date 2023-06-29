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
	sList* tags;
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

typedef struct {
	char* filename;
	int xOffset;
	int yOffset;
} BackgroundEvent;

typedef struct {
	char* filename;
	int xOffset;
	int yOffset;
} VideoEvent;

typedef struct {
	int endTime;
} BreakEvent;

typedef struct {
	int type; 
	int startTime;
	void* event; // 0 BackgroundEvent 1 VideoEvent 2 BreakEvent
} Event;

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
} ComboColour;

/* no additional params
typedef struct {

} SliderTrackOverrideColour; */

/* no additional params
typedef struct {

} SliderBorderColour; */

typedef struct {
	int type; // 0 ComboColour 1 SliderTrackOverrideColour 2 SliderBorderColour
	int red;
	int green;
	int blue;
	void* object;
} Colour;

typedef struct {
	int normal;
	int whistle;
	int finish;
	int clap;
} HitSound;

typedef struct {
	int normalSet;
	int additionSet;
	int index;
	int volume;
	char* filename;
} HitSample;

typedef struct {
	int x;
	int y;
} CurvePoint;

typedef struct {
	char* normalSet;
	char* additionSet;
} EdgeSet;

/* no additional params
typedef struct {

} HitCircle; */

typedef struct {
	char curveType;
	List* curvePoints; // CurvePoint*
	int slides;
	float length;
	iList* edgeSounds;
	List* edgeSets;  // EdgeSet*
} Slider;

typedef struct {
	// x = 256
	// y = 192
	int endTime;
} Spinner;

typedef struct {
	// y = 192
	int endTime;
} Hold;

typedef struct {
	int x;
	int y;
	int time;
	int type;
	int new_combo;
	int combo_skip;
	HitSound* hitSound;
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
ComboColour* new_comboColour();
Colour* new_colour();
HitSound* new_hitSound();
HitSample* new_hitSample();
CurvePoint* new_curvePoint();
EdgeSet* new_edgeSet();
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