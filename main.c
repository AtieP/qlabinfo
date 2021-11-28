#include "qlabinfo.h"

#include <stdlib.h>

/* TODO: Refresh rates */

static size_t current_vistar = 0;

static void cleanup()
{
	win_deinit();
	net_deinit();
}

static int display_vistar(size_t idx)
{
	void *image_buffer;
	size_t len;

	if (net_download(cern_vistars[idx].image_url, &image_buffer, &len) != 0)
	{
		qprint(LOG_WARN, "Could not retrieve status");
		return -1;
	}

	if (win_image_flush(image_buffer, len) != 0)
	{
		qprint(LOG_WARN, "Could not display status");
		return -1;
	}

	current_vistar = idx;
	free(image_buffer);

	return 0;
}

static void display_previous_vistar()
{
	size_t idx;
	if (current_vistar == 0)
		idx = cern_vistars_amount - 1;
	else
		idx = current_vistar - 1;

	if (display_vistar(idx) != 0)
	{
		if (idx == 0)
			current_vistar = cern_vistars_amount - 1;
		else
			current_vistar = current_vistar - 1;

		display_previous_vistar();
	}
}

static void display_next_vistar()
{
	size_t idx;
	if (current_vistar == (cern_vistars_amount - 1))
		idx = 0;
	else
		idx = current_vistar + 1;

	if (display_vistar(idx) != 0)
	{
		if (idx == (cern_vistars_amount - 1))
			current_vistar = 0;
		else
			current_vistar = current_vistar + 1;

		display_next_vistar();
	}
}

void win_key_event(enum Keys key)
{
	if (key == KEY_ARROW_LEFT)
	{
		display_previous_vistar();
	}
	else if (key == KEY_ARROW_RIGHT)
	{
		display_next_vistar();
	}
	else if (key == KEY_U)
	{
		display_vistar(current_vistar);
	}
	else if (key == KEY_C)
	{
		win_msgbox(LOG_INFO, "Current vistar",
			cern_vistars[current_vistar].name);
	}
	else if (key == KEY_H)
	{
		win_msgbox(LOG_INFO, "QLabInfo Help",
			"C: Show current Vistar\nU: Update status\n"
			"Arrow left: Previous Vistar\nArrow Right: Next Vistar");
	}
}

int main()
{
	atexit(cleanup);

	if (net_init() != 0)
	{
		qprint(LOG_ERROR, "Could not initialize the network stack");
		return 1;
	}

	if (win_init() != 0)
	{
		qprint(LOG_ERROR, "Could not initialize the windowing stack");
		return 1;
	}

	display_vistar(0);
	win_detach_main_flow();

	return 0;
}
