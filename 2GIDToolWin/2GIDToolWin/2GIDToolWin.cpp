#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <shlobj.h>

// Global variables
HINSTANCE hInst; // Instance handle

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK InfoWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void displayInfo(HWND hwnd, const std::string& serialNumber, int prodWeek, int prodYear);
int productionWeek(const std::string& serialNumber);
int productionYear(const std::string& serialNumber);
float distgunishBootLoader(int prodWeek, int prodYear);
std::wstring calcMinOS(int prodWeek, int prodYear);
std::wstring prodWeekToMonth(int prodWeek);
void InvalidErrorHandler(HWND hwnd);
void Credits(HWND hwnd);
std::wstring ReadDevInfo();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    hInst = hInstance; // Store instance handle
    const wchar_t CLASS_NAME[] = L"iPhone2G ID Tool v2.0";

    WNDCLASS wc = { };

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"iPhone2G ID Tool v2.0",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZE,
        CW_USEDEFAULT, CW_USEDEFAULT, 320, 250,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    // Disable resizing
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~(WS_MAXIMIZEBOX | WS_SIZEBOX));

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static std::string serialNumber;
    static int prodWeek = 0;
    static int prodYear = 0;

    switch (uMsg) {
    case WM_CREATE: {
        CreateWindow(L"STATIC", L"Enter the serial number:",
            WS_VISIBLE | WS_CHILD,
            40, 20, 200, 20,
            hwnd, NULL, NULL, NULL);

        CreateWindow(L"EDIT", NULL,
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            40, 40, 200, 20,
            hwnd, (HMENU)1, NULL, NULL);

        CreateWindow(L"BUTTON", L"Submit",
            WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            80, 70, 100, 20,
            hwnd, (HMENU)2, NULL, NULL);

        break;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == 2) {
            wchar_t wSerialNumber[12];
            GetWindowText(GetDlgItem(hwnd, 1), wSerialNumber, 12);

            // Ensure the input length is exactly 11 characters
            if (wcslen(wSerialNumber) != 11) {
                MessageBox(hwnd, L"Error: Serial number must be 11 characters long.", L"Input Error", MB_OK | MB_ICONERROR);
                return 0;
            }

            // Convert wide string to narrow string manually
            serialNumber.clear();
            for (int i = 0; i < 11; i++) {
                serialNumber.push_back(static_cast<char>(wSerialNumber[i]));
            }

            // Ensure the serial number is null-terminated
            serialNumber.push_back('\0');

            prodWeek = productionWeek(serialNumber);
            prodYear = productionYear(serialNumber);

            if (prodWeek == 0 || prodYear == 0) {
                InvalidErrorHandler(hwnd);
            }
            else {
                displayInfo(hwnd, serialNumber, prodWeek, prodYear);
            }
        }
        break;
    }
    case WM_DESTROY: {
        Credits(hwnd);
        PostQuitMessage(0);
        return 0;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Function to get the directory of the executable
std::wstring GetExecutableDirectory() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return std::wstring(buffer).substr(0, pos);
}

// Function to read the contents of devinfo.txt
std::wstring ReadDevInfo() {
    std::wstring execDir = GetExecutableDirectory();
    std::wstring filePath = execDir + L"\\devinfo.txt";

    std::wifstream file(filePath);
    if (!file.is_open()) {
        return L"Failed to read devinfo.txt!";
    }

    std::wstringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to display device information in a custom window
void displayInfo(HWND hwnd, const std::string& serialNumber, int prodWeek, int prodYear) {
    const wchar_t INFO_CLASS_NAME[] = L"DeviceInfoClass";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = InfoWindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = INFO_CLASS_NAME;

    RegisterClass(&wc);

    HWND infoHwnd = CreateWindowEx(
        0,
        INFO_CLASS_NAME,
        L"Device Information",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        hwnd, NULL, hInst, NULL
    );

    if (infoHwnd == NULL) {
        MessageBox(hwnd, L"Failed to create information window.", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    ShowWindow(infoHwnd, SW_SHOW);
}

LRESULT CALLBACK InfoWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        std::wstring info = ReadDevInfo();

        HWND hEdit = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            L"EDIT",
            info.c_str(),
            WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL,
            10, 10, 370, 240,
            hwnd,
            NULL,
            hInst,
            NULL
        );

        if (hEdit == NULL) {
            MessageBox(hwnd, L"Failed to create edit control.", L"Error", MB_OK | MB_ICONERROR);
        }

        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void InvalidErrorHandler(HWND hwnd) {
    MessageBox(hwnd, L"Error: Invalid or unknown Serial number.\nIf you believe this is in error,\n Please contact SilentHunterDEV or BJNFNE on Discord over a direct message.\b If the Desktop application doesn't work for you,\b Please consider trying out our Web-based Application of 2GIDTool.", L"Error", MB_OK | MB_ICONERROR);
}

int productionWeek(const std::string& serialNumber) {
    int week = ((static_cast<int>(serialNumber[3]) - '0') * 10) + (static_cast<int>(serialNumber[4]) - '0');
    if (week > 52 || week <= 0) {
        return 0;
    }
    return week;
}

int productionYear(const std::string& serialNumber) {
    switch (static_cast<int>(serialNumber[2]) - '0') {
    case 7: return 2007;
    case 8: return 2008;
    default: return 0;
    }
}

float distgunishBootLoader(int prodWeek, int prodYear) {
    if ((prodWeek >= 45 && prodYear == 2007) || (prodYear == 2008)) {
        return 4.6f;
    }
    return 3.9f;
}

std::wstring calcMinOS(int prodWeek, int prodYear) {
    if (prodWeek <= 48 && prodYear == 2007) {
        return L"Firmware 1.0";
    }
    return L"Firmware 1.1.1";
}

std::wstring prodWeekToMonth(int prodWeek) {
    if (prodWeek <= 5) return L"January";
    if (prodWeek <= 9) return L"February";
    if (prodWeek <= 13) return L"March";
    if (prodWeek <= 18) return L"April";
    if (prodWeek <= 22) return L"May";
    if (prodWeek <= 26) return L"June";
    if (prodWeek <= 31) return L"July";
    if (prodWeek <= 35) return L"August";
    if (prodWeek <= 39) return L"September";
    if (prodWeek <= 44) return L"October";
    if (prodWeek <= 48) return L"November";
    if (prodWeek <= 52) return L"December";

    return L"Unknown";
}

void Credits(HWND hwnd) {
    MessageBox(hwnd, L"Credits:\n SilentHunterDEV - Development\n BJNFNE Code improvements\n JustGhost101 Icon design\n", L"2GIDTool v2.0", MB_ICONASTERISK);
}
