#ifndef COMMAND_PARSER__H
#define COMMAND_PARSER__H

#include <Arduino.h>

struct CommandResponse
{
    unsigned short m_id;
    int m_result;
};

typedef struct CommandResponse tzCommandResponse;

class CComandParser
{

// Methods
public:
    CComandParser();
    ~CComandParser();

    void SendCommand(
        unsigned short usId,
        unsigned short usCommand,
        char** args = 0,
        int argsLen = 0);

    void FetchCommandResult();
    
    bool IsResultAvailable();
    void GetLastResponse(tzCommandResponse* response);

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

extern CComandParser gCommandParser;

#endif // !COMMAND_PARSER__H