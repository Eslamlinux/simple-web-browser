#pragma once

#include <wx/wx.h>

// معرفات الأحداث المخصصة
wxDECLARE_EVENT(wxEVT_BROWSER_TITLE_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_BROWSER_URL_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_BROWSER_BOOKMARK_ADDED, wxCommandEvent);

/**
 * فئة الأحداث المخصصة للمتصفح
 * تستخدم لإرسال أحداث مخصصة بين مكونات المتصفح
 */
class BrowserEvent : public wxCommandEvent {
public:
    /**
     * المنشئ
     * @param eventType نوع الحدث
     * @param id معرف الحدث
     */
    BrowserEvent(wxEventType eventType = wxEVT_NULL, int id = 0)
        : wxCommandEvent(eventType, id) {}
    
    /**
     * نسخ الحدث
     * @return نسخة من الحدث
     */
    virtual wxEvent* Clone() const override {
        return new BrowserEvent(*this);
    }
};
