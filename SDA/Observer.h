#pragma once
class Observer {
public:
    virtual void update(int notificationID) = 0;
    virtual ~Observer() {}
};