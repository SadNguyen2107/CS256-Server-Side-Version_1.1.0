#include <utility> // Include this line before Boost.Asio headers
#include "../include/Server.h"

using namespace SN_Server;

void HandleSignal(int signal);

// The Server
std::shared_ptr<Server> server;

int main(int argc, char const *argv[])
{
    // Make a Signal To Turn Off the Server
    std::signal(SIGINT, HandleSignal);

    server = std::make_shared<Server>("127.0.0.1", 6969);

    // Start The Server
    server->Start();

    while (server->IsRunning())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Server is Running!" << std::endl
                  << "In PID: " << getpid() << std::endl;
    }

    return 0;
}

void HandleSignal(int signal)
{
    std::string statement;
    switch (signal)
    {
    case SIGINT:
        statement = std::format("Received signal {0}. Initiating graceful shutdown.\n", signal);
        write(STDOUT_FILENO, statement.c_str(), statement.size());
        
        // Call The Server To Stop
        server->Stop();
        break;

    case SIGTERM:
        write(STDOUT_FILENO, "Terminate Called!\n", 19);
        break;

    case SIGTSTP:
        write(STDOUT_FILENO, "Stop Process!\n", 15);
        break;

    case SIGSTOP:
        write(STDOUT_FILENO, "Stop Process!\n", 15);
        break;

    case SIGCONT:
        write(STDOUT_FILENO, "Continue Process\n", 18);
        break;

    default:
        break;
    }
}