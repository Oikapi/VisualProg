#include "graphicseditor.h"
#include "ui_graphicseditor.h"
#include <QMediaPlayer>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QRandomGenerator>
#include <QPropertyAnimation>

GraphicsEditor::GraphicsEditor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GraphicsEditor), currentColor(Qt::white),
      currentPen(Qt::black), topWall(nullptr), bottomWall(nullptr),
      leftWall(nullptr), rightWall(nullptr), collisionSound("D:/Downloads/VisualProg/Lab_5/stuck.wav") {
  ui->setupUi(this);

  scene = new QGraphicsScene(this);
  view = new GraphicsView(scene, this);
  setCentralWidget(view);
  view->setRenderHint(QPainter::Antialiasing);
  view->setRenderHint(QPainter::SmoothPixmapTransform);
  view->setAlignment(Qt::AlignTop |
                     Qt::AlignLeft); // Выравнивание области просмотра
  view->setHorizontalScrollBarPolicy(
      Qt::ScrollBarAlwaysOn); // Включаем горизонтальную полосу прокрутки
  view->setVerticalScrollBarPolicy(
      Qt::ScrollBarAlwaysOn); // Включаем вертикальную полосу прокрутки
                              // Устанавливаем наш view как центральный виджет

  connect(view, &GraphicsView::viewportChanged, this,
          &GraphicsEditor::updateWallPositions);
  connect(
      view, &GraphicsView::resized, this,
      &GraphicsEditor::setupWalls); // Подключение сигнала resized к setupWalls
  setupWalls();

  drawGordeew();
  drawSheiko();
  createMovingObject();

  //         Таймер для перемещения объекта
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, [this]() {
    moveObject(); // Функция перемещения и обнаружения столкновений
  });
  timer->start(30); // Интервал обновления, например, 30 мс
}

GraphicsEditor::~GraphicsEditor() { delete ui; }

void GraphicsEditor::closeEvent(QCloseEvent *event) {
  // Удаление всех движущихся объектов
  for (QGraphicsItemGroup *itemGroup : movingItemGroups) {
    QList<QGraphicsItem *> children = itemGroup->childItems();
    for (QGraphicsItem *child : children) {
      scene->removeItem(child);
      delete child;
    }
    scene->removeItem(itemGroup);
    delete itemGroup;
  }
  movingItemGroups.clear();
  velocities.clear();

  // Останавливаем звук
  collisionSound.stop();

  emit editorClosed();
  QMainWindow::closeEvent(event);
}
void GraphicsEditor::on_BackColor_triggered() {
  QColor color =
      QColorDialog::getColor(currentColor, this, "Choose Background Color");

  if (color.isValid()) {
    scene->setBackgroundBrush(color);
    currentColor = color;
  }
}

void GraphicsEditor::createMovingObject() {
  // Создание частей тела человека
  QGraphicsEllipseItem *head = new QGraphicsEllipseItem(40, 0, 30, 30);
  head->setBrush(Qt::lightGray); // Голова

  QGraphicsRectItem *torso = new QGraphicsRectItem(35, 30, 40, 60);
  torso->setBrush(Qt::darkGray); // Торс

  QGraphicsLineItem *leftArm = new QGraphicsLineItem(35, 40, 15, 70);
  leftArm->setPen(QPen(Qt::darkGray, 4)); // Левая рука

  QGraphicsLineItem *rightArm = new QGraphicsLineItem(75, 40, 95, 70);
  rightArm->setPen(QPen(Qt::darkGray, 4)); // Правая рука

  QGraphicsLineItem *leftLeg = new QGraphicsLineItem(40, 90, 30, 130);
  leftLeg->setPen(QPen(Qt::darkGray, 4)); // Левая нога

  QGraphicsLineItem *rightLeg = new QGraphicsLineItem(70, 90, 80, 130);
  rightLeg->setPen(QPen(Qt::darkGray, 4)); // Правая нога

  // Группируем фигуры в один объект
  QGraphicsItemGroup *human = new QGraphicsItemGroup();
  human->addToGroup(head);
  human->addToGroup(torso);
  human->addToGroup(leftArm);
  human->addToGroup(rightArm);
  human->addToGroup(leftLeg);
  human->addToGroup(rightLeg);

  // Устанавливаем свойства и добавляем на сцену
  human->setFlag(QGraphicsItem::ItemIsSelectable, true);
  scene->addItem(human);

  human->setPos(400, 500); // Начальная позиция объекта

  // Добавляем объект и его начальную скорость в соответствующие списки
  movingItemGroups.append(human);
  velocities.append(QPointF(2, 2)); // Скорость по осям X и Y

  // Создание элементов телефона
  QGraphicsRectItem *phoneBody = new QGraphicsRectItem(20, 20, 50, 100);
  phoneBody->setBrush(Qt::darkGray); // Корпус телефона

  QGraphicsRectItem *screen = new QGraphicsRectItem(25, 30, 40, 60);
  screen->setBrush(Qt::lightGray); // Экран

  QGraphicsEllipseItem *homeButton = new QGraphicsEllipseItem(35, 95, 20, 10);
  homeButton->setBrush(Qt::black); // Кнопка "Home"

  QGraphicsRectItem *speaker = new QGraphicsRectItem(35, 22, 20, 5);
  speaker->setBrush(Qt::black); // Динамик

  // Группируем фигуры в один объект
  QGraphicsItemGroup *phone = new QGraphicsItemGroup();
  phone->addToGroup(phoneBody);
  phone->addToGroup(screen);
  phone->addToGroup(homeButton);
  phone->addToGroup(speaker);

  // Устанавливаем свойства и добавляем на сцену
  phone->setFlag(QGraphicsItem::ItemIsSelectable, true);
  scene->addItem(phone);

  phone->setPos(400, 500); // Начальная позиция объекта

  // Добавляем объект и его начальную скорость в соответствующие списки
  movingItemGroups.append(phone);
  velocities.append(QPointF(2, 2)); // Скорость по осям X и Y
}

// void GraphicsEditor::moveObject()
//{
//     int wallThickness = 10;

//    for (int i = 0; i < movingItemGroups.size(); ++i) {
//        QGraphicsItemGroup *itemGroup = movingItemGroups[i];
//        QPointF velocity = velocities[i];
//        QPointF newPos = itemGroup->pos() + velocity;

//        QRectF boundingRect = itemGroup->boundingRect();
//        qreal left = newPos.x();
//        qreal right = newPos.x() + boundingRect.width();
//        qreal top = newPos.y();
//        qreal bottom = newPos.y() + boundingRect.height();

//        bool wallCollision = false;

//        // Check for wall collisions
//        if (left <= wallThickness) {
//            velocity.setX(-velocity.x());
//            wallCollision = true;
//            collisionSound.play();
//        } else if (right >= view->viewport()->width() - 2 * wallThickness) {
//            velocity.setX(-velocity.x());
//            wallCollision = true;
//            collisionSound.play();
//        }

//        if (top <= wallThickness) {
//            velocity.setY(-velocity.y());
//            wallCollision = true;
//            collisionSound.play();
//        } else if (bottom >= view->viewport()->height() - wallThickness) {
//            velocity.setY(-velocity.y());
//            wallCollision = true;
//            collisionSound.play();
//        }

//        // Check for object collisions only if there’s no wall collision
//        if (!wallCollision) {
//            QList<QGraphicsItem *> itemsAtNewPos = scene->items(QRectF(newPos,
//            boundingRect.size())); for (QGraphicsItem *otherItem :
//            itemsAtNewPos) {
//                if (otherItem != itemGroup && otherItem->data(0) != "user") {
//                    QRectF otherBoundingRect =
//                    otherItem->boundingRect().translated(otherItem->pos());

//                    if (right > otherBoundingRect.left() && left <
//                    otherBoundingRect.right()) {
//                        velocity.setX(-velocity.x());
//                        collisionSound.play();
//                        break; // Collision detected, stop checking further
//                    }

//                    if (bottom > otherBoundingRect.top() && top <
//                    otherBoundingRect.bottom()) {
//                        velocity.setY(-velocity.y());
//                        collisionSound.play();
//                        break; // Collision detected, stop checking further
//                    }
//                }
//            }
//        }

//        // Update the position and velocity of the object
//        itemGroup->setPos(itemGroup->pos() + velocity);
//        velocities[i] = velocity;
//    }
//}

void GraphicsEditor::moveObject() {
  int wallThickness = 10;

  for (int i = 0; i < movingItemGroups.size(); ++i) {
    QGraphicsItemGroup *itemGroup = movingItemGroups[i];
    QPointF velocity = velocities[i];
    QPointF newPos = itemGroup->pos() + velocity;

    // Проверка столкновения с левой и правой стенами
    QRectF boundingRect = itemGroup->boundingRect();
    qreal left = newPos.x() + boundingRect.width();
    qreal right = newPos.x() + boundingRect.width();
    qreal top = newPos.y() + boundingRect.height();
    qreal bottom = newPos.y() + boundingRect.height();

    // Проверка столкновения с левой и правой стенами
    if (left <= wallThickness) {
      velocity.setX(-velocity.x());
      collisionSound.play();
    } else if (right >= view->viewport()->width() - 2 * wallThickness) {
      velocity.setX(-velocity.x());
      collisionSound.play();
    }

    // Проверка столкновения с верхней и нижней стенами
    if (top <= wallThickness) {
      velocity.setY(-velocity.y());
      collisionSound.play();
    } else if (bottom >= view->viewport()->height() - wallThickness) {
      velocity.setY(-velocity.y());
      collisionSound.play();
    }

    // Проверка столкновения с другими объектами на сцене
    //        QList<QGraphicsItem *> itemsAtNewPos = scene->items(newPos);
    //        bool collisionDetected = false;
    //        for (QGraphicsItem *otherItem : itemsAtNewPos) {
    //            if (otherItem != itemGroup &&
    //            itemGroup->collidesWithItem(otherItem,
    //            Qt::IntersectsItemShape) && otherItem->data(0) != "user") {
    //                collisionDetected = true;
    //                break;
    //            }
    //        }

    //        if (collisionDetected) {

    //            velocity.setX(-velocity.x()); // Изменяем направление по оси X
    //            при столкновении velocity.setY(-velocity.y()); // Изменяем
    //            направление по оси Y при столкновении collisionSound.play();
    //            // Звук столкновения
    //        }
    bool collisionDetected = false;
    QList<QGraphicsItem *> itemsAtNewPos =
        scene->items(QRectF(newPos, boundingRect.size()));
    for (QGraphicsItem *otherItem : itemsAtNewPos) {
      if (otherItem != itemGroup && otherItem->data(0) != "user") {
        QRectF otherBoundingRect =
            otherItem->boundingRect().translated(otherItem->pos());

        if (right > otherBoundingRect.left() &&
            left < otherBoundingRect.right()) {
          collisionDetected = true;
          break;
        }

        if (bottom > otherBoundingRect.top() &&
            top < otherBoundingRect.bottom()) {
          collisionDetected = true;
          break;
        }
      }
    }

    if (collisionDetected) {

      velocity.setX(
          -velocity.x()); // Изменяем направление по оси X при столкновении
      velocity.setY(
          -velocity.y()); // Изменяем направление по оси Y при столкновении
      collisionSound.play(); // Звук столкновения
    }

    // Обновляем позицию объекта и скорость
    itemGroup->setPos(newPos);
    velocities[i] = velocity;
  }
}

void GraphicsEditor::on_SetPen_triggered() {
  view->setEraserMode(false);
  QDialog dialog(this);
  dialog.setWindowTitle(tr("Настройка пера"));

  QVBoxLayout *layout = new QVBoxLayout(&dialog);
  QFormLayout *formLayout = new QFormLayout();

  // Выбор стиля пера
  QComboBox *styleComboBox = new QComboBox();
  styleComboBox->setIconSize(QSize(64, 64)); // Например, 32x32 пикселя
  styleComboBox->addItem(QIcon(":/res/images/penIcons/Solid"), "Solid",
                         QVariant::fromValue(Qt::SolidLine));
  styleComboBox->addItem(QIcon(":/res/images/penIcons/Dash"), "Dash",
                         QVariant::fromValue(Qt::DashLine));
  styleComboBox->addItem(QIcon(":/res/images/penIcons/DotLine"), "Dot",
                         QVariant::fromValue(Qt::DotLine));
  styleComboBox->addItem(QIcon(":/res/images/penIcons/DashDotLine"), "Dash Dot",
                         QVariant::fromValue(Qt::DashDotLine));
  styleComboBox->addItem(QIcon(":/res/images/penIcons/DashDotDotLine"),
                         "Dash Dot Dot",
                         QVariant::fromValue(Qt::DashDotDotLine));
  styleComboBox->setCurrentIndex(
      styleComboBox->findData(static_cast<int>(currentPen.style())));
  formLayout->addRow(tr("Стиль:"), styleComboBox);

  // Выбор ширины пера
  QSpinBox *widthSpinBox = new QSpinBox();
  widthSpinBox->setRange(1, 20);
  widthSpinBox->setValue(currentPen.width()); // начальное значение
  formLayout->addRow(tr("Ширина:"), widthSpinBox);

  // Выбор цвета
  QPushButton *colorButton = new QPushButton(tr("Выбрать цвет"));
  QColor penColor = currentPen.color(); // Начальный цвет
  colorButton->setStyleSheet(
      QString("background-color: %1").arg(penColor.name()));
  connect(colorButton, &QPushButton::clicked, [&]() {
    QColor color =
        QColorDialog::getColor(penColor, this, tr("Выберите цвет пера"));
    if (color.isValid()) {
      penColor = color;
      colorButton->setStyleSheet(
          QString("background-color: %1")
              .arg(color.name())); // Изменение цвета кнопки
    }
  });
  formLayout->addRow(tr("Цвет:"), colorButton);

  // Выбор стиля конца
  QComboBox *capStyleComboBox = new QComboBox();
  capStyleComboBox->setIconSize(QSize(64, 64));
  capStyleComboBox->addItem(QIcon(":/res/images/penIcons/FlatCap"), "Flat",
                            QVariant::fromValue(Qt::FlatCap));
  capStyleComboBox->addItem(QIcon(":/res/images/penIcons/RoundCap"), "Round",
                            QVariant::fromValue(Qt::RoundCap));
  capStyleComboBox->addItem(QIcon(":/res/images/penIcons/SquareCap"), "Square",
                            QVariant::fromValue(Qt::SquareCap));
  capStyleComboBox->setCurrentIndex(
      capStyleComboBox->findData(static_cast<int>(currentPen.capStyle())));
  formLayout->addRow(tr("Стиль конца:"), capStyleComboBox);

  // Выбор стиля соединения
  QComboBox *joinStyleComboBox = new QComboBox();
  joinStyleComboBox->setIconSize(QSize(64, 64));
  joinStyleComboBox->addItem(QIcon(":/res/images/penIcons/MilterJoin"), "Miter",
                             QVariant::fromValue(Qt::MiterJoin));
  joinStyleComboBox->addItem(QIcon(":/res/images/penIcons/BevelJoin"), "Bevel",
                             QVariant::fromValue(Qt::BevelJoin));
  joinStyleComboBox->addItem(QIcon(":/res/images/penIcons/RoundJoin"), "Round",
                             QVariant::fromValue(Qt::RoundJoin));
  joinStyleComboBox->setCurrentIndex(
      joinStyleComboBox->findData(static_cast<int>(currentPen.joinStyle())));
  formLayout->addRow(tr("Стиль соединения:"), joinStyleComboBox);

  layout->addLayout(formLayout);

  // Кнопка ОК
  QPushButton *okButton = new QPushButton(tr("ОК"));
  layout->addWidget(okButton);

  connect(okButton, &QPushButton::clicked, [&]() {
    // Установка пера с выбранными параметрами
    currentPen.setStyle(
        static_cast<Qt::PenStyle>(styleComboBox->currentData().value<int>()));
    currentPen.setWidth(widthSpinBox->value());
    currentPen.setColor(penColor);
    currentPen.setCapStyle(static_cast<Qt::PenCapStyle>(
        capStyleComboBox->currentData().value<int>()));
    currentPen.setJoinStyle(static_cast<Qt::PenJoinStyle>(
        joinStyleComboBox->currentData().value<int>()));

    view->setPen(currentPen); // Передаем перо в GraphicsView
    dialog.accept();          // Закрыть диалог
  });

  dialog.exec(); // Показать диалог
}

void GraphicsEditor::on_Clear_triggered() {
  // Останавливаем движение всех объектов (если они двигаются)
  for (int i = 0; i < movingItemGroups.size(); ++i) {
    // Останавливаем все анимации или действия, связанные с движущимися
    // объектами
    movingItemGroups[i]->setPos(QPointF(0, 0)); // Пример остановки движения
  }

  QList<QGraphicsItem *> items = scene->items();
  // Удаляем все объекты, кроме стен
  foreach (QGraphicsItem *item, items) {
    // Проверяем, что это не стена
    if (item != topWall && item != bottomWall && item != leftWall &&
        item != rightWall) {
      scene->removeItem(item); // Убираем из сцены
      movingItemGroups.removeAll(
          qgraphicsitem_cast<QGraphicsItemGroup *>(item));
      delete item; // Немедленное удаление объекта
    }
  }

  // Опционально можно перерисовать стены, чтобы они точно остались на месте
  setupWalls();

  scene->setBackgroundBrush(Qt::white); // Сброс фона (если нужно)
}

void GraphicsEditor::resizeEvent(QResizeEvent *event) {
  QMainWindow::resizeEvent(event);
  setupWalls(); // Перестраиваем стены при каждом изменении размера окна
}

void GraphicsEditor::setupWalls() {
  int viewWidth = view->viewport()->width();
  int viewHeight = view->viewport()->height();
  int wallThickness = 10;

  QPixmap wallImage(":/res/images/wall.jpg");

  QPixmap scaledTopBottom = wallImage.scaled(viewWidth, wallThickness);
  QPixmap scaledLeftRight = wallImage.scaled(wallThickness, viewHeight);

  // Если стены ещё не были созданы, создаём их, иначе просто изменяем размеры
  if (!topWall) {
    topWall = scene->addPixmap(scaledTopBottom);
    bottomWall = scene->addPixmap(scaledTopBottom);
    leftWall = scene->addPixmap(scaledLeftRight);
    rightWall = scene->addPixmap(scaledLeftRight);

    topWall->setFlag(QGraphicsItem::ItemIsMovable, false);
    bottomWall->setFlag(QGraphicsItem::ItemIsMovable, false);
    leftWall->setFlag(QGraphicsItem::ItemIsMovable, false);
    rightWall->setFlag(QGraphicsItem::ItemIsMovable, false);
  } else {
    topWall->setPixmap(scaledTopBottom);
    bottomWall->setPixmap(scaledTopBottom);
    leftWall->setPixmap(scaledLeftRight);
    rightWall->setPixmap(scaledLeftRight);
  }

  updateWallPositions();
}

void GraphicsEditor::updateWallPositions() {
  int wallThickness = 10;

  int horizontalOffset = view->horizontalScrollBar()->value();
  int verticalOffset = view->verticalScrollBar()->value();

  if (topWall)
    topWall->setPos(horizontalOffset, verticalOffset);
  if (bottomWall)
    bottomWall->setPos(horizontalOffset, view->viewport()->height() -
                                             wallThickness + verticalOffset);
  if (leftWall)
    leftWall->setPos(horizontalOffset, verticalOffset);
  if (rightWall)
    rightWall->setPos(view->viewport()->width() - wallThickness +
                          horizontalOffset,
                      verticalOffset);
}

void GraphicsEditor::on_AddFigure_triggered() {
  QDialog dialog(this);
  dialog.setWindowTitle(tr("Добавить фигуру"));

  QVBoxLayout *layout = new QVBoxLayout(&dialog);
  QFormLayout *formLayout = new QFormLayout();

  // Выбор типа фигуры
  QComboBox *shapeComboBox = new QComboBox();
  shapeComboBox->addItem("Квадрат", "Square");
  shapeComboBox->addItem("Прямоугольник", "Rectangle");
  shapeComboBox->addItem("Треугольник", "Triangle");
  shapeComboBox->addItem("Круг", "Circle");
  shapeComboBox->addItem("Эллипс", "Ellipse");
  formLayout->addRow(tr("Тип фигуры:"), shapeComboBox);

  // Ввод размера (ширина и высота)
  QSpinBox *widthSpinBox = new QSpinBox();
  widthSpinBox->setRange(1, 1000);
  widthSpinBox->setValue(100);
  formLayout->addRow(tr("Ширина:"), widthSpinBox);

  QSpinBox *heightSpinBox = new QSpinBox();
  heightSpinBox->setRange(1, 1000);
  heightSpinBox->setValue(100);
  formLayout->addRow(tr("Высота:"), heightSpinBox);

  // Функция, которая будет изменять поля в зависимости от выбранной фигуры
  auto updateShapeInputs = [&]() {
    QString shapeType = shapeComboBox->currentData().toString();

    if (shapeType == "Square") {
      heightSpinBox->setValue(
          widthSpinBox->value()); // Устанавливаем высоту равной ширине
      heightSpinBox->setEnabled(false); // Выключаем поле высоты
    } else if (shapeType == "Circle") {
      heightSpinBox->setValue(
          widthSpinBox
              ->value()); // Устанавливаем высоту равной ширине для радиуса
      heightSpinBox->setEnabled(false); // Выключаем поле высоты
    } else {
      heightSpinBox->setEnabled(true); // Включаем поле высоты для других фигур
    }
  };

  // Обновление полей при изменении типа фигуры
  connect(shapeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
          updateShapeInputs);

  // Изначально вызываем функцию для корректного отображения полей
  updateShapeInputs();

  // Выбор цвета заливки
  QPushButton *fillColorButton = new QPushButton(tr("Цвет заливки"));
  QColor fillColor = Qt::yellow;
  fillColorButton->setStyleSheet(
      QString("background-color: %1").arg(fillColor.name()));
  connect(fillColorButton, &QPushButton::clicked, [&]() {
    QColor color =
        QColorDialog::getColor(fillColor, this, tr("Выберите цвет заливки"));
    if (color.isValid()) {
      fillColor = color;
      fillColorButton->setStyleSheet(
          QString("background-color: %1").arg(color.name()));
    }
  });
  formLayout->addRow(tr("Цвет заливки:"), fillColorButton);

  // Выбор цвета обводки
  QPushButton *strokeColorButton = new QPushButton(tr("Цвет обводки"));
  QColor strokeColor = Qt::black;
  strokeColorButton->setStyleSheet(
      QString("background-color: %1").arg(strokeColor.name()));
  connect(strokeColorButton, &QPushButton::clicked, [&]() {
    QColor color =
        QColorDialog::getColor(strokeColor, this, tr("Выберите цвет обводки"));
    if (color.isValid()) {
      strokeColor = color;
      strokeColorButton->setStyleSheet(
          QString("background-color: %1").arg(color.name()));
    }
  });
  formLayout->addRow(tr("Цвет обводки:"), strokeColorButton);

  // Выбор ширины обводки
  QSpinBox *strokeWidthSpinBox = new QSpinBox();
  strokeWidthSpinBox->setRange(1, 20);
  strokeWidthSpinBox->setValue(2);
  formLayout->addRow(tr("Ширина обводки:"), strokeWidthSpinBox);

  QComboBox *brushComboBox = new QComboBox();
  brushComboBox->addItem("Кисть не задана", "NoBrush");
  brushComboBox->addItem("Однородный цвет", "SolidPattern");
  brushComboBox->addItem("Чрезвычайно плотная кисть", "Dense1Pattern");
  brushComboBox->addItem("Очень плотная кисть", "Dense2Pattern");
  brushComboBox->addItem("Довольно плотная кисть", "Dense3Pattern");
  brushComboBox->addItem("Наполовину плотная кисть", "Dense4Pattern");
  brushComboBox->addItem("Довольно редкая кисть", "Dense5Pattern");
  brushComboBox->addItem("Очень редкая кисть", "Dense6Pattern");
  brushComboBox->addItem("Чрезвычайно редкая кисть", "Dense7Pattern");
  brushComboBox->addItem("Горизонтальные линии", "HorPattern");
  brushComboBox->addItem("Вертикальные линии", "VerPattern");
  brushComboBox->addItem("Пересекающиеся вертикальные и горизонтальные линии",
                         "CrossPattern");
  brushComboBox->addItem("Обратные диагональные линии", "BDiagPattern");
  brushComboBox->addItem("Прямые диагональные линии", "FDiagPattern");
  brushComboBox->addItem("Пересекающиеся диагональные линии",
                         "DiagCrossPattern");
  formLayout->addRow(tr("Тип заливки:"), brushComboBox);

  layout->addLayout(formLayout);

  // Кнопка ОК
  QPushButton *okButton = new QPushButton(tr("ОК"));
  layout->addWidget(okButton);

  connect(okButton, &QPushButton::clicked, [&]() {
    // Получаем значения из формы
    QString shapeType = shapeComboBox->currentData().toString();
    int width = widthSpinBox->value();
    int height = (shapeType == "Square" || shapeType == "Circle")
                     ? width
                     : heightSpinBox->value();
    int x = (view->viewport()->width() - width) / 2; // Центрируем фигуру
    int y = (view->viewport()->height() - height) / 2;

    QString brushStyleStr = brushComboBox->currentData().toString();
    Qt::BrushStyle brushStyle = stringToBrushStyle(brushStyleStr);

    // Добавляем фигуру
    addShape(shapeType, QRectF(x, y, width, height), fillColor, brushStyle,
             strokeColor, strokeWidthSpinBox->value());

    dialog.accept(); // Закрыть диалог
  });

  dialog.exec(); // Показать диалог
}

void GraphicsEditor::addShape(QString shapeType, QRectF rect, QColor fillColor,
                              Qt::BrushStyle brushStyle, QColor strokeColor,
                              int strokeWidth) {
  QGraphicsItem *shape = nullptr;
  QPen pen(strokeColor, strokeWidth);
  QBrush brush(fillColor, brushStyle);

  if (shapeType == "Square") {
    // Квадрат (равные ширина и высота)
    shape = scene->addRect(rect, pen, brush);
  } else if (shapeType == "Rectangle") {
    // Прямоугольник
    shape = scene->addRect(rect, pen, brush);
  } else if (shapeType == "Circle") {
    // Круг
    shape = scene->addEllipse(rect, pen, brush);
  } else if (shapeType == "Ellipse") {
    // Эллипс
    shape = scene->addEllipse(rect, pen, brush);
  } else if (shapeType == "Triangle") {
    // Треугольник
    QPolygonF triangle;
    triangle << QPointF(rect.left() + rect.width() / 2, rect.top())
             << QPointF(rect.bottomLeft()) << QPointF(rect.bottomRight());
    shape = scene->addPolygon(triangle, pen, brush);
  }

  shape->setFlag(QGraphicsItem::ItemIsMovable, true); // Фигуры можно перемещать
  shape->setFlag(QGraphicsItem::ItemIsSelectable,
                 true); // Фигуры можно выделять
  shape->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void GraphicsEditor::on_DeleteFigure_triggered() {
  // Получаем список всех выбранных объектов на сцене
  QList<QGraphicsItem *> selectedItems = scene->selectedItems();

  // Проверка, есть ли вообще выбранные элементы
  if (selectedItems.isEmpty()) {
    qDebug() << "No items selected for deletion.";
    return;
  }

  // Выводим количество выбранных объектов
  qDebug() << "Selected items count:" << selectedItems.count();

  foreach (QGraphicsItem *item, selectedItems) {
    qDebug() << "Item type:" << item->type();

    if (QGraphicsItemGroup *group =
            qgraphicsitem_cast<QGraphicsItemGroup *>(item)) {
      // Если это группа, выводим информацию и удаляем её элементы
      qDebug() << "Removing group with child items.";

      movingItemGroups.removeAll(group);

      QList<QGraphicsItem *> children = group->childItems();
      for (QGraphicsItem *child : children) {
        qDebug() << "Removing child item:" << child;
        scene->removeItem(child); // Убираем элемент из сцены
        delete child;             // Удаляем элемент
      }

      scene->removeItem(group); // Убираем саму группу из сцены
      delete group;             // Удаляем саму группу
    } else {
      // Если это не группа, удаляем только объект
      qDebug() << "Removing single item:" << item;
      scene->removeItem(item); // Убираем объект из сцены
      delete item;             // Удаляем объект
    }
  }

  // Обновляем сцену и выводим сообщение
  scene->update();
  qDebug() << "Scene updated after deletion.";
}

void GraphicsEditor::drawGordeew() {
  // Г
  QGraphicsItemGroup *group_G = new QGraphicsItemGroup();
  QGraphicsItem *G_1 =
      scene->addLine(QLineF(15, 15, 50, 15), QPen(Qt::green, 6));
  group_G->addToGroup(G_1);
  QGraphicsItem *G_2 =
      scene->addLine(QLineF(15, 15, 15, 60), QPen(Qt::green, 6));
  group_G->addToGroup(G_2);
  groupSetFlags(group_G);
  scene->addItem(group_G);

  // О
  QGraphicsItemGroup *group_O = new QGraphicsItemGroup();
  QGraphicsEllipseItem *O =
      scene->addEllipse(QRectF(70, 15, 50, 50), QPen(Qt::red, 6));
  group_O->addToGroup(O);
  groupSetFlags(group_O);
  scene->addItem(group_O);

  // Р
  QGraphicsItemGroup *group_R = new QGraphicsItemGroup();
  QGraphicsItem *R_1 =
      scene->addLine(QLineF(140, 15, 140, 60), QPen(Qt::blue, 6));
  group_R->addToGroup(R_1);
  QGraphicsEllipseItem *R_2 =
      scene->addEllipse(QRectF(140, 15, 30, 30), QPen(Qt::blue, 6));
  group_R->addToGroup(R_2);
  groupSetFlags(group_R);
  scene->addItem(group_R);

  // Д
  QGraphicsItemGroup *group_D = new QGraphicsItemGroup();
  QGraphicsItem *D_1 =
      scene->addLine(QLineF(190, 60, 220, 15), QPen(Qt::yellow, 6));
  group_D->addToGroup(D_1);
  QGraphicsItem *D_2 =
      scene->addLine(QLineF(220, 15, 250, 60), QPen(Qt::yellow, 6));
  group_D->addToGroup(D_2);
  QGraphicsItem *D_3 =
      scene->addLine(QLineF(200, 60, 240, 60), QPen(Qt::yellow, 6));
  group_D->addToGroup(D_3);
  groupSetFlags(group_D);
  scene->addItem(group_D);

  // Е
  QGraphicsItemGroup *group_E = new QGraphicsItemGroup();
  QGraphicsItem *E_1 =
      scene->addLine(QLineF(270, 15, 270, 60), QPen(Qt::cyan, 6));
  group_E->addToGroup(E_1);
  QGraphicsItem *E_2 =
      scene->addLine(QLineF(270, 15, 300, 15), QPen(Qt::cyan, 6));
  group_E->addToGroup(E_2);
  QGraphicsItem *E_3 =
      scene->addLine(QLineF(270, 60, 300, 60), QPen(Qt::cyan, 6));
  group_E->addToGroup(E_3);
  QGraphicsItem *E_4 =
      scene->addLine(QLineF(270, 37, 290, 37), QPen(Qt::cyan, 6));
  group_E->addToGroup(E_4);
  groupSetFlags(group_E);
  scene->addItem(group_E);

  // Е (повтор)
  QGraphicsItemGroup *group_E2 = new QGraphicsItemGroup();
  QGraphicsItem *E2_1 =
      scene->addLine(QLineF(330, 15, 330, 60), QPen(Qt::cyan, 6));
  group_E2->addToGroup(E2_1);
  QGraphicsItem *E2_2 =
      scene->addLine(QLineF(330, 15, 360, 15), QPen(Qt::cyan, 6));
  group_E2->addToGroup(E2_2);
  QGraphicsItem *E2_3 =
      scene->addLine(QLineF(330, 60, 360, 60), QPen(Qt::cyan, 6));
  group_E2->addToGroup(E2_3);
  QGraphicsItem *E2_4 =
      scene->addLine(QLineF(330, 37, 350, 37), QPen(Qt::cyan, 6));
  group_E2->addToGroup(E2_4);

  groupSetFlags(group_E2);
  scene->addItem(group_E2);

  // В
  QGraphicsItemGroup *group_V = new QGraphicsItemGroup();
  QGraphicsItem *V_1 =
      scene->addLine(QLineF(400, 15, 400, 60), QPen(Qt::magenta, 6));
  group_V->addToGroup(V_1);
  QGraphicsEllipseItem *V_2 =
      scene->addEllipse(QRectF(400, 15, 30, 20), QPen(Qt::magenta, 6));
  group_V->addToGroup(V_2);
  QGraphicsEllipseItem *V_3 =
      scene->addEllipse(QRectF(400, 40, 30, 20), QPen(Qt::magenta, 6));
  group_V->addToGroup(V_3);
  groupSetFlags(group_V);
  scene->addItem(group_V);

  scene->update(); // Обновление сцены для отображения всех букв


  QMediaPlayer* player = new QMediaPlayer();
  player->setMedia(QUrl::fromLocalFile("D:/Downloads/VisualProg/Lab_5/sound.wav"));


  // Рассыпание каждой буквы на случайные точки через 10 секунд
  QTimer::singleShot(10000, [this, group_G, group_O, group_R, group_D, group_E, group_E2, group_V,player]() {
    player->play();
    scatterLetter(group_G);
    scatterLetter(group_O);
    scatterLetter(group_R);
    scatterLetter(group_D);
    scatterLetter(group_E);
    scatterLetter(group_E2);
    scatterLetter(group_V);
  });
}

void GraphicsEditor::scatterLetter(QGraphicsItemGroup* letterGroup) {
    for (auto item : letterGroup->childItems()) {
        // Если объект не является QGraphicsObject, используем таймер для его перемещения
        QTimer::singleShot(0, [item]() {
            int randomX = QRandomGenerator::global()->bounded(item->scene()->width());
            int randomY = QRandomGenerator::global()->bounded(item->scene()->height());
            item->setPos(randomX, randomY);
        });
    }
}


void GraphicsEditor::drawSheiko() {
  // Ш
  QGraphicsItemGroup *group_Sh = new QGraphicsItemGroup();
  QGraphicsItem *Sh_1 =
      scene->addLine(QLineF(10, 160, 10, 200), QPen(Qt::blue, 2));
  group_Sh->addToGroup(Sh_1);
  QGraphicsItem *Sh_2 =
      scene->addLine(QLineF(30, 160, 30, 200), QPen(Qt::blue, 2));
  group_Sh->addToGroup(Sh_2);
  QGraphicsItem *Sh_3 =
      scene->addLine(QLineF(50, 160, 50, 200), QPen(Qt::blue, 2));
  group_Sh->addToGroup(Sh_3);
  QGraphicsItem *Sh_4 =
      scene->addLine(QLineF(10, 200, 50, 200), QPen(Qt::blue, 2));
  group_Sh->addToGroup(Sh_4);
  scene->addItem(group_Sh);

  // Е
  QGraphicsItemGroup *group_E = new QGraphicsItemGroup();
  QGraphicsItem *E_1 =
      scene->addLine(QLineF(70, 160, 70, 200), QPen(Qt::red, 2));
  group_E->addToGroup(E_1);
  QGraphicsItem *E_2 =
      scene->addLine(QLineF(70, 160, 90, 160), QPen(Qt::red, 2));
  group_E->addToGroup(E_2);
  QGraphicsItem *E_3 =
      scene->addLine(QLineF(70, 180, 90, 180), QPen(Qt::red, 2));
  group_E->addToGroup(E_3);
  QGraphicsItem *E_4 =
      scene->addLine(QLineF(70, 200, 90, 200), QPen(Qt::red, 2));
  group_E->addToGroup(E_4);
  scene->addItem(group_E);

  // И
  QGraphicsItemGroup *group_I = new QGraphicsItemGroup();

  // Левая вертикальная линия
  QGraphicsItem *I_1 =
      scene->addLine(QLineF(110, 160, 110, 200), QPen(Qt::blue, 2));
  group_I->addToGroup(I_1);

  // Правая вертикальная линия
  QGraphicsItem *I_2 =
      scene->addLine(QLineF(130, 160, 130, 200), QPen(Qt::blue, 2));
  group_I->addToGroup(I_2);

  // Диагональная линия
  QGraphicsItem *I_3 =
      scene->addLine(QLineF(130, 160, 110, 200), QPen(Qt::blue, 2));
  group_I->addToGroup(I_3);
  QGraphicsItem *I_4 = scene->addEllipse(QRectF(115, 140, 10, 10),
                                         QPen(Qt::blue, 2), QBrush(Qt::blue));
  group_I->addToGroup(I_4);

  scene->addItem(group_I);

  // К
  QGraphicsItemGroup *group_K = new QGraphicsItemGroup();
  QGraphicsItem *K_1 =
      scene->addLine(QLineF(150, 160, 150, 200), QPen(Qt::blue, 2));
  group_K->addToGroup(K_1);
  QGraphicsItem *K_2 =
      scene->addLine(QLineF(150, 180, 170, 160), QPen(Qt::blue, 2));
  group_K->addToGroup(K_2);
  QGraphicsItem *K_3 =
      scene->addLine(QLineF(150, 180, 170, 200), QPen(Qt::blue, 2));
  group_K->addToGroup(K_3);
  scene->addItem(group_K);

  // О
  QGraphicsItemGroup *group_O = new QGraphicsItemGroup();
  QGraphicsItem *O_1 =
      scene->addEllipse(QRectF(190, 160, 40, 40), QPen(Qt::red, 2));
  group_O->addToGroup(O_1);
  scene->addItem(group_O);

  scene->update();
}

void GraphicsEditor::groupSetFlags(QGraphicsItemGroup *group) {
  group->setFlag(QGraphicsItem::ItemIsMovable, true);
  group->setFlag(QGraphicsItem::ItemIsSelectable, true);
  group->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void GraphicsEditor::textSetFlags(QGraphicsTextItem *item) {
  item->setFlag(QGraphicsItem::ItemIsMovable, true);
  item->setFlag(QGraphicsItem::ItemIsSelectable, true);
  item->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

Qt::BrushStyle GraphicsEditor::stringToBrushStyle(const QString &styleStr) {
  if (styleStr == "SolidPattern") {
    return Qt::SolidPattern;
  } else if (styleStr == "Dense1Pattern") {
    return Qt::Dense1Pattern;
  } else if (styleStr == "Dense2Pattern") {
    return Qt::Dense2Pattern;
  } else if (styleStr == "Dense3Pattern") {
    return Qt::Dense3Pattern;
  } else if (styleStr == "Dense4Pattern") {
    return Qt::Dense4Pattern;
  } else if (styleStr == "Dense5Pattern") {
    return Qt::Dense5Pattern;
  } else if (styleStr == "Dense6Pattern") {
    return Qt::Dense6Pattern;
  } else if (styleStr == "Dense7Pattern") {
    return Qt::Dense7Pattern;
  } else if (styleStr == "HorPattern") {
    return Qt::HorPattern;
  } else if (styleStr == "VerPattern") {
    return Qt::VerPattern;
  } else if (styleStr == "CrossPattern") {
    return Qt::CrossPattern;
  } else if (styleStr == "BDiagPattern") {
    return Qt::BDiagPattern;
  } else if (styleStr == "FDiagPattern") {
    return Qt::FDiagPattern;
  } else if (styleStr == "DiagCrossPattern") {
    return Qt::DiagCrossPattern;
  } else {
    return Qt::NoBrush; // Default if no match
  }
}

void GraphicsEditor::on_Eraser_triggered() {
  QDialog dialog(this);
  dialog.setWindowTitle(tr("Размер ластика"));

  // Create label, spin box, and OK button for the dialog
  QLabel *label = new QLabel(tr("Выбери размер ластика:"), &dialog);
  QSpinBox *sizeSpinBox = new QSpinBox(&dialog);
  sizeSpinBox->setRange(1, 100); // Set range for eraser size
  sizeSpinBox->setValue(10);     // Default size

  QPushButton *okButton = new QPushButton(tr("OK"), &dialog);
  connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

  // Arrange widgets in a vertical layout
  QVBoxLayout *layout = new QVBoxLayout(&dialog);
  layout->addWidget(label);
  layout->addWidget(sizeSpinBox);
  layout->addWidget(okButton);

  // Show dialog and get result
  if (dialog.exec() == QDialog::Accepted) {
    int eraserSize = sizeSpinBox->value();

    // Set the eraser size as the current pen width and activate eraser mode
    QPen eraserPen;
    eraserPen.setColor(
        scene->backgroundBrush()
            .color()); // Set eraser color to match the background
    eraserPen.setWidth(eraserSize);

    view->setPen(eraserPen);   // Set the pen in view as eraser
    view->setEraserMode(true); // Use the public setter to activate eraser mode
  }
}
