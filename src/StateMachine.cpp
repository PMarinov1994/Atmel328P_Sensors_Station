#include <Arduino.h>
#include <StateMachine.h>
#include <TransitionTable.h>

State gCurrentState = STATE_IDLE;

void FireEvent(Event event)
{
    int size = sizeof(gTransitionEntries) / sizeof(gTransitionEntries[0]);
    for (int i = 0; i < size; i++)
    {
        if (gTransitionEntries[i].m_event == event &&
            gTransitionEntries[i].m_from == gCurrentState)
        {
            gCurrentState = gTransitionEntries[i].m_to;
            gTransitionEntries[i].m_action();
            break;
        }
    }
};