/* to compile: gcc print_log.c -o print_log
   to run:  ./print_log
   to see results: cat logfile.txt
   */

#include <stdio.h>
#include <stdarg.h> 
#include <time.h>

int printlog(const char* fmt, ...);

static FILE* logfile = NULL;

int main()
{
    int a = 10, b = -2, sum = a + b;

	time_t result = time(NULL); /* this will give us current time stamp */

	printlog("Starting new log at @ %s", asctime(localtime(&result)));
	printlog("Add %d, %d to get %d.\n", a, b, sum);

	if (logfile != NULL)
		fclose(logfile);
}

int printlog (const char* fmt, ...)
{
	va_list args;

	if (logfile == NULL) {
		logfile = fopen("logfile.txt", "a");
		if (logfile == NULL) { 
			return -1; 
		}
	}

	va_start(args, fmt);
	return vfprintf(logfile, fmt, args);
}

