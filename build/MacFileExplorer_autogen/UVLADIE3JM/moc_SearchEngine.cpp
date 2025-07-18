/****************************************************************************
** Meta object code from reading C++ file 'SearchEngine.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/SearchEngine.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SearchEngine.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12SearchEngineE_t {};
} // unnamed namespace

template <> constexpr inline auto SearchEngine::qt_create_metaobjectdata<qt_meta_tag_ZN12SearchEngineE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SearchEngine",
        "searchStarted",
        "",
        "query",
        "searchCompleted",
        "QList<SearchResult>",
        "results",
        "searchCancelled",
        "searchProgress",
        "percentage",
        "searchError",
        "error",
        "indexingProgress",
        "indexingCompleted",
        "resultFound",
        "SearchResult",
        "result",
        "onSearchFinished",
        "onIndexingFinished",
        "onSearchWorkerFinished"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'searchStarted'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'searchCompleted'
        QtMocHelpers::SignalData<void(const QList<SearchResult> &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Signal 'searchCancelled'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'searchProgress'
        QtMocHelpers::SignalData<void(int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Signal 'searchError'
        QtMocHelpers::SignalData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Signal 'indexingProgress'
        QtMocHelpers::SignalData<void(int)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Signal 'indexingCompleted'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'resultFound'
        QtMocHelpers::SignalData<void(const SearchResult &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 15, 16 },
        }}),
        // Slot 'onSearchFinished'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onIndexingFinished'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSearchWorkerFinished'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SearchEngine, qt_meta_tag_ZN12SearchEngineE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SearchEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12SearchEngineE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12SearchEngineE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12SearchEngineE_t>.metaTypes,
    nullptr
} };

void SearchEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SearchEngine *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->searchStarted((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->searchCompleted((*reinterpret_cast< std::add_pointer_t<QList<SearchResult>>>(_a[1]))); break;
        case 2: _t->searchCancelled(); break;
        case 3: _t->searchProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->searchError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->indexingProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->indexingCompleted(); break;
        case 7: _t->resultFound((*reinterpret_cast< std::add_pointer_t<SearchResult>>(_a[1]))); break;
        case 8: _t->onSearchFinished(); break;
        case 9: _t->onIndexingFinished(); break;
        case 10: _t->onSearchWorkerFinished(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SearchEngine::*)(const QString & )>(_a, &SearchEngine::searchStarted, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (SearchEngine::*)(const QList<SearchResult> & )>(_a, &SearchEngine::searchCompleted, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (SearchEngine::*)()>(_a, &SearchEngine::searchCancelled, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (SearchEngine::*)(int )>(_a, &SearchEngine::searchProgress, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (SearchEngine::*)(const QString & )>(_a, &SearchEngine::searchError, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (SearchEngine::*)(int )>(_a, &SearchEngine::indexingProgress, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (SearchEngine::*)()>(_a, &SearchEngine::indexingCompleted, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (SearchEngine::*)(const SearchResult & )>(_a, &SearchEngine::resultFound, 7))
            return;
    }
}

const QMetaObject *SearchEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12SearchEngineE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SearchEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void SearchEngine::searchStarted(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void SearchEngine::searchCompleted(const QList<SearchResult> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void SearchEngine::searchCancelled()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SearchEngine::searchProgress(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void SearchEngine::searchError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void SearchEngine::indexingProgress(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void SearchEngine::indexingCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void SearchEngine::resultFound(const SearchResult & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}
QT_WARNING_POP
