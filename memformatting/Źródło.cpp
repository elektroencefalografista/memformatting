#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>

#define DLLEXPORT __declspec(dllexport)

extern "C" DLLEXPORT  int
__stdcall  GetMinRefreshInterval() {
	return 250;
}

extern "C" DLLEXPORT  char *
__stdcall  function1(char *param1, char *param2) {
	static char outbuf[10];
	char tmpbuf[10];
	int memMB = atoi(param1);
	int precyzja = atoi(param2);
	if (precyzja > 3) return "Zbyt wysoka precyzja";
	if (memMB > 1023) {
		float memGB = memMB / (float)1024;
		_gcvt_s(tmpbuf, memGB, precyzja+2);
		int len = strlen(tmpbuf);
		const char *last_one = &tmpbuf[len - 1];
		if (strcmp(last_one, ".") == 0) {
			strcat(tmpbuf, "0");
			if (precyzja == 1) strcat(tmpbuf, "0");
			if (precyzja == 2) {
				strcat(tmpbuf, "0");
				strcat(tmpbuf, "0");
			}
			if (precyzja >= 3) {
				strcat(tmpbuf, "0");
				strcat(tmpbuf, "0");
				strcat(tmpbuf, "0");
			}
		}
		char * pch = strtok(tmpbuf, ".");
		char * pch2 = strtok(NULL, ".");
		strcpy_s(outbuf, pch);
		strcat_s(outbuf, ",");
		strcat_s(outbuf, pch2);
		//strcpy(outbuf, tmpbuf);
		strcat_s(outbuf, "G");
	} else {
		strcpy(outbuf, param1);
		strcat(outbuf, "M");
	}
	return outbuf;
}