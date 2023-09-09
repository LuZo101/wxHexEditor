/***************************************************************
 * Name:      wx_HexEditorApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Lukas Zorn (lukas.zorn@protonmail.com)
 * Created:   2023-05-18
 * Copyright: Lukas Zorn ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "wx_HexEditorApp.h"

//(*AppHeaders
#include "wx_HexEditorMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wx_HexEditorApp);

bool wx_HexEditorApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wx_HexEditorFrame* Frame = new wx_HexEditorFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
