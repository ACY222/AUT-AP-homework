#ifndef Q3_H
#define Q3_H

#include <charconv>
#include <fstream>
#include <iostream>
#include <optional>
#include <queue>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

namespace q3 {
using namespace std;

struct Flight {
    string flight_number;
    int duration;
    int connections;
    int connection_times;
    int price;

    int calculate_weight() const {
        return duration + connection_times + 3 * price;
    }

    bool operator<(const Flight &other) const {
        return this->calculate_weight() > other.calculate_weight();
    }
};

inline int get_duration(string_view sv) {
    // 13h40m, 10h, 30m
    int h_idx = sv.find('h');
    int m_idx = sv.find('m');
    int h = 0, m = 0;

    if (h_idx != string_view::npos) {
        from_chars(sv.data(), sv.data() + h_idx, h);
    }
    if (m_idx != string_view::npos) {
        int start_idx = (h_idx == string_view::npos) ? 0 : h_idx + 1;
        from_chars(sv.data() + start_idx, sv.data() + m_idx, m);
    }

    return 60 * h + m;
}

inline int get_connection_times(string_view str) {
    // 2h,1h30m,4h15m
    int start = 0, end;
    int times = 0;

    while ((end = str.find(',', start)) != string::npos) {
        times += get_duration(str.substr(start, end - start));
        start = end + 1;
    }

    times += get_duration(str.substr(start));

    return times;
}

inline optional<Flight> process_line(const string &line) {
    // 1- flight_number:QR492 - duration:11h30m - connections:3 -
    // connection_times:2h,1h30m,4h15m - price:250
    static const regex r(
        R"((\d+)- flight_number:(\w+) - duration:(\w+) - connections:(\d+) - connection_times:([\w,]+) - price:(\d+))");
    smatch results;

    Flight f;
    if (regex_match(line, results, r)) {
        f.flight_number = results.str(2);

        auto make_view = [](const ssub_match &m) {
            return string_view(&*m.first, m.length());
        };

        f.duration = get_duration(make_view(results[3]));

        from_chars(&*results[4].first, &*results[4].second, f.connections);
        f.connection_times = get_connection_times(make_view(results[5]));
        from_chars(&*results[6].first, &*results[6].second, f.price);

        return f;
    }

    return nullopt;
}

inline auto cmp = [](const Flight &f1, const Flight &f2) {
    return f1.calculate_weight() > f2.calculate_weight();
};

inline priority_queue<Flight> gather_flights(string filename) {
    priority_queue<Flight> flights;
    ifstream file(filename);
    if (!file.is_open()) {
        return flights;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        if (auto flight_opt = process_line(line); flight_opt.has_value()) {
            flights.push(std::move(flight_opt.value()));
        }
    }
    return flights;
}

} // namespace q3

#endif // Q3_H
