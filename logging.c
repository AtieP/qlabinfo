#include "qlabinfo.h"

#include <stdio.h>

void qprint(enum LogLevels level, const char *str)
{
	const char *title;
	switch (level)
	{
		case LOG_INFO:
			title = "QLabInfo Information"; break;
		case LOG_WARN:
			title = "QLabInfo Warning"; break;
		case LOG_ERROR:
			title = "QLabInfo Error"; break;
		default:
			title = "QLabInfo Dialog"; break;
	}

	if (win_msgbox(level, title, str) != 0)
	{
		printf("%s: %s\n", title, str);
	}
}
