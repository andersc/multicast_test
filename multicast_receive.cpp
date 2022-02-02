//
// Created by Anders Cedronius on 2022-02-02.
//

#include <iostream>
#include <thread>
#include <kissnet.hpp>

const auto global_mcast_addr = "226.1.1.1"; //IPv4
//const auto global_mcast_addr = "ff12::1234"; //IPv6
const uint64_t global_mcast_port = 9000;

const std::string global_message = "This is a multicast message payload";


int main(int argc, char* argv[])
{
    kissnet::buffer<4000> receive_buffer;

    std::cout << "kissnet multicast receive" << std::endl;

    //Create a socket and join a multicast
    auto mcast_listen_socket = kissnet::udp_socket();
    mcast_listen_socket.join(kissnet::endpoint(global_mcast_addr, global_mcast_port));

    //Get 100 packets
    while (true) {
        auto [received_bytes, status] = mcast_listen_socket.recv(receive_buffer);
        if (!received_bytes || status != kissnet::socket_status::valid) {
            std::cout << "Failed getting multicast data" << std::endl;
        }
        //Did we get the correct payload
        uint64_t character_position = 0;
        for(const char& c : global_message) {
            if (c != (char)receive_buffer[character_position++]) {
                std::cout << "Data missmatch " << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "Got multicast data of size " << received_bytes << std::endl;
    }
    return 0;
}
