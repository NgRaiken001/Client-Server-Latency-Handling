#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <cmath>

using boost::asio::ip::udp;

const std::string SERVER_IP = "127.0.0.1";
const int PORT = 8080;
const float DELTA_TIME = 0.016f;
const float LERP_FACTOR = 0.1f;

struct Player {
    float x = 0, y = 0;
    float predictedX = 0, predictedY = 0;
};

void movePlayer(float& x, float& y, float dx, float dy) {
    x += dx * DELTA_TIME;
    y += dy * DELTA_TIME;
}

int main() {
    boost::asio::io_context io_context;
    udp::socket socket(io_context);
    socket.open(udp::v4());

    udp::endpoint server_endpoint(boost::asio::ip::make_address(SERVER_IP), PORT);

    Player player;
    
    while (true) {
        float dx = 1.0f, dy = 0.5f;  // Simulated input (moving diagonally)

        // **Step 1: Client-Side Prediction**
        player.predictedX += dx * DELTA_TIME;
        player.predictedY += dy * DELTA_TIME;

        // Send input to server
        std::string message = std::to_string(dx) + " " + std::to_string(dy);
        socket.send_to(boost::asio::buffer(message), server_endpoint);

        // **Step 2: Receive authoritative position from server**
        char buffer[1024];
        udp::endpoint sender_endpoint;
        size_t length = socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);

        float serverX, serverY;
        sscanf(std::string(buffer, length).c_str(), "%f %f", &serverX, &serverY);

        // **Step 3: Reconciliation (Smoothing)**
        if (std::abs(serverX - player.predictedX) > 0.1f || std::abs(serverY - player.predictedY) > 0.1f) {
            // Smooth correction using linear interpolation (LERP)
            player.x += (serverX - player.x) * LERP_FACTOR;
            player.y += (serverY - player.y) * LERP_FACTOR;
        } else {
            // No correction needed, maintain prediction
            player.x = player.predictedX;
            player.y = player.predictedY;
        }

        // Print updated position
        std::cout << "Predicted: (" << player.predictedX << ", " << player.predictedY
                  << ") | Server: (" << serverX << ", " << serverY
                  << ") | Adjusted: (" << player.x << ", " << player.y << ")\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(16));  // Simulate game loop
    }

    return 0;
}
