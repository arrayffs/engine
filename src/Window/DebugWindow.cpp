#include "DebugWindow.h"

#include "Window.h"

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


void debug_window::init()
{
  IMGUI_CHECKVERSION();

  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());


  ImGuiStyle& style = ImGui::GetStyle();
  style.ScaleAllSizes(main_scale);
  style.FontScaleDpi = main_scale;

  ImGui::StyleColorsClassic();
  
  ImGui_ImplGlfw_InitForOpenGL(window::properties::_handle, true);

  ImGui_ImplOpenGL3_Init("#version 130");
}

void debug_window::exit()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void debug_window::new_frame()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void debug_window::render()
{
  static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);;

  ImGui::Render();
  int display_w{ }, display_h{ };
  glfwGetFramebufferSize(window::properties::_handle, &display_w, &display_h);
  /*glViewport(0, 0, display_w, display_h);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);*/
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
