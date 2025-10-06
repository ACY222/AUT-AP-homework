#include "server.h"
#include "client.h"
#include "crypto.h"
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

// global variable should be defined in the source file
std::vector<std::string> pending_trxs;

Server::Server() {
  // do I need to realize it? No, nothing required
}

std::shared_ptr<Client> Server::add_client(std::string id) {
  for (const auto& client_wallet : clients) {
    // if the id already exists
    if (client_wallet.first->get_id() == id) {
      std::default_random_engine e;
      std::uniform_int_distribution u(0, 10);
      std::string tail = "";
      for (int i = 0; i < 4; ++i) {
        tail += std::to_string(u(e));
      }
      id += tail;
    }
  }
	// Client(std::string id, const Server& server);
  auto client = std::make_shared<Client>(id, *this);
  clients[client] = 5;  // assign 5 coins at the beginning
  return client;
}

// get a pointer to a Client using its `id`
std::shared_ptr<Client> Server::get_client(std::string id) const {
  // clients: vector<map<Client*, double>>
  for (const auto& client_wallet : clients) {
    if (client_wallet.first->get_id() == id) {
      return client_wallet.first;
    }
  }
  return nullptr;
}

// return the wallet value of the client with username `id`
double Server::get_wallet(std::string id) const {
  for (const auto& client_wallet : clients) {
    if (client_wallet.first->get_id() == id) {
      return client_wallet.second;
    }
  }
  return 0;
}
// trx: sender-receiver-value
// if the string is not standard, throw a runtime error
// parse this string format and outputting each property separately,
// if the string is not standard you should throw a runtime error.
bool Server::parse_trx(const std::string& trx, std::string& sender, std::string& receiver, double& value) {
  // first we should check if the trx is standard, use regular expression
  // three capture groups, w means word character, including letters(a-zA-Z), digits(0-9)
  // and '_', d means digital character, including 0-9, `+` means one or more
  std::string pattern = "(\\w+)-(\\w+)-(\\d+\\.\\d+)";
  std::regex r(pattern);
  std::smatch results;

  // if is, then we should parse the trx
  if (std::regex_match(trx, results, r)) {
    sender = results.str(1);
    receiver = results.str(2);
    value = std::stod(results.str(3));
    return true;
  }
  else {
    throw std::runtime_error("trx does not match the format");
  }
  return false;
}

// Only accept a pending transaction by authenticating the sender's signature
//  how to authenticate his signature?
// and if he has enough money in his wallet.
bool Server::add_pending_trx(std::string trx, std::string signature) const {
  // get the sender id, receiver id, and trx amount
  std::string sender_id, receiver_id;
  double value;
  if (!Server::parse_trx(trx, sender_id, receiver_id, value)) {
    return false;
  }

  auto sender_p = Server::get_client(sender_id);
  auto receiver_p = Server::get_client(receiver_id);
  if (sender_p == nullptr or receiver_p == nullptr) {
    return false; // if there's no such sender or receiver
  }
  // authenticating the sender's signature
  //    actually, I'm not sure how this function works
  // and check if the sender has enough money in the wallet
  bool authentic = crypto::verifySignature(sender_p->get_publickey(), trx, signature);
  bool has_enough_money = Server::get_wallet(sender_id) >= value;
  if (authentic and has_enough_money) {
    pending_trxs.push_back(trx);
    return true;
  }
  return false;
}

size_t Server::mine() {
  // 1. generate the mempool
  std::string mempool = "";
  for (const auto& trx : pending_trxs) {
    mempool += trx;
  }
  size_t nonce = 0;
  bool mined = false;
  while (!mined) {
    for (auto& client_wallet : clients) {
      // ask each client for a nonce
      nonce = client_wallet.first->generate_nonce();
      // calcute the sha256 of the final string
      // check if the generated sha256 has "000" in a row in the first 10 numbers
      if (crypto::sha256(mempool + std::to_string(nonce)).substr(0, 10).find("000")
        != std::string::npos) { // == npos means didn't find, like vector.end()
        // the mined is successful and the client will be awarded for 6.26 coins
        mined = true;
        client_wallet.second += 6.25;
        // all the transactions will be removed from pending
        // and the effect of them will be applied on the clients
        // I can use parse_trx to realize this part
        for (const auto& trx : pending_trxs) {
          std::string sender, receiver;
          double value;
          parse_trx(trx, sender, receiver, value);
          clients[get_client(sender)] -= value;
          clients[get_client(receiver)] += value;
        }
        pending_trxs.clear();
        // print the id of the miner and return the associate nonce.
        std::cout << "miner's id: " << client_wallet.first->get_id() << ", "
          << "associate nonce: " << nonce << std::endl;
        return nonce;
      }
    }
  }
  return nonce;
}

using MPD = std::map<std::shared_ptr<Client>, double>;
void show_wallets(const Server &server) {
  std::cout << std::string(20, '*') << std::endl;
  // how to visit server.clients?
  // for(const auto& client: server.clients)
  //   std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
  for (const auto& client : *((MPD*)&server))
    std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
  std::cout << std::string(20, '*') << std::endl;
}
