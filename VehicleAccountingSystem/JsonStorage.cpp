#include "JsonStorage.h"

bool JsonStorage::save(const QString& fileName,
	const QVector<std::shared_ptr<Vehicle>>& vehicles)
{
	QFile file(fileName);

	if (!file.open(QIODevice::WriteOnly))
		return false;

	QJsonArray jsonArray;

	for (const auto& vehicle : vehicles)
	{
		QJsonObject jsonObject;

		jsonObject["id"] = vehicle->getId();
		jsonObject["type"] = vehicle->getType();
		jsonObject["brand"] = vehicle->getBrand();
		jsonObject["model"] = vehicle->getModel();
		jsonObject["year"] = vehicle->getYear();
		jsonObject["weight"] = vehicle->getWeight();

		jsonArray.append(jsonObject);
	}

	QJsonDocument jsonDocument(jsonArray);

	file.write(jsonDocument.toJson(QJsonDocument::Indented));
	file.close();

	return true;
}

bool JsonStorage::load(const QString& fileName,
	QVector<std::shared_ptr<Vehicle>>& vehicles)
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

		QString type = jsonObject["type"].toString().trimmed();

		std::shared_ptr<Vehicle> vehicle;

		// пока только Car
		if (type == "Автомобиль")
		{
			vehicle = std::make_shared<Car>(
				jsonObject["id"].toInt(),
				jsonObject["brand"].toString(),
				jsonObject["model"].toString(),
				jsonObject["year"].toInt(),
				jsonObject["weight"].toDouble()
			);
		}
		else
		{
			vehicle = std::make_shared<Car>(
				jsonObject["id"].toInt(),
				jsonObject["brand"].toString(),
				jsonObject["model"].toString(),
				jsonObject["year"].toInt(),
				jsonObject["weight"].toDouble()
			);
		}

		vehicles.append(vehicle);
	}

	return true;
}

