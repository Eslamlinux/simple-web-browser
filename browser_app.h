#pragma once

#include <wx/wx.h>
#include <wx/intl.h>
#include <memory>
#include "browser_frame.h"

/**
 * تطبيق المتصفح الرئيسي
 * نقطة الدخول الرئيسية للمتصفح
 */
class BrowserApp : public wxApp {
public:
    /**
     * تهيئة التطبيق
     * @return true إذا تمت التهيئة بنجاح، false إذا فشلت التهيئة
     */
    virtual bool OnInit() override;
    
private:
    /**
     * تهيئة دعم اللغة العربية
     */
    void InitLocale();
    
    /**
     * التحقق من توفر محرك عرض الويب
     * @return true إذا كان محرك عرض الويب متوفراً، false إذا لم يكن متوفراً
     */
    bool CheckWebViewBackend();
    
    /**
     * تهيئة الإعدادات
     */
    void InitSettings();
    
    /**
     * كائن اللغة
     */
    std::unique_ptr<wxLocale> m_locale;
};
