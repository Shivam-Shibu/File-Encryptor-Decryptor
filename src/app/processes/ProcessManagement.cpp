#include "ProcessManagement.hpp"
#include<iostream>
#include<cstring>
#include<unistd.h>
#include <unistd.h>   // fork()
#include <sys/types.h> // pid_t
#include<windows.h>




#include"../encryptDecrypt/Cryption.hpp"



ProcessManagement::ProcessManagement() {}
bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task) {
    
        taskQueue.push(std::move(task));

        // int pid=fork();
        // if(pid<0){
        //     return false;
        // }
        // else if(pid>0){
        //     std::cout<<"Enter the parent proecess"<<std::endl;


        // }

       #include <windows.h>
#include <iostream>
using namespace std;

 
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Child process create karna
    if (CreateProcess(
        NULL,               // Application name
        (LPSTR)"notepad.exe", // Command line (child program to run)
        NULL,               // Process security attributes
        NULL,               // Primary thread security attributes
        FALSE,              // Handles are not inherited
        0,                  // Creation flags
        NULL,               // Use parent's environment
        NULL,               // Use parent's starting directory 
        &si,                // Pointer to STARTUPINFO structure
        &pi                 // Pointer to PROCESS_INFORMATION structure
    )) {
        cout << "Parent: Child process created successfully!" << endl;
        cout << "Child PID: " << pi.dwProcessId << endl;

        // Parent waits for child to finish
        WaitForSingleObject(pi.hProcess, INFINITE);

        cout << "Child process finished!" << endl;

        // Close handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        cerr << "CreateProcess failed (" << GetLastError() << ")" << endl;
    }

  


        return true;
   
}

void ProcessManagement::executeTasks() {
    while (!taskQueue.empty()) {
        std::unique_ptr<Task> taskToExecute = std::move(taskQueue.front());
        taskQueue.pop();
        // Execute the task (for demonstration, just print the task details)    
        // Assuming Task has a 'getName()' method or similar; replace with actual method as needed
       std::cout << "Executing task: " << taskToExecute->toString() << std::endl;
executeCryption(taskToExecute->toString());


    }
}