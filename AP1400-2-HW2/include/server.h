#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <map>
#include <memory>

class Client;

// global variable should be defined in the source file
// define this outside the Server class and save the pending transactions in it
extern std::vector<std::string> pending_trxs;

class Server
{
public:
	Server();
	std::shared_ptr<Client> add_client(std::string id);
	std::shared_ptr<Client> get_client(std::string id) const;
	double get_wallet(std::string id) const;
  // trx: sender-receiver-value
  // if the string is not standard, throw a runtime error
	static bool parse_trx(const std::string& trx, std::string& sender, std::string& receiver, double& value);
	bool add_pending_trx(std::string trx, std::string signature) const;
	size_t mine();
private:
	std::map<std::shared_ptr<Client>, double> clients;
};

void show_wallets(const Server& server);

#endif //SERVER_H
