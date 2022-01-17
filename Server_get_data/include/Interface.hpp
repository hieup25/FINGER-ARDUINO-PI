/*
* Create: HieuPV
* Date  : 28/07/21
*/
#pragma once
#include <iostream>
#include <memory>

class Interface
{
    private:
        struct Impl;
        std::unique_ptr<Impl> _impl;
    public:
        Interface(/* args */);
        ~Interface();
        void runForever();
};
