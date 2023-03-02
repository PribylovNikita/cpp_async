#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

class Client{
public:
    Client()
    : socket(tcp::socket(io_context)), resolver(tcp::resolver(io_context))
    {}

    void connect(char host[], char port[]) {
        try {
            boost::asio::connect(socket, resolver.resolve(host, port));
        } catch(std::exception& e) {
            std::cerr << "Exception was raised while attempting to connect to " << host << ":" << port << ":\n" << e.what() << "\n";
        }
    }

    void send_and_receive(char request[]){
        if (!socket.is_open()) {
            std::cerr << "Socket is not open, use connect() first.\n";
            return;
        }

        try {
            size_t request_length = std::strlen(request);
            boost::asio::write(socket, boost::asio::buffer(request, request_length));

            char reply[max_length];
            size_t reply_length = boost::asio::read(socket,
                                                    boost::asio::buffer(reply, request_length));
            std::cout << "Reply is: ";
            std::cout.write(reply, reply_length);
            std::cout << "\n";
        } catch(std::exception& e) {
            std::cerr << "Exception was raised during write-read cycle:\n" << e.what() << "\n";
        }
    }

private:
    boost::asio::io_context io_context;
    tcp::socket socket;
    tcp::resolver resolver;
};

void do_work(char host[], char port[], char request[], int cycles) {
    Client client;
    client.connect(host, port);
    for (int j = 0; j < cycles; j++) {
        client.send_and_receive(request);
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 5) {
            std::cerr << "Usage: blocking_tcp_echo_client <host> <port> <threads> <write-read cycles>\n";
            return 1;
        }

        char *host = argv[1];
        char *port = argv[2];
        int threads = std::atoi(argv[3]);
        int cycles = std::atoi(argv[4]);
        char *msg = "hiHelloHi";

        std::vector<std::thread> vec;
        for (int i = 0; i < threads; i++) {
            vec.push_back(std::thread(do_work, host, port, msg, cycles));
        }
        for (std::thread &t: vec) {
            t.join();
        }

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}