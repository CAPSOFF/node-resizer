#include <httplib.h>
#include <nlohmann/json.hpp>
#include "resizer.hpp"
#include <exception>

auto set_error(int code, std::string message) -> nlohmann::json {
    auto res_json = nlohmann::json{};
    res_json["code"] = code;
    res_json["message"] = message;

    return res_json;
}

auto set_success(int code, std::string message, std::string payload) -> nlohmann::json {
    auto res_json = nlohmann::json{};
    res_json["code"] = code;
    res_json["message"] = message;
    res_json["output_jpeg"] = payload;

    return res_json;
}

auto main(int argc, char** argv) -> int {
    httplib::Server server;
    auto resizer = std::make_unique<Resizer>();

    server.Post("/resize_image",
    [&](const httplib::Request &req, httplib::Response &res, const httplib::ContentReader &content_reader) {
        std::string body;
        content_reader([&](const char *data, size_t data_length) {
            body.append(data, data_length);
            return true;
        });

        auto response = nlohmann::json{};
        
        try {
            auto body_json = nlohmann::json::parse(body);

            if (body_json.find("input_jpeg") == body_json.end()) {
                throw "input_jpeg is required";
            }

            if (body_json.find("desired_width") == body_json.end()) {
                throw "desired_width is required";
            }

            if (body_json.find("desired_height") == body_json.end()) {
                throw "desired_height is required";
            }

            auto jpeg_image = resizer->base64_to_mat(body_json["input_jpeg"]);
            auto resized_image = resizer->image_resizer(jpeg_image, body_json["desired_width"], body_json["desired_height"]);
            auto resized_base64 = resizer->mat_to_base64(resized_image);
            response = set_success(200, "success", resized_base64);
        } catch (std::exception& error) {
            response = set_error(400, error.what());
        }

        res.status = response["code"];
        res.set_content(response.dump(), "application/json");
    });

    server.listen("localhost", 8080);
}