//
// Created by lkapi on 04.03.2023.
//

#include "SafeKey.h"

namespace Encryption {

    SafeKey::SafeKey()  : xor_key_("You are on thin ice") {}

    bool SafeKey::save(const string &filename, const string &data) {
        ofstream file(filename, ios::binary | ios::out);
        if (!file.is_open()) {
            cerr << "Error: failed to open file! " << filename << endl;
            CREATE_FILE(filename);

            save(filename, data);
        }

        // Encrypt the data using the XOR cipher
        string encrypted_data = xor_cipher(data);

        // Write the encrypted data to the file
        file.write(encrypted_data.c_str(), encrypted_data.size());

        // Close the file
        file.close();
        return true;
    }

    int SafeKey::load(const string &filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            CREATE_FILE(filename);
            return 1;
        }

        // Determine the size of the file
        file.seekg(0, ios::end);
        streamsize size = file.tellg();
        file.seekg(0, ios::beg);

        // Read the entire file into memory
        string data(size, '\0');
        if (!file.read(&data[0], size)) {
            cerr << "Error: failed to read file " << filename << endl;
            return 2;
        }

        // Decrypt the data using the XOR cipher
        string decrypted_data = xor_cipher(data);

        // Close the file
        file.close();

        token = std::move(decrypted_data);

        return 0;
    }

    string SafeKey::xor_cipher(const string &data) const {
        string result;
        for (size_t i = 0; i < data.size(); i++) {
            result += data[i] ^ xor_key_[i % xor_key_.size()];
        }
        return result;
    }

    string SafeKey::getToken() {
        return token;
    }

} // Encryption