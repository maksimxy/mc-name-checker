#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <codecvt>
#include <memory>


#define CURL_STATICLIB 
#include "curl.h"
#pragma comment (lib, "advapi32.lib")
#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "user32.lib")

#include <json.hpp>

#include "log.h"

#include <checker.h>