#pragma once
#include "OptionsUI.h"
#include "Utilities/FileSystemUtills_Launcher.h"
#include "Utilities/Windows_Utill.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>
//windows

#include<stdlib.h>

OptionsUI::OptionsUI()
{
}

OptionsUI::~OptionsUI()
{
}

void OptionsUI::Draw()
{
    ImGui::Begin("Option window", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

    ImGui::NewLine();
    ImGui::NewLine();

    ImGui::Text("Train Image Reconition Model");
    if (image_reconition_exe.empty())
    {
        ImGui::PushID("Train");
        ImGui::PushItemFlag(ImGuiItemFlags_::ImGuiItemFlags_Disabled, true);
        ImGui::PushItemWidth(300.0f);
        ImGui::InputText("Image Reconition exe", &image_reconition_exe);
        ImGui::PopItemWidth();
        ImGui::PopItemFlag();
        ImGui::SameLine();
        if (ImGui::SmallButton("open"))
        {
            WindowsUtilities::FileDialogue_Generic(L"img_reconition.exe", L"*.exe", [this](const std::filesystem::path& p) {
                this->image_reconition_exe = p.string();
                });
        }
        ImGui::PopID();
    }
    else
    {

        ImGui::PushID("Train");
        ImGui::PushItemFlag(ImGuiItemFlags_::ImGuiItemFlags_Disabled, true);
        ImGui::PushItemWidth(300.0f);
        ImGui::InputText("Target Folder", &file_dir);
        ImGui::PopItemWidth();
        ImGui::PopItemFlag();
        ImGui::SameLine();
        if (ImGui::SmallButton("open"))
        {
            WindowsUtilities::FileDialogue_Folder([this](const std::filesystem::path& p) {
                this->file_dir = p.parent_path().string();
                this->data_dir = p.stem().string();
                });

        }
        if (ImGui::Button("Train Model"))
        {
            const char* a[3];
            a[0] = image_reconition_exe.c_str();
            a[1] = file_dir.c_str();
            a[2] = data_dir.c_str();
            execv(image_reconition_exe.c_str(), a);
        }
        ImGui::PopID();
    }

    ImGui::NewLine();
    ImGui::NewLine();
    ImGui::Separator();

    ImGui::Text("Image Sorter");

    if (image_sorter_exe.empty())
    {
        ImGui::PushID("Sorting");
        ImGui::PushItemFlag(ImGuiItemFlags_::ImGuiItemFlags_Disabled, true);
        ImGui::PushItemWidth(300.0f);
        ImGui::InputText("Image Sorter exe", &image_sorter_exe);
        ImGui::PopItemWidth();
        ImGui::PopItemFlag();
        ImGui::SameLine();
        if (ImGui::SmallButton("open"))
        {
            WindowsUtilities::FileDialogue_Generic(L"img_sorter.exe", L"*.exe", [this](const std::filesystem::path& p) {
                this->image_sorter_exe = p.string();
                });
        }
        ImGui::PopID();
    }
    else
    {
        ImGui::PushID("Sort");

        ImGui::PushItemFlag(ImGuiItemFlags_::ImGuiItemFlags_Disabled, true);
        ImGui::PushItemWidth(300.0f);
        ImGui::InputText("Model", &model_dir);
        ImGui::PopItemWidth();
        ImGui::PopItemFlag();
        ImGui::SameLine();
        ImGui::PushID("model");
        if (ImGui::SmallButton("open"))
        {
            WindowsUtilities::FileDialogue_Generic(L"KERAS File",L"*.keras", [this](const std::filesystem::path& p) {
                this->model_dir = p.string();
                });
        }
        ImGui::PopID();


        ImGui::PushItemFlag(ImGuiItemFlags_::ImGuiItemFlags_Disabled, true);
        ImGui::PushItemWidth(300.0f);
        ImGui::InputText("Data Location", &unsortedData_dir);
        ImGui::PopItemWidth();
        ImGui::PopItemFlag();
        ImGui::SameLine();
        ImGui::PushID("data");
        if (ImGui::SmallButton("open"))
        {
            WindowsUtilities::FileDialogue_Folder([this](const std::filesystem::path& p) {
                this->unsortedData_dir = p.string();
                });
        }
        ImGui::PopID();

        if (ImGui::Button("Sort Data"))
        {
            const char* a[3];
            a[0] = image_sorter_exe.c_str();
            a[1] = model_dir.c_str();
            a[2] = unsortedData_dir.c_str();
            execv(image_sorter_exe.c_str(), a);
        }
        ImGui::Text("Data will be sorted into a folder called 'rejected' inside the Data Location folder");
        ImGui::PopID();
    }

    ImGui::End();
}


