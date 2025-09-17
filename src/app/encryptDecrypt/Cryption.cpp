#include "Cryption.hpp"
#include "../processes/Task.hpp"
#include"../fileHandling/ReadEnv.cpp"
#include <iostream>
#include <ctime>

#include<iomanip>
int executeCryption(const std::string& taskData) {
    Task task = Task::fromString(taskData);
    ReadEnv env;


    std::string keyStr = env.getenv();
    int key = std::stoi(keyStr);
    
   if(task.action==Action::ENCRYPT){
        char ch;
        while (task.f_stream.get(ch)) {
          ch=(ch+key)%256;
          task.f_stream.seekp(-1,std::ios::cur);
          task.f_stream.put(ch);
        }
        task.f_stream.close();


}
else{
    char ch;
    while(task.f_stream.get(ch)){
        ch=(ch-key+256)%256;
        task.f_stream.seekp(-1,std::ios::cur);
        task.f_stream.put(ch);

    }
    task.f_stream.close();

}
std::time_t t=std::time(nullptr);

std::tm*now=std::localtime(&t);
std::cout<<"Exiting the encryption/decryption at :"<<std::put_time(now,"%Y-%m-%d %H %M:");

return 0;
}
