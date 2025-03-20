// TreeViewPane.cpp
#include "pch.h"  // Make sure this points to your precompiled header
#include "CTreeViewPane.h"

IMPLEMENT_DYNAMIC(CTreeViewPane, CDockablePane)

CTreeViewPane::CTreeViewPane()
{
}

CTreeViewPane::~CTreeViewPane()
{
}

BEGIN_MESSAGE_MAP(CTreeViewPane, CDockablePane)
    ON_WM_CREATE()
    ON_WM_SIZE()
END_MESSAGE_MAP()

int CTreeViewPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDockablePane::OnCreate(lpCreateStruct) == -1)
        return -1;

    // Create the tree control
    if (!m_wndTreeCtrl.Create(WS_CHILD | WS_VISIBLE | TVS_HASBUTTONS |
        TVS_HASLINES | TVS_LINESATROOT,
        CRect(0, 0, 0, 0), this, 1001))
    {
        TRACE0("Failed to create tree control\n");
        return -1;
    }

    // Add some sample items
    HTREEITEM hRoot = m_wndTreeCtrl.InsertItem(_T("Root Item"));
    m_wndTreeCtrl.InsertItem(_T("Child Item 1"), hRoot);
    m_wndTreeCtrl.InsertItem(_T("Child Item 2"), hRoot);
    m_wndTreeCtrl.Expand(hRoot, TVE_EXPAND);

    return 0;
}

void CTreeViewPane::OnSize(UINT nType, int cx, int cy)
{
    CDockablePane::OnSize(nType, cx, cy);

    // Adjust tree control size to fill the pane
    if (m_wndTreeCtrl.GetSafeHwnd())
    {
        m_wndTreeCtrl.MoveWindow(0, 0, cx, cy);
    }
}