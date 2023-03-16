#include "components/ota.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>

/**
 * @brief Runs the firmware update process using the provided data stream and command.
 * 
 * @param data The data stream containing the firmware update data.
 * @param size The size of the firmware update data.
 * @param command The update command to execute.
 * @return int Returns 0 if the update was successful, and a non-zero error code otherwise.
 */
int runUpdate(Stream& data, size_t size, int command) {
    // Begin the firmware update process
    if(!Update.begin(size, command))
        return 1;

    // Write the firmware update data to the device
    if(Update.writeStream(data) != size)
        return 2;

    // End the firmware update process
    if(!Update.end())
        return 3;

    return 0;
}

/**
 * @brief Attempts to perform a firmware update using the provided URL.
 * 
 * @param url The URL of the firmware update file.
 * @return int Returns the update result code (-1 if the update failed or was not attempted, 0 if the update was successful).
 */
int update_loop(const String& url) {
    int update_num = -1;

    // Initialize an HTTP client with strict redirect handling
    HTTPClient http;
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    http.begin(url);

    // Attempt to perform an HTTP GET request on the update URL
    int httpCode = http.GET();

    // If the HTTP request was successful, attempt to perform a firmware update
    if(httpCode == HTTP_CODE_OK) {
        update_num = runUpdate(*(http.getStreamPtr()), http.getSize(), U_FLASH);
    }

    return update_num;
}