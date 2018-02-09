// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef IRIDIUM_QT_IRIDIUMADDRESSVALIDATOR_H
#define IRIDIUM_QT_IRIDIUMADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class IridiumAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit IridiumAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Iridium address widget validator, checks for a valid iridium address.
 */
class IridiumAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit IridiumAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // IRIDIUM_QT_IRIDIUMADDRESSVALIDATOR_H
