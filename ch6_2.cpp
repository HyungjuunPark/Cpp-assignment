#include <iostream>
#include <string>

using namespace std;

class YoutubeChannel {
private:
	string ChannelName;
	int subscriberCount;
	static int totalAllSubscribers;
	int adRevenue;
	mutable int infoAccessCount = 0;
	friend class ChannelAnalytics;
public:
	const static int MAX_NAME_LEN = 30;
	YoutubeChannel(string name, int subs, int ad) {
		ChannelName = name;
		subscriberCount = subs;
		totalAllSubscribers += subscriberCount;
		adRevenue = ad;
	}

	~YoutubeChannel() {
		totalAllSubscribers -= subscriberCount;
	}

	void ChangeSubscribers(int newSubs) {
		totalAllSubscribers -= subscriberCount;
		subscriberCount = newSubs;
		totalAllSubscribers += subscriberCount;
	}

	void ShowInfo() const {
		infoAccessCount++;
		cout << "[" << ChannelName << "] 구독자: " << subscriberCount << " | 광고수익: " << adRevenue
			<< " | (조회수: " << infoAccessCount << ")\n";
	}

	static int GetTotalAllSubscribers() {
		return totalAllSubscribers;
	}
};

class ChannelAnalytics {
public:
	static void GenerateRevenueReport(const YoutubeChannel& ch) {
		cout << "[Analytics] 채널 [" << ch.ChannelName << "]의 광고 수익은 ["
			<< ch.adRevenue << "]원입니다.\n";
	}
};

int YoutubeChannel::totalAllSubscribers = 0;

int main() {
	cout << "--- 일반 객체 테스트 ---\n";
	YoutubeChannel ch1("채널A", 100, 1000);
	ch1.ShowInfo();
	ch1.ShowInfo();

	ChannelAnalytics::GenerateRevenueReport(ch1);

	cout << "\n--- const 객체 테스트 ---\n";
	
	const YoutubeChannel ch_const("고정 채널C", 500, 5000);

	ch_const.ShowInfo();
	ch_const.ShowInfo();

	ChannelAnalytics::GenerateRevenueReport(ch_const);

	return 0;
}

