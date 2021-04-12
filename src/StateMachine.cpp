#include <Arduino.h>
#include <StateMachine.h>
#include <TransitionTable.h>
#include <GlobalDefines.h>
#include <LEDController.h>

State gCurrentState = STATE_IDLE;

void FireEvent(Event event)
{
    DEBUG_PRINT_LN("FireEvent");

    int size = sizeof(gTransitionEntries) / sizeof(gTransitionEntries[0]);
    for (int i = 0; i < size; i++)
    {
        if (gTransitionEntries[i].m_event == event &&
            gTransitionEntries[i].m_from == gCurrentState)
        {
            DEBUG_PRINT("STATE CHANGED -> From: ");
            DEBUG_PRINT(gCurrentState);
            DEBUG_PRINT(" To: ");
            DEBUG_PRINT_LN(gTransitionEntries[i].m_to);

            gCurrentState = gTransitionEntries[i].m_to;
            ShowInfo(gCurrentState);

            gTransitionEntries[i].m_action();
            break;
        }
    }
};