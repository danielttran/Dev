#include "framework.h"
#include "AllMyNotes.h"
#include <commctrl.h>
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Structure to hold note data
struct Note {
    std::wstring title;
    std::wstring text;
};

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize common controls
    InitCommonControls();

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_AllMyNotes, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_AllMyNotes));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AllMyNotes));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_AllMyNotes);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hTreeView; // Handle to the tree view control
    static HWND hEdit;     // Handle to the edit control

    switch (message)
    {
    case WM_CREATE:
    {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        int width = pCreate->cx;
        int height = pCreate->cy;
        int treeWidth = width * 0.3;
        int editWidth = width - treeWidth;

        // Create TreeView (left panel)
        hTreeView = CreateWindowExW(0, WC_TREEVIEWW, L"", WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS,
            0, 0, treeWidth, height,
            hWnd, nullptr, hInst, nullptr);

        // Create Edit control (right panel)
        hEdit = CreateWindowExW(0, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
            treeWidth, 0, editWidth, height,
            hWnd, nullptr, hInst, nullptr);

        // Insert root note
        TVINSERTSTRUCTW tvInsert = { 0 };
        tvInsert.hParent = nullptr;
        tvInsert.hInsertAfter = TVI_ROOT;
        tvInsert.item.mask = TVIF_TEXT | TVIF_PARAM;
        tvInsert.item.pszText = const_cast<LPWSTR>(L"Root Note");
        Note* rootNote = new Note{ L"Root Note", L"" };
        tvInsert.item.lParam = (LPARAM)rootNote;
        HTREEITEM hRoot = TreeView_InsertItem(hTreeView, &tvInsert);

        // Select the root note initially
        TreeView_SelectItem(hTreeView, hRoot);
    }
    break;

    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        int treeWidth = width * 0.3;
        int editWidth = width - treeWidth;

        MoveWindow(hTreeView, 0, 0, treeWidth, height, TRUE);
        MoveWindow(hEdit, treeWidth, 0, editWidth, height, TRUE);
    }
    break;

    case WM_NOTIFY:
    {
        LPNMHDR pNMHDR = (LPNMHDR)lParam;
        if (pNMHDR->hwndFrom == hTreeView)
        {
            if (pNMHDR->code == TVN_SELCHANGED)
            {
                LPNMTREEVIEW pNMTreeView = (LPNMTREEVIEW)lParam;

                // Save text of the previous note
                if (pNMTreeView->itemOld.hItem != nullptr)
                {
                    Note* prevNote = (Note*)pNMTreeView->itemOld.lParam;
                    int len = GetWindowTextLengthW(hEdit);
                    std::wstring text(len, L'\0');
                    GetWindowTextW(hEdit, &text[0], len + 1);
                    prevNote->text = text;
                }

                // Load text of the new note
                Note* newNote = (Note*)pNMTreeView->itemNew.lParam;
                SetWindowTextW(hEdit, newNote->text.c_str());
            }
            else if (pNMHDR->code == TVN_DELETEITEM)
            {
                LPNMTREEVIEW pNMTreeView = (LPNMTREEVIEW)lParam;
                Note* note = (Note*)pNMTreeView->itemOld.lParam;
                delete note;
            }
        }
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ADD_NOTE:
        {
            // Get the currently selected item
            HTREEITEM hSelected = TreeView_GetSelection(hTreeView);
            if (hSelected == nullptr)
                hSelected = TreeView_GetRoot(hTreeView); // Default to root if no selection

            // Create a new note
            Note* newNote = new Note{ L"New Note", L"" };

            // Insert the new note as a child of the selected item
            TVINSERTSTRUCTW tvInsert = { 0 };
            tvInsert.hParent = hSelected;
            tvInsert.hInsertAfter = TVI_LAST;
            tvInsert.item.mask = TVIF_TEXT | TVIF_PARAM;
            tvInsert.item.pszText = const_cast<LPWSTR>(L"New Note");
            tvInsert.item.lParam = (LPARAM)newNote;
            HTREEITEM hNewItem = TreeView_InsertItem(hTreeView, &tvInsert);

            // Select the new item
            TreeView_SelectItem(hTreeView, hNewItem);
        }
        break;

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}