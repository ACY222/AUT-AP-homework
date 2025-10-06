
size_t Server::mine() {
	std::string mempool{};
	for (const auto& trx : pending_trxs) {
		mempool += trx;
	}
	size_t nonce = 0;
	bool flag = false;  //not mined
	while (!flag) {
		for (auto& c_w : clients) {
			nonce = c_w.first->generate_nonce();
			if (crypto::sha256(mempool + std::to_string(nonce)).substr(0, 10).find("000") != std::string::npos) {   //mined
                flag = true;
				c_w.second += 6.25;
				for (const auto& trx : pending_trxs) {
					std::string sender, receiver;
					double value;
					Server::parse_trx(trx, sender, receiver, value);
					clients[get_client(sender)] -= value;
					clients[get_client(receiver)] += value;
				}
				pending_trxs.clear();
                return nonce;
			}
		}
	}
	return nonce;
}
