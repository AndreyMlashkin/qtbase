/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtTest module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QTAPTESTLOGGER_P_H
#define QTAPTESTLOGGER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtTest/private/qabstracttestlogger_p.h>

QT_BEGIN_NAMESPACE

class QTapTestLogger : public QAbstractTestLogger
{
public:
    QTapTestLogger(const char *filename);
    ~QTapTestLogger();

    void startLogging() override;
    void stopLogging() override;

    void enterTestFunction(const char *) override;
    void leaveTestFunction() override {}

    void enterTestData(QTestData *data) override;

    void addIncident(IncidentTypes type, const char *description,
                     const char *file = nullptr, int line = 0) override;
    void addMessage(MessageTypes type, const QString &message,
                    const char *file = nullptr, int line = 0) override;

    void addBenchmarkResult(const QBenchmarkResult &) override {}
private:
    void outputTestLine(bool ok, int testNumber, const QTestCharBuffer &directive);
    void outputBuffer(const QTestCharBuffer &buffer);
    bool hasMessages() const { return m_comments.constData()[0] || m_messages.constData()[0]; }
    void flushMessages();
    void beginYamlish();
    void endYamlish();
    bool m_wasExpectedFail;
    QTestCharBuffer m_comments;
    QTestCharBuffer m_messages;
    bool m_gatherMessages = false;
};

QT_END_NAMESPACE

#endif // QTAPTESTLOGGER_P_H
