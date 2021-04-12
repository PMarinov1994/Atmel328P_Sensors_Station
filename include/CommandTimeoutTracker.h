#ifndef COMMAND_TIME_OUT_TRACKER__H
#define COMMAND_TIME_OUT_TRACKER__H

/*
*   \brief Call once every iteration of main loop.
*          This will tick and check for command response time left.
*
*/
void TickCommandTracker();

/*
*   \brief Call before you send/invoke the command.
*          Starts a timer for that command to get a response.
*          If a command is already being tracked, this method will do nothing.
*
*/
void TrackCommand(unsigned short id);

/*
*   \brief Call right after a command response is received and before
*          any call to transition the state machine. Only one command can be tracked
*          at a time, so if a new TrackCommand is requests before the old is canceled it will not work.
*
*/
void UntrackCommand(unsigned short id);

#endif // !COMMAND_TIME_OUT_TRACKER__H