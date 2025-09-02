#include "gtest/gtest.h"
#include <vector>

struct speedEntry {
    uint32_t speed;
    float    percent;
    uint32_t offset;
    uint32_t scale;
};

static void setupSpeeds(std::vector<speedEntry>& speeds, uint32_t max_dev_speed) {
    int nsegments = speeds.size() - 1;
    if (nsegments < 1) {
        return;
    }
    for (int i = 0; i < nsegments; ++i) {
        speeds[i].offset = speeds[i].percent / 100.0f * max_dev_speed;
        float deltaPercent = (speeds[i + 1].percent - speeds[i].percent) / 100.0f;
        float deltaRPM     = speeds[i + 1].speed - speeds[i].speed;
        float scale        = deltaRPM == 0.0f ? 0.0f : (deltaPercent / deltaRPM);
        scale *= max_dev_speed;
        speeds[i].scale = uint32_t(scale * 65536);
    }
    speeds[nsegments].offset = speeds[nsegments].percent / 100.0f * max_dev_speed;
    speeds[nsegments].scale  = 0;
}

static uint32_t mapSpeed(const std::vector<speedEntry>& speeds, uint32_t speed) {
    if (speeds.empty()) {
        return 0;
    }
    if (speed < speeds[0].speed) {
        return speeds[0].offset;
    }
    int num_segments = speeds.size() - 1;
    int i;
    for (i = 0; i < num_segments; i++) {
        if (speed < speeds[i + 1].speed) {
            break;
        }
    }
    uint32_t dev_speed = speeds[i].offset;
    if (i < num_segments) {
        dev_speed += uint32_t(((speed - speeds[i].speed) * uint64_t(speeds[i].scale)) >> 16);
    }
    return dev_speed;
}

TEST(DacSpindleScaling, LinearMapping8Bit) {
    std::vector<speedEntry> speeds = { {0,0}, {1000,100} };
    setupSpeeds(speeds, 255);
    EXPECT_EQ(mapSpeed(speeds,0), 0u);
    EXPECT_NEAR(mapSpeed(speeds,500), 127u, 1u);
    EXPECT_EQ(mapSpeed(speeds,1000), 255u);
}

TEST(DacSpindleScaling, LinearMapping12Bit) {
    std::vector<speedEntry> speeds = { {0,0}, {1000,100} };
    setupSpeeds(speeds, 4095);
    EXPECT_EQ(mapSpeed(speeds,0), 0u);
    EXPECT_NEAR(mapSpeed(speeds,500), 2047u, 2u);
    EXPECT_EQ(mapSpeed(speeds,1000), 4095u);
}
