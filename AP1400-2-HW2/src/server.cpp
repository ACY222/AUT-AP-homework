#include "server.h"
#include "client.h"
#include "crypto.h"
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <regex>
#include <vector>

std::vector<std::string> pending_trxs;

Server::Server() {
  // nothing to do
}

// add a new client in clients
// create a new Client with the specified id, if the id already exists, the
// server should add a random 4 digit number at the end of it
std::shared_ptr<Client> Server::add_client(std::string id) {
  // 1. Check if the id already exists
  for (auto& client_wallet : clients) {
    if (client_wallet.first->get_id() == id) {
      // if exists, add a random 4 digit number at the end of it
      std::random_device rd;                    // seed
      std::mt19937 engine(rd());                // random number engines
      std::uniform_int_distribution dist(0, 9); // random number distribution
      for (int i = 0; i < 4; ++i) {
        id += std::to_string(dist(engine));
      }
      break;
    }
  }
  auto client = std::make_shared<Client>(id, *this);
  clients[client] = 5.0;
  return client;
}

// get a poointer to a Client using id
std::shared_ptr<Client> Server::get_client(std::string id) const {
  for (const auto& client_wallet : clients) {
    if (client_wallet.first->get_id() == id) {
      return client_wallet.first;
    }
  }
  return {};
}

// return the wallet value of the client with username id
double Server::get_wallet(std::string id) const {
  for (const auto& client_wallet : clients) {
    if (client_wallet.first->get_id() == id) {
      return client_wallet.second;
    }
  }
  return 0;
}

// staic. using regular expression to parse the transaction into three parts
// trx = sender_id-receiver_id-value
bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) {
  std::string pattern = R"((\w+)-(\w+)-(\d+\.\d+))";
  std::regex rg(pattern);
  std::smatch results;

  if (std::regex_match(trx, results, rg)) {
    sender = results[1].str();
    receiver = results[2].str();
    value = std::stod(results[3].str());
    return true;
  }
  else {
    throw std::runtime_error("The transaction is not standard");
  }
  return false;
}

// Only accept a pending transaction by authenticating the sender's signature
//    and if he has enough money in his wallet
// hint: To authenticate a string with your RSA keys, use:
//    bool authentic = crypto::verifySignature(public_key, "my data", signature);
bool Server::add_pending_trx(std::string trx, std::string signature) const {
  std::string sender_id, receiver_id;
  double money;
  if (parse_trx(trx, sender_id, receiver_id, money)) {
    auto sender = this->get_client(sender_id);
    auto receiver = this->get_client(receiver_id);
    if (receiver == nullptr) {  // maybe the receiver doesn't exist
      return false;
    }
    bool authentic = crypto::verifySignature(sender->get_publickey(), trx, signature);
    bool has_money = sender->get_wallet() >= money;
    if (authentic and has_money) {
      pending_trxs.push_back(trx);
      return true;
    }
  }
  return false;
}

// Hint: To calculate the sha256 of a string
//    std::string hash {crypto::sha256("hi")};
size_t Server::mine() {
  // 1. put the pending transactions together
  std::string mempool = "";
  for (auto& trx : pending_trxs) {
    mempool += trx;
  }
  // 2. asks each Client for a nonce and calculates the sha256 of the final string
  bool mined = false;
  while (!mined) {
    for (auto& client_wallet : clients) {
      std::string nonce = std::to_string(client_wallet.first->generate_nonce());
      std::string hash = crypto::sha256(mempool + nonce);

      // check if the hash has "000" in a row in the first 10 numbers
      if (hash.substr(0, 10).find("000") != std::string::npos) {
        // mine successful, award the client with 6.25 coins
        std::cout << client_wallet.first->get_id() << "\n";
        client_wallet.second += 6.25;
        // all the transactions will be removed from pending and the effect of
        // them will be applied on the clients
        for (auto& trx : pending_trxs) {
          std::string sender_id, receiver_id;
          double value;
          parse_trx(trx, sender_id, receiver_id, value);
          auto sender = get_client(sender_id);
          auto receiver = get_client(receiver_id);
          clients[sender] -= value;
          clients[receiver] += value;
        }
        pending_trxs.clear();
        return std::stoi(nonce);
      }
    }
  }
  return -1;
}

using MPD = std::map<std::shared_ptr<Client>, double>;
void show_wallets(const Server& server) {
		std::cout << std::string(20, '*') << std::endl;
    for (const auto& client : *((MPD*)&server))
			std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
		std::cout << std::string(20, '*') << std::endl;
}
