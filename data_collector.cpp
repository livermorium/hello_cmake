# include <iostream>
# include <queue>

#include <thread>
#include <unistd.h>

class A{
    public: 
        std::queue<std::string> imgs;
        bool isLoaded;
        std::queue<std::string> img_filenames;
        std::string current_video_name;

        int unload_image();
        int load_image();

        int consume_image();
        static void* produce_image(void*);

        A();
        ~A();
    private:
        pthread_t tid ;
        int get_default_image();
        int load_current_video_image();
        int img_index = 0;
};

A::A(){
    isLoaded = true;

    current_video_name = "0";
    img_filenames.push("0a");
    img_filenames.push("0b");
    img_filenames.push("0c");
    img_filenames.push("1d");
    img_filenames.push("1e");
}

A::~A(){
    // pthread_exit(NULL);
}

void* A::produce_image(void* p_a){
    std::cout << "+" << std::endl;
    A* a = (A*) p_a;

    a->load_current_video_image();

    a->isLoaded = true;
    std::cout << "-" << std::endl;

    pthread_exit(NULL);
}

int A::load_current_video_image(){
    while (!img_filenames.empty()){
        std::string next_img_filename = img_filenames.front();
        if (next_img_filename[0] == current_video_name[0]){
            img_filenames.pop();
            // std::cout << "load:" << next_img_filename << std::endl;
            load_image();
            imgs.push(next_img_filename);
        }
        else{
            current_video_name=next_img_filename[0];
            return 0;
        }
    }
    
    return -1;
}

int A::load_image(){
    sleep(3);
    return 0;
}

int A::unload_image(){
    return 0;
}

int A::get_default_image(){
    std::cout << "default" << std::endl;
    return 0;
}

int A::consume_image(){
    if (isLoaded){
        if (img_filenames.empty()&& imgs.empty()){
            return -1;
        }

        if (imgs.empty()){

            isLoaded = false;
            // 启动线程 开始加载
            int ret = pthread_create(&tid, NULL, produce_image, (void*)this);
            if (ret != 0)
            {
                std::cout << "pthread_create error: error_code=" << ret << std::endl;
            }

            return get_default_image();
        }
        else{
            std::cout << "consume:" << imgs.front() << std::endl;
            imgs.pop();
            return 0;
        }
    }
    else{
        return get_default_image();// 返回默认图片
    }
}

int main(){

    A a;
    // int m = a.consume_image();
    // std::cout << "x" << m << std::endl;
    while(0==a.consume_image()){
        sleep(1);
    }

    return 0;
}