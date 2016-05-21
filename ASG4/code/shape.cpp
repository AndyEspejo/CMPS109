// $Id: shape.cpp,v 1.1 2015-07-16 16:47:51-07 - - $

#include <typeinfo>
#include <unordered_map>
using namespace std;

#include "shape.h"
#include "util.h"
#include <GL/glut.h>
#include <math.h>
typedef float GLfloat;
typedef int GLint;

static unordered_map<void*,string> fontname {
   {GLUT_BITMAP_8_BY_13       , "Fixed-8x13"    },
   {GLUT_BITMAP_9_BY_15       , "Fixed-9x15"    },
   {GLUT_BITMAP_HELVETICA_10  , "Helvetica-10"  },
   {GLUT_BITMAP_HELVETICA_12  , "Helvetica-12"  },
   {GLUT_BITMAP_HELVETICA_18  , "Helvetica-18"  },
   {GLUT_BITMAP_TIMES_ROMAN_10, "Times-Roman-10"},
   {GLUT_BITMAP_TIMES_ROMAN_24, "Times-Roman-24"},
};

static unordered_map<string,void*> fontcode {
   {"Fixed-8x13"    , GLUT_BITMAP_8_BY_13       },
   {"Fixed-9x15"    , GLUT_BITMAP_9_BY_15       },
   {"Helvetica-10"  , GLUT_BITMAP_HELVETICA_10  },
   {"Helvetica-12"  , GLUT_BITMAP_HELVETICA_12  },
   {"Helvetica-18"  , GLUT_BITMAP_HELVETICA_18  },
   {"Times-Roman-10", GLUT_BITMAP_TIMES_ROMAN_10},
   {"Times-Roman-24", GLUT_BITMAP_TIMES_ROMAN_24},
};

ostream& operator<< (ostream& out, const vertex& where) {
   out << "(" << where.xpos << "," << where.ypos << ")";
   return out;
}

shape::shape() {
   DEBUGF ('c', this);
}

text::text (void* glut_bitmap_font, const string& textdata):
      glut_bitmap_font(glut_bitmap_font), textdata(textdata) {
   DEBUGF ('c', this);
}

ellipse::ellipse (GLfloat width, GLfloat height):
dimension ({width, height}) {

   DEBUGF ('c', this);
}

circle::circle (GLfloat diameter): ellipse (diameter, diameter) {
  cout << "Drawing Cirle" << diameter << endl;
   DEBUGF ('c', this);
}


polygon::polygon (const vertex_list& vertices): vertices(vertices) {
   DEBUGF ('c', this);
}

rectangle::rectangle (GLfloat w, GLfloat h):
            polygon({
              {-w/2, h/2},
              {w/2, h/2},
              {w/2, -h/2},
              {-w/2,-h/2}
            }) {


   DEBUGF ('c', this << "(" << w << "," << h << ")");
}

square::square (GLfloat width): rectangle (width, width) {
   DEBUGF ('c', this);
}

void text::draw (const vertex& center, const rgbcolor& color) const {
  rgbcolor textColor;
  textColor = color;

  glColor3ubv(textColor.ubvec);
  glRasterPos2f(center.xpos, center.ypos);
  glutBitmapString(glut_bitmap_font,
    reinterpret_cast<const GLubyte*> (textdata.c_str()));
  //glutSwapBuffers();
   DEBUGF ('d', this << "(" << center << "," << color << ")");
}

void ellipse::draw (const vertex& center, const rgbcolor& color) const {


  glBegin(GL_LINE_LOOP);
  glColor3ubv(color.ubvec);
  const float DEG2RAD = 3.14159/180.0;
  float w = dimension.xpos;
  float h = dimension.ypos;
  //Modified code from the OpenGL forums
  //https://goo.gl/x5Zpo1
  for(int i = 0; i < 360; i++){
    float rad = i*DEG2RAD;
    glVertex2f(cos(rad)*w + center.xpos,
      sin(rad)*h + center.xpos);
  }
  glEnd();
   DEBUGF ('d', this << "(" << center << "," << color << ")");
}

void polygon::draw (const vertex& center, const rgbcolor& color) const {

  glBegin(GL_POLYGON);
  glEnable(GL_LINE_SMOOTH);
  glColor3ubv(color.ubvec);
  for(auto& iter: vertices){
    vertex coordVert;
    coordVert = iter;
    glVertex2f(coordVert.xpos + center.xpos,
      coordVert.ypos + center.ypos);
  }
  glEnd();
   DEBUGF ('d', this << "(" << center << "," << color << ")");
}

void shape::show (ostream& out) const {
   out << this << "->" << demangle (*this) << ": ";
}

void text::show (ostream& out) const {
   shape::show (out);
   out << glut_bitmap_font << "(" << fontname[glut_bitmap_font]
       << ") \"" << textdata << "\"";
}

void ellipse::show (ostream& out) const {
   shape::show (out);
   out << "{" << dimension << "}";
}

void polygon::show (ostream& out) const {
   shape::show (out);
   out << "{" << vertices << "}";
}

ostream& operator<< (ostream& out, const shape& obj) {
   obj.show (out);
   return out;
}
