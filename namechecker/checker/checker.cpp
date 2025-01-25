#include "checker.h"
using json = nlohmann::json; 
nlohmann::json config;

void c_checker::checkRandom(int length) {
    while (true)
    {
        std::string username = randomString(length);

        if (generatedUsernames.find(username) != generatedUsernames.end()) {
            continue;  
        }

        generatedUsernames.insert(username);

        if (checkUsername(username)) {
            saveUsername(username, "C:\\mc\\");       
            Beep(500, 500); 
            std::cout << " \033[32m" << "[AVAILABLE] \033[37m" << username << std::endl; 
        }
        else {
            
            std::cout << " \033[31m" << "[TAKEN] \033[37m" << username << std::endl;
        }
    }
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool c_checker::checkUsername(const std::string username) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if (curl) {
        std::string url = "https://api.mojang.com/users/profiles/minecraft/" + username;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());  

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "CURL request failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);  
            curl_global_cleanup();    
            return false;
        }

        try {
            json j = json::parse(readBuffer); // Will read the buffer and check if it has an errorMessage cause if it is avaible and not taken

            if (j.contains("errorMessage")) {
                return true;   
            }
            else {
                return false;  
            }

        }
        catch (json::parse_error& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return false;
}

std::string c_checker::randomString(int length) {
    std::string result = {};
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz1234567890";

    srand((unsigned)time(0) * 5);

    for (unsigned int i = 0; i < length; i++)
        result += alphabet[rand() % (alphabet.length() - 1)];

    return result;
}

namespace fs = std::filesystem;
int path_exists(const char* path)
{
    struct stat info;
    if (stat(path, &info) != 0)
        return 0;
    else if (info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}

void c_checker::saveUsername(std::string username, std::string path) {
    if (path_exists(path.c_str())) {
        std::ofstream outfile(path + "/available.txt", std::ios::app); 
        if (outfile.is_open()) {
            outfile << "[AVAILABLE]" << username << std::endl;
            outfile.close();
        }
        else {
            std::cerr << "Error saving" << std::endl;
        }
    }
    else {
        try {
            fs::create_directories(path);
        }
        catch (const std::exception& e) {

        }
    }
}

 