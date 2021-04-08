#ifndef COMMAND_PARSER__H
#define COMMAND_PARSER__H

class CComandParser
{
public:
    CComandParser();
    ~CComandParser();

    void SendCommand(
        unsigned short usId,
        const char* pCommandName,
        const char* args,
        int argsLen);

    void ReceiveCommandResult(const char* pCommandResult, unsigned short* pusId, int* pResult);
};

#endif // !COMMAND_PARSER__H