#ifndef SERIAL_H
#define SERIAL_H

#include <boost/asio/serial_port.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class Serial
{
    protected :

        /**
        * Called when an async read completes or has been cancelled.
        **/
        void read_complete(const boost::system::error_code& error, size_t bytes_transferred);

        /**
        * Called when the timer's deadline expires.
        **/
        void time_out(const boost::system::error_code& error);

        /**
        *
        **/
        boost::asio::serial_port& port;

        /**
        *
        **/
        size_t timeout;

        /**
        *
        **/
        char c;

        /**
        *
        **/
        boost::asio::deadline_timer timer;

        /**
        *
        **/
        bool read_error;

    public :

        /**
        * Constructs a blocking reader, pass in an open serial_port and
        * a timeout in milliseconds.
        **/
        Serial(boost::asio::serial_port& port, size_t timeout);

        /**
        * Reads a character or times out.
        * returns false if the read times out.
        **/
        bool read_char(char& val);
};

#endif // SERIAL_H
