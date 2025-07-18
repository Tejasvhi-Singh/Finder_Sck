/****************************************************************************
** Meta object code from reading C++ file 'MacOSIntegration.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/MacOSIntegration.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MacOSIntegration.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN16MacOSIntegrationE_t {};
} // unnamed namespace

template <> constexpr inline auto MacOSIntegration::qt_create_metaobjectdata<qt_meta_tag_ZN16MacOSIntegrationE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MacOSIntegration",
        "spotlightSearchStarted",
        "",
        "query",
        "spotlightSearchCompleted",
        "QList<SpotlightResult>",
        "results",
        "spotlightSearchCancelled",
        "spotlightSearchProgress",
        "percentage",
        "spotlightSearchError",
        "error",
        "fileSystemEventOccurred",
        "FileSystemEventInfo",
        "event",
        "fileSystemMonitoringStarted",
        "fileSystemMonitoringStopped",
        "fileSystemMonitoringError",
        "quickLookPreviewShown",
        "filePath",
        "quickLookPreviewHidden",
        "workspaceNotificationReceived",
        "type",
        "QHash<QString,QVariant>",
        "info",
        "securityAccessGranted",
        "path",
        "securityAccessDenied",
        "onSpotlightQueryFinished",
        "onFileSystemEventReceived",
        "onWorkspaceNotificationReceived"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'spotlightSearchStarted'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'spotlightSearchCompleted'
        QtMocHelpers::SignalData<void(const QList<SpotlightResult> &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Signal 'spotlightSearchCancelled'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'spotlightSearchProgress'
        QtMocHelpers::SignalData<void(int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Signal 'spotlightSearchError'
        QtMocHelpers::SignalData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Signal 'fileSystemEventOccurred'
        QtMocHelpers::SignalData<void(const FileSystemEventInfo &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 13, 14 },
        }}),
        // Signal 'fileSystemMonitoringStarted'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'fileSystemMonitoringStopped'
        QtMocHelpers::SignalData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'fileSystemMonitoringError'
        QtMocHelpers::SignalData<void(const QString &)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Signal 'quickLookPreviewShown'
        QtMocHelpers::SignalData<void(const QString &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 },
        }}),
        // Signal 'quickLookPreviewHidden'
        QtMocHelpers::SignalData<void()>(20, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'workspaceNotificationReceived'
        QtMocHelpers::SignalData<void(const QString &, const QHash<QString,QVariant> &)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 22 }, { 0x80000000 | 23, 24 },
        }}),
        // Signal 'securityAccessGranted'
        QtMocHelpers::SignalData<void(const QString &)>(25, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 26 },
        }}),
        // Signal 'securityAccessDenied'
        QtMocHelpers::SignalData<void(const QString &)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 26 },
        }}),
        // Slot 'onSpotlightQueryFinished'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onFileSystemEventReceived'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onWorkspaceNotificationReceived'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MacOSIntegration, qt_meta_tag_ZN16MacOSIntegrationE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MacOSIntegration::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16MacOSIntegrationE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16MacOSIntegrationE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16MacOSIntegrationE_t>.metaTypes,
    nullptr
} };

void MacOSIntegration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MacOSIntegration *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->spotlightSearchStarted((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->spotlightSearchCompleted((*reinterpret_cast< std::add_pointer_t<QList<SpotlightResult>>>(_a[1]))); break;
        case 2: _t->spotlightSearchCancelled(); break;
        case 3: _t->spotlightSearchProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->spotlightSearchError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->fileSystemEventOccurred((*reinterpret_cast< std::add_pointer_t<FileSystemEventInfo>>(_a[1]))); break;
        case 6: _t->fileSystemMonitoringStarted(); break;
        case 7: _t->fileSystemMonitoringStopped(); break;
        case 8: _t->fileSystemMonitoringError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->quickLookPreviewShown((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->quickLookPreviewHidden(); break;
        case 11: _t->workspaceNotificationReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QHash<QString,QVariant>>>(_a[2]))); break;
        case 12: _t->securityAccessGranted((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 13: _t->securityAccessDenied((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->onSpotlightQueryFinished(); break;
        case 15: _t->onFileSystemEventReceived(); break;
        case 16: _t->onWorkspaceNotificationReceived(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)(const QString & )>(_a, &MacOSIntegration::spotlightSearchStarted, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)(const QList<SpotlightResult> & )>(_a, &MacOSIntegration::spotlightSearchCompleted, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)()>(_a, &MacOSIntegration::spotlightSearchCancelled, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)(int )>(_a, &MacOSIntegration::spotlightSearchProgress, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)(const QString & )>(_a, &MacOSIntegration::spotlightSearchError, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)(const FileSystemEventInfo & )>(_a, &MacOSIntegration::fileSystemEventOccurred, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)()>(_a, &MacOSIntegration::fileSystemMonitoringStarted, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)()>(_a, &MacOSIntegration::fileSystemMonitoringStopped, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)(const QString & )>(_a, &MacOSIntegration::fileSystemMonitoringError, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)(const QString & )>(_a, &MacOSIntegration::quickLookPreviewShown, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)()>(_a, &MacOSIntegration::quickLookPreviewHidden, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)(const QString & , const QHash<QString,QVariant> & )>(_a, &MacOSIntegration::workspaceNotificationReceived, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)(const QString & )>(_a, &MacOSIntegration::securityAccessGranted, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (MacOSIntegration::*)(const QString & )>(_a, &MacOSIntegration::securityAccessDenied, 13))
            return;
    }
}

const QMetaObject *MacOSIntegration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MacOSIntegration::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16MacOSIntegrationE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MacOSIntegration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MacOSIntegration::spotlightSearchStarted(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void MacOSIntegration::spotlightSearchCompleted(const QList<SpotlightResult> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void MacOSIntegration::spotlightSearchCancelled()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MacOSIntegration::spotlightSearchProgress(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void MacOSIntegration::spotlightSearchError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void MacOSIntegration::fileSystemEventOccurred(const FileSystemEventInfo & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void MacOSIntegration::fileSystemMonitoringStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MacOSIntegration::fileSystemMonitoringStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void MacOSIntegration::fileSystemMonitoringError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}

// SIGNAL 9
void MacOSIntegration::quickLookPreviewShown(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 10
void MacOSIntegration::quickLookPreviewHidden()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void MacOSIntegration::workspaceNotificationReceived(const QString & _t1, const QHash<QString,QVariant> & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1, _t2);
}

// SIGNAL 12
void MacOSIntegration::securityAccessGranted(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 12, nullptr, _t1);
}

// SIGNAL 13
void MacOSIntegration::securityAccessDenied(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 13, nullptr, _t1);
}
QT_WARNING_POP
