/* See LICENSE file for copyright and license details. */

/* neo.c, made by Leliel, 2025 (inspired by narkhy's MatrixHasYou.py). */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LIGHT_GREEN "\033[92m"
#define DARK_GREEN "\033[0;32m"
#define BOLDON "\033[1m"
#define CURSORON "\x1b[?25h"
#define CURSOROFF "\x1b[?25l"
#define END "\033[0m"
#define IDENTATION "\n\n\n      "

/* 
 * makes text strings seem typed live. Inspired in the film "The Matrix".
 * const char *msg: string to simulate typed live
 * float delay: seconds before new character shows up
 * int remain: seconds before message dissappears
 */
void live_type(const char *msg, float delay, float remain);

/*
 * same as live_type, but it takes an array of secs for each character to wait
 * const char *msg: string to simulate typed live
 * const char *secs: number of microsecs for each character of the message to wait
 * float delay_factor: the delay factor for each character to wait until the next one is displayed
 * float remain_factor: the remain factor for the text to stay in the screen
 */
void variable_live_type(const char *msg, const float *secs, float delay_factor, float remain_factor);

int
main(void)
{ 
	const float remain_factor = 0.2f * 1000000; // affects typing speed. Lower for faster emulation. '1.0f * 1000000' for real scene times.
	const float delay_factor = 0.7f * 1000000; // affects messages display time. Lower for faster emulation. '1.0f * 100000' for real scene times.

	const char *msg1 = "Wake up, Neo...";
	const char *msg2 = "The Matrix has you...";
	const char *msg3 = "Follow the white rabbit.";
	const char *msg4 = "Knock, knock, Neo.";

	const float secs1[] = {
		0.0000, 0.1500, 0.1625, 0.1500, 0.1625,
		0.1500, 0.1625, 0.1500, 0.1200, 0.1250,
		0.1200, 0.1250, 0.0625, 0.0875, 0.0625,
	};
    
	const float secs2[] = {
		0.0000, 0.7325, 0.6700, 0.6000, 0.7800,
		0.0950, 0.1350, 0.1075, 0.5275, 0.6225,
		0.0080, 0.1200, 0.1475, 0.4500, 0.0080,
		0.4275, 0.1275, 0.1425, 0.3550, 0.2275, 0.1450
	};

	system("clear && stty -echo");
	/* set text to bold green, hide the cursor and put identation on the line. */
	printf(BOLDON LIGHT_GREEN CURSOROFF IDENTATION);

	variable_live_type(msg1, secs1, delay_factor, 16.03 * remain_factor);
	variable_live_type(msg2, secs2, delay_factor, 7.54 * remain_factor);
	live_type(msg3, 0.1167 * delay_factor, 8.515 * remain_factor);

	printf("%s", msg4);
	fflush(stdout);
	sleep(4);

 	/* unhide cursor and set all text formating back to system default. */
	printf("%s\n", CURSORON END);
	system("clear");
	
	return 0;
}

void live_type(const char *msg, float delay, float remain)
{
	char c;
	while (c = *(msg++)) {
		putchar(c);
		fflush(stdout);
        	usleep(delay);
	}
	usleep(remain);

	system("clear");
	printf(IDENTATION);
}

void variable_live_type(const char *msg, const float *secs, float delay_factor, float remain_factor)
{
	int i = 0;
       	char c;
	while ((c = msg[i]) != '\0') {
		usleep(secs[i++] * delay_factor);
		putchar(c);
		fflush(stdout);
	}
	usleep(remain_factor);

	system("clear");
	printf(IDENTATION);
}
