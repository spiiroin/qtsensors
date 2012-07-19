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
#ifndef BBROTATIONSENSOR_H
#define BBROTATIONSENSOR_H

#include "bbsensorbackend.h"
#include <qrotationsensor.h>

class BbRotationSensor : public BbSensorBackend<QRotationReading>
{
    Q_OBJECT

public:
    explicit BbRotationSensor(QSensor *sensor);

    static QString devicePath();

    void setGuiHelper(BbGuiHelper *guiHelper) Q_DECL_OVERRIDE;

protected:
    void additionalDeviceInit() Q_DECL_OVERRIDE;
    bool addDefaultRange() Q_DECL_OVERRIDE;
    qreal convertValue(float bbValue) Q_DECL_OVERRIDE;
    bool updateReadingFromEvent(const sensor_event_t &event, QRotationReading *reading) Q_DECL_OVERRIDE;
    bool isAutoAxisRemappingEnabled() const;

private slots:
    void updateOrientation();

private:
    float m_mappingMatrix[4];
};

#endif
