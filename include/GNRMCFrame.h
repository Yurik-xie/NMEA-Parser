#ifndef GNRMCFRAME_H
#define GNRMCFRAME_H

#include "Frame.h"

class GNRMCFrame : public Frame
{
    public:
        /**
        *
        **/
        GNRMCFrame();

        /**
        *
        **/
        bool decode(const char& c);

        /**
        *
        **/
        float utc() const;

        /**
        *
        **/
        char status() const;

        /**
        *
        **/
        float latitude() const;

        /**
        *
        **/
        float longitude() const;

        /**
        *
        **/
        float speed() const;

        /**
        *
        **/
        float course() const;

    protected:
        /**
        * Status character of the last GPRMC sentence received.
        * Can be 'A' (for Active) or 'V' (for Void), and signals whether the
        * GPS was active when the positioning was made.
        **/
        char _status;

        /**
        * UTC time of the last GPS positioning.
        * Represented by a floating-point value which contains the hour, minutes,
        * seconds and milliseconds. For example a value of 235219.281 indicates
        * that the measurement was made at 23h52, 19 seconds and 281 milliseconds UTC.
        **/
        float _utc;

        /**
        *
        **/
        float _latitude;

        /**
        *
        **/
        float _longitude;

        /**
        *
        **/
        float _speed;

        /**
        *
        **/
        float _course;
};

#endif // GNRMCFRAME_H
