#include "Serial.h"

using namespace boost;

Serial::Serial(asio::serial_port& port, size_t timeout) : port(port), timeout(timeout), timer(port.get_io_service()), read_error(true)
{

}

void Serial::read_complete(const system::error_code& error, size_t bytes_transferred)
{
    read_error = (error || bytes_transferred == 0);

    // read has finished, so cancel the timer.
    timer.cancel();
}

void Serial::time_out(const system::error_code& error)
{
    // was the timeout was cancelled ?
    if (error)
    {
        return;
    }

    // no, we have timed out, so kill the read operation
    port.cancel();
}

bool Serial::read_char(char& val)
{
    val = c = '\0';

    // after a timeout & cancel it seems we need to do a reset for subsequent reads to work.
    port.get_io_service().reset();

    // asynchronously read 1 character
    asio::async_read(port, asio::buffer(&c, 1), bind(&Serial::read_complete, this, asio::placeholders::error, asio::placeholders::bytes_transferred));

    // setup a deadline time to implement our timeout.
    timer.expires_from_now(posix_time::milliseconds(timeout));
    timer.async_wait(bind(&Serial::time_out, this, asio::placeholders::error));

    // this will block until a character is read or until the it is cancelled.
    port.get_io_service().run();

    if (!read_error)
    {
        val = c;
    }

    return !read_error;
}
