#include "kvs.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

int main() {
    void* kvslib = dlopen("libkvs.so", RTLD_LAZY);
    if (!kvslib) {
        fprintf(stderr, "Failed to open libkvs.so: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    kvs_t* (*open)() = dlsym(kvslib, "open");
	if (open == NULL) {
        fprintf(stderr, "Failed to find function open: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    void (*set)(kvs_t*, const char*, const char*) = dlsym(kvslib, "set");
	if (set == NULL) {
        fprintf(stderr, "Failed to find function set: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    char* (*get)(kvs_t*, const char*) = dlsym(kvslib, "get");
	if (get == NULL) {
        fprintf(stderr, "Failed to find function get: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    void (*close)(kvs_t*) = dlsym(kvslib, "close");
	if (close == NULL) {
        fprintf(stderr, "Failed to find function close: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    if(dlerror() != NULL) {
        fprintf(stderr, "Failed to find functions: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    kvs_t* kvs = open();
    if(!kvs) {
        printf("Failed to open kvs\n");
        return -1;
    }

    FILE* file = fopen("query.dat", "r");
    if(!file) {
        printf("Failed to open file: query.dat\n");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];
    while(fgets(line, sizeof(line), file)) {
        char* op = strtok(line, ",");
        char* key = strtok(NULL, ",");
        char* value = strtok(NULL, ",");

        if(strcmp(op, "set") == 0) {
            set(kvs, key, value);
        } else if(strcmp(op, "get") == 0) {
            char* result = get(kvs, key);
            FILE* out = fopen("answer.dat", "a");
            if(out) {
                if (result) {
                    fprintf(out, "%s", result);
                    free(result);
                } else {
                    fprintf(out, "%s\n", "-1");
                }
                fclose(out);
            }
        }
    }

    fclose(file);
    close(kvs);
    dlclose(kvslib);

    return 0;
}
