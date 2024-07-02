#pragma once

#include "include/cef_app.h"

class SimpleApp : public CefApp, public CefBrowserProcessHandler {
public:
    SimpleApp();

    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override
    {
        return this;
    }

    virtual void OnContextInitialized() override;

    CefRefPtr<CefClient> GetDefaultClient() override;

private:
    IMPLEMENT_REFCOUNTING(SimpleApp);

};

