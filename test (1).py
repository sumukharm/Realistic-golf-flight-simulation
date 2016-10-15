# Authors : Sumukha RM , Naresh V

from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
import sys
import time

name = 'Golf Ball Simulation'
ctr=0
f=open("simData",'r');
content=f.read();
lines=content.splitlines();
max_x=0
max_y=0
max_z=0
frames=0
def main():
    global max_x,max_y,max_z,frames
    for l in lines:
      p=l.split();
      if int(float(p[0]))>max_x:
	max_x=int(float(p[0]))
      if int(float(p[1]))>max_y:
	max_y=int(float(p[1]))
      if int(float(p[2]))>max_z:
	max_z=int(float(p[2]))
      frames=frames+1
    print(max_x,max_y,max_z)
    
    
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH)
    glutInitWindowPosition(20,20);
    glutInitWindowSize(600,600)
    glutCreateWindow(name)

    
    glClearColor(0.,0.,0.,0.)
    glMatrixMode(GL_PROJECTION)
    gluOrtho2D(0,600,0,600);
    ctr=0
    '''glShadeModel(GL_SMOOTH)
    glEnable(GL_CULL_FACE)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_LIGHTING)
    lightZeroPosition = [10.,4.,10.,1.]
    lightZeroColor = [0.8,1.0,0.8,1.0] #green tinged
    glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor)
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1)
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05)
    glEnable(GL_LIGHT0)
    
    
    gluPerspective(40.,1.,1.,40.)
    
    gluLookAt(0,0,10,
              0,0,0,
              0,1,0)'''
    
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glutDisplayFunc(display)
    glPushMatrix()
    #time.sleep(1.0)
    glutMainLoop()
    return

def display():
    global ctr,frames
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
    
    #glutSolidSphere(2,20,20)
    for i in xrange(ctr):
       if ctr>frames:
         return
       if ctr==1:
         time.sleep(1.0);
       points=lines[i].split()       
       x=float(points[0]);
       y=float(points[1]);
       glBegin(GL_POINTS)
       glColor3f(x/y,y/x,x)
       glVertex2i(int(x*7),int(y*7))
       glEnd()
    ctr=ctr+1
    glFlush()
    glutSwapBuffers()
    glutPostRedisplay()


if __name__ == '__main__': main()
