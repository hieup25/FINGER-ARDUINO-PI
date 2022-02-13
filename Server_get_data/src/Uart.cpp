#include "../include/Uart.hpp"
#include <vector>

std::vector<int> g_check; // 1 là đã điểm danh, 0 là chưa điểm danh

Uart::Uart()
{
    g_check.assign(9, 0); // Khởi tạo
    g_check[8] = 1;
    g_check[0] = 1;
}
void Uart::ReadUart()
{
    
}