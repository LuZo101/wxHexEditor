/***************************************************************
 * Name:      wx_HexEditorApp.h
 * Purpose:   Defines Application Class
 * Author:    Lukas Zorn (lukas.zorn@protonmail.com)
 * Created:   2023-05-18
 * Copyright: Lukas Zorn ()
 * License:
 **************************************************************/

#ifndef WX_HEXEDITORAPP_H
#define WX_HEXEDITORAPP_H

#include <wx/app.h>

class wx_HexEditorApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // WX_HEXEDITORAPP_H
