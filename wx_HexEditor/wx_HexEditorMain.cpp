/***************************************************************
 * Name:      wx_HexEditorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Lukas Zorn (lukas.zorn@protonmail.com)
 * Created:   2023-05-18
 * Copyright: Lukas Zorn ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "wx_HexEditorMain.h"
#include <wx/msgdlg.h>
#include <stdexcept>
#include <wx/tokenzr.h>
//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(wx_HexEditorFrame)
const long wx_HexEditorFrame::ID_TEXTCTRLASCII = wxNewId();
const long wx_HexEditorFrame::ID_TEXTCTRLHEX = wxNewId();
const long wx_HexEditorFrame::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wx_HexEditorFrame,wxFrame)
    //(*EventTable(wx_HexEditorFrame)
    //*)
END_EVENT_TABLE()

wx_HexEditorFrame::wx_HexEditorFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(wx_HexEditorFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    TextCtrlAscii = new wxTextCtrl(Panel1, ID_TEXTCTRLASCII, _("Text content"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRLASCII"));
    TextCtrlAscii->SetMinSize(wxDLG_UNIT(Panel1,wxSize(400,100)));
    BoxSizer2->Add(TextCtrlAscii, 0, wxALL, 5);
    TextCtrlHEX = new wxTextCtrl(Panel1, ID_TEXTCTRLHEX, _("HEX representation"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRLHEX"));
    TextCtrlHEX->SetMinSize(wxDLG_UNIT(Panel1,wxSize(400,100)));
    BoxSizer2->Add(TextCtrlHEX, 0, wxALL, 5);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 0, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_TEXTCTRLASCII,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&wx_HexEditorFrame::OnTextCtrlAsciiText);
    Connect(ID_TEXTCTRLHEX,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&wx_HexEditorFrame::OnTextCtrlHEXText);
    //*)

    isUpdatingAscii = false;
    isUpdatingHex = false;
    wxString lastValidHex;

}

wx_HexEditorFrame::~wx_HexEditorFrame()
{
    //(*Destroy(wx_HexEditorFrame)
    //*)
}


void wx_HexEditorFrame::OnTextCtrlAsciiText(wxCommandEvent& event)
{
    if (!isUpdatingHex)
    {
        isUpdatingAscii = true;
        wxString asciiText = TextCtrlAscii->GetValue();
        TextCtrlHEX->SetValue(StringToHex(asciiText));


    }
    isUpdatingAscii = false;
    event.Skip();
}

void wx_HexEditorFrame::OnTextCtrlHEXText(wxCommandEvent& event)
{
    if (!isUpdatingAscii)
    {
        isUpdatingHex = true;
        wxString hexText = TextCtrlHEX->GetValue();
        if (IsHexInput(hexText))
        {
            TextCtrlAscii->SetValue(HexToString(hexText));
            lastValidHex = hexText; // Speichern der letzten gültigen HEX-Zahl
        }
        else
        {
            wxMessageBox("Invalid HEX!", "Error", wxOK | wxICON_ERROR);
            TextCtrlHEX->SetValue(lastValidHex); // Anzeigen der letzten gültigen HEX-Zahl
        }
    }
    isUpdatingHex = false;
    event.Skip();
}


wxString wx_HexEditorFrame::StringToHex(const wxString& input)
{
    wxString hex;
    wxString lastValidHex;
    bool hasInvalidASCII = false;

    for (size_t i = 0; i < input.length(); i++)
    {
        wxChar c = input[i];
        if (IsASCII(c))
        {
            hex += wxString::Format("%02X ", static_cast<unsigned int>(c));
        }
        else
        {
            hasInvalidASCII = true;
            break;
        }
        lastValidHex = hex;
    }

    if (hasInvalidASCII)
    {
        wxMessageBox("Invalid ASCII!", "Error", wxOK | wxICON_ERROR);
        TextCtrlAscii->SetValue(lastValidHex);
    }

    return hex;
}



wxString wx_HexEditorFrame::HexToString(const wxString& input)
{
    wxString text;
    wxString cleanedInput = input;
    cleanedInput.Replace(" ", ""); // Leerzeichen entfernen

    size_t inputLen = cleanedInput.length();
    size_t numPairs = inputLen / 2;

    for (size_t i = 0; i < numPairs; i++)
    {
        wxString hex = cleanedInput.Mid(i * 2, 2);
        long value;
        if (hex.ToLong(&value, 16))
        {
            text += static_cast<wxChar>(value);
        }
    }

    return text;
}


bool wx_HexEditorFrame::IsASCII(wxChar c)
{
    return c < 128;
}
bool wx_HexEditorFrame::IsHexInput(const wxString& input)
{
    wxString hexChars = "0123456789ABCDEFabcdef ";
    for (size_t i = 0; i < input.length(); i++)
    {
        wxChar c = input[i];
        if (hexChars.Find(c) == wxString::npos)
        {
            return false;
        }
    }
    return true;
}
