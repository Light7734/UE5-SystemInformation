#pragma once

#define UNDETECTED_INFO_STR "N/A"
#define UNKNOWN_INFO_STR "Unknown"

#define FIND_IN_ITER(token) (iter->find(token) != std::string::npos) && (iter->find(token) == 0)