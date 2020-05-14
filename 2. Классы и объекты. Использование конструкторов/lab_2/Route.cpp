#include "Route.h"


Route::Route()
{
	std::cout << "Вызван конструктор без параметров для объекта " << this << std::endl;

	departurePoint = "";
	arrivalPoint = "";
	travelTime = 0.0;
}

Route::Route(const std::string &pointA, const std::string &pointB, const float &time)
{
	std::cout << "Вызван конструктор с параметрами для объекта " << this << std::endl;

	departurePoint = pointA;
	arrivalPoint = pointB;
	travelTime = time;
}

Route::Route(const Route &r)
{
	std::cout << "Вызван конструктор копирования для объекта " << this << std::endl;

	departurePoint = r.departurePoint;
	arrivalPoint = r.arrivalPoint;
	travelTime = r.travelTime;
}

Route::~Route()
{
	std::cout << "Вызван деструктор для объекта " << this << std::endl;
}

std::string Route::getDeparturePoint() const
{
	return departurePoint;
}

void Route::setDeparturePoint(const std::string &point)
{
	departurePoint = point;
}

std::string Route::GetArrivalPoint() const
{
	return arrivalPoint;
}

void Route::setArrivalPoint(const std::string &point)
{
	arrivalPoint = point;
}

float Route::getTravelTime() const
{
	return travelTime;
}

void Route::setTravelTime(const float &time)
{
	travelTime = time;
}

void Route::show() const
{
	std::cout << "Пункт отправления: " << departurePoint << std::endl;
	std::cout << "Пункт назначения: " << arrivalPoint << std::endl;
	std::cout << "Время в пути: " << travelTime << std::endl;
}