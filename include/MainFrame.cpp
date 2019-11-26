#include "MainFrame.h"


bool MainApp::OnInit()
{

//----- Initalisieren der wxApp------------------

    MainFrame *mainWin = new MainFrame();
    mainWin->Show(true);
    return true;
}


MainFrame::MainFrame(const wxSize& size):
    wxFrame(NULL, wxID_MainFrame, "BBWInv-Client", wxDefaultPosition, wxSize(300, 500))
{
//----------- Auslesen der Host und Interface Informationen------------

    this->data = hdata_init();

//-----------Instaliseren des Fenters
    this->hPanel = new HostPanel(this, wxPoint(10, 10), wxSize(280, 190), this->data);

    this->bottomPan = new wxPanel(this, wxID_BottomPanel, wxPoint(10, 450), wxSize(280, 40));
    this->exitB = new wxButton(bottomPan, wxID_EXIT, wxT("Beenden"), wxDefaultPosition, wxSize(100, 40));
    this->exitB->Show();

    this->Bind(wxEVT_BUTTON, &MainFrame::OnExit, this, wxID_EXIT);
}


void MainFrame::OnExit(wxCommandEvent& event)
{
    hdata_del(data);
    this->Close(true);
}


HostPanel::HostPanel(wxWindow *parent, const wxPoint& pos, 
                        const wxSize& size , hdata_t *data) :
    wxPanel(parent, wxID_ANY, pos, size)
{
    this->topsizer = new wxBoxSizer( wxVERTICAL);

    this->nameCtrl = new wxTextCtrl(this, wxID_ANY, wxString(data->name));
    topsizer->Add( this->nameCtrl,
                    1,
                    wxEXPAND |
                    wxALL,
                    10);

    this->kernelCtrl = new wxTextCtrl(this, wxID_ANY);
    this->cpuCtrl = new wxTextCtrl(this, wxID_ANY);

    this->SetSizerAndFit(topsizer);
}
