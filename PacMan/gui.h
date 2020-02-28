#ifndef GUI_H
#define GUI_H


#include <QGraphicsView>
#include <QGraphicsScene>

class Gui : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Gui(QWidget *parent = nullptr);

    void displayMainMenu();
private:
    //var
    QGraphicsScene *scene;

    //methods
    void displayGame();
signals:

public slots:
   void singleplayerButtonClicked();
   void multiplayerButtonClicked();
   void quitButtonClicked();


};

#endif // GUI_H
