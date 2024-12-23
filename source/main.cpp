#include "error.h"
#include "data.h"
#include "client.h"
#include "terminal.h"
#include <array>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        cout << "[LOG] Initializing Terminal..." << endl;
        Terminal terminal;
        terminal.parseArgs(argc, argv);

        cout << "[LOG] Config Path: " << terminal.getConfigPath() << endl;
        cout << "[LOG] Input Path: " << terminal.getInputPath() << endl;
        cout << "[LOG] Output Path: " << terminal.getOutputPath() << endl;
        cout << "[LOG] Server Address: " << terminal.getAddress() << endl;
        cout << "[LOG] Server Port: " << terminal.getPort() << endl;

        cout << "[LOG] Connecting to server at " << terminal.getAddress() << ":" << terminal.getPort() << "..." << endl;
        Client client(terminal.getAddress(), terminal.getPort());
        client.connectToServer();

        cout << "[LOG] Loading configuration from " << terminal.getConfigPath() << "..." << endl;
        DataHandler data(terminal.getConfigPath(), terminal.getInputPath(), terminal.getOutputPath());

        array<string, 2> userpass = data.loadConfig();
        cout << "[LOG] Username: " << userpass[0] << endl;

        cout << "[LOG] Authenticating user " << userpass[0] << "..." << endl;
        client.authenticate(userpass[0], userpass[1]);

        cout << "[LOG] Reading data from " << terminal.getInputPath() << "..." << endl;
        vector<vector<double>> vectors = data.readData();
        cout << "[LOG] Read data: " << endl;
        PrintVectors(vectors);

        cout << "[LOG] Calculating results..." << endl;
        vector<double> result = client.calculate(vectors);
        cout << "[LOG] Calculated results: " << endl;
        PrintVector(result);

        cout << "[LOG] Writing results to " << terminal.getOutputPath() << "..." << endl;
        data.writeData(result);

        cout << "[LOG] Operation completed successfully!" << endl;
    }
    catch (const RuntimeError &e)
    {
        cerr << "[ERR] Runtime error: " << e.what() << endl;
        return 1;
    }
    catch (const exception &e)
    {
        cerr << "[ERR] Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
