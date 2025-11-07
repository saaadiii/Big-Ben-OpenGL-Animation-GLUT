#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define PI 3.14159265358979323846
#include<math.h>

bool isDay = true;

float hourAngle = 0.0f;
float minuteAngle = 0.0f;

float leftCar = -1.0f;
float rightCar = 1.0f;
float carSpeed = 0.01f;

float cloud1X = -0.75f;
float cloud2X = -0.1f;
float cloud3X = 0.65f;


float cloud1Speed = 0.00499f;
float cloud2Speed = 0.004550f;
float cloud3Speed = 0.003900f;


void update(int value)
{
    leftCar += carSpeed;
    if(leftCar > 1.0f)
        leftCar = -1.0f;

    rightCar -= carSpeed;
    if(rightCar < -1.0f)
        rightCar = 1.0f;

      minuteAngle -= 0.5f;
      if (minuteAngle < 0.0f)
        minuteAngle += 360.0f;

      hourAngle -= 0.05f;
      if (hourAngle < 0.0f)
        hourAngle += 360.0f;

        // Move clouds to the right
    cloud1X += cloud1Speed;
    cloud2X += cloud2Speed;
    cloud3X += cloud3Speed;


    float resetPos = -1.2f;
    float offScreenX = 1.2f;

    if (cloud1X > offScreenX) cloud1X = resetPos;
    if (cloud2X > offScreenX) cloud2X = resetPos;
    if (cloud3X > offScreenX) cloud3X = resetPos;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}



void drawCircle(float cx, float cy, float r, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        glVertex2f(cx + r * cos(2.0f * PI * i / segments),
                   cy + r * sin(2.0f * PI * i / segments));
    }
    glEnd();
}
void drawCloud(float x, float y) {
    if (isDay) {
        glColor3f(1.0f, 1.0f, 1.0f);
    } else {
        glColor3f(0.7f, 0.7f, 0.7f);
    }

    drawCircle(x, y, 0.1f, 100);
    drawCircle(x + 0.12f, y + 0.04f, 0.09f, 100);
    drawCircle(x - 0.08f, y + 0.05f, 0.10f, 100);
    drawCircle(x + 0.02f, y + 0.10f, 0.09f, 100);
}

void drawClock(float cx, float cy) {
    int lineAmount = 100;
    GLfloat radius = 0.1f;

    // White  circle
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(cx, cy, radius, lineAmount);

    // Black border
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i <= lineAmount; i++) {
            GLfloat twicePi = 2.0f * PI;
            glVertex2f(
                cx + (radius * cos(i * twicePi / lineAmount)),
                cy + (radius * sin(i * twicePi / lineAmount))
            );
        }
    glEnd();

    // Hour
    glPushMatrix();
        glTranslatef(cx, cy, 0.0f);
        glRotatef(hourAngle, 0.0f, 0.0f, 1.0f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.0f, 0.06f);
            glEnd();
            glPopMatrix();

    // Minute
    glPushMatrix();
        glTranslatef(cx, cy, 0.0f);
        glRotatef(minuteAngle, 0.0f, 0.0f, 1.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.0f, 0.09f);
            glEnd();
            glPopMatrix();
}


void display()
{
    if (isDay) {
        glClearColor(0.95f, 0.98f, 1.0f, 1.0f);
    } else {
        glClearColor(0.05f, 0.05f, 0.2f, 1.0f);
    }
    glClear(GL_COLOR_BUFFER_BIT);


    // Sky
    glColor3f(0.6f, 0.85f, 1.0f);
    if (!isDay) {
        glColor3f(0.1f, 0.1f, 0.4f);
    }
    glBegin(GL_QUADS);
        glVertex2f(-1.0f,  -0.3f);
        glVertex2f( 1.0f,  -0.3f);
        glVertex2f( 1.0f,  1.0f);
        glVertex2f(-1.0f,  1.0f);
        glEnd();

        //sun/moon
        if (isDay) {
             glColor3f(1.0f, 0.84f, 0.0f);
        } else {
             glColor3f(1.0f, 1.0f, 0.9f);
        }
        drawCircle(0.8f, 0.85f, 0.12f, 100);

    //clouds
    drawCloud(cloud1X, 0.8f);
    drawCloud(cloud2X, 0.9f);
    drawCloud(cloud3X, 0.70f);


    // Road

    glColor3f(0.25f,0.25f,0.25f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f, -0.42f);
        glVertex2f(-1.0f, -0.42f);
        glEnd();


    // White divider dashes

    glLineWidth(6.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);
    // Dash 1
    glVertex2f(-0.9f, -0.665f);
    glVertex2f(-0.82f, -0.665f);
    // Dash 2
    glVertex2f(-0.7f, -0.665f);
    glVertex2f(-0.62f, -0.665f);
    // Dash 3
    glVertex2f(-0.5f, -0.665f);
    glVertex2f(-0.42f, -0.665f);
    // Dash 4
    glVertex2f(-0.3f, -0.665f);
    glVertex2f(-0.22f, -0.665f);
    // Dash 5
    glVertex2f(-0.1f, -0.665f);
    glVertex2f(-0.02f, -0.665f);
    // Dash 6
    glVertex2f(0.1f, -0.665f);
    glVertex2f(0.18f, -0.665f);
    // Dash 7
    glVertex2f(0.3f, -0.665f);
    glVertex2f(0.38f, -0.665f);
    // Dash 8
    glVertex2f(0.5f, -0.665f);
    glVertex2f(0.58f, -0.665f);
    // Dash 9
    glVertex2f(0.7f, -0.665f);
    glVertex2f(0.78f, -0.665f);
   // Dash 10
    glVertex2f(0.9f, -0.665f);
    glVertex2f(0.98f, -0.665f);
    glEnd();

    // Grass


    if (isDay) {
        glColor3f(0.196f, 0.804f, 0.196f);
    } else {
        glColor3f(0.1f, 0.4f, 0.1f);
    }
    glBegin(GL_QUADS);
      glVertex2f(-1.0f, -0.42f);
      glVertex2f( 1.0f, -0.42f);
      glVertex2f( 1.0f, -0.3f);
      glVertex2f(-1.0f, -0.3f);
      glEnd();



    //Bing ben
    //First Rectangle
    if (isDay) {
        glColor3f(0.82f, 0.62f, 0.36f);
    } else {
        glColor3f(0.5f, 0.4f, 0.2f);
    }

   glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.2f, 0.1f);
        glVertex2f(-0.2f, 0.1f);
        glEnd();

      // Horizontal stripes

        glColor3f(0.4f, 0.3f, 0.15f);
        glLineWidth(15.0f);

        glBegin(GL_LINES);
      // Stripe 1
        glVertex2f(-0.2f, -0.25f);
        glVertex2f( 0.2f, -0.25f);

      // Stripe 2

        glVertex2f(-0.2f, -0.1f);
        glVertex2f( 0.2f, -0.1f);

      // Stripe 3
        glVertex2f(-0.2f, 0.05f);
        glVertex2f( 0.2f, 0.05f);
        glEnd();

      // vertical lines

         glColor3f(0.4f, 0.3f, 0.15f);
         glLineWidth(2.0f);

         glBegin(GL_LINES);
      // line 1
         glVertex2f(-0.12f, -0.4f);
         glVertex2f(-0.12f, 0.1f);

      // line 2
         glVertex2f(-0.04f, -0.4f);
         glVertex2f(-0.04f, 0.1f);

      // line 3
         glVertex2f(0.04f, -0.4f);
         glVertex2f(0.04f, 0.1f);

      // line 4
         glVertex2f(0.12f, -0.4f);
         glVertex2f(0.12f, 0.1f);
         glEnd();




    //clock face
    if (isDay) {
        glColor3f(0.72f, 0.52f, 0.26f);
    } else {
        glColor3f(0.4f, 0.3f, 0.15f);
    }
   glBegin(GL_QUADS);
     glVertex2f(-0.22f, 0.1f);
     glVertex2f( 0.22f, 0.1f);
     glVertex2f( 0.22f, 0.5f);
     glVertex2f(-0.22f, 0.5f);
     glEnd();


    drawClock(0.0f, 0.3f);

   //rectangle above clock face

    if (isDay) {
        glColor3f(0.82f, 0.62f, 0.36f);
    } else {
        glColor3f(0.5f, 0.4f, 0.2f);
    }
   glBegin(GL_QUADS);
     glVertex2f(-0.2f, 0.5f);
     glVertex2f( 0.2f, 0.5f);
     glVertex2f( 0.2f, 0.6f);
     glVertex2f(-0.2f, 0.6f);
     glEnd();

    // 6  doors

  glColor3f(0.4f, 0.3f, 0.15f);

    // door 1
  glBegin(GL_QUADS);
    glVertex2f(-0.18f, 0.5f);
    glVertex2f(-0.14f, 0.5f);
    glVertex2f(-0.14f, 0.57f);
    glVertex2f(-0.18f, 0.57f);
    glEnd();

    // door 2
  glBegin(GL_QUADS);
    glVertex2f(-0.11f, 0.5f);
    glVertex2f(-0.07f, 0.5f);
    glVertex2f(-0.07f, 0.57f);
    glVertex2f(-0.11f, 0.57f);
    glEnd();

    // door 3
   glBegin(GL_QUADS);
    glVertex2f(-0.04f, 0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.0f, 0.57f);
    glVertex2f(-0.04f, 0.57f);
    glEnd();

   // door 4
   glBegin(GL_QUADS);
    glVertex2f(0.03f, 0.5f);
    glVertex2f(0.07f, 0.5f);
    glVertex2f(0.07f, 0.57f);
    glVertex2f(0.03f, 0.57f);
    glEnd();

   // door 5
   glBegin(GL_QUADS);
    glVertex2f(0.09f, 0.5f);
    glVertex2f(0.13f, 0.5f);
    glVertex2f(0.13f, 0.57f);
    glVertex2f(0.09f, 0.57f);
    glEnd();

   // door 6
   glBegin(GL_QUADS);
    glVertex2f(0.15f, 0.5f);
    glVertex2f(0.19f, 0.5f);
    glVertex2f(0.19f, 0.57f);
    glVertex2f(0.15f, 0.57f);
    glEnd();

   //dome 1 above the doors
    if (isDay) {
        glColor3f(0.333f, 0.333f, 0.333f);
    } else {
        glColor3f(0.2f, 0.2f, 0.2f);
    }
    glBegin(GL_QUADS);
      glVertex2f(-0.1f, 0.7f);
      glVertex2f( 0.1f, 0.7f);
      glVertex2f( 0.22f, 0.6f);
      glVertex2f(-0.22f, 0.6f);
      glEnd();

   //rectangle above dome 1

    if (isDay) {
        glColor3f(0.82f, 0.62f, 0.36f);
    } else {
        glColor3f(0.5f, 0.4f, 0.2f);
    }
    glBegin(GL_QUADS);
    glVertex2f(-0.1f, 0.7f);
    glVertex2f( 0.1f, 0.7f);
    glVertex2f( 0.1f, 0.8f);
    glVertex2f(-0.1f, 0.8f);
    glEnd();


    // 4 doors in rectangle above dome 1
    glColor3f(0.4f, 0.3f, 0.15f);

    // door 1
  glBegin(GL_QUADS);
    glVertex2f(-0.09f, 0.7f);
    glVertex2f(-0.042f, 0.7f);
    glVertex2f(-0.042f, 0.78f);
    glVertex2f(-0.09f, 0.78f);
    glEnd();

    // door 2
  glBegin(GL_QUADS);
    glVertex2f(-0.02f, 0.7f);
    glVertex2f(0.03f, 0.7f);
    glVertex2f(0.03f, 0.78f);
    glVertex2f(-0.02f, 0.78f);
    glEnd();

    // door 3
  glBegin(GL_QUADS);
    glVertex2f(0.05f, 0.7f);
    glVertex2f(0.09f, 0.7f);
    glVertex2f(0.09f, 0.78f);
    glVertex2f(0.05f, 0.78f);
    glEnd();

    //dome 2
    if (isDay) {
        glColor3f(0.333f, 0.333f, 0.333f);
    } else {
        glColor3f(0.2f, 0.2f, 0.2f);
    }
    glBegin(GL_TRIANGLES);
    glVertex2f( 0.0f, 1.0f);
    glVertex2f(-0.1f, 0.8f);
    glVertex2f( 0.1f, 0.8f);

    glEnd();

    //small tower
    if (isDay) {
        glColor3f(0.72f, 0.55f, 0.31f);
    } else {
        glColor3f(0.55f, 0.4f, 0.2f);
    }
    glBegin(GL_QUADS);
    glVertex2f(-0.2f, -0.4f);
    glVertex2f(-0.45f, -0.4f);
    glVertex2f(-0.45f, 0.0f);
    glVertex2f(-0.2f, 0.0f);
    glEnd();

    // Roof of small building

      glLineWidth(10.0f);
      glColor3f(0.333f, 0.333f, 0.333f);
      glBegin(GL_LINES);
      glVertex2f(-0.45f, 0.0f);
      glVertex2f(-0.2f, 0.0f);
      glEnd();



    // Pillar for small building
    glColor3f(0.4f, 0.3f, 0.15f);
    glBegin(GL_POLYGON);

    glVertex2f(-0.34f, -0.4f);
    glVertex2f(-0.29f, -0.4f);
    glVertex2f(-0.29f, 0.02f);
    glVertex2f(-0.313f, 0.08f);//top
    glVertex2f(-0.34f, 0.02f);
    glEnd();


    //Windows of small building
    if (isDay) {
        glColor3f(0.7f, 0.85f, 0.95f);
    } else {
        glColor3f(1.0f, 1.0f, 0.6f);
    }

    // Left window
   glBegin(GL_QUADS);
    glVertex2f(-0.42f, -0.3f);
    glVertex2f(-0.36f, -0.3f);
    glVertex2f(-0.36f, -0.09f);
    glVertex2f(-0.42f, -0.09f);
    glEnd();

    // Right window
   glBegin(GL_QUADS);
    glVertex2f(-0.27f, -0.3f);
    glVertex2f(-0.22f, -0.3f);
    glVertex2f(-0.22f, -0.09f);
    glVertex2f(-0.27f, -0.09f);
    glEnd();

    //window stripes
      glLineWidth(2.0f);
      glColor3f(0.0f, 0.0f, 0.0f);
      glBegin(GL_LINES);

      //left window
      // vertical stripe
      glVertex2f(-0.39f, -0.3f);
      glVertex2f(-0.39f, -0.09f);

      // horizontal stripe
      glVertex2f(-0.42f, -0.195f);
      glVertex2f(-0.36f, -0.195f);


      // Right window
      //vertical stripe
      glVertex2f(-0.245f, -0.3f);
      glVertex2f(-0.245f, -0.09f);

      //horizontal stripe
      glVertex2f(-0.27f, -0.195f);
      glVertex2f(-0.22f, -0.195f);
      glEnd();

      //left big building
    if (isDay) {
        glColor3f(0.72f, 0.55f, 0.31f);
    } else {
        glColor3f(0.6f, 0.45f, 0.25f);
    }
      glBegin(GL_QUADS);
         glVertex2f(-0.75f, -0.4f);
         glVertex2f(-0.45f, -0.4f);
         glVertex2f(-0.45f, 0.35f);
         glVertex2f(-0.75f, 0.35f);
         glEnd();

    // Roof for left big building
      glColor3f(0.333f, 0.333f, 0.333f);
      glBegin(GL_QUADS);
        glVertex2f(-0.75f, 0.35f);
        glVertex2f(-0.45f, 0.35f);
        glVertex2f(-0.55f, 0.50f);
        glVertex2f(-0.67f, 0.50f);
        glEnd();

    // Left pillar
     glColor3f(0.4f, 0.3f, 0.15f);
     glBegin(GL_POLYGON);
        glVertex2f(-0.75f, -0.4f);
        glVertex2f(-0.70f, -0.4f);
        glVertex2f(-0.70f, 0.4f);
        glVertex2f(-0.725f, 0.5f); // top
        glVertex2f(-0.75f, 0.4f);
        glEnd();

    // Right pillar
       glColor3f(0.4f, 0.3f, 0.15f);
       glBegin(GL_POLYGON);
          glVertex2f(-0.50f, -0.4f);
          glVertex2f(-0.45f, -0.4f);
          glVertex2f(-0.45f, 0.4f);
          glVertex2f(-0.475f, 0.5f);   // top
          glVertex2f(-0.50f, 0.4f);
          glEnd();


    if (isDay) {
        glColor3f(0.7f, 0.85f, 0.95f);
    } else {
        glColor3f(1.0f, 1.0f, 0.6f);
    }

    //Window of Left big building
     // Bottom left
       glBegin(GL_QUADS);
         glVertex2f(-0.685f, -0.2f);
         glVertex2f(-0.625f, -0.2f);
         glVertex2f(-0.625f, 0.0f);
         glVertex2f(-0.685f, 0.0f);
         glEnd();

     // Bottom right
       glBegin(GL_QUADS);
         glVertex2f(-0.565f, -0.2f);
         glVertex2f(-0.512f, -0.2f);
         glVertex2f(-0.512f, 0.0f);
         glVertex2f(-0.565f, 0.0f);
         glEnd();

     // Top left
       glBegin(GL_QUADS);
         glVertex2f(-0.685f, 0.12f);
         glVertex2f(-0.625f, 0.12f);
         glVertex2f(-0.625f, 0.32f);
         glVertex2f(-0.685f, 0.32f);
         glEnd();

     // Top right
        glBegin(GL_QUADS);
          glVertex2f(-0.565f, 0.12f);
          glVertex2f(-0.512f, 0.12f);
          glVertex2f(-0.512f, 0.32f);
          glVertex2f(-0.565f, 0.32f);
          glEnd();

    //Window stripes
    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Bottom left window
    glBegin(GL_LINES);
    glVertex2f(-0.655f, -0.2f);
    glVertex2f(-0.655f, 0.0f);
    glVertex2f(-0.685f, -0.1f);
    glVertex2f(-0.625f, -0.1f);
    glEnd();

    // Bottom right window
   glBegin(GL_LINES);
   glVertex2f(-0.5385f, -0.2f);
   glVertex2f(-0.5385f, 0.0f);
   glVertex2f(-0.565f, -0.1f);
   glVertex2f(-0.512f, -0.1f);
   glEnd();

   // Top left window
   glBegin(GL_LINES);
   glVertex2f(-0.655f, 0.12f);
   glVertex2f(-0.655f, 0.32f);
   glVertex2f(-0.685f, 0.22f);
   glVertex2f(-0.625f, 0.22f);
   glEnd();

   // Top-right window panes
   glBegin(GL_LINES);

   glVertex2f(-0.5385f, 0.12f);
   glVertex2f(-0.5385f, 0.32f);
   glVertex2f(-0.565f, 0.22f);
   glVertex2f(-0.512f, 0.22f);
   glEnd();

   //Right Building 1
    if (isDay) {
        glColor3f(0.95f, 0.80f, 0.75f);
    } else {
        glColor3f(0.75f, 0.65f, 0.6f);
    }
       glBegin(GL_QUADS);
         glVertex2f(0.6f, -0.4f);
         glVertex2f(0.23f, -0.4f);
         glVertex2f(0.23f, 0.3f);
         glVertex2f(0.6f, 0.3f);
         glEnd();
    // Roof for Right Building 1
       glColor3f(0.7f, 0.7f, 0.7f);
       glBegin(GL_QUADS);
         glVertex2f(0.23f, 0.3f);
         glVertex2f(0.6f, 0.3f);
         glVertex2f(0.52f, 0.45f);
         glVertex2f(0.31f, 0.45f);
         glEnd();


    if (isDay) {
        glColor3f(0.7f, 0.85f, 0.95f);
    } else {
        glColor3f(1.0f, 1.0f, 0.6f);
    }
    // Windows of right building 1

    // Bottom left window
      glBegin(GL_QUADS);
        glVertex2f(0.28f, -0.2f);
        glVertex2f(0.34f, -0.2f);
        glVertex2f(0.34f, 0.0f);
        glVertex2f(0.28f, 0.0f);
        glEnd();

    // Bottom right window
      glBegin(GL_QUADS);
        glVertex2f(0.49f, -0.2f);
        glVertex2f(0.55f, -0.2f);
        glVertex2f(0.55f, 0.0f);
        glVertex2f(0.49f, 0.0f);
        glEnd();

    // Top left window
      glBegin(GL_QUADS);
        glVertex2f(0.28f, 0.08f);
        glVertex2f(0.34f, 0.08f);
        glVertex2f(0.34f, 0.25f);
        glVertex2f(0.28f, 0.25f);
        glEnd();

    // Top right window
      glBegin(GL_QUADS);
        glVertex2f(0.49f, 0.08f);
        glVertex2f(0.55f, 0.08f);
        glVertex2f(0.55f, 0.25f);
        glVertex2f(0.49f, 0.25f);
        glEnd();

      // Window stripes
      glColor3f(0.0f, 0.0f, 0.0f);
      glLineWidth(2.0f);
      glBegin(GL_LINES);
    // Bottom left window
        glVertex2f(0.31f, -0.2f);
        glVertex2f(0.31f, 0.0f);
        glVertex2f(0.28f, -0.1f);
        glVertex2f(0.34f, -0.1f);
    // Bottom right window
        glVertex2f(0.52f, -0.2f);
        glVertex2f(0.52f, 0.0f);
        glVertex2f(0.49f, -0.1f);
        glVertex2f(0.55f, -0.1f);
    // Top left window
        glVertex2f(0.31f, 0.08f);
        glVertex2f(0.31f, 0.25f);
        glVertex2f(0.28f, 0.165f);
        glVertex2f(0.34f, 0.165f);
    // Top right window
        glVertex2f(0.52f, 0.08f);
        glVertex2f(0.52f, 0.25f);
        glVertex2f(0.49f, 0.165f);
        glVertex2f(0.55f, 0.165f);
        glEnd();


      // Door
      glColor3f(0.4f, 0.3f, 0.15f);
      glBegin(GL_QUADS);
        glVertex2f(0.36f, -0.4f);
        glVertex2f(0.47f, -0.4f);
        glVertex2f(0.47f, -0.15f);
        glVertex2f(0.36f, -0.15f);
        glEnd();

      // Chimney pillar
      glColor3f(0.4f, 0.4f, 0.4f);
      glBegin(GL_QUADS);
        glVertex2f(0.34f, 0.45f);
        glVertex2f(0.38f, 0.45f);
        glVertex2f(0.38f, 0.55f);
        glVertex2f(0.34f, 0.55f);
        glEnd();

    // Chimney top
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
      glVertex2f(0.33f, 0.55f);
      glVertex2f(0.39f, 0.55f);
      glVertex2f(0.39f, 0.57f);
      glVertex2f(0.33f, 0.57f);
      glEnd();

      // Right Building 2
    if (isDay) {
        glColor3f(0.0f, 0.6f, 0.6f);
    } else {
        glColor3f(0.0f, 0.4f, 0.4f);
    }
    glBegin(GL_QUADS);
      glVertex2f(0.63f, -0.4f);
      glVertex2f(0.98f, -0.4f);
      glVertex2f(0.98f, 0.3f);
      glVertex2f(0.63f, 0.3f);
      glEnd();

    // Roof rectangle
    glColor3f(0.333f, 0.333f, 0.333f);
    glBegin(GL_QUADS);
      glVertex2f(0.63f, 0.3f);
      glVertex2f(0.98f, 0.3f);
      glVertex2f(0.89f, 0.45f);
      glVertex2f(0.72f, 0.45f);
      glEnd();

    if (isDay) {
        glColor3f(0.85f, 0.95f, 1.0f);
    } else {
        glColor3f(1.0f, 1.0f, 0.6f);
    }
      // Windows for Right Building 2

    // Bottom left window
    glBegin(GL_QUADS);
    glVertex2f(0.66f, -0.2f);
    glVertex2f(0.73f, -0.2f);
    glVertex2f(0.73f, 0.0f);
    glVertex2f(0.66f, 0.0f);
    glEnd();

    // Bottom right window
    glBegin(GL_QUADS);
    glVertex2f(0.88f, -0.2f);
    glVertex2f(0.95f, -0.2f);
    glVertex2f(0.95f, 0.0f);
    glVertex2f(0.88f, 0.0f);
    glEnd();

    // Top left window
    glBegin(GL_QUADS);
    glVertex2f(0.66f, 0.08f);
    glVertex2f(0.73f, 0.08f);
    glVertex2f(0.73f, 0.25f);
    glVertex2f(0.66f, 0.25f);
    glEnd();

    // Top right window
    glBegin(GL_QUADS);
    glVertex2f(0.88f, 0.08f);
    glVertex2f(0.95f, 0.08f);
    glVertex2f(0.95f, 0.25f);
    glVertex2f(0.88f, 0.25f);
    glEnd();

    //window stripes

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    // Bottom left window
    glVertex2f(0.695f, -0.2f);
    glVertex2f(0.695f, 0.0f);
    glVertex2f(0.66f, -0.1f);
    glVertex2f(0.73f, -0.1f);

    // Bottom right window
    glVertex2f(0.915f, -0.2f);
    glVertex2f(0.915f, 0.0f);
    glVertex2f(0.88f, -0.1f);
    glVertex2f(0.95f, -0.1f);

    // Top left window
    glVertex2f(0.695f, 0.08f);
    glVertex2f(0.695f, 0.25f);
    glVertex2f(0.66f, 0.165f);
    glVertex2f(0.73f, 0.165f);

    // Top right window
    glVertex2f(0.915f, 0.08f);
    glVertex2f(0.915f, 0.25f);
    glVertex2f(0.88f, 0.165f);
    glVertex2f(0.95f, 0.165f);

    glEnd();



    // Door
    glColor3f(0.85f, 0.70f, 0.50f);
    glBegin(GL_QUADS);
    glVertex2f(0.75f, -0.4f);
    glVertex2f(0.86f, -0.4f);
    glVertex2f(0.86f, -0.15f);
    glVertex2f(0.75f, -0.15f);
    glEnd();



    //Tree
   // Tree trunk
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.89f, -0.3f);
    glVertex2f(-0.84f, -0.3f);
    glVertex2f(-0.84f, -0.05f);
    glVertex2f(-0.89f, -0.05f);
    glEnd();

   // Tree leaves

   // Bottom triangle
    glColor3f(0.0f, 0.45f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.99f, -0.1f);
    glVertex2f(-0.75f, -0.1f);
    glVertex2f(-0.87f, 0.20f);
    glEnd();

    // Middle triangle
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.97f, 0.06f);
    glVertex2f(-0.77f, 0.06f);
    glVertex2f(-0.87f, 0.40f);
    glEnd();

    // Top triangle
    glColor3f(0.0f, 0.7f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.94f, 0.25f);
    glVertex2f(-0.79f, 0.25f);
    glVertex2f(-0.865f, 0.55f);
    glEnd();


    // LEFT CAR
glPushMatrix();
glTranslatef(leftCar, -0.75f, 0.0f);

// Body
glColor3f(1.0f, 0.71f, 0.76f);
glBegin(GL_QUADS);
    glVertex2f(-0.175f, -0.09f);
    glVertex2f( 0.175f, -0.09f);
    glVertex2f( 0.175f,  0.09f);
    glVertex2f(-0.175f,  0.09f);
glEnd();

// Roof
glColor3f(0.9f, 0.50f, 0.58f);
glBegin(GL_QUADS);
    glVertex2f(-0.10f,  0.09f);
    glVertex2f( 0.10f,  0.09f);
    glVertex2f( 0.07f,  0.20f);
    glVertex2f(-0.07f,  0.20f);
glEnd();

// Windows
glColor3f(0.6f, 0.8f, 1.0f);
// Front window
glBegin(GL_QUADS);
    glVertex2f(-0.09f, 0.09f);
    glVertex2f(-0.01f, 0.09f);
    glVertex2f(-0.01f, 0.18f);
    glVertex2f(-0.068f, 0.18f);
glEnd();
// Rear window
glBegin(GL_QUADS);
    glVertex2f(0.01f, 0.09f);
    glVertex2f(0.09f, 0.09f);
    glVertex2f(0.068f, 0.18f);
    glVertex2f(0.01f, 0.18f);
glEnd();


// Wheels
glColor3f(0.0f, 0.0f, 0.0f);
drawCircle(-0.10f, -0.09f, 0.05f, 100);
drawCircle( 0.10f, -0.09f, 0.05f, 100);

glPopMatrix();


// RIGHT CAR
glPushMatrix();
glTranslatef(rightCar, -0.40f, 0.0f);

// Body
glColor3f(0.93f, 0.88f, 0.78f);
glBegin(GL_QUADS);
    glVertex2f(-0.175f, -0.09f);
    glVertex2f( 0.175f, -0.09f);
    glVertex2f( 0.175f,  0.09f);
    glVertex2f(-0.175f,  0.09f);
glEnd();

// Roof
glColor3f(0.29f, 0.0f, 0.51f);
glBegin(GL_QUADS);
    glVertex2f(-0.10f,  0.09f);
    glVertex2f( 0.10f,  0.09f);
    glVertex2f( 0.07f,  0.20f);
    glVertex2f(-0.07f,  0.20f);
glEnd();

// Windows
glColor3f(0.6f, 0.8f, 1.0f);
// Front window
glBegin(GL_QUADS);
    glVertex2f(-0.09f, 0.09f);
    glVertex2f(-0.01f, 0.09f);
    glVertex2f(-0.01f, 0.18f);
    glVertex2f(-0.068f, 0.18f);
glEnd();
// Rear window
glBegin(GL_QUADS);
    glVertex2f(0.01f, 0.09f);
    glVertex2f(0.09f, 0.09f);
    glVertex2f(0.068f, 0.18f);
    glVertex2f(0.01f, 0.18f);
glEnd();

// Wheels
glColor3f(0.0f, 0.0f, 0.0f);
drawCircle(-0.10f, -0.09f, 0.05f, 50);
drawCircle( 0.10f, -0.09f, 0.05f, 50);

glPopMatrix();


    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'd':
        case 'D':
            isDay = true;
            break;
        case 'n':
        case 'N':
            isDay = false;
            break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Big Ben");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
