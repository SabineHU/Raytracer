#pragma once

#include <cmath>
#include <iomanip>
#include <ostream>
#include <string>
#include <chrono>

enum PrintType {
    NO_PRINT,
    FRACTION,
    PROGRESS_BAR
};

class ProgressBar
{
    public:
        ProgressBar(std::ostream& stream, int width, PrintType type = FRACTION)
            : _stream{stream}, _width(width), _start(std::chrono::system_clock::now()), _type(type)
        {}

        // Not copyable
        ProgressBar(const ProgressBar&) = delete;
        ProgressBar& operator=(const ProgressBar&) = delete;

        ~ProgressBar() { _stream << '\n'; }

        /* Methods */
        void write(int nb, int max) const;
        void write(double fraction) const;

        /* Getters */
        PrintType get_type() const { return _type; }

    private:
        void write_time() const;
        void write_progress_bar(double fraction) const;

        /* Attributes */
        std::ostream& _stream;
        int _width;
        std::chrono::system_clock::time_point _start;
        PrintType _type;
};

void ProgressBar::write_progress_bar(double fraction) const {
    if (fraction < 0)
        fraction = 0;

    fraction = fraction > 1 ? 1 : fraction;

    int offset = _width - static_cast<unsigned>(_width * fraction);

    _stream << "\r[";

    for (int i = 0; i < _width - offset; ++i)
        _stream << "▒";

    for (int i = 0; i < offset; ++i)
        _stream << " ";

    _stream << "] " << std::setprecision(1) << std::fixed << 100 * fraction << "% | ";

    write_time();
}

void ProgressBar::write_time() const {
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - _start;

    _stream << elapsed.count() << "s\r";
    _stream << std::flush;
}

void ProgressBar::write(int nb, int max) const {
    switch (_type) {
    case NO_PRINT:
        return;
    case FRACTION:
        _stream << '\r' << nb << " / " << max << " | ";
        write_time();
        return;
    default:
        write_progress_bar((double) nb / (double) max);
        return;
    }
}

void ProgressBar::write(double fraction) const {
    switch (_type) {
    case NO_PRINT:
        return;
    case FRACTION:
        _stream << '\r' << fraction << " | ";
        write_time();
        return;
    default:
        write_progress_bar(fraction);
        return;
    }
}
