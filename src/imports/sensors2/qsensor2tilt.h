/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSEONSOR2TILT_H
#define QSEONSOR2TILT_H

#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>
#include <qaccelerometer.h>
#include "qsensor2common.h"

QT_BEGIN_NAMESPACE

class QSensor2Tilt : public qsensor2common, public QAccelerometerFilter
{
    Q_OBJECT
    Q_ENUMS(Unit Speed)
    Q_PROPERTY(qreal yRotation READ yRotation NOTIFY yRotationChanged)
    Q_PROPERTY(qreal xRotation READ xRotation NOTIFY xRotationChanged)
    Q_PROPERTY(Unit unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(Speed speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(qreal accuracy READ accuracy WRITE setAccuracy NOTIFY accuracyChanged)
    Q_PROPERTY(QByteArray settings READ settings WRITE setSettings)

public:
    QSensor2Tilt(QObject* parent = 0);
    virtual ~QSensor2Tilt();
    Q_INVOKABLE void calibrate();

    enum Unit{
        Radians = 0
        , Degrees
    };

    enum Speed{
        Slow = 0
        , Medium
        , Fast
    };


Q_SIGNALS:
    void unitChanged();
    void yRotationChanged();
    void xRotationChanged();
    void speedChanged();
    void tiltChanged(qreal deltaX, qreal deltaY);
    void accuracyChanged();

public:
    // Override of QAcclerometerFilter::filter(QAccelerometerReading*)
    qreal yRotation();
    qreal xRotation();
    Unit unit();
    void setUnit(const Unit val);
    Speed speed();
    void setSpeed(const Speed val);
    void setEnabled(bool val);
    qreal accuracy();
    void setAccuracy(const qreal val);
    QByteArray settings() const;
    void setSettings(const QByteArray val);
    void createRunModeDataRateMap();
    QMap<Speed, int> dataRate();

private:
    bool filter(QAccelerometerReading* reading);

    QSensor *sensor() { return _accel; }
    QAccelerometer* _accel;
    qreal _yRotation;
    qreal _xRotation;
    qreal _radAccuracy;
    Unit _unit;
    qreal _pitch;
    qreal _roll;
    qreal _calibratedPitch;
    qreal _calibratedRoll;
    QMap<Speed, int> _dataRate;
    Speed _speed;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QSensor2Tilt)

#endif // QSEONSOR2TILT_H
