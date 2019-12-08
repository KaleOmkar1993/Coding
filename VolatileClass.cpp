#include<iostream>
#include<cstdint>

using namespace std;

// Macro For Read-Write Access To A Device
#define C_PTR   ( (uint32_t*)(0x12345678) )

// Volatile Class Basics
// Class cannot be declared as volatile
// Member Functions Of the Class Have To Be Volatile
// Every Non-static member of class is volatile but class is not.
// Using reinterpret cast, we are using copy constructor.

//Example Volatile Class For UART
typedef class nv_uart{
    public:
        //This enum only allows to enter valid values.
        enum class UART_NUM{ONE, TWO, THREE};
        nv_uart(UART_NUM uart_num) : uart_num_(uart_num) {}
        void put(int c) volatile;
        int get() volatile {std::cout << "UART Get Called\n"; return 0;}
        int set(); //Not declared volatile so it cannot be called
    private:
        //Registers should be private
        uint8_t STATUS_REG;
        uint8_t READ_REG;
        UART_NUM uart_num_;
}volatile UART;

int main(){    
    // Finding Location Of Device
    // C Style
    uint32_t * const ptr_c = (uint32_t*)(0x12345678);

    // C++ Style
    uint32_t * const ptr_cpp = reinterpret_cast<uint32_t*>(0x12345678);

    // UART Volatile Class Object
    UART uart1(UART::UART_NUM::ONE);

    // Create A Pointer To An UART Object At 0x12345678
    UART volatile &uart2 = *reinterpret_cast<UART*>(0x12345678);
    uart1.get();

    //uart1.set(); //This cannot be called as get is not volatile

    return 0;

}