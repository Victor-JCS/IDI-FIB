#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();
  public slots:
    void cam ();
    void cub_1 ();
    void cub_2 ();
    void cub_3 ();

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void modelTransformCub (float escala, float angle);
    virtual void modelTransformPatricio ();
    virtual void projectTransform ();
    virtual void viewTransform ();

  private:
    int printOglError(const char file[], int line, const char func[]);
    float alfa;
    float alfac1 = 0.0;
    float alfac2 = 120.0;
    float alfac3 = 240.0;
    float c1 = 4.0;
    float c2 = 5.0;
    float c3 = 6.0;
    bool cubo = true;
    bool foco = false;
};
