#pragma once
#include <string>
class OptionsUI
{
public:
    OptionsUI();
    ~OptionsUI();

    void Draw();

    std::string file_dir;
    std::string data_dir;

    std::string model_dir;
    std::string unsortedData_dir;

    std::string image_reconition_exe;
    std::string image_sorter_exe;
private:
};

