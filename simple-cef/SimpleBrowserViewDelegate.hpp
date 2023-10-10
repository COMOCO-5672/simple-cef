#pragma once

#include "include/views/cef_browser_view_delegate.h"
#include "include/views/cef_window.h"
#include "include/views/cef_window_delegate.h"

class SimpleBrowserViewDelegate : public CefBrowserViewDelegate
{
public:
	SimpleBrowserViewDelegate()
	{
	}

	bool OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browser_view, CefRefPtr<CefBrowserView> popup_browser_view, bool is_devtools) OVERRIDE
	{
		CefWindow::CreateTopLevelWindow(new SimpleWindowDelegate(popup_browser_view));
		return true;
	}

private:
	IMPLEMENT_REFCOUNTING(SimpleBrowserViewDelegate);
	DISALLOW_COPY_AND_ASSIGN(SimpleBrowserViewDelegate);
};


class SimpleWindowDelegate : public CefWindowDelegate
{
public:
	explicit SimpleWindowDelegate(CefRefPtr<CefBrowserView> browser_view)
		: browser_view_(browser_view)
	{

	}

	void OnWindowCreated(CefRefPtr<CefWindow> window) OVERRIDE
	{
		window->AddChildView(browser_view_);
		window->Show();

		browser_view_->RequestFocus();
	}

	void OnWindowDestroyed(CefRefPtr<CefWindow> window) OVERRIDE
	{
		browser_view_ = nullptr;
	}

	bool CanClose(CefRefPtr<CefWindow> window) OVERRIDE
	{

	}

	CefSize GetPreferredSize(CefRefPtr<CefView> view) OVERRIDE
	{
		return CefSize(800, 600);
	}

private:
	CefRefPtr<CefBrowserView> browser_view_;

	IMPLEMENT_REFCOUNTING(SimpleWindowDelegate);
	DISALLOW_COPY_AND_ASSIGN(SimpleWindowDelegate);

};

