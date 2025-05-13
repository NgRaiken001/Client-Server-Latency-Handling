#include <iostream>
#include <unordered_map>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

const int PORT = 8080;
const float DELTA_TIME = 0.016f;  // 16ms per frame (~60FPS)

struct Player {
    float x, y;
};

std::unordered_map<std::string, Player> players;

int main() {
    boost::asio::io_context io_context;
    udp::socket socket(io_context, udp::endpoint(udp::v4(), PORT));
    
    char buffer[1024];
    udp::endpoint client_endpoint;

    std::cout << "Server running on port " << PORT << "...\n";

    while (true) {
        size_t length = socket.receive_from(boost::asio::buffer(buffer), client_endpoint);
        std::string received_data(buffer, length);

        float dx, dy;
        sscanf(received_data.c_str(), "%f %f", &dx, &dy);

        // Update player's position on server
        std::string client_ip = client_endpoint.address().to_string();
        players[client_ip].x += dx * DELTA_TIME;
        players[client_ip].y += dy * DELTA_TIME;

        // Send updated position back to client
        std::string response = std::to_string(players[client_ip].x) + " " + std::to_string(players[client_ip].y);
        socket.send_to(boost::asio::buffer(response), client_endpoint);
    }

    return 0;
}
