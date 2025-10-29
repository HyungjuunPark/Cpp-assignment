#include <iostream>
#include <string>

using namespace std;

class YoutubeChannel {
private:
	string ChannelName;
	int subscriberCount;
	static int totalAllSubscribers;
public:
	const static int MAX_NAME_LEN = 30;
	YoutubeChannel(string name, int subs) {
		ChannelName = name;
		subscriberCount = subs;
		totalAllSubscribers += subscriberCount;
	}

	~YoutubeChannel() {
		totalAllSubscribers -= subscriberCount;
	}

	void ChangeSubscribers(int newSubs) {
		totalAllSubscribers -= subscriberCount;
		subscriberCount = newSubs;
		totalAllSubscribers += subscriberCount;
	}

	void ShowInfo() {
		cout << "[" << ChannelName << "] 구독자: " << subscriberCount << '\n';
	}

	static int GetTotalAllSubscribers() {
		return totalAllSubscribers;
	}
};

int YoutubeChannel::totalAllSubscribers = 0;

void CreatTempChannel() {
	cout << "--- 임시 채널 생성 (+1000) ---\n";
	YoutubeChannel temp("임시 채널", 1000);
	temp.ShowInfo();
	cout << "현재 총 구독자: " << YoutubeChannel::GetTotalAllSubscribers() << '\n';
	cout << "--- 임시 채널 소멸 (함수 종료) (-1000)\n";
}

int main() {
	cout << "최대 채널 이름 길이: " << YoutubeChannel::MAX_NAME_LEN << '\n';
	cout << "현재 총 구독자: " << YoutubeChannel::GetTotalAllSubscribers() << '\n';
	cout << "------------------------\n";

	YoutubeChannel ch1("채널A", 100);
	ch1.ShowInfo();
	cout << "현재 총 구독자: " << YoutubeChannel::GetTotalAllSubscribers() << '\n';
	cout << "------------------------\n";

	YoutubeChannel ch2("채널B", 200);
	ch2.ShowInfo();
	cout << "현재 총 구독자: " << YoutubeChannel::GetTotalAllSubscribers() << '\n';
	cout << "------------------------\n";

	CreatTempChannel();

	cout << "------------------------\n";

	cout << "임시 채널 소멸 후 총 구독자: " << YoutubeChannel::GetTotalAllSubscribers() << '\n';
	cout << "------------------------\n";

	cout << "채널A 구독자 변경 (100 -> 150) (+50)\n";
	ch1.ChangeSubscribers(150);
	ch1.ShowInfo();

	cout << "현재 총 구독자: " << YoutubeChannel::GetTotalAllSubscribers() << '\n';

	return 0;
}