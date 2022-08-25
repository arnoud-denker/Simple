#ifndef __ALOG_H_
#define __ALOG_H_

#include "sdkconfig.h"
#include "esp_log.h"

#define DBG(format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_DEBUG, TAG, format, ##__VA_ARGS__)
#define LOG(format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO, TAG, format, ##__VA_ARGS__)
#define WARN(format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_WARN, TAG, format, ##__VA_ARGS__)
#define ERR(format, ... ) do { ESP_LOG_LEVEL_LOCAL(ESP_LOG_ERROR, TAG, format, ##__VA_ARGS__); } while(0)
// #define FATAL(err, format, ... ) do { ESP_LOG_LEVEL_LOCAL(ESP_LOG_ERROR, TAG, format, ##__VA_ARGS__); fatal_abort(err); } while(1)


#ifdef CONFIG_DEBUG_NETWORK
#define NETDBG(format, ... ) do { ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO, TAG, format, ##__VA_ARGS__); } while(0)
#else
#define NETDBG(format, ...) do {} while(0)
#endif

#ifdef CONFIG_LOG_RETRY
#define NETRTR(format, ... ) do { ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO, TAG, format, ##__VA_ARGS__); } while(0)
#else
#define NETRTR(format, ...) do {} while(0)
#endif

#ifdef CONFIG_LOG_NETWORK
#define NETLOG(format, ... ) do { ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO,    TAG, format, ##__VA_ARGS__); } while(0)
#else
#define NETLOG(format, ...) do {} while(0)
#endif

#ifdef CONFIG_DEBUG_LINKINTF
#define LINKDBG(format, ... ) do { ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO, TAG, format, ##__VA_ARGS__); } while(0)
#else
#define LINKDBG(format, ...) do {} while(0)
#endif

#ifdef CONFIG_LOG_LINKINTF
#define LINKLOG(format, ... ) do { ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO, TAG, format, ##__VA_ARGS__); } while(0)
#else
#define LINKLOG(format, ...) do {} while(0)
#endif

#endif // ALOG_H
