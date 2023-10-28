/* needs c_utils repo to be in the parent directory (see structs.h):
	../
		c_utils/
			...
		beatmap_parser/
			...
			test.c (this file)
*/
#include <unistd.h>
#include <signal.h>

#include "src/parser.h"
#include "src/prints.h"
#include "src/jsonify.h"

void handle_SIGUSR1(int sig) {
	printf("Received SIGUSR1. Doing custom handling.\n");
}

#define MAIN_BODY_LINUX \
	struct sigaction new_action;\
	new_action.sa_handler = handle_SIGUSR1;\
    sigemptyset(&new_action.sa_mask);\
    new_action.sa_flags = 0;\
    sigaction(SIGUSR1, &new_action, NULL);\
	printf("%u", getpid());\
	pause();\
	printf("signal received");\

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