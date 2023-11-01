
#if HERMIT_LOGGING_ON == 1
    #include <stdio.h>
    #include <time.h>
    void log_event(const char* function_name, const char* content) {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        const time_t now = tv.tv_sec;
        struct tm* tm_info = localtime(&now);
        char timestamp[25];  // Adjust the buffer size to accommodate milliseconds
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

        // Calculate and append milliseconds
        int milliseconds = tv.tv_usec / 1000;
        snprintf(timestamp + 19, 6, ".%03d", milliseconds);
        printf("%s - %s - LOG::[%s]\n", timestamp, function_name, content);
    }
#else
    void log_event(const char* function_name, const char* content) {}
#endif