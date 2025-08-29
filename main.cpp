#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

int main(int argc, char** argv) {
    // Check if folder path is provided
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <folder_path> [width] [quality: low|medium|high]\n";
        return -1;
    }

    std::string folderPath = argv[1];

    // Width argument (optional)
    int width = 150;
    if (argc >= 3) {
        try {
            width = std::stoi(argv[2]);
        } catch (...) {
            std::cout << "Invalid width argument. Using default width 150.\n";
            width = 150;
        }
    }

    // Quality argument (optional)
    std::string quality = "low";
    if (argc >= 4) {
        quality = argv[3];
    }

    std::string ASCII;
    if (quality == "low") {
        ASCII = "@%#*+=-:.";
    } else if (quality == "medium") {
        ASCII = "s@&#%OX0CLi!~+-?1";
    } else if (quality == "high") {
        ASCII = "S@B%8&WM#oahkbdpqmwZO0QLCJUYXzcvunxrjft\\/|()1(}{]?-_+~i!lI;:,\"^";
    } else {
        std::cout << "Unknown quality. Using low.\n";
        ASCII = "@%#*+=-:.";
    }

    namespace fs = std::filesystem;

    // Create output folder
    std::string outFolder = folderPath + "/ascii_output";
    fs::create_directories(outFolder);

    // Iterate over all files in the directory
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        std::string imagePath = entry.path().string();

        // Skip directories
        if (fs::is_directory(entry.path())) continue;

        // Load image
        cv::Mat image = cv::imread(imagePath);
        if (image.empty()) {
            std::cout << "Failed to load: " << imagePath << std::endl;
            continue;
        }

        // Convert to grayscale and enhance
        cv::Mat gray;
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);
        gray.convertTo(gray, -1, 1, 30);

        // Resize while maintaining aspect ratio
        float aspectRatio = static_cast<float>(gray.cols) / gray.rows;
        float charAspect = 2.0; // terminal character ratio
        int height = static_cast<int>(width / aspectRatio / charAspect);

        cv::Mat resizeImg;
        cv::resize(gray, resizeImg, cv::Size(width, height));

        // Prepare output text file
        std::string fileName = entry.path().filename().string();
        std::string txtPath = outFolder + "/" + fileName + ".txt";
        std::ofstream outFile(txtPath);

        if (!outFile.is_open()) {
            std::cout << "Failed to open output file: " << txtPath << std::endl;
            continue;
        }

        // Write ASCII art to file
        for (int y = 0; y < resizeImg.rows; y++) {
            for (int x = 0; x < resizeImg.cols; x++) {
                uchar pixel = resizeImg.at<uchar>(y, x);
                int idx = pixel * (ASCII.size() - 1) / 255;
                outFile << ASCII[idx];
            }
            outFile << "\n";
        }

        outFile.close();
        std::cout << "Saved ASCII art for: " << imagePath << " -> " << txtPath << std::endl;
    }

    return 0;
}

