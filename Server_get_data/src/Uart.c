/*
*<Copyright Notice>
*Product		: <Product Name>
*Module		: <Module Name>
*Version		: <Version>
*Author		: <Author Name>
*Created		: <Creation Date>
*Modified	:
*Released	: <Date>
*Description	: <Description>
*Note		: <Note>
*/
//wiper: ttyHS0, pt: ttyHS1
#include "../include/Uart.h"
#include <termios.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int cCport[3];
int p;
long lError;
extern int v_min_uart;
char mode[] = {'8', 'N', '1', 0};
struct termios new_port_settings, //structure to store the port setting
	   old_port_settings[3];
//char cComports[3][16] = {"/dev/ttyMSM1", "/dev/ttyMSM2", "/dev/ttyUSB0"};
char cComports[3][20] = {"/dev/ttyUSB0", "/dev/ttyHS1", "/dev/ttyUSB0"};


long UartOpenPort(int byPortNum, long lBaudRate)
{
	p = byPortNum;
	char cStatus;
	if((byPortNum > 2) || (byPortNum < 0)) // if comport number without array
	{
		printf("illegal comport number\n");
		return(1);
	}
	//printf("%s\n", cComports[byPortNum]);
	switch (lBaudRate) // choose comport
	{
		case      50 : lBaudRate = B50;
					   break;
		case      75 : lBaudRate = B75;
					   break;
		case     110 : lBaudRate = B110;
					   break;
		case     134 : lBaudRate = B134;
					   break;
		case     150 : lBaudRate = B150;
					   break;
		case     200 : lBaudRate = B200;
					   break;
		case     300 : lBaudRate = B300;
					   break;
		case     600 : lBaudRate = B600;
					   break;
		case    1200 : lBaudRate = B1200;
					   break;
		case    1800 : lBaudRate = B1800;
					   break;
		case    2400 : lBaudRate = B2400;
					   break;
		case    4800 : lBaudRate = B4800;
					   break;
		case    9600 : lBaudRate = B9600;
					   break;
		case   19200 : lBaudRate = B19200;
					   break;
		case   38400 : lBaudRate = B38400;
					   break;
		case   57600 : lBaudRate = B57600;
					   break;
		case  115200 : lBaudRate = B115200;
					   break;
		case  230400 : lBaudRate = B230400;
					   break;
		case  460800 : lBaudRate = B460800;
					   break;
		case  500000 : lBaudRate = B500000;
					   break;
		case  576000 : lBaudRate = B576000;
					   break;
		case  921600 : lBaudRate = B921600;
					   break;
		case 1000000 : lBaudRate = B1000000;
					   break;
		case 1152000 : lBaudRate = B1152000;
					   break;
		case 1500000 : lBaudRate = B1500000;
					   break;
		case 2000000 : lBaudRate = B2000000;
					   break;
		case 2500000 : lBaudRate = B2500000;
					   break;
		case 3000000 : lBaudRate = B3000000;
					   break;
		case 3500000 : lBaudRate = B3500000;
					   break;
		case 4000000 : lBaudRate = B4000000;
					   break;
		default      : printf("invalid lBaudRate\n");
					   return (1);
					   break;
	}
	long lCbits = CS8;// 8 data bits
	long lCpar =0;
	long lIpar = IGNPAR;
	long lBstop = 0;
	switch (mode[0])
	{
		case '8': lCbits = CS8;
				  break;
		case '7': lCbits = CS7;
				  break;
		case '6': lCbits = CS6;
				  break;
		case '5': lCbits = CS5;
				  break;
		default : printf("invalid number of data-bits '%c'\n", mode[0]);
				  return (1);
				  break;
	}
	switch (mode[1])
	{
		case 'N':
		case 'n': lCpar = 0;
				  lIpar= IGNPAR;
				  break;
		case 'E':
		case 'e': lCpar = PARENB;
				  lIpar= INPCK;
				  break;
		case 'O':
		case 'o': lCpar = (PARENB | PARODD);
				  lIpar= INPCK;
				  break;
		default : printf("invalid parity '%c'\n", mode[1]);
				  return (1);
				  break;
	}
	switch (mode[2])
	{
		case '1': lBstop = 0;
				  break;
		case '2': lBstop = CSTOPB;
				  break;
		default : printf("invalid number of stop bits '%c'\n", mode[2]);
				  return (1);
				  break;
	}
/*
http://pubs.opengroup.org/onlinepubs/7908799/xsh/termios.h.html

http://man7.org/linux/man-pages/man3/termios.3.html
*/
	cCport[byPortNum] = open(cComports[byPortNum], O_RDWR | O_NOCTTY);
	if (cCport[byPortNum] < 0)
	{
		perror("unable to open comport ");
		return (1);
	}
	//struct termios SerialPortSetting;
	lError = tcgetattr(cCport[byPortNum], &old_port_settings[byPortNum]);
	if (lError == -1)
	{
		close(cCport[byPortNum]);
		perror("unable to read portsettings ");
		return (1);
	}
	/* Setting the Baud rate */
	//cfsetispeed(&old_port_settings[byPortNum], lBaudRate);
	//cfsetospeed(&old_port_settings[byPortNum], lBaudRate);
	cfsetspeed(&old_port_settings[byPortNum], lBaudRate);
	tcflush(cCport[byPortNum], TCIOFLUSH);
	old_port_settings[byPortNum].c_cflag &= ~CSIZE;
	old_port_settings[byPortNum].c_cflag |= CS8;
	old_port_settings[byPortNum].c_cflag &= ~CRTSCTS;
	old_port_settings[byPortNum].c_cflag |= CREAD | CLOCAL;
	old_port_settings[byPortNum].c_lflag &= ~ICANON; // tat che do chuan
	old_port_settings[byPortNum].c_lflag &= ~ECHO; // Disable echo
	old_port_settings[byPortNum].c_lflag &= ~ECHOE; // Disable erasure
	old_port_settings[byPortNum].c_lflag &= ~ECHONL; // Disable new-line echo
	old_port_settings[byPortNum].c_lflag &= ~ISIG;

	old_port_settings[byPortNum].c_iflag &= ~(IXON | IXOFF | IXANY);
	old_port_settings[byPortNum].c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

	old_port_settings[byPortNum].c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	old_port_settings[byPortNum].c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
	old_port_settings[byPortNum].c_cc[VMIN] = 1;      /* Read at least 10 charactrs */ //byte
	old_port_settings[byPortNum].c_cc[VTIME] = 10;     /* Wait indefinetly   */ //time-out value/10
	tcsetattr(cCport[byPortNum], TCSANOW, &old_port_settings[byPortNum]);
	return (0);
}

/*-------------------------------------------------------------------------------
 * Function:
 * Purpose:
 * Parameters:
 * Return:
 * Comments:
 * Modified:
 * -------------------------------------------------------------------------------*/
long UartPollPort(unsigned char byPortNum, char* pBuffer, unsigned char bySize)
{
	long n = -2;
	n = read(cCport[byPortNum], pBuffer, bySize);
	//return (n);
	return (strlen(pBuffer) == 0)? -1 : n;
}

/*-------------------------------------------------------------------------------
 * Function:
 * Purpose:
 * Parameters:
 * Return:
 * Comments:
 * Modified:
 * -------------------------------------------------------------------------------*/
long UartSendByte(int byPortNum, unsigned char byByte)
{
	long n;
	n = write(cCport[byPortNum], &byByte, sizeof(byByte));
	 return n;
}

/*-------------------------------------------------------------------------------
 * Function:
 * Purpose:
 * Parameters:
 * Return:
 * Comments:
 * Modified:
 * -------------------------------------------------------------------------------*/
long UartSendBuf(unsigned char byPortNum, unsigned char* pBuffer, unsigned char bySize)
{
	return(write(cCport[byPortNum], pBuffer, bySize));
}

/*-------------------------------------------------------------------------------
 * Function:
 * Purpose:
 * Parameters:
 * Return:
 * Comments:
 * Modified:
 * -------------------------------------------------------------------------------*/
long UartCloseComport(unsigned char byPortNum)
{
	//signed long cStatus;
	long lRetVal;
	lRetVal = close(cCport[byPortNum]);
	return lRetVal;
}
/*-------------------------------------------------------------------------------
 * Function:
 * Purpose:
 * Parameters:
 * Return:
 * Comments:
 * Modified:
 * -------------------------------------------------------------------------------*/
long UartIsDCDEnabled(unsigned char byPortNum)
{
	char cStatus;
	ioctl(cCport[byPortNum], TIOCMGET, &cStatus);
	if (cStatus & TIOCM_CAR) return (1);
	else return (0);
}

/*-------------------------------------------------------------------------------
 * Function:
 * Purpose:
 * Parameters:
 * Return:
 * Comments:
 * Modified:
 * -------------------------------------------------------------------------------*/
long UartIsCTSEnabled(unsigned char byPortNum)
{
	char cStatus;
	ioctl(cCport[byPortNum], TIOCMGET, &cStatus);
	if (cStatus & TIOCM_CTS) return (1);
	else return (0);
}

/*-------------------------------------------------------------------------------
 * Function:
 * Purpose:
 * Parameters:
 * Return:
 * Comments:
 * Modified:
 * -------------------------------------------------------------------------------*/
long UartIsDSREnabled(unsigned char byPortNum)
{
	char cStatus;
	ioctl(cCport[byPortNum], TIOCMGET, &cStatus);
	if (cStatus & TIOCM_DSR) return (1);
	else return (0);
}

/*-------------------------------------------------------------------------------
 * Function:
 * Purpose:
 * Parameters:
 * Return:
 * Comments:
 * Modified:
 * -------------------------------------------------------------------------------*/
void UartEnableDTR(unsigned char byPortNum)
{
	char cStatus;
	if (ioctl(cCport[byPortNum], TIOCMGET, &cStatus) == -1)
	{
		perror("unable to get portstatus");
	}
	cStatus |= TIOCM_DTR;    /* turn on DTR */
	if (ioctl(cCport[byPortNum], TIOCMSET, &cStatus) == -1)
	{
		perror("unable to set portstatus");
	}
}

/*-------------------------------------------------------------------------------
 * Function:
 * Purpose:
 * Parameters:
 * Return:
 * Comments:
 * Modified:
 * -------------------------------------------------------------------------------*/
void UartDisableDTR(unsigned char byPortNum)
{
	char cStatus;
	if (ioctl(cCport[byPortNum], TIOCMGET, &cStatus) == -1)
	{
		perror("unable to get portstatus");
	}
	cStatus &= ~TIOCM_DTR;    /* turn off DTR */
	if (ioctl(cCport[byPortNum], TIOCMSET, &cStatus) == -1)
	{
		perror("unable to set portstatus");
	}
}

/*-------------------------------------------------------------------------------
 * Function:
 * Purpose:
 * Parameters:
 * Return:
 * Comments:
 * Modified:
 * -------------------------------------------------------------------------------*/
void UartEnableRTS(unsigned char byPortNum)
{
	char cStatus;
	if (ioctl(cCport[byPortNum], TIOCMGET, &cStatus) == -1)
	{
		perror("unable to get portstatus");
	}
	cStatus |= TIOCM_RTS;    /* turn on RTS */
	if (ioctl(cCport[byPortNum], TIOCMSET, &cStatus) == -1)
	{
		perror("unable to set portstatus");
	}
}

/*-------------------------------------------------------------------------------
 * Function:
 * Purpose:
 * Parameters:
 * Return:
 * Comments:
 * Modified:
 * -------------------------------------------------------------------------------*/
void UartDisableRTS(unsigned char byPortNum)
{
	char cStatus;
	if(ioctl(cCport[byPortNum], TIOCMGET, &cStatus) == -1)
	{
		perror("unable to get portstatus");
	}
	cStatus &= ~TIOCM_RTS;    /* turn off RTS */
	if (ioctl(cCport[byPortNum], TIOCMSET, &cStatus) == -1)
	{
		perror("unable to set portstatus");
	}
}

/*-------------------------------------------------------------------------------
 * Function:
 * Purpose:
 * Parameters:
 * Return:
 * Comments:
 * Modified:
 * -------------------------------------------------------------------------------*/
long UartReadComport(int byPortNum, char* buffer, unsigned char bySize)
{
	int n = read(cCport[byPortNum], (char*)buffer, bySize);
	return n;
}