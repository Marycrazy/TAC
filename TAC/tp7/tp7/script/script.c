#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define BUFFER_SIZE 1024

// error codes
#define ERROR_OPEN_SERIAL_PORT 1
#define ERROR_CONFIGURE_SERIAL_PORT 2
#define ERROR_OPEN_FILE 3
#define ERROR_SET_COMM_TIMEOUTS 4

// prototypes
int configureSerialPort(HANDLE hSerial);
int captureData(HANDLE hSerial, FILE* fp);
FILE* openDataFile();

int main() {
    HANDLE hSerial;
    FILE* fp;
    char portName[20];
    int errorCode = 0;

    // get serial port name from user
    printf("Enter serial port name (e.g. COM3): ");
    scanf("%s", portName);
    while (getchar() != '\n'); // flush input buffer

    // verify serial port
    printf("Verifying serial port...\n");
    hSerial = CreateFile(portName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error: Failed to open serial port\n");
        getchar();
        return ERROR_OPEN_SERIAL_PORT;
    }
    CloseHandle(hSerial);

    // open data file for writing
    fp = openDataFile();
    if (fp == NULL) {
        CloseHandle(hSerial);
        getchar();
        return 1;
    }

    // open serial port
    printf("Opening serial port...\n");
    hSerial = CreateFile(portName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error: Failed to open serial port\n");
        getchar();
        return ERROR_OPEN_SERIAL_PORT;
    }

    // configure serial port
    errorCode = configureSerialPort(hSerial);
    if (errorCode != 0) {
        CloseHandle(hSerial);
        printf("Error: Failed to configure serial port\n");
        getchar();
        return errorCode;
    }

    // capture data
    errorCode = captureData(hSerial, fp);
    if (errorCode != 0) {
        fclose(fp);
        CloseHandle(hSerial);
        printf("Error: Failed to capture data\n");
        getchar();
        return errorCode;
    }

    // close file and serial port
    printf("\nStopping data capture...\n");
    fclose(fp);
    CloseHandle(hSerial);

    return 0;
}

int configureSerialPort(HANDLE hSerial) {
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};

    // configure serial port
    printf("Configuring serial port...\n");
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Error: Could not get comm state\n");
        getchar();
        return ERROR_CONFIGURE_SERIAL_PORT;
    }
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)){
        printf("Error: Could not set comm state\n");
        getchar();
        return ERROR_CONFIGURE_SERIAL_PORT;
    }

    // configure timeouts
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("Error: Could not set comm timeouts\n");
        getchar();
        return ERROR_SET_COMM_TIMEOUTS;
    }

    printf("Serial port configured successfully.\n");
    return 0;
}

int captureData(HANDLE hSerial, FILE* fp) {
    // wait for 5 seconds before starting data capture
    printf("Data capture starting in 5... ");
    Sleep(1000);
    printf("4... ");
    Sleep(1000);
    printf("3... ");
    Sleep(1000);
    printf("2... ");
    Sleep(1000);
    printf("1...\n");
    Sleep(1000);

    // flush serial port buffer
    printf("Flushing serial port buffer...\n");
    PurgeComm(hSerial, PURGE_RXCLEAR);

    // read from serial and write to file
    printf("Data capture started. Writing data to file...\nPress Ctrl+C to stop data capture.\n\n");
    char buffer[BUFFER_SIZE];
    DWORD bytesRead;
    while (1) {
        if (ReadFile(hSerial, buffer, BUFFER_SIZE, &bytesRead, NULL)) {
            // get current date/time
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            if ((int) bytesRead == 0) {
                continue;
            }
            // append data to file with timestamp
            fprintf(fp, "[%02d-%02d-%04d - %02d:%02d:%02d]\n%.*s", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
                    tm.tm_hour, tm.tm_min, tm.tm_sec, (int) bytesRead, buffer);
            fflush(fp);

            // print captured data with timestamp to console
            printf("[%02d-%02d-%04d - %02d:%02d:%02d]\n%.*s", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
                    tm.tm_hour, tm.tm_min, tm.tm_sec, (int) bytesRead, buffer);
        }
    }
}

FILE* openDataFile() {
    FILE* fp;
    char fileName[50];
    char fileFormat[10];

    // get file name and format from user
    printf("Enter file name: ");
    scanf("%s", fileName);
    while (getchar() != '\n'); // flush input buffer
    printf("Enter file format (e.g. txt): ");
    scanf("%s", fileFormat);
    while (getchar() != '\n'); // flush input buffer

    // default to ".txt" if no file format is specified or if an invalid file format is entered
    if (strlen(fileFormat) == 0 || strlen(fileFormat) > 4) {
        strcpy(fileFormat, "txt");
    }

    // concatenate file format to file name
    strcat(fileName, ".");
    strcat(fileName, fileFormat);

    // open file for writing
    fp = fopen(fileName, "a");
    if (fp == NULL) {
        printf("Error: Could not open file for writing\n");
        return NULL;
    }

    return fp;
}