/****************************************************************************
**
** Copyright (C) 2012 Research In Motion
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "bbaccelerometer.h"
#include "bbaltimeter.h"
#include "bbambientlightsensor.h"
#include "bbcompass.h"
#include "bbgyroscope.h"
#include "bbirproximitysensor.h"
#include "bblightsensor.h"
#include "bbmagnetometer.h"
#include "bborientationsensor.h"
#include "bbpressuresensor.h"
#include "bbproximitysensor.h"
#include "bbrotationsensor.h"
#include "bbtemperaturesensor.h"
#include "bbguihelper.h"

#include <qsensormanager.h>
#include <qsensorplugin.h>

static const char *bbAccelerometerId = "bbAccelerometer";
static const char *bbAltitmeterId = "bbAltimeter";
static const char *bbAmbientLightSensorId = "bbAmbientLightSensor";
static const char *bbCompassId = "bbCompass";
static const char *bbGyroscopeId = "bbGyroscope";
static const char *bbIRProximitySensorId = "bbIRProximitySensor";
static const char *bbLightSensorId = "bbLightSensor";
static const char *bbMagnetometerId = "bbMagnetometer";
static const char *bbOrientationSensorId = "bbOrientationSensor";
static const char *bbPressureSensorId = "bbPressureSensor";
static const char *bbProximitySensorId = "bbProximitySensor";
static const char *bbRotationSensorId = "bbRotationSensor";
static const char *bbTemperatureSensorId = "bbTemperatureSensor";

class BbSensorPlugin : public QObject, public QSensorPluginInterface, public QSensorBackendFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.nokia.Qt.QSensorPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(QSensorPluginInterface)

public:
    void registerSensors() Q_DECL_OVERRIDE
    {
        if (sensorSupported(BbAccelerometer::devicePath()))
            QSensorManager::registerBackend(QAccelerometer::type, bbAccelerometerId, this);
        if (sensorSupported(BbAltimeter::devicePath()))
            QSensorManager::registerBackend("BbAltimeter", bbAltitmeterId, this);
        if (sensorSupported(BbAmbientLightSensor::devicePath()))
            QSensorManager::registerBackend(QAmbientLightSensor::type, bbAmbientLightSensorId, this);
        if (sensorSupported(BbCompass::devicePath()))
            QSensorManager::registerBackend(QCompass::type, bbCompassId, this);
        if (sensorSupported(BbGyroscope::devicePath()))
            QSensorManager::registerBackend(QGyroscope::type, bbGyroscopeId, this);
        if (sensorSupported(BbIRProximitySensor::devicePath()))
            QSensorManager::registerBackend(QIRProximitySensor::type, bbIRProximitySensorId, this);
        if (sensorSupported(BbLightSensor::devicePath()))
            QSensorManager::registerBackend(QLightSensor::type, bbLightSensorId, this);
        if (sensorSupported(BbMagnetometer::devicePath()))
            QSensorManager::registerBackend(QMagnetometer::type, bbMagnetometerId, this);
        if (sensorSupported(BbOrientationSensor::devicePath()))
            QSensorManager::registerBackend(QOrientationSensor::type, bbOrientationSensorId, this);
        if (sensorSupported(BbPressureSensor::devicePath()))
            QSensorManager::registerBackend("BbPressureSensor", bbPressureSensorId, this);
        if (sensorSupported(BbProximitySensor::devicePath()))
            QSensorManager::registerBackend(QProximitySensor::type, bbProximitySensorId, this);
        if (sensorSupported(BbRotationSensor::devicePath()))
            QSensorManager::registerBackend(QRotationSensor::type, bbRotationSensorId, this);
        if (sensorSupported(BbTemperatureSensor::devicePath()))
            QSensorManager::registerBackend("BbTemperatureSensor", bbTemperatureSensorId, this);
    }

    QSensorBackend *createBackend(QSensor *sensor) Q_DECL_OVERRIDE
    {
        BbSensorBackendBase *backend = 0;
        if (sensor->identifier() == bbAccelerometerId)
            backend = new BbAccelerometer(sensor);
        if (sensor->identifier() == bbAltitmeterId)
            backend = new BbAltimeter(sensor);
        if (sensor->identifier() == bbAmbientLightSensorId)
            backend = new BbAmbientLightSensor(sensor);
        if (sensor->identifier() == bbCompassId)
            backend = new BbCompass(sensor);
        if (sensor->identifier() == bbGyroscopeId)
            backend = new BbGyroscope(sensor);
        if (sensor->identifier() == bbIRProximitySensorId)
            backend = new BbIRProximitySensor(sensor);
        if (sensor->identifier() == bbLightSensorId)
            backend = new BbLightSensor(sensor);
        if (sensor->identifier() == bbMagnetometerId)
            backend = new BbMagnetometer(sensor);
        if (sensor->identifier() == bbOrientationSensorId)
            backend = new BbOrientationSensor(sensor);
        if (sensor->identifier() == bbPressureSensorId)
            backend = new BbPressureSensor(sensor);
        if (sensor->identifier() == bbProximitySensorId)
            backend = new BbProximitySensor(sensor);
        if (sensor->identifier() == bbRotationSensorId)
            backend = new BbRotationSensor(sensor);
        if (sensor->identifier() == bbTemperatureSensorId)
            backend = new BbTemperatureSensor(sensor);
        backend->initSensorInfo();
        backend->setGuiHelper(&m_guiHelper);
        return backend;
    }

private:
    bool sensorSupported(const QString &devicePath)
    {
        return QFile::exists(devicePath);
    }

    BbGuiHelper m_guiHelper;
};

#include "main.moc"
