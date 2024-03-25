#include "OpenWingsApp.hpp"
#include "MainFrame.hpp"

using namespace ow;
bool OWApp::OnInit(){
    // Main application window
    MainFrame *pFrame = new MainFrame();
    pFrame->Show(true);
    return true;
}
