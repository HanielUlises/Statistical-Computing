#pragma once

#include <stdexcept>
#include <string>

namespace stat {

class stat_error : public std::runtime_error {
public:
    explicit stat_error(const std::string& msg)
        : std::runtime_error(msg) {}
};

class domain_error : public stat_error {
public:
    explicit domain_error(const std::string& msg)
        : stat_error("Domain error: " + msg) {}
};

class convergence_error : public stat_error {
public:
    explicit convergence_error(const std::string& msg)
        : stat_error("Convergence error: " + msg) {}
};

class numerical_error : public stat_error {
public:
    explicit numerical_error(const std::string& msg)
        : stat_error("Numerical error: " + msg) {}
};

} // namespace stat
