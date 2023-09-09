/***************************************************************
 * Name:      wx_HexEditorMain.h
 * Purpose:   Defines Application Frame
 * Author:    Lukas Zorn (lukas.zorn@protonmail.com)
 * Created:   2023-05-18
 * Copyright: Lukas Zorn ()
 * License:
 **************************************************************/

#ifndef WX_HEXEDITORMAIN_H
#define WX_HEXEDITORMAIN_H

//(*Headers(wx_HexEditorFrame)
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
//*)

class wx_HexEditorFrame: public wxFrame
{
public:

    wx_HexEditorFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~wx_HexEditorFrame();

    wxString StringToHex(const wxString& input);

    wxString HexToString(const wxString& input);
    bool IsASCII(wxChar c);
    bool IsHexInput(const wxString& input);

private:
    static const long ID_TEXTCTRLASCII;
    static const long ID_TEXTCTRLHEX;
    static const long ID_PANEL1;
      wxString lastValidHex;

    bool isUpdatingAscii;
    bool isUpdatingHex;

    //(*Handlers(wx_HexEditorFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnTextCtrlAsciiText(wxCommandEvent& event);
    void OnTextCtrlHEXText(wxCommandEvent& event);
    //*)

    //(*Identifiers(wx_HexEditorFrame)
    wxPanel* Panel1;
    wxTextCtrl* TextCtrlAscii;
    wxTextCtrl* TextCtrlHEX;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // WX_HEXEDITORMAIN_H

