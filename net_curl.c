#include "qlabinfo.h"

#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

static struct
{
	char *dest;
	size_t size;
} destination;

static size_t receive_data(void *buf, size_t size, size_t nmemb, void *userp)
{
	size_t actual_size = size * nmemb;

	char *dest = realloc(destination.dest,
			destination.size + actual_size + 1);
	if (dest == NULL)
		return 0;

	destination.dest = dest;
	memcpy(&destination.dest[destination.size], buf, actual_size);
	destination.size += actual_size;

	return actual_size;
}

int net_init()
{
	if (curl_global_init(CURL_GLOBAL_ALL) != 0)
	{
		qprint(LOG_ERROR, "curl: Failed to initialize library");
		return -1;
	}
	return 0;
}

int net_deinit()
{
	curl_global_cleanup();
	return 0;
}

int net_download(const char *url, void **buf, size_t *size)
{
	destination.dest = NULL;
	destination.size = 0;

	CURL *handle = curl_easy_init();
	curl_easy_setopt(handle, CURLOPT_URL, url);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, receive_data);

	if (curl_easy_perform(handle) != 0)
		return -1;

	*buf = destination.dest;
	*size = destination.size;

	return 0;
}
