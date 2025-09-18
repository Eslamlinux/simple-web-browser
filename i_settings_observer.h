
#include "i_observer.h"

/**
 * واجهة مراقب الإعدادات
 * تستخدم للإشعار بتغييرات الإعدادات
 */
class ISettingsObserver : public IObserver {
public:
    /**
     * يتم استدعاؤها عند تغيير الإعدادات
     */
    virtual void OnSettingsChanged() = 0;
};
