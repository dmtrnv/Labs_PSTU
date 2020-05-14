#pragma once
#include <string>
#include <iostream>


class Route
{
private:
	std::string departurePoint;
	std::string arrivalPoint;
	float travelTime;

public:
	Route();
	Route(const std::string &pointA, const std::string &pointB, const float &time);
	Route(const Route &r);
	~Route();
	std::string getDeparturePoint() const;
	void setDeparturePoint(const std::string &point);
	std::string GetArrivalPoint() const;
	void setArrivalPoint(const std::string &point);
	float getTravelTime() const;
	void setTravelTime(const float &time);
	void show() const;
};

