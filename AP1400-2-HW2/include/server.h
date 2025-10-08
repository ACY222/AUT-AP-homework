#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <map>
#include <string>
#include <vector>

extern std::vector<std::string> pending_trxs;

class Client;

class Server {
public:
	Server();
  // add a new client in clients
	std::shared_ptr<Client> add_client(std::string id);
	std::shared_ptr<Client> get_client(std::string id) const;
	double get_wallet(std::string id) const;
	static bool parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value);
  // I need to use get_client/clients in this function, so I cannot use static
	bool add_pending_trx(std::string trx, std::string signature) const;
  // I'm not sure if I should use static or const here
	size_t mine();
private:
  // map each client to its wallet, the wallet is the amount of money the client
  // has
	std::map<std::shared_ptr<Client>, double> clients;
};

void show_wallets(const Server& server);
#endif //SERVER_H
