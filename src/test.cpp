#include <iostream>
#include <edupage.hpp>
#include <clocale>
int main() {

    const std::string payload = "groupid=1205235&text=cppimpl&moredata=%7B%22attachments%22%3A%5B%5D%7D&recipient=";

    auto encoded = eplib::encode(payload);
    printf("%s", encoded.c_str());

    return 0;
}
