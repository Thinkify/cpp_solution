#include<bits/stdc++.h>

using namespace std;

class Seller {

private :
	string sellerName;

public :
	Seller() {
		sellerName = "";
	}

	Seller(string name) {
		this->sellerName = name;
	}

	string getSellerName() {
		return this->sellerName;
	}
};

class Buyer {

private :
	string buyerName;
	map<string, vector<int>> bids;

public :
	Buyer() {
		buyerName = "";
	}

	Buyer(string name) {
		this->buyerName = name;
	}

	void addNewBid(string auctionId, int amount) {
		bids[auctionId].push_back(amount);
	}

	// getters setters
	string getBuyerName() {
		return this->buyerName;
	}

	vector<int> getBids(string auctionId) {
		return this->bids[auctionId];
	}
};

class Auction {

private :

	string auctionId;
	string sellerName;
	int lowestBidAmount;
	int highestBidAmount;
	vector<Buyer> buyers;
	map<int, int> allBids;

public :

	Auction() {

	}

	Auction(string auctionId,
	        string sellerName,
	        int lowestBidAmount,
	        int highestBidAmount) {

		this->auctionId = auctionId;
		this->sellerName = sellerName;
		this->lowestBidAmount = lowestBidAmount;
		this->highestBidAmount = highestBidAmount;
	}

	void addBid(Buyer buyer, int amount) {
		buyer.addNewBid(auctionId, amount);
		this->buyers.emplace_back(buyer);
		this->allBids[amount]++;
	}

	// getters and setters

	string getAuctionId() {
		return this->auctionId;
	}

	map<int, int> getAllBids() {
		return this->allBids;
	}

	vector<Buyer>  getAllBuyers() {
		return this->buyers;
	}

	string getWinner() {

		int winningAmount = -1;
		Buyer winner;

		for (auto bid : getAllBids()) {
			// cout << bid.first << endl;
			if (bid.second == 1) {
				winningAmount = max(winningAmount, bid.first);
			}
		}

		for (Buyer buyer : buyers) {
			// cout << buyer.getBuyerName() << endl;
			vector<int> bidsOfBuyer = buyer.getBids(this->auctionId);

			for (int value : bidsOfBuyer) {
				if (value == winningAmount) {
					winner = buyer;
					break;
				}
			}
		}

		if (winningAmount == -1) {
			return "No Winner...";
		} else {
			return winner.getBuyerName();
		}
	}

	bool isAmountValid(int amount) {
		if (amount >= lowestBidAmount && amount <= highestBidAmount) {
			return true;
		}
		return false;
	}

	int getLowest() {
		return this->lowestBidAmount;
	}
};

class Handler {

private :

	vector<Buyer> buyers;
	vector<Seller> sellers;
	vector<Auction> auctions;

	bool isAuctionPresent(string auctionId) {
		for (Auction &auction : auctions) {
			if (auction.getAuctionId() == auctionId) {
				return true;
			}
		}
		return false;
	}

	Auction getAuctionFromId(string auctionId) {
		Auction currentAuction;
		for (Auction &auction : this->auctions) {
			cout << auction.getAuctionId() << endl;
			cout << auction.getAllBids().size() << endl;
			if (auction.getAuctionId() == auctionId) {
				return auction;
			}
		}
		return currentAuction;
	}

	bool isSellerPresent(string sellerName) {
		for (Seller &seller : sellers) {
			if (seller.getSellerName() == sellerName) {
				return true;
			}
		}
		return false;
	}

	bool isBuyerPresent(string buyerName) {
		for (Buyer &buyer : buyers) {
			if (buyer.getBuyerName() == buyerName) {
				return true;
			}
		}
		return false;
	}

	Buyer getBuyerFromName(string buyerName) {
		Buyer currentBuyer;
		for (Buyer &buyer : buyers) {
			if (buyer.getBuyerName() == buyerName) {
				return buyer;
			}
		}
		return currentBuyer;
	}

public :

	Handler() {

	}

	void addBuyer(string buyerName) {

		if (!isBuyerPresent(buyerName)) {

			Buyer buyer(buyerName);
			buyers.push_back(buyer);
		}
	}

	void addSeller(string sellerName) {

		if (!isSellerPresent(sellerName)) {

			Seller seller(sellerName);
			sellers.push_back(seller);
		}
	}

	void createAuction(string auctionId,
	                   string sellerName,
	                   int lowestBidAmount,
	                   int highestBidAmount) {

		if (isSellerPresent(sellerName)
		        && (lowestBidAmount <= highestBidAmount)
		        && (lowestBidAmount >= 0)) {

			Auction auction(auctionId,
			                sellerName,
			                lowestBidAmount,
			                highestBidAmount);

			this->auctions.push_back(auction);

		}
	}

	void createBid(string buyerName, string auctionId, int amount) {

		if (isBuyerPresent(buyerName) && isAuctionPresent(auctionId)) {

			Buyer currentBuyer = getBuyerFromName(buyerName);
			Auction currentAuction = getAuctionFromId(auctionId);

			if (currentAuction.isAmountValid(amount)) {
				currentAuction.addBid(currentBuyer, amount);
			}
		}
	}

	string closeAuction(string auctionId) {

		if (isAuctionPresent(auctionId)) {
			Auction currentAuction = getAuctionFromId(auctionId);
			cout << currentAuction.getLowest();
			return currentAuction.getWinner();
		}

		return "No auction Present";
	}
};

int main() {

	// Handler handler;

	// handler.addBuyer("b1");
	// handler.addBuyer("b2");
	// handler.addBuyer("b3");

	// handler.addSeller("s1");
	// handler.addSeller("s2");

	// handler.createAuction("a1", "s1", 100, 1000);



	// handler.createBid("b1", "a1", 200);

	// cout << (handler.closeAuction("a1"));

	Auction auction("a1", "s1", 100, 1000);

	Buyer buyer("b1");
	Buyer buyer2("b2");
	// auction.addBid(buyer2, 800);
	// auction.addBid(buyer2, 200);

	auction.addBid(buyer, 800);
	auction.addBid(buyer2, 200);
	auction.addBid(buyer2, 800);

	cout << auction.getWinner();
}
