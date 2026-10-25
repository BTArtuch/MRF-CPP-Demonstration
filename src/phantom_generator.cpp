#include "../headers/phantom_generator.hpp"
#include <iostream>
#include <cmath>

// Generate a simple circular brain-like phantom
std::vector<std::vector<Voxel>> createPhantom(int size) {
    std::vector<std::vector<Voxel>> phantom(size, std::vector<Voxel>(size));
    int center = size / 2;
    int radiusOuter = size * 0.4;
    int radiusInner = size * 0.2;

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            float distance = std::sqrt(std::pow(x - center, 2) + std::pow(y - center, 2));

            if (distance < radiusInner) {
                // Inner circle (Simulating White Matter)
                phantom[y][x] = {1084.0f, 69.0f, 0.8f}; 
            } else if (distance < radiusOuter) {
                // Outer ring (Simulating Gray Matter)
                phantom[y][x] = {1820.0f, 99.0f, 0.95f}; 
            } else {
                // Background (Air)
                phantom[y][x] = {0.0f, 0.0f, 0.0f};
            }
        }
    }
    return phantom;
}

// Export a specific parameter map to an image using OpenCV
void exportWithOpenCV(const std::vector<std::vector<Voxel>>& phantom, const std::string& filename, const std::string& parameter, bool applyHeatmap) {
    int size = phantom.size();
    cv::Mat img(size, size, CV_32FC1);
    float maxVal = 0.0f;

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            float val = 0.0f;
            if (parameter == "T1") val = phantom[y][x].T1;
            else if (parameter == "T2") val = phantom[y][x].T2;
            else if (parameter == "PD") val = phantom[y][x].PD;
            
            img.at<float>(y, x) = val;
            if (val > maxVal) maxVal = val;
        }
    }

    cv::Mat img8Bit;
    if (maxVal > 0.0f) {
        img.convertTo(img8Bit, CV_8UC1, 255.0 / maxVal);
    } else {
        img.convertTo(img8Bit, CV_8UC1);
    }

    cv::Mat outputImg;
    if (applyHeatmap) {
        cv::applyColorMap(img8Bit, outputImg, cv::COLORMAP_JET);
    } else {
        outputImg = img8Bit; 
    }

    if (cv::imwrite(filename, outputImg)) {
        std::cout << "Successfully exported " << parameter << " map to " << filename << "\n";
    } else {
        std::cerr << "Error: Could not write to " << filename << "\n";
    }
}

int main() {
    int imageSize = 128; // 128x128 matrix size
    
    std::cout << "Initializing digital phantom...\n";
    auto phantom = createPhantom(imageSize);

    // Export using the root-relative path
    exportWithOpenCV(phantom, "outputs/phantom_T1_map.png", "T1", true);
    exportWithOpenCV(phantom, "outputs/phantom_T2_map.png", "T2", true);
    exportWithOpenCV(phantom, "outputs/phantom_PD_map.png", "PD", false);

    return 0;
}