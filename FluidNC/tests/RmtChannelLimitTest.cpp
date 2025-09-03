#include "gtest/gtest.h"
#define HAL_TARGET_ESP32S3 1
#include "../esp32/rmt_hal.h"

// Verify log message when too many axes are configured
// Overí hlásenie pre 5 osí na ESP32-S3
TEST(RmtChannelLimit, ErrorMessage) {
    EXPECT_EQ(RmtAxisLimitMsg(5),
              std::string("ESP32-S3 supports 4 RMT TX channels; configured=5"));
}
