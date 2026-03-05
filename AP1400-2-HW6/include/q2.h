#ifndef Q2_H
#define Q2_H

#include <array>
#include <charconv>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace q2 {
using namespace std;
struct Patient {
    string name;
    int age;
    int smokes;
    int area_q;
    int alkhol;

    int calculate_risk() const {
        return 3 * age + 5 * smokes + 2 * area_q + 4 * alkhol;
    }
};

inline Patient process_line(string_view line) {
    size_t start{0};
    array<string_view, 6> tokens;

    for (int i = 0; i < 5; ++i) {
        size_t end = line.find(',', start);
        tokens[i] = line.substr(start, end - start);
        start = end + 1;
    }
    tokens[5] = line.substr(start);

    auto fast_stoi = [](string_view sv) {
        int val = 0;
        from_chars(sv.data(), sv.data() + sv.size(), val);
        return val;
    };

    return {string(tokens[0]) + " " + string(tokens[1]), fast_stoi(tokens[2]),
            fast_stoi(tokens[3]), fast_stoi(tokens[4]), fast_stoi(tokens[5])};
}

inline vector<Patient> read_file(string filename) {
    vector<Patient> patients;
    ifstream file(filename);
    if (!file.is_open()) {
        return patients;
    }

    string line;

    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        // line == John,Wick,35,3,5,4
        patients.emplace_back(process_line(line));
    }

    return patients;
}

inline void sort(vector<Patient> &patients) {
    std::stable_sort(patients.begin(), patients.end(),
                     [](const Patient &p1, const Patient &p2) {
                         return p1.calculate_risk() > p2.calculate_risk();
                     });
}

} // namespace q2

#endif // Q2_H
