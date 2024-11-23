#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCheckBox>
#include <QCloseEvent>
#include <QColorDialog>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QSettings>
#include <QSpinBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTemporaryFile>
#include <QTextBlock>
#include <QTextEdit>
#include <QTextStream>
#include <QTextTableCell>
#include <QVBoxLayout>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_CreateNewFile_triggered();

  void on_OpenFile_triggered();

  void on_SaveFile_triggered();

  void on_SaveFileAs_triggered();

  void on_Search_triggered();

  void on_Replace_triggered();

  void on_Copy_triggered();

  void on_Paste_triggered();

  void on_Cut_triggered();

  void on_Redo_triggered();

  void on_Palette_triggered();

  void on_FontAndSize_triggered();

  void on_Table_triggered();

  void setupShortcuts();

  void on_Clear_triggered();

  void loadTextSettings(const QString &filePath);

  void saveTextSettings(const QString &filePath);

  void onTableCellChanged(int row, int column);

  void on_AddRow_triggered();

  void on_Undo_triggered();

  void on_AddColumn_triggered();

  void on_DeleteRow_triggered();

  void on_DeleteColumn_triggered();

private:
  Ui::MainWindow *ui;
  int pageIndex;
  QTextEdit *editor;
  QTableWidget *tableWidget;
  QFont currentFont;
  QColor textColor;
  QColor backgroundColor;
  QString appDir = "Laboratory_5";
  bool tableModified = true;
  static QTemporaryFile tempFile;
};

#endif // MAINWINDOW_H