#include "RelationshipData.hpp"
using namespace ow;

RelationshipData::RelationshipData(const SystemItem& source, int influence, const SystemItem& target): wxClientData(){
    this->influenceValue = influence;
    this->source = source;
    this->target = target;
}

RelationshipData::SystemItem RelationshipData::CreateItem(int weight, wxString label){
    SystemItem item = {weight, label};
    return item;
}
