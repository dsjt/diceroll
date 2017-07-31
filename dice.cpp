// #include <OpenGL/OpenGL.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <GLUT/GLUT.h>
#include <vector>

using namespace std;

GLdouble vertex[8][3]={
  {-1.0,-1.0,-1.0},
  {1.0,-1.0,-1.0},
  {1.0,1.0,-1.0},
  {-1.0,1.0,-1.0},
  {-1.0,-1.0,1.0},
  {1.0,-1.0,1.0},
  {1.0,1.0,1.0},
  {-1.0,1.0,1.0}
};

int edge[][2] = {
  { 0, 1 },
  { 1, 2 },
  { 2, 3 },
  { 3, 0 },
  { 4, 5 },
  { 5, 6 },
  { 6, 7 },
  { 7, 4 },
  { 0, 4 },
  { 1, 5 },
  { 2, 6 },
  { 3, 7 }
};

int face[][4] = {
  {0,1,2,3},
  {1,5,6,2},
  {5,4,7,6},
  {4,0,3,7},
  {4,5,1,0},
  {3,2,6,7}
};

/* void cube(){ */
/*   int i,j; */
/*   glBegin(GL_POLYGON); */
/*   glColor3d(0.9,0.9,0.9); */
/*   for(i=0;i<6;i++){ */
/*     for(j=0;j<4;j++){ */
/*       glVertex3dv(vertex[face[i][j]]); */
/*     } */
/*   } */
/*   glEnd(); */
/* } */

/* void cube_contour(){ */
/*   int i; */
/*   glColor3d(0.0,0.0,0.0); */
/*   glBegin(GL_LINES); */
/*   for(i=0;i<12;i++){ */
/*     glVertex3dv(vertex[edge[i][0]]); */
/*     glVertex3dv(vertex[edge[i][1]]); */
/*   } */
/*   glEnd(); */
/* } */

class Dice
{
public:
  double pos[3];                // 位置
  double direc[3];              // 向き
  double v[3];                  // 速度
  double w[3];                  // 角速度

  double me;
  double r;
  double vr;
  double gr;
  double random_angle;

  Dice();
  virtual ~Dice();
  void init(double x,double y,double z);
  void calc();
  void display();
  void face_one();
  void face_two();
  void face_three();
  void face_four();
  void face_five();
  void face_six();
  void cube_face();
  void dice(double x, double y, double z, int num);
  void circle();
};

Dice::Dice(){
  ;
}

Dice::~Dice(){
  ;
}

void Dice::init(double x, double y, double z){
  pos[0]=x;
  pos[1]=y;
  pos[2]=z;

  direc[0]=0.0;
  direc[1]=1.0;
  direc[2]=0.0;

  v[0]=0.0;
  v[1]=0.0;
  v[2]=0.0;

  double theta = rand()%360;
  // double phi = 90+rand()%90;
  w[0]=cos(theta);
  w[1]=0.0;
  w[2]=sin(theta);

  me = rand()%6+1;
  r = 1000;
  vr = 20;

  random_angle = rand()%360;
}

void Dice::calc(){
// 床に接触した場合、速度を反転減衰
  if(pos[1]==0)v[1]=-0.75*v[1];

  // 重力に従った速さの更新
  v[1] -= 0.1;

  // 現在の速さによる位置の更新
  // pos[0]+=v[0];
  pos[1]+=v[1];
  // pos[2]+=v[2];

  if(vr > 7)vr-=0.2;
  if(r>0){
    r -= vr;
  }

  // 床に接触している場合、沈み込まないように。
  if(pos[1]<0){
    pos[1]=0;
  }
}

void Dice::display(){
  glPushMatrix();
  dice(pos[0],pos[1],pos[2],me);
  glPopMatrix();
}

void Dice::dice(double x,double y, double z, int num){

  glTranslated(x,y,z);

  glRotated(r,w[0],w[1],w[2]);
  glRotated(random_angle,0,1,0);

  /* cube(); */
  /* cube_contour() */
  glColor3d(0.9,0.9,0.9);
  glutSolidCube( 2 );           //BOX
  glColor3d(0.1,0.1,0.1);
  glutWireCube( 2 );             //フレームBOX

  switch(num){
  case 1:
    break;
  case 2:
    glRotated(-90,1.0,0.0,0.0);
    break;
  case 3:
    glRotated(90,0.0,0.0,1.0);
    break;
  case 4:
    glRotated(-90,0.0,0.0,1.0);
    break;
  case 5:
    glRotated(90,1.0,0.0,0.0);
    break;
  case 6:
    glRotated(180,1.0,0.0,0.0);
    break;
  default:
    break;
  }
  cube_face();

}

void Dice::face_one(){
  /* 1 */
  glPushMatrix();
  glTranslated(0.0,1.01,0.0);
  glScalef(0.4,0.4,0.4);
  glColor3d(0.9,0.1,0.1);
  circle();
  glPopMatrix();
}

void Dice::face_two(){

  double radi = 0.5;
  /* 2 */
  glPushMatrix();

  glTranslated(0.0,0.0,1.01);
  glColor3d(0.1,0.1,0.1);
  glRotated(90.0,-1.0,0,0);

  glPushMatrix();
  glTranslated(-radi,0.0,radi);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(radi,0.0,-radi);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPopMatrix();
}

void Dice::face_three(){
  double radi=0.5;

  glPushMatrix();

  glColor3d(0.1,0.1,0.1);
  glTranslated(1.01,0.0,0.0);
  glRotated(90.0,0.0,0.0,1.0);

  glPushMatrix();
  glTranslated(-radi,0.0,radi);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.0,0.0,0.0);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(radi,0.0,-radi);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPopMatrix();

}

void Dice::face_four(){

  double radi=0.5;

  glPushMatrix();

  glColor3d(0.1,0.1,0.1);
  glTranslated(-1.01,0.0,0.0);
  glRotated(90.0,0.0,0.0,1.0);

  glPushMatrix();
  glTranslated(-radi,0.0,radi);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(radi,0.0, radi);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(radi,0.0,-radi);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-radi,0.0, -radi);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPopMatrix();

}

void Dice::face_five(){

  double radi=0.5;

  glPushMatrix();

  glColor3d(0.1,0.1,0.1);
  glTranslated(0.0,0.0,-1.01);
  glRotated(90.0,1.0,0.0,0.0);

  glPushMatrix();
  glTranslated(-radi,0.0,radi);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(radi,0.0, radi);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(radi,0.0,-radi);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-radi,0.0, -radi);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.0,0.0, 0.0);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPopMatrix();

}

void Dice::face_six(){

  double radi=0.5;

  glPushMatrix();

  glColor3d(0.1,0.1,0.1);
  glTranslated(0.0,-1.01,0.0);

  glPushMatrix();
  glTranslated(-radi,0.0,-radi*0.8);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.0,0.0, -radi*0.8);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(radi,0.0,-radi*0.8);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-radi,0.0,radi*0.8);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.0,0.0, radi*0.8);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(radi,0.0,radi*0.8);
  glScalef(0.2,0.2,0.2);
  circle();
  glPopMatrix();

  glPopMatrix();

}

void Dice::cube_face(){

  face_one();
  face_two();
  face_three();
  face_four();
  face_five();
  face_six();

}

void Dice::circle(){
  int poly = 12;
  double i;

  /* glMaterialfv(GL_FRONT, GL_DIFFUSE, orange); */
  glBegin(GL_POLYGON);
  /* glNormal3dv(normal); */
  glNormal3f(0.0,1.0,0.0);
  for(i=0.0;i<2*M_PI;i+=M_PI/poly){
    glVertex3d(cos(i),0.0,sin(i));
  }
  glEnd();

}

vector<Dice> d(8);

void display(){
  static int t=0;
  static int rolling = 0;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  gluLookAt(0.0,40.0,10.0,
            0.0,0.0,0.0,
            0.0,1.0,0.0);


  for(int i=0;i<d.size();i++){
    d[i].calc();
    d[i].display();
  }

  glutSwapBuffers();
  glFlush();
}

void resize(int w, int h){
  // ウィンドウ全体をビューポートにする
  glViewport(0,0,w,h);

  glMatrixMode(GL_PROJECTION);

  // 変換行列の初期化
  glLoadIdentity();

  gluPerspective(30.0,(double)w/(double)h,1.0,100.0);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 'q':
  case 'Q':
  case '\033':
    exit(0);
  deafault:
    break;
  }
}

void idle(){
  glutPostRedisplay();
}

void init(){
  glClearColor(0.05, 0.2, 0.2, 1.0);
  glEnable(GL_DEPTH_TEST);

  int width = (int)ceil(sqrt(d.size()));
  for(int i=0;i<(int)d.size();i++){
    double x = i/width - width/2.0;
    double z = i%width - width/2.0;
    d[i].init(4.0*x,14,4.0*z);
  }
}

void mouse(int button, int state, int x, int y){
  switch(button){
  case GLUT_LEFT_BUTTON:
    if(state == GLUT_DOWN){
      init();
    }
    break;
  default:
    break;
  }
}

int main(int argc, char *argv[]){
  srand((unsigned int)time(NULL));
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(500, 480);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutIdleFunc(idle);

  init();
  glutMainLoop();
  return 0;
}
