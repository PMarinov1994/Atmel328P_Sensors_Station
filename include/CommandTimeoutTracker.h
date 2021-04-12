#ifndef COMMAND_TIME_OUT_TRACKER__H
#define COMMAND_TIME_OUT_TRACKER__H

void TickCommandTracker();
void TrackCommand(unsigned short id);
void UntrackCommand(unsigned short id);

#endif // !COMMAND_TIME_OUT_TRACKER__H