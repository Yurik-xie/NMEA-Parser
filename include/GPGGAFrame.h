#ifndef GPGGAFRAME_H
#define GPGGAFRAME_H

#include "Frame.h"

class GPGGAFrame : public Frame
{
    public:
        /**
        *
        **/
        GPGGAFrame();

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
        float latitude() const;

        /**
        *
        **/
        float longitude() const;

        /**
        *
        **/
        unsigned char fix_quality() const;

        /**
        *
        **/
        unsigned char satellites() const;

        /**
        *
        **/
        float hdop() const;

        /**
        *
        **/
        float altitude() const;

        /**
        *
        **/
        float geoid() const;

    protected:
        /**
        *
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
        float _fix_quality;

        /**
        *
        **/
        float _satellites;

        /**
        *
        **/
        float _hdop;

        /**
        *
        **/
        float _altitude;

        /**
        *
        **/
        float _geoid;
};

#endif // PGGGAFRAME_H
