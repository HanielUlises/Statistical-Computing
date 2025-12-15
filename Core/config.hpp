#pragma once

namespace stat::config {

// Global compile-time policies
inline constexpr bool enable_runtime_checks = true;

// Default tolerances
inline constexpr double default_tol = 1e-8;
inline constexpr int    default_max_iter = 10'000;

// Log-space safety
inline constexpr double log_epsilon = 1e-12;

// Instrumentation
inline constexpr bool enable_diagnostics = false;

} // namespace stat::config
