#include "client.h"
#include "crypto.h"
#include "server.h"
#include <climits>
#include <random>
#include <string>


Client::Client(std::string id, const Server& server) : id(id), server(&server) {
  // generate public and private keys
  crypto::generate_key(this->public_key, this->private_key);
}

std::string Client::get_id() const {
  return this->id;
}

std::string Client::get_publickey() const {
  return this->public_key;
}

// We need to turn to Server's get_wallet(std::string id);
double Client::get_wallet() const {
  return this->server->get_wallet(this->id);
}

// signs the input txt with the private key and returns the signature
// Hint: TO sign a string with your RSA keys, use
//    std::string signature = crypto::signMessage(private_key, "my data");
std::string Client::sign(std::string txt) const {
  return crypto::signMessage(this->private_key, txt);
}

// creates a transaction in the server according to the input
// use the specified string format and sign the final transaction string with
// your private key
bool Client::transfer_money(std::string receiver, double value) const {
  std::string trx = this->get_id() + "-" + receiver + "-" + std::to_string(value);
  return this->server->add_pending_trx(trx, sign(trx));
}

// returns a random number as a nonce so the server uses it for mining
// use static to get a non-repetitive sequence
size_t Client::generate_nonce() {
  static std::random_device rd;
  static std::mt19937 engine(rd());
  static std::uniform_int_distribution dist(0, INT_MAX);
  return dist(engine);
}
