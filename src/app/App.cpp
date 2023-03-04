//
// Created by lkapi on 25.02.2023.
//

#include "App.h"

#include <fstream>
#include <utility>

using namespace Encryption;

namespace Application {

    void App::process() {

        helpMessage();

        bool isFirst = true;
        while (1) {
            if (!isFirst) {
                cout << endl;
                helpMessageBody();
            }
            RESET_COLOR

            int operation = getOperation();

            if (operation == 2) {
                USE_COLOR(BOLD_GREEN);
                cout << "TOKEN FOR USE: " << key << endl;
                RESET_COLOR
            } else if (operation == 3) {
                string inputString = getInputString();

                if (!isOutputDefined)
                    output = getFilename();

                // Encrypt and write to files
                Encryptor::encryptToFile(key, inputString, output);
            } else if (operation == 4) {
                // Read and decrypt from files
                if (!isInputDefined)
                    input = getFilename();

                string decrypted = Encryptor::decryptFromFile(key, input);
                USE_COLOR(BOLD_GREEN);
                cout << "Decrypted output: " << decrypted << endl;
                RESET_COLOR
            } else if (operation == 1) {
                askKeyInput();
            } else if (operation == 5) {
                break;
            } else {
                cerr << "SELECT 1/2/3/4/5 !!!" << endl;
            }

            isFirst = false;
        }

        waitForAnyKey();

    }

    string App::askKeyInput() {
        string key;

        string answer;

        // Get the key from the user and save it in the files
        USE_COLOR(BACKGROUND_YELLOW);
        USE_COLOR(BOLD_BLACK);
        cout << "Enter the key: ";
        RESET_COLOR

        cin >> key;

        USE_COLOR(YELLOW);
        cout << "Does i save key? (y/n) ";
        RESET_COLOR

        cin >> answer;
        if (answer.empty() || answer.starts_with('n')) {
            return key;
        }

        SafeKey keyFile;
        keyFile.save(getFilename(), key);

        return key;
    }

    string App::getInputString() {
        string answer;

        string temp;

        USE_COLOR(BACKGROUND_YELLOW);
        USE_COLOR(BLACK);
        cout << "Enter the string:";
        RESET_COLOR

        cin >> temp;

        getline(cin, answer);

        return temp + answer;
    }

    string App::getFilename() {
        string answer;

        USE_COLOR(BACKGROUND_BLUE);
        USE_COLOR(BLACK);
        cout << "Enter the filename:";
        RESET_COLOR

        cin >> answer;

        return answer;
    }

    int App::getOperation() {
        int answer;

        // Get the key from the user and save it in the files
        USE_COLOR(BACKGROUND_YELLOW);
        cout << "Select operation(1/2/3/4):";
        RESET_COLOR

        cin >> answer;

        return answer;
    }

    void App::helpMessage() {
        USE_COLOR(CYAN);
        cout << "**********************************************\n";
        cout << "*          Welcome to ProjectSafe!           *\n";
        cout << "* This program can encrypt and decrypt files *\n";
        cout << "* and strings. Choose an option from below   *\n";
        cout << "**********************************************\n";
        helpMessageBody();
        cout << "*********************************************\n";
        RESET_COLOR
    }

    void App::waitForAnyKey() {
        cout << endl;
        USE_COLOR(BACKGROUND_RED);
        cout << "======== Done ========";
        RESET_COLOR
        cout << "\n";
        USE_COLOR(BOLD_CYAN);
        cout << "Press any key to exit." << endl;
        _getch();  // wait for a key press
    }

    void App::setKey(string str) {
        this->key = std::move(str);
    }

    void App::setOutput(string str) {
        this->output = std::move(str);
        isOutputDefined = true;
    }

    void App::setInput(string str) {
        this->input = std::move(str);
        isInputDefined = true;
    }

    void App::helpMessageBody() {
        USE_COLOR(CYAN);
        cout << "1. Change/Select key.\n";
        cout << "2. View key.\n";
        cout << "3. Encrypt string.\n";
        cout << "4. Decrypt files.\n";
        cout << "5. Exit\n";
    }

} // Application