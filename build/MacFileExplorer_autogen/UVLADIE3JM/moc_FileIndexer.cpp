/****************************************************************************
** Meta object code from reading C++ file 'FileIndexer.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/FileIndexer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileIndexer.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11FileIndexerE_t {};
} // unnamed namespace

template <> constexpr inline auto FileIndexer::qt_create_metaobjectdata<qt_meta_tag_ZN11FileIndexerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "FileIndexer",
        "indexingStarted",
        "",
        "indexingProgress",
        "percentage",
        "indexingCompleted",
        "indexingPaused",
        "indexingResumed",
        "indexingStopped",
        "indexingError",
        "error",
        "fileIndexed",
        "IndexedFile",
        "file",
        "onIndexingFinished"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'indexingStarted'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'indexingProgress'
        QtMocHelpers::SignalData<void(int)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 4 },
        }}),
        // Signal 'indexingCompleted'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'indexingPaused'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'indexingResumed'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'indexingStopped'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'indexingError'
        QtMocHelpers::SignalData<void(const QString &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 10 },
        }}),
        // Signal 'fileIndexed'
        QtMocHelpers::SignalData<void(const IndexedFile &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 13 },
        }}),
        // Slot 'onIndexingFinished'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<FileIndexer, qt_meta_tag_ZN11FileIndexerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject FileIndexer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11FileIndexerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11FileIndexerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11FileIndexerE_t>.metaTypes,
    nullptr
} };

void FileIndexer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FileIndexer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->indexingStarted(); break;
        case 1: _t->indexingProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->indexingCompleted(); break;
        case 3: _t->indexingPaused(); break;
        case 4: _t->indexingResumed(); break;
        case 5: _t->indexingStopped(); break;
        case 6: _t->indexingError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->fileIndexed((*reinterpret_cast< std::add_pointer_t<IndexedFile>>(_a[1]))); break;
        case 8: _t->onIndexingFinished(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (FileIndexer::*)()>(_a, &FileIndexer::indexingStarted, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (FileIndexer::*)(int )>(_a, &FileIndexer::indexingProgress, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (FileIndexer::*)()>(_a, &FileIndexer::indexingCompleted, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (FileIndexer::*)()>(_a, &FileIndexer::indexingPaused, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (FileIndexer::*)()>(_a, &FileIndexer::indexingResumed, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (FileIndexer::*)()>(_a, &FileIndexer::indexingStopped, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (FileIndexer::*)(const QString & )>(_a, &FileIndexer::indexingError, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (FileIndexer::*)(const IndexedFile & )>(_a, &FileIndexer::fileIndexed, 7))
            return;
    }
}

const QMetaObject *FileIndexer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileIndexer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11FileIndexerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FileIndexer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void FileIndexer::indexingStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FileIndexer::indexingProgress(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void FileIndexer::indexingCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void FileIndexer::indexingPaused()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void FileIndexer::indexingResumed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void FileIndexer::indexingStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void FileIndexer::indexingError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void FileIndexer::fileIndexed(const IndexedFile & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}
QT_WARNING_POP
