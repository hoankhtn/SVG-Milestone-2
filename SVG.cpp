#include "ReadFileSVG.h"
#include "BackgroundDecorator.h"
#include "BorderDecorator.h"
#include "TextDecorator.h"
#include "LoadFileSVG.h"

vector<Shape*> shapes;

void LoadFileSVG::LoadSVG(const string& fileName) {
    ifstream file(fileName);
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    xml_document<> doc;
    doc.parse<0>(&buffer[0]);

    ReadFileSVG reader(fileName);

    xml_node<>* root = doc.first_node();
    while (root && string(root->name()) != "svg") {
        root = root->next_sibling();
    }

    if (!root) return;

    xml_node<>* node = root->first_node();

    while (node) {
        string name = node->name();
        Shape* shape = nullptr;
        if (name == "rect") {
            shape = reader.parseRectangle(node);
        }
        else if (name == "circle") {
            shape = reader.parseCircle(node);
        }
        else if (name == "ellipse") {
            shape = reader.parseEllipse(node);
        }
        else if (name == "line") {
            shape = reader.parseLine(node);
        }
        else if (name == "polyline") {
            shape = reader.parsePolyline(node);
        }
        else if (name == "polygon") {
            shape = reader.parsePolygon(node);
        }
        else if (name == "text") {
            shape = reader.parseText(node);
        }
        else if (name == "path") {
            shape = reader.parsePath(node);
        }
        else if (name == "g") {
            shape = reader.parseGroup(node);
        }
        if (shape) {
            if (name == "g")
                shapes.push_back(shape);

            if (name != "line" && name != "text") {
                shape = new BorderDecorator(shape);        
                shape = new BackgroundDecorator(shape);
                /*shape = new BorderDecorator(shape);*/
            }
            else if (name != "text") {
                shape = new BorderDecorator(shape);
            }

            shapes.push_back(shape);
        }
        
        node = node->next_sibling();
    }
}

int main() {
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    LoadFileSVG loader;
    loader.LoadSVG("svg-11.svg");

    GdiplusShutdown(gdiplusToken);
    return 0;
}

VOID OnPaint(HDC hdc)
{
   Graphics graphics(hdc);

    for (Shape* shape : shapes)
    {
        if (shape)
            shape->draw(graphics);
    }
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR lpCmdLine, INT iCmdShow)
{
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    /*string fileName = lpCmdLine;*/
    LoadFileSVG loader;
    loader.LoadSVG("svg-11.svg");

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("GettingStarted");

    RegisterClass(&wndClass);

    hWnd = CreateWindow(
        TEXT("GettingStarted"),   // window class name
        TEXT("SVG"),  // window caption
        WS_OVERLAPPEDWINDOW,      // window style
        CW_USEDEFAULT,            // initial x position
        CW_USEDEFAULT,            // initial y position
        CW_USEDEFAULT,            // initial x size
        CW_USEDEFAULT,            // initial y size
        NULL,                     // parent window handle
        NULL,                     // window menu handle
        hInstance,                // program instance handle
        NULL);                    // creation parameters

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        OnPaint(hdc);

        EndPaint(hWnd, &ps);
        return 0;
    }
    case WM_DESTROY:
        for (Shape* shape : shapes)
            delete shape;
        shapes.clear();

        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
