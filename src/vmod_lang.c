/**
 * vmod_lang.c
 *
 * Copyright (c) 2014 by Byteworks GmbH
 * All rights reserved
 *
 * http://www.byteworks.ch/
 *
 * This vmod has been inspired by:
 * - https://github.com/varnish/libvmod-example
 * - https://github.com/cosimo/varnish-accept-language
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "config.h"

#include "vrt.h"
#include "bin/varnishd/cache.h"

#include "vcc_if.h"

#define LANG_LIST_SIZE		16
#define LANG_SIZE			8


typedef struct {
	char lang[LANG_SIZE];
	float prio;
} lang_list_item_t;

typedef struct{
	lang_list_item_t data[LANG_LIST_SIZE];
	unsigned int count;
} lang_list_t;


void
_lang_list_push(lang_list_t *lang_list, char *lang, float prio)
{
	// FIXME: At the moment we silently ignore if we have more than LANG_LIST_SIZE languages...
	if (lang_list->count >= LANG_LIST_SIZE - 1) return;

	strncpy(lang_list->data[lang_list->count].lang, lang, LANG_SIZE);
	lang_list->data[lang_list->count].prio = prio;
	lang_list->count++;
}


int
_lang_list_sort(const void *x, const void *y)
{
    lang_list_item_t *a = (lang_list_item_t *) x;
    lang_list_item_t *b = (lang_list_item_t *) y;

    if (a->prio > b->prio) return -1;
    if (a->prio < b->prio) return 1;

    return 0;
}


void
strtolower(char *str)
{
	char *c;

	for (c = str; *c; c++) {
		if (isupper(*c)) *c = tolower(*c);
	}

	return;
}


int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
    return (0);
}

const char
*vmod_detect(struct sess *sp, const char *header, const char *languages, const char *language)
{
	char       *token;
	char       *token_ptr;
	char        data[256];
	char       *data_ptr;
	char       *temp_ptr;
	lang_list_t lang_list;
	float       prio;
    int         i;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	CHECK_OBJ_NOTNULL(sp->ws, WS_MAGIC);
	assert(languages);
	assert(language);

	// Empty or default header, return immediately
    if (!header || strlen(header) == 0 || strcmp(header, language) == 0) {
		return language;
	}

	// Copy header as strtok() changes the source string
	strncpy(data, header, sizeof(data));
	data_ptr = data;

	strtolower(data);

	// Initialize language list
	memset(&lang_list, 0, sizeof(lang_list));

	// Tokenize accept-language header
	while ((token = strtok_r(data_ptr, ",", &token_ptr))) {
		// strtok() wants NULL on subsequent calls 
		data_ptr = NULL;

		// Ignore spaces
		while (*token == ' ') token++;

		// Ignore any/empty language
		if (*token == '*' || strlen(token) == 0) continue;

		// Get priority
		if ((temp_ptr = strstr(token, ";q="))) {
			*temp_ptr = '\0';

            if (sscanf(temp_ptr + 3, "%f", &prio) == 0) continue;
		}
		else {
			prio = 1.0;
		}

		// Add language to list
		_lang_list_push(&lang_list, token, prio);

		// In case of languages like en-GB add also the root language en
		if ((temp_ptr = strstr(token, "-"))) {
			*temp_ptr = '\0';

			_lang_list_push(&lang_list, token, prio - 0.0001);
		}
	}

	// Sort by priority
	qsort(lang_list.data, lang_list.count, sizeof(lang_list_item_t), &_lang_list_sort);

	for (i = 0; i < lang_list.count; i++) {
		if (strstr(languages, lang_list.data[i].lang) != NULL) {
			return WS_Dup(sp->ws, lang_list.data[i].lang);
		}
	}

	return WS_Dup(sp->ws, language);
}


const char *
vmod_version(struct sess *sp)
{
	return VERSION;
}

