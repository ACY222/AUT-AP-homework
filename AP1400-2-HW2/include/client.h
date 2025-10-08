#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Server;

class Client {
public:
	Client(std::string id, const Server& server);
	std::string get_id() const;
	std::string get_publickey() const;
  // We need to turn to Server's get_wallet(std::string id);
	double get_wallet() const;
  // signs the input txt with the private key and returns the signature
	std::string sign(std::string txt) const;
  // creates a transaction in the server according to the input
	bool transfer_money(std::string receiver, double value) const;
  // returns a random number as a nonce so the server uses it for mining
	static size_t generate_nonce();

private:
	Server const* const server;
	const std::string id;
	std::string public_key;
	std::string private_key;
};
#endif //CLIENT_H
