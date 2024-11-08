#include <map>
#include <vector>
#include <random>
#include "inet/networklayer/common/L3Address.h"
#include "inet/common/geometry/common/Coord.h"
using namespace inet;
class QTable {
  private:
        typedef std::pair<L3Address,L3Address > Destination_Nexthop_Pair;   // đến nút đích - thì tốn value time giây
        std::map<Destination_Nexthop_Pair, double> qTable;   // Bảng định tuyến: dest -nextHop -- Qvalue
  public:
    QTable() {};
    L3Address getHopMinQ(const L3Address& sender, const L3Address& destination);
    L3Address getHopRandom(const L3Address& sender, const L3Address& destination);
    void UpdateQnew(const L3Address& nextHop,const L3Address& destination, double Qvalue);
    void AddNewEntry(const L3Address& destination,const L3Address& nextHop, double qValue);
    bool ExistedEntry(const L3Address& destination, const L3Address& nextHop);
    double getOldMinQ(const L3Address& nextHop, const L3Address& destination);
    double getMinQ(const L3Address& destination);
    void Delete(const L3Address& nextHop);
    friend std::ostream& operator<<(std::ostream& o, const QTable& t);
};
