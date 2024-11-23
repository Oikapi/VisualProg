/****************************************************************************
** Meta object code from reading C++ file 'graphicseditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Lab_5/graphicseditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphicseditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GraphicsEditor_t {
    QByteArrayData data[30];
    char stringdata0[422];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphicsEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphicsEditor_t qt_meta_stringdata_GraphicsEditor = {
    {
QT_MOC_LITERAL(0, 0, 14), // "GraphicsEditor"
QT_MOC_LITERAL(1, 15, 12), // "editorClosed"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 22), // "on_BackColor_triggered"
QT_MOC_LITERAL(4, 52, 19), // "on_SetPen_triggered"
QT_MOC_LITERAL(5, 72, 18), // "on_Clear_triggered"
QT_MOC_LITERAL(6, 91, 10), // "setupWalls"
QT_MOC_LITERAL(7, 102, 19), // "updateWallPositions"
QT_MOC_LITERAL(8, 122, 22), // "on_AddFigure_triggered"
QT_MOC_LITERAL(9, 145, 8), // "addShape"
QT_MOC_LITERAL(10, 154, 9), // "shapeType"
QT_MOC_LITERAL(11, 164, 4), // "rect"
QT_MOC_LITERAL(12, 169, 9), // "fillColor"
QT_MOC_LITERAL(13, 179, 14), // "Qt::BrushStyle"
QT_MOC_LITERAL(14, 194, 10), // "brushStyle"
QT_MOC_LITERAL(15, 205, 11), // "strokeColor"
QT_MOC_LITERAL(16, 217, 11), // "strokeWidth"
QT_MOC_LITERAL(17, 229, 25), // "on_DeleteFigure_triggered"
QT_MOC_LITERAL(18, 255, 11), // "drawGordeew"
QT_MOC_LITERAL(19, 267, 13), // "groupSetFlags"
QT_MOC_LITERAL(20, 281, 19), // "QGraphicsItemGroup*"
QT_MOC_LITERAL(21, 301, 5), // "group"
QT_MOC_LITERAL(22, 307, 12), // "textSetFlags"
QT_MOC_LITERAL(23, 320, 18), // "QGraphicsTextItem*"
QT_MOC_LITERAL(24, 339, 4), // "item"
QT_MOC_LITERAL(25, 344, 18), // "stringToBrushStyle"
QT_MOC_LITERAL(26, 363, 8), // "styleStr"
QT_MOC_LITERAL(27, 372, 18), // "createMovingObject"
QT_MOC_LITERAL(28, 391, 10), // "moveObject"
QT_MOC_LITERAL(29, 402, 19) // "on_Eraser_triggered"

    },
    "GraphicsEditor\0editorClosed\0\0"
    "on_BackColor_triggered\0on_SetPen_triggered\0"
    "on_Clear_triggered\0setupWalls\0"
    "updateWallPositions\0on_AddFigure_triggered\0"
    "addShape\0shapeType\0rect\0fillColor\0"
    "Qt::BrushStyle\0brushStyle\0strokeColor\0"
    "strokeWidth\0on_DeleteFigure_triggered\0"
    "drawGordeew\0groupSetFlags\0QGraphicsItemGroup*\0"
    "group\0textSetFlags\0QGraphicsTextItem*\0"
    "item\0stringToBrushStyle\0styleStr\0"
    "createMovingObject\0moveObject\0"
    "on_Eraser_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicsEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    6,  101,    2, 0x08 /* Private */,
      17,    0,  114,    2, 0x08 /* Private */,
      18,    0,  115,    2, 0x08 /* Private */,
      19,    1,  116,    2, 0x08 /* Private */,
      22,    1,  119,    2, 0x08 /* Private */,
      25,    1,  122,    2, 0x08 /* Private */,
      27,    0,  125,    2, 0x08 /* Private */,
      28,    0,  126,    2, 0x08 /* Private */,
      29,    0,  127,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QRectF, QMetaType::QColor, 0x80000000 | 13, QMetaType::QColor, QMetaType::Int,   10,   11,   12,   14,   15,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 23,   24,
    0x80000000 | 13, QMetaType::QString,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GraphicsEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GraphicsEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editorClosed(); break;
        case 1: _t->on_BackColor_triggered(); break;
        case 2: _t->on_SetPen_triggered(); break;
        case 3: _t->on_Clear_triggered(); break;
        case 4: _t->setupWalls(); break;
        case 5: _t->updateWallPositions(); break;
        case 6: _t->on_AddFigure_triggered(); break;
        case 7: _t->addShape((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QRectF(*)>(_a[2])),(*reinterpret_cast< QColor(*)>(_a[3])),(*reinterpret_cast< Qt::BrushStyle(*)>(_a[4])),(*reinterpret_cast< QColor(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 8: _t->on_DeleteFigure_triggered(); break;
        case 9: _t->drawGordeew(); break;
        case 10: _t->groupSetFlags((*reinterpret_cast< QGraphicsItemGroup*(*)>(_a[1]))); break;
        case 11: _t->textSetFlags((*reinterpret_cast< QGraphicsTextItem*(*)>(_a[1]))); break;
        case 12: { Qt::BrushStyle _r = _t->stringToBrushStyle((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Qt::BrushStyle*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->createMovingObject(); break;
        case 14: _t->moveObject(); break;
        case 15: _t->on_Eraser_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsTextItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GraphicsEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GraphicsEditor::editorClosed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GraphicsEditor::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_GraphicsEditor.data,
    qt_meta_data_GraphicsEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GraphicsEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicsEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicsEditor.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int GraphicsEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void GraphicsEditor::editorClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
