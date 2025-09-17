#include<iostream>

#include<filesystem>
#include "./src/app/processes/ProcessManagement.hpp"


#include "./src/app/processes/Task.hpp"
namespace fs=std::filesystem;

int main(int argc,char *argv[]){
    std::string directory;
    std::string action;

    std::cout << "enter the directory path ->:" << std::endl;
    std::getline(std::cin,directory);


    std::cout<<"Enter the action means what you want (encrypt/decrypt)::"<<std::endl;
    std::getline(std::cin,action);
      

    try{
        if(fs::exists(directory)&&fs::is_directory(directory)){
            ProcessManagement ProcessManagement;

            for(const auto &entry: fs::recursive_directory_iterator(directory)){
                if(entry.is_regular_file()){
                    std::string filePath=entry.path().string();
                    IO io(filePath);
                    std::fstream f_stream=std::move(io.getFileStream());

                    if(f_stream.is_open()){
                        Action taskAction=(action=="ENCRYPT"?Action::ENCRYPT:Action::DECRYPT);

                        auto task =std::make_unique<Task>(std::move(f_stream),taskAction,filePath);
                        ProcessManagement.submitToQueue(std::move(task));


                    }
                    else{
                        std::cout<<"We are unable to open the file :"<<filePath<<std::endl;
                    }

                }
            }
            ProcessManagement.executeTasks();
        } else{
            std::cout<<"Invalid directory path"<<std::endl;
        }
 
    } catch(const fs::filesystem_error &ex){
        std::cout<<"Filesystem error:"<<ex.what()<<std::endl;

    }
    

}


// THE GIVEN BELOW IS FOR THE MAIN CASE
// STUDY IT PROPERLY 



// #include <iostream>
// #include <filesystem>
// #include <fstream>
// #include <string>
// #include <vector>
// #include <memory>
// #include <algorithm> // For std::transform
// #include "./src/app/processes/ProcessManagement.hpp"
// #include "./src/app/processes/Task.hpp"

// namespace fs = std::filesystem;

// // Function to check if a file has an image or video extension
// bool isMediaFile(const std::string& filePath) {
//     std::string extension = "";
//     size_t dotPos = filePath.rfind('.');
//     if (dotPos != std::string::npos) {
//         extension = filePath.substr(dotPos + 1);
//         std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
//     }
//     return (extension == "jpg" || extension == "jpeg" || extension == "png" || extension == "gif" || extension == "bmp" ||
//             extension == "mp4" || extension == "avi" || extension == "mov" || extension == "wmv");
// }

// // Function to read the entire file into a byte vector
// std::vector<unsigned char> readFile(const std::string& filePath) {
//     std::ifstream file(filePath, std::ios::binary);
//     if (!file) {
//         throw std::runtime_error("Failed to open file: " + filePath);
//     }

//     file.seekg(0, std::ios::end);
//     std::streampos length = file.tellg();
//     file.seekg(0, std::ios::beg);

//     std::vector<unsigned char> buffer(length);
//     file.read(reinterpret_cast<char*>(buffer.data()), length);

//     return buffer;
// }

// // Function to write the byte vector back to the file
// void writeFile(const std::string& filePath, const std::vector<unsigned char>& data) {
//     std::ofstream file(filePath, std::ios::binary);
//     if (!file) {
//         throw std::runtime_error("Failed to open file for writing: " + filePath);
//     }
//     file.write(reinterpret_cast<const char*>(data.data()), data.size());
// }

// // Placeholder for encryption/decryption function (replace with your actual implementation)
// void processData(std::vector<unsigned char>& data, Action action) {
//     if (action == Action::ENCRYPT) {
//         std::cout << "Placeholder: Encrypting data" << std::endl;
//         // Implement your encryption logic here (e.g., AES)
//     } else {
//         std::cout << "Placeholder: Decrypting data" << std::endl;
//         // Implement your decryption logic here (e.g., AES)
//     }
// }

// int main(int argc, char* argv[]) {
//     std::string directory;
//     std::string action;

//     std::cout << "Enter the directory path ->:" << std::endl;
//     std::getline(std::cin, directory);

//     std::cout << "Enter the action (ENCRYPT/DECRYPT)::" << std::endl;
//     std::getline(std::cin, action);

//     try {
//         if (fs::exists(directory) && fs::is_directory(directory)) {
//             ProcessManagement processManagement;

//             for (const auto& entry : fs::recursive_directory_iterator(directory)) {
//                 if (entry.is_regular_file()) {
//                     std::string filePath = entry.path().string();

//                     if (isMediaFile(filePath)) {
//                         // Handle image and video files
//                         Action taskAction = (action == "ENCRYPT" ? Action::ENCRYPT : Action::DECRYPT);
//                         try {
//                             std::vector<unsigned char> fileData = readFile(filePath);
//                             processData(fileData, taskAction); // Encrypt or decrypt the data
//                             writeFile(filePath, fileData); // Write the processed data back to the file
//                             std::cout << "Processed media file: " << filePath << std::endl;
//                         } catch (const std::exception& e) {
//                             std::cerr << "Error processing media file: " << filePath << " - " << e.what() << std::endl;
//                         }
//                     } else {
//                         // Handle other files (e.g., text files)
//                         IO io(filePath);
//                         std::fstream f_stream = std::move(io.getFileStream());

//                         if (f_stream.is_open()) {
//                             Action taskAction = (action == "ENCRYPT" ? Action::ENCRYPT : Action::DECRYPT);
//                             auto task = std::make_unique<Task>(std::move(f_stream), taskAction, filePath);
//                             processManagement.submitToQueue(std::move(task));
//                         } else {
//                             std::cout << "We are unable to open the file: " << filePath << std::endl;
//                         }
//                     }
//                 }
//             }
//             processManagement.executeTasks();
//         } else {
//             std::cout << "Invalid directory path" << std::endl;
//         }
//     } catch (const fs::filesystem_error& ex) {
//         std::cout << "Filesystem error:" << ex.what() << std::endl;
//     }

//     return 0;
// }
