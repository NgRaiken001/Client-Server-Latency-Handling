#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

const int PORT = 8080;

int main() {
    try {
        boost::asio::io_context io_context;
        udp::socket socket(io_context, udp::endpoint(udp::v4(), PORT));

        char recv_buffer[1024];
        udp::endpoint remote_endpoint;

        std::cout << "Server is running on port " << PORT << "...\n";

        while (true) {
            size_t length = socket.receive_from(boost::asio::buffer(recv_buffer), remote_endpoint);
            std::string received_data(recv_buffer, length);

            std::cout << "Received: " << received_data << " from " << remote_endpoint << std::endl;

            // Echo back to client (simulating a simple response)
            std::string response = "ACK: " + received_data;
            socket.send_to(boost::asio::buffer(response), remote_endpoint);
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
