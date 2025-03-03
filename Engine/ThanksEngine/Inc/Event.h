#pragma once

namespace ThanksEngine
{
    enum class EventType
    {
        None,
        SpacePressed,
        FKeyPressed
    };

    class Event
    {
    public:
        Event() = default;
        Event(EventType et) : mEventType(et) {}
        virtual ~Event() = default;

        EventType GetType() const { return mEventType; }

    private:
        EventType mEventType = EventType::None;
    };

    class SpacePressedEvent : public Event
    {
    public:
        SpacePressedEvent() : Event(EventType::SpacePressed) {}
    };

    class FKeyPressedEvent : public Event
    {
    public:
        FKeyPressedEvent() : Event(EventType::FKeyPressed) {}
    };
}