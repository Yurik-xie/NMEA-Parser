#include "GPGGAFrame.h"

#define GPGGA_TOKEN "$GPGGA"

GPGGAFrame::GPGGAFrame()
{
    //ctor
}

bool GPGGAFrame::decode(const char& c)
{
    if (_n > 99 || _terms >= 30 || _nt >= 15 || c == 0xA || c == 0xD)
    {
        _state = WAITING;

        return false;
    }

    if (c == '$')
    {
        _state = READ_FRAME;

        _tag = 0;

        _sentence[0] = '$';
        _n = 1;

        _terms = 0;
        _nt = 0;

        return false;
    }

    switch (_state)
    {
        case WAITING :
            break;

        case READ_FRAME :
            if (_n < 6)
            {
                if (GPGGA_TOKEN[_n] == c)
                {
                    _tag++;
                }
            }

            _sentence[_n++] = c;

            switch (c)
            {
                case ',' :
                    (_term[_terms++])[_nt] = 0;
                    _nt = 0;

                    break;

                case '*' :
                    (_term[_terms++])[_nt] = 0;
                    _nt = 0;

                    _state++;

                    break;

                default :
                    (_term[_terms])[_nt++] = c;

                    break;
            }

            break;

        case READ_CHECKSUM_1 :
            _sentence[_n++] = c;
            (_term[_terms])[_nt++] = c;

            _state++;

            break;

        case READ_CHECKSUM_2 :
            _sentence[_n++] = c;
            _sentence[_n++] = 0;

            (_term[_terms])[_nt++] = c;
            (_term[_terms++])[_nt] = 0;

            _state = WAITING;

            if (_tag == 5)
            {
                _utc = decimal(_term[1]);

                // calculate signed degree-decimal value of latitude term
                _latitude = decimal(_term[2]) / 100.0;
                float degs = floor(_latitude);
                _latitude = (100.0 * (_latitude - degs)) / 60.0;
                _latitude += degs;

                // southern hemisphere is negative-valued

                if ((_term[3])[0] == 'S')
                {
                    _latitude =  -_latitude;
                }

                // calculate signed degree-decimal value of longitude term
                _longitude = decimal(_term[4]) / 100.0;
                degs = floor(_longitude);
                _longitude = (100.0 * (_longitude - degs)) / 60.0;
                _longitude += degs;

                // western hemisphere is negative-valued
                if ((_term[5])[0] == 'W')
                {
                    _longitude = -_longitude;
                }

                _fix_quality = decimal(_term[6]);
                _satellites = decimal(_term[7]);
                _hdop = decimal(_term[8]);
                _altitude = decimal(_term[9]);
                _geoid = decimal(_term[11]);

                _last_sentence = "";

                for (size_t i = 0; i < _n; i++)
                {
                    _last_sentence += _sentence[i];
                }

                return true;
            }

            return false;

        default :
            _state = WAITING;

            break;
    }

    return false;
}

float GPGGAFrame::utc() const
{
    return _utc;
}

float GPGGAFrame::latitude() const
{
    return _latitude;
}

float GPGGAFrame::longitude() const
{
    return _longitude;
}

unsigned char GPGGAFrame::fix_quality() const
{
    return (unsigned char) _fix_quality;
}

unsigned char GPGGAFrame::satellites() const
{
    return (unsigned char) _satellites;
}

float GPGGAFrame::hdop() const
{
    return _hdop;
}

float GPGGAFrame::altitude() const
{
    return _altitude;
}

float GPGGAFrame::geoid() const
{
    return _geoid;
}
