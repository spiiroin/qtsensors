/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
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
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QDebug>
#include <QTimer>
#include <QFile>

#include "qsimulatorrecognizer.h"
#include "simulatorgesturescommon.h"

QSimulatorSensorGestureRecognizer::QSimulatorSensorGestureRecognizer(QObject *parent)
    : QSensorGestureRecognizer(parent)
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));

    timer->setInterval(1000);
}

QSimulatorSensorGestureRecognizer::~QSimulatorSensorGestureRecognizer()
{
    if (timer->isActive())
        timer->stop();
}

void QSimulatorSensorGestureRecognizer::create()
{
    SensorGesturesConnection *connection =  new SensorGesturesConnection(this);
    connect(connection,SIGNAL(sensorGestureDetected()),this,SLOT(sensorGestureDetected()));
}

void QSimulatorSensorGestureRecognizer::sensorGestureDetected()
{
    detectingState = true;
}


bool QSimulatorSensorGestureRecognizer::start()
{
    timer->start();
    timeout();
    return timer->isActive();
}

bool QSimulatorSensorGestureRecognizer::stop()
{
    timer->stop();
    return timer->isActive();
}


bool QSimulatorSensorGestureRecognizer::isActive()
{
    return timer->isActive();
}

QString QSimulatorSensorGestureRecognizer::id() const
{
    return QString("QtSensors.simulator");
}

void QSimulatorSensorGestureRecognizer::timeout()
{
    if (detectingState) {
        QString str = get_qtSensorGestureData();
        emit detected(str);
        detectingState = false;
    }
}
