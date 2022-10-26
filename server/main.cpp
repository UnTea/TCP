#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 42069));

        while (true) {
            std::cout << "Accepting connection on port 42069\n";
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::cout << "Client connected! Sending message!\n";
            std::string hello_message = "Hello from server!\n";
            boost::system::error_code error;

            boost::asio::write(socket, boost::asio::buffer(hello_message), error);
        }
    } catch (std::exception& exception) {
        std::cerr << exception.what() << std::endl;
    }
}
