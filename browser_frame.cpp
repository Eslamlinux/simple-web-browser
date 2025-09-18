#include "browser_frame.h"
#include <wx/artprov.h>
#include "settings_manager.h"
#include "session_manager.h"
#include <wx/log.h>
#include "browser_event.h"

wxBEGIN_EVENT_TABLE(BrowserFrame, wxFrame)
    EVT_MENU(BrowserConstants::ID_NEW_TAB, BrowserFrame::OnNewTab)
    EVT_MENU(BrowserConstants::ID_CLOSE_TAB, BrowserFrame::OnCloseTab)
    EVT_MENU(BrowserConstants::ID_BOOKMARKS, BrowserFrame::OnBookmarks)
    EVT_MENU(BrowserConstants::ID_PRIVATE_BROWSING, BrowserFrame::OnTogglePrivateBrowsing)
    EVT_MENU(BrowserConstants::ID_READER_MODE, BrowserFrame::OnToggleReaderMode)
    EVT_MENU(BrowserConstants::ID_SETTINGS, BrowserFrame::OnSettings)
    EVT_MENU(wxID_EXIT, BrowserFrame::OnExit)
    EVT_CLOSE(BrowserFrame::OnClose)
wxEND_EVENT_TABLE()

