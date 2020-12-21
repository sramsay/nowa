/*
 * json.c
 *
 * This file is part of nowa. Functions for retrieving JSON data (with libcurl).
 *
 * Written and maintained by Stephen Ramsay (sramsay on GitHub)
 *
 * Last Modified: Mon Dec 21 12:16:58 CST 2020
 *
 * Copyright © 2020 Stephen Ramsay
 *
 * nowa is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option) any
 * later version.
 *
 * nowa is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with nowa; see the file COPYING.  If not see
 * <http://www.gnu.org/licenses/>.
 */

#include "json.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct memory_struct memory_struct;

struct memory_struct {
  char* memory;
  size_t size;
};

static size_t write_memory_callback(void* contents, size_t size, size_t nmemb,
                                    void* userp);

cJSON* json_init(char const url[restrict static 1]) {
  cJSON* json = {0};

  struct memory_struct chunk;
  chunk.memory = malloc(1);
  if (!chunk.memory) {
    fprintf(stderr, "Fatal Error: No available memory\n");
    exit(1);
  }
  chunk.size = 0;

  curl_global_init(CURL_GLOBAL_ALL);
  CURL* curl_handle = curl_easy_init();

  if (curl_handle) {
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT,
                     "nowa, https://github.com/sramsay/nowa/issues");
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_memory_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
    CURLcode res = curl_easy_perform(curl_handle);
    if (res != CURLE_OK) {
      fprintf(stderr, "Network Error: %s\n", curl_easy_strerror(res));
      curl_easy_cleanup(curl_handle);
      free(chunk.memory);
      curl_global_cleanup();
      exit(1);
    } else {
      json = cJSON_Parse(chunk.memory);
    }
  }

  curl_easy_cleanup(curl_handle);
  free(chunk.memory);
  curl_global_cleanup();
  return json;
}

static size_t write_memory_callback(void* contents, size_t size, size_t nmemb,
                                    void* userp) {
  size_t realsize = size * nmemb;
  struct memory_struct* mem = (struct memory_struct*)userp;

  char* ptr = realloc(mem->memory, mem->size + realsize + 1);
  if (ptr == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}
