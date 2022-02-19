#pragma once
#include <string>
#include <mutex>
#include <vector>
#include "Uart.h"
#include <pthread.h>
#include <map>

class DataStudent
{
    private:
        std::mutex mu;
        pthread_t idTh;
        std::vector<std::pair<int, std::string>> check_attendance; // id - time | 1 là đã điểm danh, 0 là chưa điểm danh
        // index vector: so thu tu hoc sinh tu 1 -> 9
        static void* routine(void*);
    public:
        DataStudent();
        std::vector<std::pair<int, std::string>> GetAttendance();
};