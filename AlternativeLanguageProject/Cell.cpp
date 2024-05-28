#include "Cell.h"

Cell::Cell() : launch_announced(0), body_weight(0.0f), display_size(0.0f) {}

Cell::Cell(const std::string& oem, const std::string& model, int launch_announced, const std::string& launch_status,
	const std::string& body_dimensions, float body_weight, const std::string& body_sim, const std::string& display_type, float display_size,
	const std::string& display_resolution, const std::string& features_sensors, const std::string& platform_os) 
	: oem(oem), model(model), launch_announced(launch_announced), launch_status(launch_status),
	body_dimensions(body_dimensions), body_weight(body_weight), body_sim(body_sim), display_type(display_type),
	display_size(display_size), display_resolution(display_resolution), features_sensors(features_sensors),
	platform_os(platform_os) {}

// Getters
const std::string& Cell::getOem() const { return oem; }
const std::string& Cell::getModel() const { return model; }
int Cell::getLaunchAnnounced() const { return launch_announced; }
const std::string& Cell::getLaunchStatus() const { return launch_status; }
const std::string& Cell::getBodyDimensions() const { return body_dimensions; }
float Cell::getBodyWeight() const { return body_weight; }
const std::string& Cell::getBodySim() const { return body_sim; }
const std::string& Cell::getDisplayType() const { return display_type; }
float Cell::getDisplaySize() const { return display_size; }
const std::string& Cell::getDisplayResolution() const { return display_resolution; }
const std::string& Cell::getFeaturesSensors() const { return features_sensors; }
const std::string& Cell::getPlatformOs() const { return platform_os; }

// Setters
void Cell::setOem(const std::string& oem) { this->oem = oem; }
void Cell::setModel(const std::string& model) { this->model = model; }
void Cell::setLaunchAnnounced(int launch_announced) { this->launch_announced = launch_announced; }
void Cell::setLaunchStatus(const std::string& launch_status) { this->launch_status = launch_status; }
void Cell::setBodyDimensions(const std::string& body_dimensions) { this->body_dimensions = body_dimensions; }
void Cell::setBodyWeight(float body_weight) { this->body_weight = body_weight; }
void Cell::setBodySim(const std::string& body_sim) { this->body_sim = body_sim; }
void Cell::setDisplayType(const std::string& display_type) { this->display_type = display_type; }
void Cell::setDisplaySize(float display_size) { this->display_size = display_size; }
void Cell::setDisplayResolution(const std::string& display_resolution) { this->display_resolution = display_resolution; }
void Cell::setFeaturesSensors(const std::string& features_sensors) { this->features_sensors = features_sensors; }
void Cell::setPlatformOs(const std::string& platform_os) { this->platform_os = platform_os; }

std::string Cell::toString() const {
    std::stringstream ss;
    ss << "OEM: " << oem << ", " << std::endl
        << "Model: " << model << ", " << std::endl
        << "Launch Announced: " << launch_announced << ", " << std::endl
        << "Launch Status: " << launch_status << ", " << std::endl
        << "Body Dimensions: " << body_dimensions << ", " << std::endl
        << "Body Weight: " << body_weight << ", " << std::endl
        << "Body SIM: " << body_sim << ", " << std::endl
        << "Display Type: " << display_type << ", " << std::endl
        << "Display Size: " << display_size << ", " << std::endl
        << "Display Resolution: " << display_resolution << ", " << std::endl
        << "Features Sensors: " << features_sensors << ", " << std::endl
        << "Platform OS: " << platform_os << std::endl;
    return ss.str();
}