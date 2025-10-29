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
		cout << "[" << ChannelName << "] ������: " << subscriberCount << " | �������: " << adRevenue
			<< " | (��ȸ��: " << infoAccessCount << ")\n";
	}

	static int GetTotalAllSubscribers() {
		return totalAllSubscribers;
	}
};

class ChannelAnalytics {
public:
	static void GenerateRevenueReport(const YoutubeChannel& ch) {
		cout << "[Analytics] ä�� [" << ch.ChannelName << "]�� ���� ������ ["
			<< ch.adRevenue << "]���Դϴ�.\n";
	}
};

int YoutubeChannel::totalAllSubscribers = 0;


int main() {
	cout << "--- �Ϲ� ��ü �׽�Ʈ ---\n";
	YoutubeChannel ch1("ä��A", 100, 1000);
	ch1.ShowInfo();
	ch1.ShowInfo();

	ChannelAnalytics::GenerateRevenueReport(ch1);

	cout << "\n--- const ��ü �׽�Ʈ ---\n";
	
	const YoutubeChannel ch_const("���� ä��C", 500, 5000);

	ch_const.ShowInfo();
	ch_const.ShowInfo();

	ChannelAnalytics::GenerateRevenueReport(ch_const);

	return 0;
}
