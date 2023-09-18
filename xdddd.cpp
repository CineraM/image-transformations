#include <iostream>
#include <vector>

// Function to rotate a 2D array 90 degrees clockwise
std::vector<std::vector<int>> rotate90(std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    std::vector<std::vector<int>> result(cols, std::vector<int>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[j][rows - 1 - i] = matrix[i][j];
        }
    }

    return result;
}

// Function to rotate a 2D array 180 degrees clockwise
std::vector<std::vector<int>> rotate180(std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrix[rows - 1 - i][cols - 1 - j];
        }
    }

    return result;
}

// Function to rotate a 2D array 270 degrees clockwise
std::vector<std::vector<int>> rotate270(std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    std::vector<std::vector<int>> result(cols, std::vector<int>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[cols - 1 - j][i] = matrix[i][j];
        }
    }

    return result;
}

int main() {
    // Example 2D array
    std::vector<std::vector<int>> arr = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Rotate by 90 degrees
    std::vector<std::vector<int>> rotated90 = rotate90(arr);

    // Rotate by 180 degrees
    std::vector<std::vector<int>> rotated180 = rotate180(arr);

    // Rotate by 270 degrees
    std::vector<std::vector<int>> rotated270 = rotate270(arr);

    // Output rotated matrices
    std::cout << "Rotated by 90 degrees:" << std::endl;
    for (const auto& row : rotated90) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Rotated by 180 degrees:" << std::endl;
    for (const auto& row : rotated180) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Rotated by 270 degrees:" << std::endl;
    for (const auto& row : rotated270) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}



#include <iostream>
#include <vector>

// Function to rotate a region inside a 2D array by 90 degrees clockwise
void rotateRegion90(std::vector<std::vector<int>>& matrix, int startX, int startY, int width, int height) {
    // Check if the region dimensions are valid
    if (startX < 0 || startY < 0 || startX + width > matrix.size() || startY + height > matrix[0].size()) {
        std::cout << "Invalid region dimensions." << std::endl;
        return;
    }

    std::vector<std::vector<int>> rotatedRegion(height, std::vector<int>(width));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            rotatedRegion[i][j] = matrix[startX + j][startY + height - 1 - i];
        }
    }

    // Copy the rotated region back to the original matrix
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[startX + j][startY + i] = rotatedRegion[i][j];
        }
    }
}

int main() {
    // Example 2D array
    std::vector<std::vector<int>> arr = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    // Rotate a specific region (e.g., top-left 2x2 subregion)
    rotateRegion90(arr, 0, 0, 2, 2);

    // Output the modified array
    for (const auto& row : arr) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
