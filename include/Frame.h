#ifndef FRAME_H
#define FRAME_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cmath>

/**
* $GPGGA : Global Positioning System fix data
* $GPRMC : recommended minimum specific GPS/transit data
**/

#define WAITING                 0       // waiting for next routine
#define READ_FRAME              1       // reading current frame
#define READ_CHECKSUM_1         2       // reading first char of checksum
#define READ_CHECKSUM_2         3       // reading second char of checksum

#define LATITUDE                0
#define LONGITUDE               1

class Frame
{
    public:
        /**
        * Constructor for NMEA parser object.
        * Parse sentences of GPRMC or ALL.
        **/
        Frame();

        /**
        * Decodes characters received from the GPS.
        * Returns true if the incoming character completes a sentence.
        **/
        virtual bool decode(const char& c) = 0;

        /**
        * Decodes a NMEA sentence.
        **/
        void decode(const std::string& s);

        /**
        * Retrieves the last received complete sentence.
        **/
        std::string sentence() const;

        /**
        * Formats decimal degrees to a string representing
        * degrees, minutes, seconds.
        **/
        std::string format_coords(float dd, unsigned char c) const;

        /**
        *
        **/
        std::string format_time(const float& utc) const;

    protected:
        /**
        * Current state.
        **/
        std::size_t _state;

        /**
        *
        **/
        std::size_t _tag;

        /**
        * The sentence being decoded.
        **/
        char _sentence[100];

        /**
        * Number of written characters in the current sentence.
        **/
        std::size_t _n;

        /**
        * Terms of the current sentence (separated by a comma)
        */
        char* _term[30];

        /**
        * Number of terms in the current sentence.
        **/
        std::size_t _terms;

        /**
        *
        **/
        std::size_t _nt;

        /**
        *
        **/
        std::string _last_sentence;

        /**
        *
        **/
        float decimal(const std::string& s);
};

/**
*
**/
template <class T>

bool from_string(T& t, const std::string& s)
{
  std::istringstream iss(s);

  return !(iss >> t).fail();
}

#endif // FRAME_H
