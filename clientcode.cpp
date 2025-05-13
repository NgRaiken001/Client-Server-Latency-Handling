#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

const std::string SERVER_IP = "127.0.0.1";
const int PORT = 8080;

int main() {
    try {
        boost::asio::io_context io_context;
        udp::socket socket(io_context);
        socket.open(udp::v4());

        udp::endpoint server_endpoint(boost::asio::ip::make_address(SERVER_IP), PORT);

        std::string message = "Player Position: (10, 20)";
        socket.send_to(boost::asio::buffer(message), server_endpoint);

        char recv_buffer[1024];
        udp::endpoint sender_endpoint;
        size_t length = socket.receive_from(boost::asio::buffer(recv_buffer), sender_endpoint);

        std::cout << "Server Response: " << std::string(recv_buffer, length) << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
