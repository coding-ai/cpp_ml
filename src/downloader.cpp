#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>

size_t writeData(void* ptr,  size_t size, size_t nmemb, FILE* stream){
    size_t written = fwrite(ptr,size,  nmemb, stream);
    return written;
}

void downloadFile(const char* url, const char* file){
    CURL* curl;
    FILE* fp;
    CURLcode res;

    curl = curl_easy_init();
    if (curl){
        fp = fopen(file, "wb");
        if (fp) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA,  fp);
            res =  curl_easy_perform(curl);

            curl_easy_cleanup(curl);
            fclose(fp);
        } else {
            std::cerr << "Error opening file " << file << std::endl;
        }
        
    } else {
        std::cerr << "Error initializing CURL" << std::endl;
    }
}

int main() {
    const char* url = "https://gist.github.com/netj/8836201#file-iris-csv";
    const char* file = "../data/dataset.csv";
    downloadFile(url, file);
    return 0;
}
