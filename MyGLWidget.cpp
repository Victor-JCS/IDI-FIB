// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[])
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502:
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::paintGL ()   // Mètode que has de modificar
{

  //ExamGLWidget::paintGL();
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Pintem el Patricio
  if (cubo == false){
    glBindVertexArray (VAO_Patr);
    modelTransformPatricio ();
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  }

  // Pintem el cub
  if(cubo == true){
    glBindVertexArray(VAO_Cub);
    modelTransformCub (4.0f, alfac1);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(VAO_Cub);
    modelTransformCub (5.0f, alfac2);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(VAO_Cub);
    modelTransformCub (6.0f, alfac3);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
  glBindVertexArray(0);
}

void MyGLWidget::modelTransformCub (float escala, float angle)
{
  //ExamGLWidget::modelTransformCub (1.0, 0.0);
  // En aquest mètode has de substituir aquest codi per construir la
  // transformació geomètrica (TG) del cub usant els paràmetres adientment
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, glm::radians(angle), glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3 (5.0,0.0,0.0));
  TG = glm::scale(TG, glm::vec3 (escala, escala, escala));
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPatricio ()    // Mètode que has de modificar
{
  ExamGLWidget::modelTransformPatricio ();
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, glm::radians(alfa), glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3 (5.0,0.0,0.0));
  TG = glm::scale(TG, glm::vec3 (2*escala, 2*escala, 2*escala));
  TG = glm::rotate(TG, glm::radians(-90.0f), glm::vec3(0, 1, 0));
  TG = glm::translate(TG, -centreBasePat);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()    // Mètode que has de modificar
{
  if (!camPlanta)
    ExamGLWidget::viewTransform();
  else
  {
    // Codi per a la viewMatrix de la Càmera-2
    View = lookAt(glm::vec3(0.0, 2*radiEsc+1.5f, 0.0), centreEsc, glm::vec3(1, 0, 0));
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else
  {
    // Codi per a la projectMatrix de la Càmera-2
    glm::mat4 Proj;  // Matriu de projecció
    Proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, zn, zf);

    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_V: {
      // ...
      cubo = !cubo;
    break;
	}
  case Qt::Key_1: {
      // ...
      alfa = 0.0;
    break;
	}
  case Qt::Key_2: {
      // ...
      alfa = 120.0;
    break;
	}
  case Qt::Key_3: {
      // ...
      alfa = 240.0;
    break;
	}
  case Qt::Key_F: {
      // ...
      //foco = !foco;
      if (colFoc == glm::vec3(1,1,1)) {
        colFoc = glm::vec3(1,1,0);
      }
      else if (colFoc == glm::vec3(1,1,0)) {
        colFoc = glm::vec3(1,1,1);
      }
      enviaColFocus();
    break;
	}
  case Qt::Key_C: {
      // ...
      camPlanta = !camPlanta;
      viewTransform();
      projectTransform();
    break;
	}
  case Qt::Key_Right: {
      // ...
      /*alfac1 = 0;
      alfac2 = 120;
      alfac3 = 240;

      alfac1 = 240;
      alfac2 = 0;
      alfac3 = 120;*/

      if(alfa == alfac1){
          float aux = alfac1;
          alfac1 = alfac3;
          alfac3 = alfac2;
          alfac2 = aux;

          alfa = alfac1;
      }else if(alfa == alfac2){
          float aux = alfac1;
          alfac1 = alfac3;
          alfac3 = alfac2;
          alfac2 = aux;

          alfa = alfac2;
      }else{
          float aux = alfac1;
          alfac1 = alfac3;
          alfac3 = alfac2;
          alfac2 = aux;

          alfa = alfac3;
        }
    break;
	}
  case Qt::Key_Left: {
      // ...
      // ...
      /*alfac1 = 0;
      alfac2 = 120;
      alfac3 = 240;

      alfac1 = 240;
      alfac2 = 0;
      alfac3 = 120;*/

      if(alfa == alfac1){
          float aux = alfac1;
          alfac1 = alfac2;
          alfac2 = alfac3;
          alfac3 = aux;

          alfa = alfac1;
      }else if(alfa == alfac2){
          float aux = alfac1;
          alfac1 = alfac2;
          alfac2 = alfac3;
          alfac3 = aux;

          alfa = alfac2;
      }else{
          float aux = alfac1;
          alfac1 = alfac2;
          alfac2 = alfac3;
          alfac3 = aux;

          alfa = alfac3;
        }
    break;

	}
  case Qt::Key_R: {
      // ...
      alfa = 0.0;
      cubo = true;
      colFoc = glm::vec3(1,1,1);
      enviaColFocus();
      c1 = 4.0;
      c2 = 5.0;
      c3 = 6.0;
      camPlanta = false;
      viewTransform();
      projectTransform();
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::cam(){
  camPlanta = !camPlanta;
  viewTransform();
  projectTransform();
  makeCurrent();
  viewTransform();
  update();
}
void MyGLWidget::cub_1(){
  makeCurrent();
  alfa = 0.0;
  viewTransform();
  update();
}
void MyGLWidget::cub_2(){
  makeCurrent();
  alfa = 120.0;
  viewTransform();
  update();
}
void MyGLWidget::cub_3(){
  makeCurrent();
  alfa = 240.0;
  viewTransform();
  update();
}
