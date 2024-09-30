#include <iostream>
#include <string>
#include <format>
#include "re2/re2.h"

int main() {
    std::string text = "google.com.com";
    
    const std::string rfc_1035_label     =              
        "(([[:alnum:]][-[:alnum:]]{1,61}[[:alnum:]])|([[:alnum:]]{1,2}))";
    const std::string rfc_1035_subdomain = 
        std::vformat("({}[.])", std::make_format_args(rfc_1035_label));
    const std::string rfc_1035_regex     = 
        std::vformat("^({}*{})$", std::make_format_args(rfc_1035_subdomain, rfc_1035_label));
    
    
    RE2 regex(rfc_1035_regex);

    std::string fqdn;
    if (RE2::FullMatch(text, regex, &fqdn)) {
        std::cout << "Matched: " << fqdn << std::endl;
    } else {
        std::cout << "No match found." << std::endl;
    }

    return 0;
}