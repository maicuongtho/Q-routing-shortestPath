/*
 * Qtable.cpp
 *
 *  Created on: Sep 15, 2023
 *      Author: mctho
 */
#include <fstream>
#include "QTable.h"


void QTable::AddNewEntry(const L3Address& destination, const L3Address& nextHop,  double qValue){
    Destination_Nexthop_Pair p = std::make_pair(destination, nextHop);
    qTable[p] = qValue;
}
bool QTable::ExistedEntry(const L3Address& destination,const L3Address& nextHop ) {
    Destination_Nexthop_Pair p = std::make_pair(destination, nextHop);
    auto it =  qTable.find(p);
    return (it == qTable.end()) ? false : true;
}
void QTable::UpdateQnew(const L3Address& nextHop,const L3Address& destination, double Qvalue){
    if (! ExistedEntry(destination,nextHop)) AddNewEntry(destination,nextHop, Qvalue);
    else
    {
    Destination_Nexthop_Pair p = std::make_pair(destination, nextHop);
    std::map<Destination_Nexthop_Pair, double >::iterator i =  qTable.find(p);
    i->second =Qvalue;
    }
}

double QTable::getOldMinQ(const L3Address& nextHop, const L3Address& destination) {
    Destination_Nexthop_Pair p = std::make_pair(destination, nextHop);
    return qTable.find(p)->second;
}

double QTable::getMinQ(const L3Address& destination) {
    double minValue=600;
    for (auto elem : qTable) {
        if (elem.first.first == destination)
          if ( elem.second <  minValue)
              minValue =elem.second;
       }
    if (minValue==100) minValue=0;
    return minValue;
}


void QTable::Delete(const L3Address& nextHop){
    for (auto it = qTable.begin(); it != qTable.end(); ) {
            if (it->first.second == nextHop) {
                it = qTable.erase(it);  // Xóa phần tử và cập nhật iterator
            } else {
                ++it;
            }
   }
}

L3Address QTable::getHopMinQ( const L3Address& sender, const L3Address& destination){
    L3Address hopAction;
    double minValue=70000000;
    for (auto elem : qTable) {
       if ((elem.first.first== destination) &&  (elem.first.second != sender)){
           if( ( elem.second <  minValue) && ( elem.second !=0))  { //=0 nghĩa là chưa có thông tin
                     minValue =elem.second;
                     hopAction=elem.first.second;
                 }
       }
    }
   return hopAction;
}


L3Address QTable::getHopRandom(const L3Address& sender, const L3Address& destination){
    // Lọc các lựa chọn hợp lệ
        std::vector<std::pair<L3Address, double>> validActions;
        for (const auto& elem : qTable) {
            if (elem.first.first == destination && elem.first.second != sender) {
                validActions.emplace_back(elem.first.second, elem.second);
            }
        }

        int size = validActions.size();
        if (size == 0) {
            return L3Address();  // Trả về địa chỉ rỗng nếu không có lựa chọn hợp lệ
        }

        // Khởi tạo bộ sinh số ngẫu nhiên
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, size - 1);

        // Chọn ngẫu nhiên một hành động từ các hành động hợp lệ
        int randomIndex = dis(gen);
        L3Address hopAction = validActions[randomIndex].first;

        return hopAction;
}
std::ostream& operator<<(std::ostream& o, const QTable& t)
{
    // o << "===========Bảng định tuyến QTable======="<<endl;
    o << "| Destination   |  Next hop   |  Q_value"<<endl;
    for (auto elem : t.qTable) {
        o <<"| "<< elem.first.first << "  | " << elem.first.second << " |  " << elem.second<<endl;
    }
    return o;
}
