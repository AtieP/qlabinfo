#ifndef QLABINFO_H
#define QLABINFO_H

#include <stddef.h>

/* globals */

struct cern_vistar
{
	const char *name;
	const char *image_url;
	const char *logbook_url;
	const char *documentation_url;
	int refresh_rate;
	int ext_refresh_rate;
};

extern struct cern_vistar cern_vistars[];
extern size_t cern_vistars_amount;

/* networking */

int net_init();
int net_download(const char *url, void **buf, size_t *size);
int net_deinit();

/* logging */

enum LogLevels
{
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR
};

void qprint(enum LogLevels level, const char *str);

/* windowing */

enum Keys
{
	KEY_C,
	KEY_D,
	KEY_H,
	KEY_L,
	KEY_U,

	KEY_ARROW_LEFT,
	KEY_ARROW_RIGHT
};

int win_init();
int win_msgbox(enum LogLevels level, const char *title,  const char *str);
int win_image_flush(void *buf, size_t size);
int win_deinit();
void win_detach_main_flow(); /* this timeouts */

extern void win_key_event(enum Keys key);

#endif

