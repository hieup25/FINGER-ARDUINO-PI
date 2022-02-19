#ifndef _UART_H_
#define _UART_H_
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

long UartPollPort(unsigned char byPortNum, char* pBuffer, unsigned char bySize);
long UartOpenPort(int byPortNum, long lBaudRate);
long UartSendByte(int byPortNum, unsigned char nByte);
long UartSendBuf(unsigned char byPortNum, unsigned char* pBufferf, unsigned char bySize);
long UartCloseComport(unsigned char byPortNum);
void Uartcputs(unsigned char byPortNum, const char *);
long UartIsDCDEnabled(unsigned char byPortNum);
long UartIsCTSEnabled(unsigned char byPortNum);
long UartIsDSREnabled(unsigned char byPortNum);
void UartEnableDTR(unsigned char byPortNum);
void UartDisableDTR(unsigned char byPortNum);
void UartEnableRTS(unsigned char byPortNum);
void UartDisableRTS(unsigned char byPortNum);
long UartReadComport(int byPortNum, char* pBuffer, unsigned char bySize);

#ifdef __cplusplus
}
#endif

#endif //Uart_h