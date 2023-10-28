/* needs c_utils repo to be in the parent directory (see structs.h):
	../
		c_utils/
			...
		beatmap_parser/
			...
			test.c (this file)
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "src/parser.h"
#include "src/prints.h"
#include "src/jsonify.h"

void handle_SIGINT(int sig) {
	FILE* fp = fopen("io/busy", "w+");
	fclose(fp);
	Beatmap* bm = parse_beatmap("../io/in");
	jsonify_beatmap(bm, "../io/out");
	remove("io/busy");
}

#define MAIN_BODY_LINUX \
	struct sigaction new_action;\
	new_action.sa_handler = handle_SIGINT;\
    sigemptyset(&new_action.sa_mask);\
    new_action.sa_flags = 0;\
    sigaction(SIGINT, &new_action, NULL);\
	while (1)\
		pause();\
	printf("beatmap_parser terminated");

#define MAIN_BODY_WIN MAIN_BODY_LINUX

#ifndef _WIN32

int main(int argc, char* argv[]){
	MAIN_BODY_LINUX
	return 0;
}

#else

#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	MAIN_BODY_WIN
	return 0;
}

#endif