#include <iostream>
#include "rapidxml.hpp"
#include <gdiplus.h>
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

enum class TransformType {
    Translate,
    Scale,
    Rotate,
    Skew,
    // Thêm các loại biến đổi khác nếu cần
};

struct Transform {
    TransformType type;
    float a, b, c, d, e, f;  // Tham số cho biến đổi
};

void applyTransform(const Transform& transform, Graphics& graphics) {
    switch (transform.type) {
    case TransformType::Translate:
        graphics.TranslateTransform(transform.a, transform.b);
        break;
    case TransformType::Scale:
        graphics.ScaleTransform(transform.a, transform.b);
        break;
    case TransformType::Rotate:
        graphics.RotateTransform(transform.a);
        break;
    //case TransformType::Skew:
    //    graphics.MultiplyTransform(new Matrix(1, skewY, skewX, 1, 0, 0));
    //    break;
        // Thêm các loại biến đổi khác nếu cần
    }
}

std::vector<Transform> parseTransform(const char* transformValue) {
    std::vector<Transform> transforms;

    std::string transformString(transformValue);
    std::istringstream iss(transformString);

    while (iss) {
        std::string transformTypeStr;
        iss >> transformTypeStr;

        if (!transformTypeStr.empty()) {
            Transform transform;

            // Chuyển đổi từ chuỗi thành enum TransformType
            if (transformTypeStr == "translate") {
                transform.type = TransformType::Translate;
            }
            else if (transformTypeStr == "scale") {
                transform.type = TransformType::Scale;
            }
            else if (transformTypeStr == "rotate") {
                transform.type = TransformType::Rotate;
            }
            //else if (transformTypeStr == "skew") {
            //    transform.type = TransformType::Skew;
            //}
            else {
                // Loại biến đổi không được nhận dạng
                std::cerr << "Unsupported transform type: " << transformTypeStr << std::endl;
                continue;
            }

            // Xử lý các giá trị biến đổi
            while (iss && iss.peek() != '(') {
                iss.ignore();
            }

            iss >> transform.a;
            if (transform.type != TransformType::Rotate) {
                iss >> transform.b >> transform.c >> transform.d;
            }

            //if (transform.type == TransformType::Translate || transform.type == TransformType::Skew) {
            //    iss >> transform.e;
            //}

            if (transform.type == TransformType::Translate) {
                iss >> transform.f;
            }

            // Bỏ qua ký tự ')'
            iss.ignore();

            transforms.push_back(transform);
        }
    }

    return transforms;
}

