#include "../include/DataStudent.hpp"
#include <iostream>
#include "../include/json.hpp"
DataStudent::DataStudent()
{
    check.assign(9, 0); // Khởi tạo hoc sinh chua diem danh
    check_attendance.assign(9, {0, "NULL"});
    UartOpenPort(0, 9600);
    pthread_create(&idTh, NULL, routine, this);
}
std::vector<std::pair<int, std::string>> DataStudent::GetAttendance()
{
    std::lock_guard<std::mutex> lk(this->mu);
    return check_attendance;
}
void* DataStudent::routine(void* data)
{
    auto arg = static_cast<DataStudent*>(data);
    while(1)
    {
        char buff[50] = {0};
        UartReadComport(0, buff, 50);
        std::cout <<"Buff ori: " << buff << std::endl;
        std::lock_guard<std::mutex> lk(arg->mu);
        // push data
        json j = json::parse(buff);
        arg->check_attendance[j["id"].get<int>() - 1] = {1, j["time"].get<std::string>()};
    }
    pthread_exit(NULL);
}