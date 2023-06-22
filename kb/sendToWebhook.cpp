#include "sendToWebhook.h"


#include "curl/curl.h"

#define CURL_STATICLIB //let's not use DLL curl :)

#pragma comment (lib, "curl/libcurl_a.lib")

#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib, "advapi32.lib")

void sendToWebhook(std::string url, std::string avatar_url)
{

}