#pragma once
#include <string>
#include <SFML/Network.hpp>
#include "..\JSONparser\JSONparser.h"


class Leaderboard {
	sf::Http http;
	sf::Http::Request getRequest;
	sf::Http::Request postRequest;
	JSONparser parser;

public:
	Leaderboard() {
		http.setHost("http://myexperiments.altervista.org/");
		getRequest = sf::Http::Request("ledearboard/getLeaderboard.php", sf::Http::Request::Get);
		postRequest = sf::Http::Request("ledearboard/addScore.php", sf::Http::Request::Post);
	}
	~Leaderboard() {}

	struct result {
		std::string name = "";
		std::string score = "";
		bool cheated = false;
	};

	std::vector<result> getLeadeboard() {
		std::vector<result> r;
		
		sf::Http::Response response = http.sendRequest(getRequest);
		std::string responsejson = response.getBody();
		parser.reset();
		parser.setJSON(&responsejson);
		parser.readJSON();

		for (JSONparser::datatypes row : parser.doc["leaderboard"].arr) {
			// parse time and put colons
			// eg: 31465 -> 3:14:65
			int count = 0;
			std::string score = row.obj["score"].str;
			std::string finalscore = "";
			for (size_t k = score.size(); k > 0; k--) {
				count++;
				finalscore = score[k - 1] + finalscore;
				if (count % 2 == 0 && count != 0 && count != score.size()) {
					finalscore = ":" + finalscore;
				}
			}

			bool cheated = false;
			if (row.obj["cheated"].str != "0") cheated = true;

			r.push_back({ row.obj["name"].str, finalscore, cheated });
		}
		
		return r;
	}

	void sendScore(std::string username, std::string score, bool cheated) {
		// max username size to not mess up the page is 7 characters
		username.resize(7);
		
		// setup the request and send to the database
		postRequest.setBody("name=" + username + "&score=" + score + "&cheated=" + std::to_string(cheated));
		std::cout << "BODY: " << "name=" + username + "&score=" + score + "&cheated=" + std::to_string(cheated) << "\n";

		sf::Http::Response rr = http.sendRequest(postRequest);
		std::cout << rr.getBody() << "\n";
	}
};