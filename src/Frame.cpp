#include "Frame.h"

using namespace std;

Frame::Frame() : _state(WAITING), _n(0), _terms(0), _nt(0)
{
    for (size_t t = 0; t < 30; t++)
    {
        _term[t] = (char*) malloc (15 * sizeof(char));
    }
}

void Frame::decode(const string& s)
{
    for (size_t i = 0; i < s.size(); i++)
    {
        decode(s[i]);
    }
}

string Frame::sentence() const
{
    return _last_sentence;
}

string Frame::format_coords(float dd, unsigned char c) const
{
    char dir;

    if (c == LATITUDE) {
        dir = (dd < 0) ? 'S' : 'N';
    } else {
        dir = (dd < 0) ? 'W' : 'E';
    }

    dd = fabs(dd);

    int d = (int) dd;
    float mm = ((dd - d) * 60);
    int m = (int) mm;
    float s = (mm - m) * 60;

    ostringstream os;
    os << d << ' ' << m << '\'' << s << "''" << ' ' << dir;
    return os.str();
}

string Frame::format_time(const float& utc) const
{
    ostringstream o;
    o << utc;

    string str = o.str();

    string s = str.substr(str.size() - 2, 2);
    string m = str.substr(str.size() - 4, 2);
    string h = str.substr(0, str.size() - 4);

    return h + ':' + m + ':' + s + " UTC";
}

float Frame::decimal(const string& s)
{
    float f;

    if(from_string<float>(f, s))
    {
        return f;
    }

    return 0.0f;
}
