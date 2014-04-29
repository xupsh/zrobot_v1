/****************************************************************************
** Meta object code from reading C++ file 'scores.h'
**
** Created: Sat Jul 27 13:24:26 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "scores.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scores.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_scores[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      37,    7,    7,    7, 0x08,
      73,   67,    7,    7, 0x08,
      96,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_scores[] = {
    "scores\0\0on_pushButton_file_clicked()\0"
    "on_pushButton_score_clicked()\0event\0"
    "timerout(QTimerEvent*)\0showresult()\0"
};

const QMetaObject scores::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_scores,
      qt_meta_data_scores, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &scores::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *scores::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *scores::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_scores))
        return static_cast<void*>(const_cast< scores*>(this));
    return QDialog::qt_metacast(_clname);
}

int scores::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButton_file_clicked(); break;
        case 1: on_pushButton_score_clicked(); break;
        case 2: timerout((*reinterpret_cast< QTimerEvent*(*)>(_a[1]))); break;
        case 3: showresult(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
