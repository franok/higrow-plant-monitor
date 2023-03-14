// general config


//maximum is 400 days
// uint64_t DEEPSLEEP_SECONDS = 10; // 10 seconds
// uint64_t DEEPSLEEP_SECONDS = 30; // 10 seconds
// uint64_t DEEPSLEEP_SECONDS = 180; // 3 min
// uint64_tDEEPSLEEP_SECONDS = 1800; // 30 min
// uint64_t DEEPSLEEP_SECONDS = 3600; // 60 min number to big
// uint64_t DEEPSLEEP_SECONDS = 7200; // every two hours
// uint64_t DEEPSLEEP_SECONDS = 3600*6; // every 6 hours
// uint64_t DEEPSLEEP_SECONDS = 3600*8; // every 8 hours
uint64_t DEEPSLEEP_SECONDS = 3600*12; // twice a day
// uint64_t DEEPSLEEP_SECONDS = 3600*24; // once a day

uint64_t DEEPSLEEP_CALIBRATION_SECONDS = 0; // if deepsleep lasts longer or shorter than expected, configure this with a positive or negative integer value

#define TEMP_CALIBRATION 0.0 // positive or negative float value to calibrate the temp sensor to the correct temperature
#define SOIL_MIN 1470 // value when soil sensor is in water // round to lower
#define SOIL_MAX 3450 // value when soil sensor is in air // round to upper, otherwise relative value will overflow

// ntp settings
const char* ntpServer = myNtpServer; //"pool.ntp.org";
const long  gmtOffset_sec = 3600; // 0: UTC, 3600: CET
const int   daylightOffset_sec = 3600; // do not change default offset for DST


const String serverUrl = myServerUrl;
const int serverPort = 443;

bool debugEnabled = false; // true if server response starts with "debug", otherwise default: false
