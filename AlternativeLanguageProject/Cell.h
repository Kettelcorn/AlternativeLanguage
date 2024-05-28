#ifndef CELL_H
#define CELL_H


#include <string>
#include <sstream>


class Cell {
public:
    Cell();

	Cell(const std::string& oem, const std::string& model, int launch_announced, const std::string& launch_status,
		const std::string& body_dimensions, float body_weight, const std::string& body_sim, const std::string& display_type, float display_size,
		const std::string& display_resolution, const std::string& features_sensors, const std::string& platform_os);

    const std::string& getOem() const;
    const std::string& getModel() const;
    int getLaunchAnnounced() const;
    const std::string& getLaunchStatus() const;
    const std::string& getBodyDimensions() const;
    float getBodyWeight() const;
	const std::string& getBodySim() const;
    const std::string& getDisplayType() const;
    float getDisplaySize() const;
    const std::string& getDisplayResolution() const;
    const std::string& getFeaturesSensors() const;
    const std::string& getPlatformOs() const;

    void setOem(const std::string& oem);
    void setModel(const std::string& model);
    void setLaunchAnnounced(int launch_announced);
    void setLaunchStatus(const std::string& launch_status);
    void setBodyDimensions(const std::string& body_dimensions);
    void setBodyWeight(float body_weight);
	void setBodySim(const std::string& body_sim);
    void setDisplayType(const std::string& display_type);
    void setDisplaySize(float display_size);
    void setDisplayResolution(const std::string& display_resolution);
    void setFeaturesSensors(const std::string& features_sensors);
    void setPlatformOs(const std::string& platform_os);

    std::string toString() const;

private:
    std::string oem;
    std::string model;
    int launch_announced;
    std::string launch_status;
    std::string body_dimensions;
    float body_weight;
	std::string body_sim;
    std::string display_type;
    float display_size;
    std::string display_resolution;
    std::string features_sensors;
    std::string platform_os;
};

#endif // CELL_H