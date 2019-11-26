#include <wx/wx.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "ifdata.h"
#include "cl.h"

struct HostPanel;

enum
{
    wxID_HostPanel = 10,
    wxID_BottomPanel,
    wxID_MainFrame
};


class MainApp : public wxApp
{
public:
    virtual bool OnInit();
};


// Hauptdialog-Fenster der Andwendung, das erste Fenster das sich öffnet
class MainFrame : public wxFrame
{
public:
    MainFrame(const wxSize& size = wxDefaultSize);
private:
//--------------- Die Daten die von der Appp verwendet werde-------------
    hdata_t *data;

//-------------------Widgets---------------------
    HostPanel *hPanel;
    
    wxPanel *bottomPan;
    wxButton *exitB;


//--------------Events-----------
    void OnExit(wxCommandEvent& event);
};


// Erstes Panel zum Anzeigen der Ausgelesenen Daten zum Platzieren im MainFrame: 
// Informationen zum Host 
struct HostPanel : public wxPanel
{
public:
    HostPanel(wxWindow *parent, const wxPoint& = wxDefaultPosition, const wxSize& = wxDefaultSize,
                 hdata_t* data = NULL); // Wenn kein daten asugelesen werden konnten lässt 

private:
    wxBoxSizer *topsizer;

    wxTextCtrl *nameCtrl;
    wxTextCtrl *kernelCtrl;
    wxTextCtrl *cpuCtrl;
};