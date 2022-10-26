#include <array>
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_context io_context;
        tcp::resolver resolver{io_context};
        auto endpoint = resolver.resolve("127.0.0.1", "42069");
        tcp::socket socket{io_context};
        boost::asio::connect(socket, endpoint);

        while (true) {
            // Listen for messages

            std::array<char, 128> buffer{};
            boost::system::error_code error;
            size_t length = socket.read_some(boost::asio::buffer(buffer), error);

            if (error == boost::asio::error::eof) {
                // Clean connection cut off
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            }

            std::cout.write(buffer.data(), length);
        }
    } catch (std::exception& exception) {
        std::cerr << exception.what() << std::endl;
    }
}
