/*
	Uncomment to run isolated tests on beatmap_parser only.
	Otherwise, it considers to be used as a library.
*/

#define BEATMAP_PARSER_TEST

#include <time.h>
#include "parser.h"
#include "prints.h"
#include "jsonify.h"

#define MAIN_ARGS void

#define MAIN_BODY \
	Beatmap* bm = parse_beatmap("mania.osu");\
	jsonify_beatmap(bm, "test_bm.json");

#ifdef linux
int main(MAIN_ARGS){
	clock_t begin = clock();
	MAIN_BODY
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time of execution: %lf\n", time_spent);
	return 0;
}
#else
int WinMain(MAIN_ARGS){
	clock_t begin = clock();
	MAIN_BODY
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time of execution: %lf\n", time_spent);
	return 0;
}
#endif