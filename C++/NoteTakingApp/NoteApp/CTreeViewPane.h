#pragma once
#include <afxdockablepane.h>
class CTreeViewPane :
    public CDockablePane
{
    DECLARE_DYNAMIC(CTreeViewPane)

public:
    CTreeViewPane();
    virtual ~CTreeViewPane();

protected:
    CTreeCtrl m_wndTreeCtrl;

    DECLARE_MESSAGE_MAP()

public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);

    CTreeCtrl& GetTreeCtrl() { return m_wndTreeCtrl; }
};

