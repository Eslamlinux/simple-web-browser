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

void BrowserApp::InitLocale() {
    // تهيئة دعم اللغة العربية
    wxLocale* locale = new wxLocale(wxLANGUAGE_ARABIC);
    
    // التأكد من أن wxWidgets يستخدم ترميز UTF-8
    wxConvCurrent = &wxConvUTF8;
    
    // إضافة مسار الترجمة إذا كان لديك ملفات ترجمة
    locale->AddCatalogLookupPathPrefix("./locale");
    
    // تعيين اللغة الافتراضية
    locale->AddCatalog("browser");
    
    // حفظ الإشارة إلى الكائن locale
    m_locale.reset(locale);
}

bool BrowserApp::CheckWebViewBackend() {
    // التحقق من توفر محرك عرض الويب
    if (!wxWebView::IsBackendAvailable(wxWebViewBackendDefault)) {
        wxMessageBox("لم يتم العثور على محرك عرض ويب مناسب", "خطأ", wxOK | wxICON_ERROR);
        return false;
    }
    
    return true;
}

void BrowserApp::InitSettings() {
    // تهيئة مدير الإعدادات
    SettingsManager::GetInstance().LoadSettings();
    
    // تهيئة سجل الأخطاء
    wxLog::SetActiveTarget(new wxLogStderr());
}

wxIMPLEMENT_APP(BrowserApp);
