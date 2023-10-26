// Uncomment to run isolated tests on beatmap_parser only.
// Otherwise, it considers to be used as a library.
// (see structs.h to understand what it means)

#include <time.h>

#include "parser.h"
#include "prints.h"
#include "jsonify.h"

#define MAIN_BODY_WIN \
	if (!strcmp(lpCmdLine, ""))\
		return 1;\
	Beatmap* bm = parse_beatmap((char*)lpCmdLine);\
	char filename[1024];\
	if (sprintf(filename, "%i.json", bm->metadata->beatmapID) < 0)\
		return 1;\
	jsonify_beatmap(bm, filename);

#define MAIN_BODY_LINUX \
	if (argc < 2)\
		return 1;\
	Beatmap* bm = parse_beatmap((char*)argv[1]);\
	char filename[1024];\
	if (sprintf(filename, "%i.json", bm->metadata->beatmapID) < 0)\
		return 1;\
	jsonify_beatmap(bm, filename);

#ifndef _WIN32

int main(int argc, char* argv[]){
	clock_t begin = clock();
	MAIN_BODY_LINUX
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time of execution: %lf\n", time_spent);
	return 0;
}

#else

#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	clock_t begin = clock();
	MAIN_BODY_WIN
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time of execution: %lf\n", time_spent);
	return 0;
}

#endif
