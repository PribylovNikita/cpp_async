#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <string>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

class Client{
public:
    Client()
    : socket(tcp::socket(io_context)), resolver(tcp::resolver(io_context))
    {}

    boost::system::error_code connect(const std::string& host, const std::string& port) {
        boost::asio::connect(socket, resolver.resolve(host, port), connect_ec);
        return connect_ec;
    }

    int send_and_receive(const std::string& request){
        if (connect_ec) {
            std::cerr << "Connection is not established, use connect() first.\n";
            return -1;
        }

        try {
            size_t request_length = request.length();
            boost::asio::write(socket, boost::asio::buffer(request, request_length));

            char reply[max_length];
            size_t reply_length = boost::asio::read(socket,
                                                    boost::asio::buffer(reply, request_length));
            std::cout << "Reply is: ";
            std::cout.write(reply, reply_length);
            std::cout << "\n";
        } catch(std::exception& e) {
            std::cerr << "Write-read cycle failed:\n" << e.what() << "\n";
        }

        return 0;
    }

private:
    boost::asio::io_context io_context;
    tcp::socket socket;
    tcp::resolver resolver;
    boost::system::error_code connect_ec;
};

int connect_send_and_receive(const std::string& host, const std::string& port, const std::string& request, int cycles) {
    Client client;
    client.connect(host, port);
    for (int j = 0; j < cycles; j++) {
        client.send_and_receive(request);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 5) {
            std::cerr << "Usage: blocking_tcp_echo_client <host> <port> <threads> <write-read cycles>\n";
            return 1;
        }

        const std::string host = argv[1];
        const std::string port = argv[2];
        int threads_amount = std::atoi(argv[3]);
        int cycles = std::atoi(argv[4]);
        const std::string msg = "echo echo";

        std::vector<std::thread> threads;
        for (int i = 0; i < threads_amount; i++) {
            threads.emplace_back(connect_send_and_receive, host, port, msg, cycles);
        }
        for (std::thread &t: threads) {
            t.join();
        }

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}