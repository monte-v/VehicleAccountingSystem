#include "JsonStorage.h"

bool JsonStorage::save(const QString& fileName, const QVector<Vehicle>& vehicles)
{
	QFile file(fileName);

	if (!file.open(QIODevice::WriteOnly))
		return false;

	QJsonArray jsonArray;

	for (const Vehicle& vehicle : vehicles) 
	{
		QJsonObject jsonObject;

		jsonObject["id"] = vehicle.id;
		jsonObject["type"] = vehicle.type;
		jsonObject["brand"] = vehicle.brand;
		jsonObject["model"] = vehicle.model;
		jsonObject["year"] = vehicle.year;
		jsonObject["weight"] = vehicle.weight;

		jsonArray.append(jsonObject);
	}

	QJsonDocument jsonDocument(jsonArray);

	file.write(jsonDocument.toJson(QJsonDocument::Indented));
	file.close();

	return true;
}

bool JsonStorage::load(const QString& fileName, QVector<Vehicle>& vehicles)
{
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly))
		return false;

	QByteArray data = file.readAll();
	file.close();
	
	QJsonDocument jsonDocument = QJsonDocument::fromJson(data);

	if (!jsonDocument.isArray())
		return false;
	
	vehicles.clear();

	QJsonArray jsonArray = jsonDocument.array();

	for (const QJsonValue& value : jsonArray)
	{
		QJsonObject jsonObject = value.toObject();

		Vehicle vehicle;

		vehicle.id = jsonObject["id"].toInt();
		vehicle.type = jsonObject["type"].toString();
		vehicle.brand = jsonObject["brand"].toString();
		vehicle.model = jsonObject["model"].toString();
		vehicle.year = jsonObject["year"].toInt();
		vehicle.weight= jsonObject["weight"].toDouble();

		vehicles.append(vehicle);
	}

	return true;
}

