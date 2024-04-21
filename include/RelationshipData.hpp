#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP

namespace ow{
    class RelationshipData : public wxClientData{
        struct SystemItem{
            int weight = 0;
            wxString label = wxEmptyString;
        };
        public:
            RelationshipData(const SystemItem& source, int influence, const SystemItem& target);
            int influenceValue;
            SystemItem source;
            SystemItem target;
            static SystemItem CreateItem(int weight, wxString label);
        protected:
        private:
    };
    inline bool operator==(const RelationshipData& left, const RelationshipData& right){
        return left.source.label == right.source.label
            && left.target.label == right.target.label
            && left.influenceValue == right.influenceValue;
        };
} // namespace ow