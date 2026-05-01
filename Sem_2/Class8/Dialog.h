#pragma once

#include <iostream>
#include <string>

#include "List.h"
#include "Event.h"

class Dialog : public List {
public:
    Dialog(void);
    virtual ~Dialog(void);

    virtual void GetEvent(TEvent& event);
    virtual int Execute();
    virtual void HandleEvent(TEvent& event);
    virtual void ClearEvent(TEvent& event);
    int Valid();
    void EndExec();

protected:
    int EndState;
};