#include "json.h"

#include <curl/curl.h>
#include <string.h>

static size_t write_memory_callback(void* contents, size_t size, size_t nmemb,
                                    void* userp);

cJSON* json_init(char* url) {
  CURL* curl_handle = (void*)0;
  CURLcode res = 0;

	cJSON* json = { 0 };

  memoryStruct chunk;

  chunk.memory = malloc(1);
  chunk.size = 0;

  curl_global_init(CURL_GLOBAL_ALL);
  curl_handle = curl_easy_init();

  if (curl_handle) {
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT,
                     "drouth, https://github.com/sramsay/drouth/issues");
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_memory_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
    res = curl_easy_perform(curl_handle);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    } else {
      json = cJSON_Parse(chunk.memory);
      curl_easy_cleanup(curl_handle);
			free(chunk.memory);
    }
  }

  curl_global_cleanup();
	return json;
}

static size_t write_memory_callback(void* contents, size_t size, size_t nmemb,
                                    void* userp) {
  size_t realsize = size * nmemb;
  struct memoryStruct* mem = (struct memoryStruct*)userp;

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
