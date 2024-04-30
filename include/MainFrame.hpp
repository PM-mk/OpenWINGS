#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include "wx/xml/xml.h"
#include "AboutFrame.hpp"
#include "OpenWingsApp.hpp"
#include "ControlPanel.hpp"
#include "helper.hpp"

namespace ow{
    class MainFrame : public wxFrame{
        public:
            MainFrame();
        protected:
        private:
            ControlPanel* pControlPanel;
            wxPanel* pStartPanel;
            wxXmlDocument* pProjectFile;
            void SetPanel(wxPanel* pPanel);
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