#include "GNRMCFrame.h"

#define GNRMC_TOKEN "$GNRMC"

GNRMCFrame::GNRMCFrame()
{
    //ctor
}

bool GNRMCFrame::decode(const char& c)
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
                if (GNRMC_TOKEN[_n] == c)
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
                _status = (_term[2])[0];

                // calculate signed degree-decimal value of latitude term
                _latitude = decimal(_term[3]) / 100.0;
                float degs = floor(_latitude);
                _latitude = (100.0 * (_latitude - degs)) / 60.0;
                _latitude += degs;

                // southern hemisphere is negative-valued

                if ((_term[4])[0] == 'S')
                {
                    _latitude =  -_latitude;
                }

                // calculate signed degree-decimal value of longitude term
                _longitude = decimal(_term[5]) / 100.0;
                degs = floor(_longitude);
                _longitude = (100.0 * (_longitude - degs)) / 60.0;
                _longitude += degs;

                // western hemisphere is negative-valued
                if ((_term[6])[0] == 'W')
                {
                    _longitude = -_longitude;
                }

                _speed = decimal(_term[7]);
                _course = decimal(_term[8]);

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

float GNRMCFrame::utc() const
{
	return _utc;
}

char GNRMCFrame::status() const
{
	return _status;
}

float GNRMCFrame::latitude() const
{
	return _latitude;
}

float GNRMCFrame::longitude() const
{
	return _longitude;
}

float GNRMCFrame::speed() const
{
	return (_speed * 1.852);
}

float GNRMCFrame::course() const
{
	return _course;
}
