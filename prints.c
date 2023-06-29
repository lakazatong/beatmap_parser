#include "prints.h"

void print_int_list(int* list, int size) {
	printf("[");
	for (int i = 0; i < size; i++) {
		printf("%d", list[i]);
		if (i < size - 1) {
			printf(", ");
		}
	}
	printf("]\n");
}
void print_string_list(char** list, int size) {
	printf("[");
	for (int i = 0; i < size; i++) {
		printf("%s", list[i]);
		if (i < size - 1) {
			printf(", ");
		}
	}
	printf("]\n");
}

void printGeneral(const General* general) {
	printf("General:\n\n");
	printf("Audio Filename: %s\n", general->audioFilename);
	printf("Audio Lead-In: %d\n", general->audioLeadIn);
	printf("Audio Hash: %s\n", general->audioHash);
	printf("Preview Time: %d\n", general->previewTime);
	printf("Countdown: %d\n", general->countdown);
	printf("Sample Set: %s\n", general->sampleSet);
	printf("Stack Leniency: %f\n", general->stackLeniency);
	printf("Mode: %d\n", general->mode);
	printf("Letterbox In Breaks: %d\n", general->letterboxInBreaks);
	printf("Story Fire In Front: %d\n", general->storyFireInFront);
	printf("Use Skin Sprites: %d\n", general->useSkinSprites);
	printf("Always Show Playfield: %d\n", general->alwaysShowPlayfield);
	printf("Overlay Position: %s\n", general->overlayPosition);
	printf("Skin Preference: %s\n", general->skinPreference);
	printf("Epilepsy Warning: %d\n", general->epilepsyWarning);
	printf("Countdown Offset: %d\n", general->countdownOffset);
	printf("Special Style: %d\n", general->specialStyle);
	printf("Widescreen Storyboard: %d\n", general->widescreenStoryboard);
	printf("Samples Match Playback Rate: %d\n\n", general->samplesMatchPlaybackRate);
}

void printEditor(const Editor* editor) {
	printf("Editor:\n\n");
	printf("Bookmarks: ");
	if (editor->bookmarks == NULL)
		printf("NULL\n");
	else
		print_int_list(editor->bookmarks->elements, editor->bookmarks->size);
	printf("Distance Spacing: %f\n", editor->distanceSpacing);
	printf("Beat Divisor: %d\n", editor->beatDivisor);
	printf("Grid Size: %d\n", editor->gridSize);
	printf("Timeline Zoom: %f\n\n", editor->timelineZoom);
}

void printMetadata(const Metadata* metadata) {
	printf("Metadata:\n\n");
	printf("Title: %s\n", metadata->title);
	printf("Title (Unicode): %s\n", metadata->titleUnicode);
	printf("Artist: %s\n", metadata->artist);
	printf("Artist (Unicode): %s\n", metadata->artistUnicode);
	printf("Creator: %s\n", metadata->creator);
	printf("Version: %s\n", metadata->version);
	printf("Source: %s\n", metadata->source);
	printf("Tags: ");
	if (metadata->tags == NULL)
		printf("NULL\n");
	else
		print_string_list(metadata->tags->elements, metadata->tags->size);
	printf("Beatmap ID: %d\n", metadata->beatmapID);
	printf("Beatmap Set ID: %d\n", metadata->beatmapSetID);
}

void printDifficulty(const Difficulty* difficulty) {
	printf("Difficulty:\n\n");
	printf("HP Drain Rate: %.2f\n", difficulty->hpDrainRate);
	printf("Circle Size: %.2f\n", difficulty->circleSize);
	printf("Overall Difficulty: %.2f\n", difficulty->overallDifficulty);
	printf("Approach Rate: %.2f\n", difficulty->approachRate);
	printf("Slider Multiplier: %.2f\n", difficulty->sliderMultiplier);
	printf("Slider Tick Rate: %.2f\n\n", difficulty->sliderTickRate);
}