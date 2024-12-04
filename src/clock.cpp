#include <NTPClient.h>
#include <RTC.h>
#include <WiFiUdp.h>
#include <cstdio>

#include "clock.h"

static constexpr char *dateTimeTemplate = "%.2d-%.2d-%.2d %.2d:%.2d";

static WiFiUDP udp;
static NTPClient timeClient(udp);

void initialiseTime() {
  RTC.begin();
  timeClient.begin();
  timeClient.update();

  // NZDT is UTC+13 i.e. 13 hours ahead of UTC
  // 60 minutes per hour, 60 seconds per minute
  const int timeZoneOffsetMiliseconds = 13 * 60 * 60;
  time_t unixTimeStamp = timeClient.getEpochTime() + timeZoneOffsetMiliseconds;
  RTCTime now(unixTimeStamp);
  RTC.setTime(now);
}

void formatCurrentTime(timeStampString buffer) {
  RTCTime now;
  RTC.getTime(now);

  sprintf(buffer, dateTimeTemplate, now.getDayOfMonth(), now.getMonth(),
          now.getYear(), now.getHour(), now.getMinutes());
}
