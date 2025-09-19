#pragma once

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/aui/aui.h>
#include <vector>
#include <memory>
#include "browser_tab.h"
#include "bookmark_manager.h"
#include "i_browser_tab_observer.h"
#include "i_bookmark_observer.h"
#include "i_settings_observer.h"
#include "browser_constants.h"

/**
 * النافذة الرئيسية للمتصفح
 * تمثل النافذة الرئيسية للمتصفح وتتعامل مع علامات التبويب والقوائم
 */
class BrowserFrame : public wxFrame, public IBrowserTabObserver, public IBookmarkObserver, public ISettingsObserver {
public:
    /**
     * المنشئ
     */
    BrowserFrame();
    

};
