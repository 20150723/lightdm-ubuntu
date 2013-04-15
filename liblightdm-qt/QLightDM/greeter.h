/*
 * Copyright (C) 2010-2011 David Edmundson.
 * Copyright (C) 2010-2011 Robert Ancell
 * Author: David Edmundson <kde@davidedmundson.co.uk>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2 or version 3 of the License.
 * See http://www.gnu.org/copyleft/lgpl.html the full text of the license.
 */

#ifndef QLIGHTDM_GREETER_H
#define QLIGHTDM_GREETER_H

#include <QtCore/QObject>
#include <QtCore/QVariant>


namespace QLightDM
{
    class GreeterPrivate;

class Q_DECL_EXPORT Greeter : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(bool authenticated READ isAuthenticated ) //NOTFIY authenticationComplete
    Q_PROPERTY(QString authenticationUser READ authenticationUser )
    Q_PROPERTY(QString defaultSession READ defaultSessionHint CONSTANT)
    Q_PROPERTY(QString selectUser READ selectUserHint CONSTANT)
    Q_PROPERTY(bool selectGuest READ selectGuestHint CONSTANT)

    Q_PROPERTY(QString hostname READ hostname CONSTANT)
    Q_PROPERTY(bool hasGuestAccount READ hasGuestAccountHint CONSTANT)
    Q_PROPERTY(bool locked READ lockHint CONSTANT)
    
    Q_PROPERTY(QString hostname READ hostname CONSTANT)

    Q_ENUMS(PromptType MessageType)

public:
    enum PromptType {
        PromptTypeQuestion,
        PromptTypeSecret
    };

    enum MessageType {
        MessageTypeInfo,
        MessageTypeError
    };

    explicit Greeter(QObject* parent=0);
    virtual ~Greeter();

    QString getHint(const QString &name) const;   
    QString defaultSessionHint() const;
    bool hideUsersHint() const;
    bool showManualLoginHint() const;
    bool showRemoteLoginHint() const;
    bool lockHint () const;
    bool hasGuestAccountHint() const;
    QString selectUserHint() const;
    bool selectGuestHint() const;
    QString autologinUserHint() const;
    bool autologinGuestHint() const;
    int autologinTimeoutHint() const;

    bool inAuthentication() const;
    bool isAuthenticated() const;
    QString authenticationUser() const;
    QString hostname() const;

public Q_SLOTS:
    bool connectSync();
    void authenticate(const QString &username=QString());
    void authenticateAsGuest();
    void authenticateAutologin();
    void authenticateRemote(const QString &session=QString(), const QString &username=QString());
    void respond(const QString &response);
    void cancelAuthentication();
    void setLanguage (const QString &language);
    bool startSessionSync(const QString &session=QString());

Q_SIGNALS:
    void showMessage(QString text, QLightDM::Greeter::MessageType type);
    void showPrompt(QString text, QLightDM::Greeter::PromptType type);
    void authenticationComplete();
    void autologinTimerExpired();

private:
    GreeterPrivate *d_ptr;
    Q_DECLARE_PRIVATE(Greeter)

};
};

#endif // QLIGHTDM_GREETER_H
