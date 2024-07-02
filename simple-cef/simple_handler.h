#pragma once

#include <list>

#include "include/cef_client.h"

class SimpleHandler : public CefClient
    , public CefDisplayHandler
    , public CefLifeSpanHandler
    , public CefLoadHandler {
public:
    explicit SimpleHandler(bool is_alloy_style);
    ~SimpleHandler() override;

    static SimpleHandler *GetInstance();

    // CefClient
    CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
    CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }

    // CefDisplayHandler
    void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString &title) override;

    // CefLifeSpanHandler
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    bool DoClose(CefRefPtr<CefBrowser> browser) override;
    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    // CefLoadHandler
    void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString &errorText, const CefString &failedUrl) override;

    void ShowMainWindow();

    void CloseAllBrowser(bool force_close);

    bool IsClosing() const { return is_closing_; }

private:
    void PlatformTitleChange(CefRefPtr<CefBrowser> browser
        , const CefString &title);

    void PlatformShowWindow(CefRefPtr<CefBrowser> browser);

private:

    typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
    BrowserList browser_list_;

    bool is_alloy_style_ = false;
    bool is_closing_ = false;

    IMPLEMENT_REFCOUNTING(SimpleHandler);

};
