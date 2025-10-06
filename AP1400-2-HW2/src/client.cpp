#include "server.h"
#include "client.h"
#include "crypto.h"
#include <climits>
#include <random>
#include <string>


	// Server const* const server;
	// const std::string id;
	// std::string public_key;
	// std::string private_key;

// Creates an object of Client and assigning the specified variables using the inputs
// Also generate RSA keys for the client (public and private keys).
Client::Client(std::string id, const Server& server) : id(id), server(&server) {
  crypto::generate_key(this->public_key, this->private_key);
}

std::string Client::get_id() const {
  return this->id;
}

std::string Client::get_publickey() const {
  return this->public_key;
}

double Client::get_wallet() const {
  return this->server->get_wallet(this->id);
}

// signs the input with the private key and returns the signature.
std::string Client::sign(std::string txt) const {
  return crypto::signMessage(this->private_key, txt);
}

// Creates a transaction in the server according to its inputs.
//    use the specified string format described in above sections
//    sign the final transaction string with your private key.
// use both your signature and your transaction signature to create a pending transaction in the Server using *add_pending_trx* function.
bool Client::transfer_money(std::string receiver, double value) const {
  std::string trx = this->get_id() + "-" + receiver + "-" + std::to_string(value);
  std::string signature = sign(trx);
  return server->add_pending_trx(trx, signature);
}

// Returns a random number as a nonce so the server uses it for mining.
size_t Client::generate_nonce() {
  // using static to avoid initializing e and u every time
  // so that we can save a lot of time
  static std::default_random_engine e;
  static std::uniform_int_distribution u(0, INT_MAX);
  return u(e);
}
