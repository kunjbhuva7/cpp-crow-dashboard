#include "crow.h"
#include <string>
#include <ctime>

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        crow::mustache::context ctx;
        ctx["title"] = "Local C++ Crow Dashboard";
        ctx["status"] = "Running on localhost:9999 ✅";
        ctx["time"] = std::to_string(std::time(nullptr));
        return crow::mustache::load("dashboard.html").render(ctx);
    });

    CROW_ROUTE(app, "/health")([](){
        return "healthy";
    });

    app.port(9999).multithreaded().run();
    return 0;
}

