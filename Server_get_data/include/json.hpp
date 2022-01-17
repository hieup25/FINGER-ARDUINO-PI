#pragma once
#include "../libs/nlohmann/json.hpp"
using json = nlohmann::basic_json<std::map, std::vector, std::string, bool, std::int64_t, std::uint64_t, float>;
#define REQUIRED(j, n) do { j.at(#n).get_to(n); } while (0)
#define OPTIONAL(j, n) do { try { n = j[#n]; } catch (std::exception& e) { } } while (0)