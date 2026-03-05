#ifndef Q4_H
#define Q4_H

#include <numeric>
#include <utility>
#include <vector>

namespace q4 {
struct Vector2D {
    double x{};
    double y{};

    Vector2D operator+(const Vector2D &other) const {
        return Vector2D{this->x + other.x, this->y + other.y};
    }

    Vector2D operator*(double other) const {
        return Vector2D{x * other, y * other};
    }

    Vector2D operator/(double other) const {
        return Vector2D{x / other, y / other};
    }
};

struct Sensor {
    Vector2D pos;
    double accuracy;
};

inline Vector2D kalman_filter(std::vector<Sensor> sensors) {
    if (sensors.empty()) {
        return {0, 0};
    }

    Vector2D mean_pos{0, 0};
    double accuracies = 0;
    auto result =
        std::accumulate(sensors.begin(), sensors.end(),
                        std::pair<Vector2D, double>{Vector2D{0, 0}, 0},
                        [](const std::pair<Vector2D, double> &accumulate,
                           const Sensor &sensor) {
                            return std::pair<Vector2D, double>(
                                accumulate.first + sensor.pos * sensor.accuracy,
                                accumulate.second + sensor.accuracy);
                        });
    if (result.second == 0.0) {
        return Vector2D{0, 0};
    }

    return result.first / result.second;
}

} // namespace q4
#endif // Q4_H
