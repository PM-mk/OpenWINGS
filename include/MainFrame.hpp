#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include "tinyxml2.h"
#include "AboutFrame.hpp"
#include "OpenWingsApp.hpp"
#include "ControlPanel.hpp"
#include "helper.hpp"

namespace ow{
    class MainFrame : public wxFrame{
        public:
            MainFrame();
            ControlPanel* pControlPanel;
        protected:
        private:
            std::unordered_map<std::string, wxPanel*> panelMap;
            tinyxml2::XMLDocument projectFile;
            void SetPanel(std::string key);
            void EnableSaving(bool enable);
            bool IsFileLoaded();
        // handlers:
            void OnNewFile(wxCommandEvent& event);
            void OnOpen(wxCommandEvent& event);
            void OnSave(wxCommandEvent& event);
            void OnSaveAs(wxCommandEvent& event);
            void OnQuit(wxCommandEvent& event);
            void OnAbout(wxCommandEvent& event);
    };
} // namespace ow