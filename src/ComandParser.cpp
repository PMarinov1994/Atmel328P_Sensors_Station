#include <CommandParser.h>
#include <Arduino.h>
#include <CommDefinitions.h>
#include <GlobalDefines.h>
#include <CommandTimeoutTracker.h>

CComandParser gCommandParser;

CComandParser::CComandParser()
    : m_currState(SerialFetchState::eWait_Start), m_hasResponse(false){};

CComandParser::~CComandParser(){};

/*
*   \brief
*
*   \param [IN] The command ID
*   \param [IN] The command number
*   \param [IN] A pointer to a char array with command arguments
*   \param [IN] The count of @param args
*/
void CComandParser::SendCommand(
    unsigned short usId,
    unsigned short usCommand,
    char **args,
    int argsLen)
{
    String cmd;
    cmd += MESSAGE_START;
    cmd += usId;
    cmd += COMMAND_ID_SEPARATOR;
    cmd += usCommand;

    for (int i = 0; i < argsLen; i++)
    {
        cmd += " ";
        cmd += args[i];
    }

    cmd += MESSAGE_END;

    TrackCommand(usCommand);
    Serial.println(cmd);
    Serial.flush();
}

/*
*   \brief
*
*/
bool CComandParser::IsResultAvailable()
{
    return m_hasResponse;
}

/*
*   \brief
*
*/
void CComandParser::GetLastResponse(tzCommandResponse *response)
{
    memcpy(response, &m_response, sizeof(tzCommandResponse));
    m_hasResponse = false;
}

/*
*   \brief
*
*   \param [IN] The command result to be parsed.
*   \param [OUT] The command ID that this result is for.
*   \param [OUT] The command Result
*/
void CComandParser::ParseCommandResult(const char *pCommandResult, unsigned short *pusId, int *pResult)
{
    String cmd(pCommandResult);
    int separator = cmd.indexOf(COMMAND_ID_SEPARATOR);
    if (-1 == separator)
    {
        DEBUG_PRINT_LN("No CMD/ID Separator found");

        *pusId = 0xFF;
        *pResult = ERROR_UNKNOWN_CMD;
        return;
    }

    String id = cmd.substring(0, separator);
    String result = cmd.substring(separator + 1);

    *pusId = atoi(id.c_str());
    *pResult = atoi(result.c_str());
}

/*
*   \brief
*
*/
void CComandParser::FetchCommandResult()
{
    if (Serial.available() == 0)
        return;

    char ch;
    Serial.readBytes(&ch, 1);

    switch (m_currState)
    {
    case SerialFetchState::eWait_Start:
        if (MESSAGE_START == ch)
            m_currState = SerialFetchState::eWait_End;

        break;

    case SerialFetchState::eWait_End:
        if (MESSAGE_END == ch)
            m_currState = SerialFetchState::eParse;
        else
            m_serailBuffer += ch;

        break;

    case SerialFetchState::eParse:

        unsigned short id;
        int cmdResult;

        ParseCommandResult(m_serailBuffer.c_str(), &id, &cmdResult);

        m_response.m_id = id;
        m_response.m_result = cmdResult;

        m_hasResponse = true;
        m_serailBuffer = String();

        m_currState = SerialFetchState::eWait_Start;
        break;
    }
}