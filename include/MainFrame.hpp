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
#include "ow_background_gray.xpm"

namespace ow{
    class MainFrame : public wxFrame{
        public:
            MainFrame();
        protected:
        private:
            ControlPanel* pControlPanel;
            wxPanel* pStartPanel;
            wxXmlDocument* pProjectFile;
            wxString fileName = wxEmptyString;
            void setPanel(wxPanel* pPanel);
            void enableSaving(bool enable);
            void loadData();
            void dumpData();
            bool isFileLoaded();
        // handlers:
            void OnNewFile(wxCommandEvent& event);
            void OnOpen(wxCommandEvent& event);
            void OnSave(wxCommandEvent& event);
            void OnSaveAs(wxCommandEvent& event);
            void OnQuit(wxCommandEvent& event);
            void OnAbout(wxCommandEvent& event);
            void OnEditScales(wxCommandEvent& event);
    };
} // namespace ow