#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

string generate_html(const string& name) {
    return R"(
<!DOCTYPE html>
<html>
<head>
  <title>Nom du Service</title>
</head>
<body>
  <h1>Bienvenue sur le service Docker!</h1>
  <p>Le nom du service est: )" + name + R"(
  </p>
</body>
</html>
)";
}

int main() {
    io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 80));
    
    while (true) {
        tcp::socket socket(io_service);
        acceptor.accept(socket);
        
        string name = "Sofiane";
        string html_content = generate_html(name);
        
        string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " + to_string(html_content.size()) + "\r\n\r\n" + html_content;
        
        boost::system::error_code ignored_error;
        boost::asio::write(socket, buffer(response), ignored_error);
    }

    return 0;
}
