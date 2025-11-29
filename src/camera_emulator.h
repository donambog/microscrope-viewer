#ifndef CAMERA_EMULATOR_H
#define CAMERA_EMULATOR_H

#include <vector>
#include <cmath>
#include <chrono>
#include "Data.h"

/**
 * @brief Camera emulator for microscope
 * 
 * Generates 200x100 pixel frames with three Gaussian spots:
 * - Two fixed spots (left and right)
 * - One moving spot (center, moves horizontally and oscillates vertically)
 */
class CameraEmulator {
public:
    static constexpr int WIDTH = 200;
    static constexpr int HEIGHT = 100;
    
    /**
     * @brief Reads the current frame from the emulated camera
     * @return Frame 100x200 with values between 0 and ~3
     */
    static Frame readCurrentFrame();
    
    /**
     * @brief Calculate X-axis profile (average along columns)
     * @param frame Input frame
     * @return Vector of 200 values (one per column)
     */
    static std::vector<double> calculateXProfile(const Frame& frame);
    
    /**
     * @brief Calculate Y-axis profile (average along rows)
     * @param frame Input frame
     * @return Vector of 100 values (one per row)
     */
    static std::vector<double> calculateYProfile(const Frame& frame);
    
private:
    /**
     * @brief Calculates time-based index for animation
     * @return Index between 0 and 99
     */
    static int getCurrentIndex();
};

#endif // CAMERA_EMULATOR_H
