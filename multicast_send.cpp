//
// Created by Anders Cedronius on 2022-02-02.
//
#include <iostream>
#include <thread>
#include <kissnet.hpp>

int main(int argc, char* argv[])
{
    const auto mcast_addr = "226.1.1.1"; //IPv4
    const uint64_t mcast_port = 9000;
    const std::string mcast_message = "This is a multicast message payload";

    std::cout << "kissnet multicast send packets started." << std::endl;
    std::cout << "mcast IP -> " << mcast_addr << " mcast port -> " << mcast_port << std::endl;
    //Max IPv6 UDP payload is 1452.. IPv4 is 1472
    kissnet::buffer<1452> send_this;
    std::memcpy(send_this.data(), mcast_message.c_str(), mcast_message.size());

    //Tell kissnet where to send the multicast packets
    kissnet::udp_socket mcast_send_socket(kissnet::endpoint(mcast_addr, mcast_port));
    while (true) {
        //Send the payload
        auto[sent_bytes, status] = mcast_send_socket.send(send_this, sizeof(send_this));
        if (sent_bytes != sizeof(send_this) || status != kissnet::socket_status::valid) {
            std::cout << "kissnet multicast send failure" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "Sent multicast packet." << std::endl;

        //Wait for 100 milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return EXIT_SUCCESS;
}