#ifndef COMMAND_PARSER__H
#define COMMAND_PARSER__H

#include <Arduino.h>

class CComandParser
{

// Type defs
public:
    struct tzCommandResponse
    {
        unsigned short m_id;
        int m_result;
    };

// Methods
public:
    CComandParser();
    ~CComandParser();

    void SendCommand(
        unsigned short usId,
        unsigned short usCommand,
        const char* args,
        int argsLen);

    void FetchCommandResult();
    
    bool IsResultAvailable();
    void GetLastResult(tzCommandResponse* response);

// Type defs
private:
    enum SerialFetchState
    {
        eWait_Start,
        eWait_End,
        eParse
    };

// Methods
private:
    void ParseCommandResult(const char* pCommandResult, unsigned short* pusId, int* pResult);

// Members
private:

    String m_serailBuffer;
    SerialFetchState m_currState;

    tzCommandResponse m_response;
    bool m_hasResponse;
};

#endif // !COMMAND_PARSER__H