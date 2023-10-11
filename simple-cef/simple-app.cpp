#include "simple-app.h"

#include <include/views/cef_window.h>

#include "SimpleBrowserViewDelegate.hpp"
#include "simple_client.h"

SimpleApp::SimpleApp()
{
}

void SimpleApp::OnContextInitialized()
{
    //CEF_REQUIRE_UI_THREAD();

    CefRefPtr<CefCommandLine> command_line =
        CefCommandLine::GetGlobalCommandLine();

    const bool enable_chrome_runtime =
        command_line->HasSwitch("enable-chrome-runtime");

#if defined(OS_WIN) || defined(OS_LINUX)
    // Create the browser using the Views framework if "--use-views" is specified
    // via the command-line. Otherwise, create the browser using the native
    // platform framework. The Views framework is currently only supported on
    // Windows and Linux.
    const bool use_views = command_line->HasSwitch("use-views");
#else
    const bool use_views = false;
#endif

    // SimpleHandler implements browser-level callbacks.
    CefRefPtr<SimpleClient> handler(new SimpleClient(use_views));

    // Specify CEF browser settings here.
    CefBrowserSettings browser_settings;

    std::string url;

    // Check if a "--url=" value was provided via the command-line. If so, use
    // that instead of the default URL.
    url = command_line->GetSwitchValue("url");
    if (url.empty())
        url = "https://www.cnblogs.com/w4ngzhen/";

    if (use_views && !enable_chrome_runtime) {
        // Create the BrowserView.
        CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(
            handler, url, browser_settings, nullptr, nullptr,
            new SimpleBrowserViewDelegate());

        // Create the Window. It will show itself after creation.
        CefWindow::CreateTopLevelWindow(new SimpleWindowDelegate(browser_view));
    }
    else {
        // Information used when creating the native window.
        CefWindowInfo window_info;

#if defined(OS_WIN)
        // On Windows we need to specify certain flags that will be passed to
        // CreateWindowEx().
        window_info.SetAsPopup(NULL, "simple-cef by w4ngzhen");
#endif

        // Create the first browser window.
        CefBrowserHost::CreateBrowser(window_info, handler, url, browser_settings,
            nullptr, nullptr);
    }
}