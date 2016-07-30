#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>
#include <jansson.h>

#include "postdrop.h"

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp; 
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  } 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0; 
  return realsize;
}
 
void PDget(const char *hostname, const char *shorturl) {
  CURL *curl;
  CURLcode res;
  struct MemoryStruct chunk;
  chunk.memory = malloc(1);
  chunk.size = 0;
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if(curl) {
    /* Build URL */
    char url[256];
    strcpy(url,hostname);
    strcat(url,"/note/");
    strcat(url,shorturl);

    /* set URL to request from */
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /* send all data to this function  */ 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    /* Perform request and handle error or success */
    res = curl_easy_perform(curl);
    long http_code = -1;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if(http_code != 200) {
      fprintf(stderr, "Request failed: %d\n", http_code);
    } else {
      /* JSON Parsing */
      json_t *root, *message, *title;
      const char *message_text, *title_text;
      json_error_t error;
      root = json_loads(chunk.memory, 0, &error);
      if(!root)
      {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return;
      }
      if(!json_is_object(root)) {
        fprintf(stderr, "Unexpected JSON");
        return;
      }

      message = json_object_get(root, "text");
      if(!json_is_string(message)) {
        fprintf(stderr, "Unexpected JSON");
        return;
      }
      message_text = json_string_value(message);

      title = json_object_get(root, "title");
      if(!json_is_string(message)) {
        fprintf(stderr, "Unexpected JSON");
        return;
      }
      title_text = json_string_value(title);
      fprintf(stdout, "%s : %s\n", title_text, message_text);
    }
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  free(chunk.memory);
  curl_global_cleanup();
}
void PDlist(const char *hostname) {
  CURL *curl;
  CURLcode res;
  struct MemoryStruct chunk;
  chunk.memory = malloc(1);
  chunk.size = 0;
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if(curl) {
    /* Build URL */
    char url[256];
    strcpy(url,hostname);
    strcat(url,"/note/");

    /* set URL to request from */
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /* send all data to this function  */ 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    /* Perform request and handle error or success */
    res = curl_easy_perform(curl);
    long http_code = -1;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if(http_code != 200) {
      fprintf(stderr, "Request failed: %d\n", http_code);
    } else {
      /* JSON Parsing */
      json_t *root, *notes;
      json_error_t error;
      root = json_loads(chunk.memory, 0, &error);
      if(!root)
      {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return;
      }
      if(!json_is_object(root)) {
        fprintf(stderr, "Unexpected JSON");
        return;
      }

      notes = json_object_get(root, "notes");
      if(!json_is_array(notes)) {
        fprintf(stderr, "Unexpected JSON");
      }

      for(int i=0; i<json_array_size(notes); i++) {
        json_t *note, *message, *title, *shorturl;
        const char *message_text, *title_text, *shorturl_text;
        
        note = json_array_get(notes, i);
        if(!json_is_object(note)) {
          fprintf(stderr, "Unexpected JSON");
          return;
        }

        message = json_object_get(note, "text");
        if(!json_is_string(message)) {
          fprintf(stderr, "Unexpected JSON");
          return;
        }
        message_text = json_string_value(message);

        title = json_object_get(note, "title");
        if(!json_is_string(title)) {
          fprintf(stderr, "Unexpected JSON");
          return;
        }
        title_text = json_string_value(title);
        
        shorturl = json_object_get(note, "shorturl");
        if(!json_is_string(shorturl)) {
          fprintf(stderr, "Unexpected JSON");
          return;
        }
        shorturl_text = json_string_value(shorturl);

        fprintf(stdout, "%s | %s : %s\n", shorturl_text, title_text, message_text);
      }
    }
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  free(chunk.memory);
  curl_global_cleanup();
}
