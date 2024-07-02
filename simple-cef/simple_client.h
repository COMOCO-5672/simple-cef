#pragma once

#include "include/cef_client.h"
#include <list>

class SimpleClient : public CefClient
    , public CefDisplayHandler
    , public CefLifeSpanHandler
    , public CefLoadHandler {
public:
    explicit SimpleClient(bool use_views);
    ~SimpleClient();

    static SimpleClient *GetInstance();

    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override
    {
        return this;
    }

    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override
    {
        return this;
    }

    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override
    {
        return this;
    }

    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override;

    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;

    virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;

    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) override;

    void CloseAllBrowsers(bool force_close);

    bool IsClosing() const
    {
        return is_closing_;
    }

private:

    void PlatformTitleChange(CefRefPtr<CefBrowser> browser
        , const CefString &title);

    const bool use_views_;

    typedef std::list<CefRefPtr<CefBrowser>> BrowserList;

    BrowserList browser_list_;

    bool is_closing_;
    IMPLEMENT_REFCOUNTING(SimpleClient);

};
