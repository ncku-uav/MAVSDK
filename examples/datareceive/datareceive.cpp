#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <chrono>
#include <future>
#include <iostream>
#include <memory>
#include <thread>
#include <stdio.h>   
#include <string>

#pragma comment(lib,"ws2_32.lib")    



using namespace mavsdk;
using std::this_thread::sleep_for;
using std::chrono::seconds;

void usage(const std::string& bin_name)
{
    std::cerr << "Usage : " << bin_name << " <connection_url>\n"
              << "Connection URL format should be :\n"
              << " For TCP : tcp://[server_host][:server_port]\n"
              << " For UDP : udp://[bind_host][:bind_port]\n"
              << " For Serial : serial:///path/to/serial/dev[:baudrate]\n"
              << "For example, to connect to the simulator use URL: udp://:14540\n";
}

std::shared_ptr<System> get_system(Mavsdk& mavsdk)
{
    std::cout << "Waiting to discover system...\n";
    auto prom = std::promise<std::shared_ptr<System>>{};
    auto fut = prom.get_future();

    // We wait for new systems to be discovered, once we find one that has an
    // autopilot, we decide to use it.
    mavsdk.subscribe_on_new_system([&mavsdk, &prom]() {
        auto system = mavsdk.systems().back();

        if (system->has_autopilot()) {
            std::cout << "Discovered autopilot\n";

            // Unsubscribe again as we only want to find one system.
            mavsdk.subscribe_on_new_system(nullptr);
            prom.set_value(system);
        }
    });

    // We usually receive heartbeats at 1Hz, therefore we should find a
    // system after around 3 seconds max, surely.
    // if (fut.wait_for(seconds(3)) == std::future_status::timeout) {
    //     std::cerr << "No autopilot found.\n";
    //     return {};
    // }

    // Get discovered system now.
    return fut.get();
}

static void get_ina219(std::shared_ptr<System> system);

    // static void get_position(std::shared_ptr<System> system);
    // static void get_eulerangle(std::shared_ptr<System> system);



int main(int argc, char** argv)
{
    if (argc != 2) {
        usage(argv[0]);
        return 1;
    }

    Mavsdk mavsdk;
    ConnectionResult connection_result = mavsdk.add_any_connection(argv[1]);

    if (connection_result != ConnectionResult::Success) {
        std::cerr << "Connection failed: " << connection_result << '\n';
        return 1;
    }

    auto system = get_system(mavsdk);
    if (!system) {
        return 1;
    }

    auto telemetry = Telemetry{system};

    // while (!telemetry.health_all_ok()) {
    //     std::cout << "Waiting for system to be ready\n";
    //     sleep_for(seconds(1));
    // }
    // std::cout << "System is ready\n";

    const Telemetry::Result set_rate_result = telemetry.set_rate_position(50);

    if (set_rate_result != Telemetry::Result::Success) {
        std::cerr << "Setting rate failed:" << set_rate_result << '\n';
        return 1;
    }
    
    

    std::vector<std::thread> threads;



    std::thread ina219 (&get_ina219,std::ref(system));



 
    ina219.join();



    return 0;       

}

void get_ina219(std::shared_ptr<System> system) {
    auto telemetry = Telemetry{system};
    std::string voltageLeft,currentLeft,powerLeft,voltageRight,currentRight,powerRight;
    std::string timeStamp;
    while(1){
        telemetry.subscribe_ina219([&timeStamp,&voltageLeft,&currentLeft,&powerLeft,&voltageRight,&currentRight,&powerRight](Telemetry::Ina219 ina219) {

            std::cout << "Left solar: " << "\nvoltage: " << ina219.leftVoltage << "\ncurrent: " << ina219.leftCurrent << "\npower" << ina219.leftPower
                    << "\nRight solar:" << "\nvoltage: " << ina219.rightVoltage << "\ncurrent: " << ina219.rightCurrent << "\npower" << ina219.rightPower;

        });   
    } 
    

}


