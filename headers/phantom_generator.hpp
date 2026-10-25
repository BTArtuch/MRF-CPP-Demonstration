#pragma once

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

// Define the physical parameters for a single voxel
struct Voxel {
    float T1; // Spin-lattice relaxation time (ms)
    float T2; // Spin-spin relaxation time (ms)
    float PD; // Proton Density (relative 0.0 to 1.0)
};

// Function declarations (Prototypes)
std::vector<std::vector<Voxel>> createPhantom(int size);

void exportWithOpenCV(const std::vector<std::vector<Voxel>>& phantom, 
                      const std::string& filename, 
                      const std::string& parameter, 
                      bool applyHeatmap = false);