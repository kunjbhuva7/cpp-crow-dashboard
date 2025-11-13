#include "crow.h"
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <algorithm>

// Helper to read file contents safely
std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return "Unavailable";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Get system uptime
std::string getUptime() {
    std::ifstream file("/proc/uptime");
    double uptimeSeconds;
    if (!(file >> uptimeSeconds)) return "Unknown";
    int hours = static_cast<int>(uptimeSeconds / 3600);
    int mins = static_cast<int>((uptimeSeconds - hours * 3600) / 60);
    return std::to_string(hours) + "h " + std::to_string(mins) + "m";
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        std::string hostname = readFile("/etc/hostname");
        std::string osInfo = readFile("/etc/os-release");
        std::string uptime = getUptime();

        hostname.erase(std::remove(hostname.begin(), hostname.end(), '\n'), hostname.end());

        std::ostringstream html;
        html << "<html><body style='font-family:Arial;text-align:center;margin-top:60px;'>"
             << "<h2>🐳 Docker Container Info API</h2>"
             << "<p><b>Hostname:</b> " << hostname << "</p>"
             << "<p><b>OS Info:</b><br><pre>" << osInfo << "</pre></p>"
             << "<p><b>Uptime:</b> " << uptime << "</p>"
             << "<hr><p>Generated at: " << std::time(nullptr) << "</p>"
             << "</body></html>";
        return html.str();
    });

    CROW_ROUTE(app, "/info")([]() {
        std::string hostname = readFile("/etc/hostname");
        std::string osInfo = readFile("/etc/os-release");
        std::string uptime = getUptime();

        hostname.erase(std::remove(hostname.begin(), hostname.end(), '\n'), hostname.end());

        crow::json::wvalue data;
        data["id"] = hostname;
        data["os"] = osInfo;
        data["uptime"] = uptime;
        return data;
    });

    // ✅ Running on port 55000 now
    app.port(55000).multithreaded().run();
    return 0;
}

