// string data를 입력받아 00:00-23:59 사이의 주차요금 정리
#include <map>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct parkingInfo{
	bool isParked = false;	//주차 여부
	int inTime;				//입차 시간
	int totalTime;			//주차 시간
};

int hhmmToInt(const string hhmm) {
	return stoi(hhmm.substr(0, 2)) * 60 + stoi(hhmm.substr(3, 2));
}

int calFee(vector<int> fees, int time) {
	int fee = fees[1];
	int overTime = time - fees[0];
	if (overTime < 0)
		return fee;
	fee += (overTime / fees[2] * fees[3]);
	return overTime % fees[2] == 0 ? fee : fee + fees[3];
}

vector<int> solution(vector<int> fees, vector<string> records) {
	vector<int> answer;
	map<string, parkingInfo> logs;
 
	for(const string& record : records){
		stringstream ss(record);
		string tmp, id, status;
		ss >> tmp >> id >> status;
		int		time = hhmmToInt(tmp);
		
		if (status == "IN") {
			logs[id].isParked = true;
			logs[id].inTime = time;
		}
		else if (status == "OUT") {
			logs[id].isParked = false;
			logs[id].totalTime += (time - logs[id].inTime);
		}
	}
	
	for (auto& log : logs) {
		if (log.second.isParked)
			log.second.totalTime += hhmmToInt("23:59") - log.second.inTime;

		int fee = calFee(fees, log.second.totalTime);
		answer.push_back(fee);
	}

	return answer;
}

int main() {
	vector<string> records = { "05:34 5961 IN", "06:00 0000 IN" };
	vector<int> fees = {180,5000,10,600};
	solution(fees, records);
	return 0;
}
