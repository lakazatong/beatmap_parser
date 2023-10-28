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
	pid_t pid = getpid();\
	FILE* fp = fopen("../io/pid", "w+");\
	char* pid_str = malloc(1);\
	sprintf(pid_str, "%u", pid);\
	fwrite(pid_str, strlen(pid_str), 1, fp);\
	fclose(fp);\
	struct sigaction new_action;\
	new_action.sa_handler = handle_SIGUSR1;\
    sigemptyset(&new_action.sa_mask);\
    new_action.sa_flags = 0;\
    sigaction(SIGUSR1, &new_action, NULL);\
	printf("Program is now waiting for a signal...\n");\
	pause();\
	printf("Resuming program after signal...\n");\
	fp = fopen("../io/out", "w+");\
	fwrite("signal received", 15, 1, fp);\
	fclose(fp);

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