#include <iostream>
#include <vector>
#include <cstring>

struct Message {
    uint32_t id;
    uint32_t length;
    std::vector<char> data;
    
    std::vector<char> serialize() const {
        std::vector<char> buffer(sizeof(id) + sizeof(length) + data.size());
        std::memcpy(buffer.data(), &id, sizeof(id));
        std::memcpy(buffer.data() + sizeof(id), &length, sizeof(length));
        std::memcpy(buffer.data() + sizeof(id) + sizeof(length), data.data(), data.size());
        return buffer;
    }

    static Message deserialize(const std::vector<char>& buffer) {
        Message msg;
        std::memcpy(&msg.id, buffer.data(), sizeof(msg.id));
        std::memcpy(&msg.length, buffer.data() + sizeof(msg.id), sizeof(msg.length));
        msg.data.resize(msg.length);
        std::memcpy(msg.data.data(), buffer.data() + sizeof(msg.id) + sizeof(msg.length), msg.length);
        return msg;
    }
};

int main() {
    Message msg {1, 5, {'H', 'e', 'l', 'l', 'o'}};
    auto serialized = msg.serialize();
    
    Message deserialized = Message::deserialize(serialized);
    std::cout << "ID: " << deserialized.id << ", Length: " << deserialized.length << ", Data: ";
    for (char c : deserialized.data) {
        std::cout << c;
    }
    std::cout << std::endl;
    
    return 0;
}
