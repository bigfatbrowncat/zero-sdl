#ifndef CONTROLLER_H
#define CONTROLLER_H

enum EventResult {
	erProcessed, erExit
};

EventResult processEvents();

#endif