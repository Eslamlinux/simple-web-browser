#include "browser_app.h"
#include <wx/webview.h>
#include "settings_manager.h"
#include <wx/log.h>
#include <wx/intl.h>
#include <wx/translation.h>
#include "browser_constants.h"

bool BrowserApp::OnInit() {
    // تهيئة دعم اللغة العربية
    InitLocale();
    
    // تهيئة الإعدادات
    InitSettings();
    
    // التحقق من توفر محرك عرض الويب
    if (!CheckWebViewBackend()) {
        return false;
    }
    
    // إنشاء النافذة الرئيسية
    BrowserFrame* frame = new BrowserFrame();
    frame->Show();
    
    return true;
}


