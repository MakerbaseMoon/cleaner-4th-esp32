#ifndef __CLEANER_OTA_H__
#define __CLEANER_OTA_H__

#include <Arduino.h>

int update_loop(const String& url);
int runUpdate(Stream& data, size_t size, int command);

#endif