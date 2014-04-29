/****************************************************************************
** Meta object code from reading C++ file 'piano.h'
**
** Created: Fri Jul 26 20:44:25 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "piano.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'piano.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_piano[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x08,
      33,    6,    6,    6, 0x08,
      59,    6,    6,    6, 0x08,
      85,    6,    6,    6, 0x08,
     111,    6,    6,    6, 0x08,
     137,    6,    6,    6, 0x08,
     163,    6,    6,    6, 0x08,
     189,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_piano[] = {
    "piano\0\0on_pushButton_1_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_3_clicked()\0"
    "on_pushButton_4_clicked()\0"
    "on_pushButton_5_clicked()\0"
    "on_pushButton_6_clicked()\0"
    "on_pushButton_7_clicked()\0"
    "on_pushButton_record_clicked()\0"
};

const QMetaObject piano::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_piano,
      qt_meta_data_piano, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &piano::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *piano::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *piano::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_piano))
        return static_cast<void*>(const_cast< piano*>(this));
    return QDialog::qt_metacast(_clname);
}

int piano::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButton_1_clicked(); break;
        case 1: on_pushButton_2_clicked(); break;
        case 2: on_pushButton_3_clicked(); break;
        case 3: on_pushButton_4_clicked(); break;
        case 4: on_pushButton_5_clicked(); break;
        case 5: on_pushButton_6_clicked(); break;
        case 6: on_pushButton_7_clicked(); break;
        case 7: on_pushButton_record_clicked(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
