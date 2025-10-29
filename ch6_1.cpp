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
		cout << "[" << ChannelName << "] ������: " << subscriberCount << '\n';
	}

	static int GetTotalAllSubscribers() {
		return totalAllSubscribers;
	}
};

int YoutubeChannel::totalAllSubscribers = 0;

void CreatTempChannel() {
	cout << "--- �ӽ� ä�� ���� (+1000) ---\n";
	YoutubeChannel temp("�ӽ� ä��", 1000);
	temp.ShowInfo();
	cout << "���� �� ������: " << YoutubeChannel::GetTotalAllSubscribers() << '\n';
	cout << "--- �ӽ� ä�� �Ҹ� (�Լ� ����) (-1000)\n";
}

int main() {
	cout << "�ִ� ä�� �̸� ����: " << YoutubeChannel::MAX_NAME_LEN << '\n';
	cout << "���� �� ������: " << YoutubeChannel::GetTotalAllSubscribers() << '\n';
	cout << "------------------------\n";

	YoutubeChannel ch1("ä��A", 100);
	ch1.ShowInfo();
	cout << "���� �� ������: " << YoutubeChannel::GetTotalAllSubscribers() << '\n';
	cout << "------------------------\n";

	YoutubeChannel ch2("ä��B", 200);
	ch2.ShowInfo();
	cout << "���� �� ������: " << YoutubeChannel::GetTotalAllSubscribers() << '\n';
	cout << "------------------------\n";

	CreatTempChannel();

	cout << "------------------------\n";

	cout << "�ӽ� ä�� �Ҹ� �� �� ������: " << YoutubeChannel::GetTotalAllSubscribers() << '\n';
	cout << "------------------------\n";

	cout << "ä��A ������ ���� (100 -> 150) (+50)\n";
	ch1.ChangeSubscribers(150);
	ch1.ShowInfo();

	cout << "���� �� ������: " << YoutubeChannel::GetTotalAllSubscribers() << '\n';

	return 0;
}