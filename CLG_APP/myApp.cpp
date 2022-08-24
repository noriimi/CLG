#include "myApp.h"

myApp::myApp() {
}
ImVec2 myApp::WorldToScreen(const ImVec2 World)
{
    return ImVec2((int)((World.x - Offset.x) * Scale.x) - Offsetw.x, (int)((World.y - Offset.y) * Scale.y) - Offsetw.y);
}
ImVec2 myApp::ScreenToWorld(const ImVec2 Screen)
{
    return ImVec2(((float)(Screen.x + Offsetw.x) / Scale.x) + Offset.x, ((float)(Screen.y + Offsetw.y) / Scale.y) + Offset.y);
}
void myApp::initOffset(ImVec2 in)
{
    Offset.x = -in.x;
    Offset.y = -in.y;
    InitOffset = in;
    runned = true;
}
void Item::convert()
{
    start.x = 10 * round(start.x / 10);
    start.y = 10 * round(start.y / 10);
    end.x = 10 * round(end.x / 10);
    end.y = 10 * round(end.y / 10);
}
int Item::area()
{
    return abs((end.x - start.x) * (end.y - start.y));
}
void myApp::Init()
{
    show_demo_window = true;
    show_another_window = false;
    wheel = 4;
    oldwheel = 4;
    Offset = { 0.0f,0.0f };
    Offsetw = { 0.0f,0.0f };
    Scale = { 1.0f,1.0f };
    StartPan = { 0.0f,0.0f };
    /*for (int i = 0; i < 7; i++)
    {
        Colors[i] = (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f);
    }*/
    ColorID = RED;
    ColRect = Colors[ColorID];
}
void myApp::Update()
{
    static ImVector<ImVec2> points;
    static bool opt_enable_grid = false;
    static bool opt_filled = true;
    static bool adding_line = false;
    io = ImGui::GetIO();
    oldwheel = wheel;
    wheel += io.MouseWheel;
    ImVec2 Mouse = io.MousePos;
    ImGui::Begin("test");
    ImGui::Checkbox("Enable grid", &opt_enable_grid);
    ImGui::Checkbox("Fill", &opt_filled);
    ImGui::Text("Kursor  %f     \t \t  %f", (double)io.MousePos.x - ve2[0], (double)io.MousePos.y - ve2[1]);
    //
    ImGui::InputFloat4("POS", ve);
    for (int i = 0; i < 6; i++)
    {
        if (i > 0)
            ImGui::SameLine();
        ImGui::PushID(i);
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)Colors[i]);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
        if (ImGui::Button("Click"))
        {
            ColRect = Colors[i];
            ColorID = ColorsID(i);
        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }
    // Typically you would use a BeginChild()/EndChild() pair to benefit from a clipping region + own scrolling.
    // Here we demonstrate that this can be replaced by simple offsetting + custom drawing + PushClipRect/PopClipRect() calls.
    // To use a child window instead we could use, e.g:
    // Using InvisibleButton() as a convenience 1) it will advance the layout cursor and 2) allows us to use IsItemHovered()/IsItemActive()
    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
    ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
    Offsetw.x = -(canvas_p0.x - InitOffset.x);
    Offsetw.y = -(canvas_p0.y - InitOffset.y);
    // Resize canvas to what's available
    if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
    if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
    const float mouse_threshold_for_pan = opt_filled ? -1.0f : 0.0f;
    if (!runned)
        initOffset(canvas_p0);


    // Draw border and background color

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
    draw_list->PushClipRect(canvas_p0, canvas_p1);
    // This will catch our interactions
    ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
    const bool is_hovered = ImGui::IsItemHovered(); // Hovered
    const bool is_active = ImGui::IsItemActive();   // Held

    if (is_active && ImGui::IsMouseDragging(ImGuiMouseButton_Right, mouse_threshold_for_pan))
    {
        Offset.x -= io.MouseDelta.x / Scale.x;
        Offset.y -= io.MouseDelta.y / Scale.y;
    }
    // Add first and second point
    if (is_hovered && !adding_line && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        item.start = ScreenToWorld(Mouse);
        item.end = ScreenToWorld(Mouse);
        adding_line = true;
    }
    if (adding_line)
    {
        item.end = ScreenToWorld(Mouse);
        item.color = ColorID;
        item.convert();
        if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            if (item.area())
            {
                Items.push_back(item);
                item.start = { 0,0 };
                item.end = { 0,0 };
            }
            adding_line = false;
        }
    }
    ve[0] = item.start.x;
    ve[1] = item.start.y;
    ve[2] = item.end.x;
    ve[3] = item.end.y;
    if (opt_enable_grid)
    {
        Offset.x = 0;
        Offset.y = 0;
        wheel = 4;
        oldwheel = 4;
    }
    ImVec2 MouseWorld_BeforeZoom = ScreenToWorld(Mouse);
    if (wheel - oldwheel > 0)
    {
        Scale.x *= 1.1f;
        Scale.y *= 1.1f;
    }
    if (wheel - oldwheel < 0)
    {
        Scale.x *= 0.9f;
        Scale.y *= 0.9f;
    }
    ImVec2 MouseWorld_AfterZoom = ScreenToWorld(Mouse);

    Offset.x += (MouseWorld_BeforeZoom.x - MouseWorld_AfterZoom.x);
    Offset.y += (MouseWorld_BeforeZoom.y - MouseWorld_AfterZoom.y);

    ImVec4 a;
    float fWorldLeft, fWorldTop, fWorldRight, fWorldBottom;
    fWorldLeft = ScreenToWorld(canvas_p0).x;
    fWorldTop = ScreenToWorld(canvas_p0).y;
    fWorldRight = ScreenToWorld(canvas_p1).x;
    fWorldBottom = ScreenToWorld(canvas_p1).y;

    ImVec2 Start = { 10 * (float)floor(fWorldLeft / 10) ,10 * (float)floor(fWorldTop / 10) };
    ImVec2 End = { 10 * (float)ceil(fWorldRight / 10) ,10 * (float)ceil(fWorldBottom / 10) };
    for (Start.x; Start.x <= End.x; Start.x += 10)
    {
        ImVec2 Pixel_Start = { WorldToScreen(Start).x,WorldToScreen(Start).y }, Pixel_End = { WorldToScreen(End).x,WorldToScreen(End).y };
        draw_list->AddLine(Pixel_Start, ImVec2(Pixel_Start.x, Pixel_End.y), IM_COL32(100, 100, 100, 100));
    }

    Start = { 10 * (float)floor(fWorldLeft / 10) ,10 * (float)floor(fWorldTop / 10) };
    End = { 10 * (float)ceil(fWorldRight / 10) ,10 * (float)ceil(fWorldBottom / 10) };
    for (Start.y; Start.y <= End.y; Start.y += 10)
    {
        ImVec2 Pixel_Start = { WorldToScreen(Start).x,WorldToScreen(Start).y }, Pixel_End = { WorldToScreen(End).x,WorldToScreen(End).y };
        draw_list->AddLine(Pixel_Start, ImVec2(Pixel_End.x, Pixel_Start.y), IM_COL32(100, 100, 100, 100));
    }



    draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(0, 255, 255, 255));
    if (!opt_filled)
    {
        for (auto& it : Items)
        {
            draw_list->AddRect(WorldToScreen(it.start), WorldToScreen(it.end), Colors[it.color]);
        }
        if (item.area())
            draw_list->AddRect(WorldToScreen(item.start), WorldToScreen(item.end), ColRect);
    }
    else
    {
        for (auto& it : Items)
        {
            draw_list->AddRectFilled(WorldToScreen(it.start), WorldToScreen(it.end), Colors[it.color]);
        }
        if (item.area())
            draw_list->AddRectFilled(WorldToScreen(item.start), WorldToScreen(item.end), ColRect);
    }
    draw_list->PopClipRect();
    ImGui::End();
}
