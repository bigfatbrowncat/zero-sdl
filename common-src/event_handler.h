#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

enum EventResult {
	erProcessed, erExit
};

EventResult processEvents();

#endif