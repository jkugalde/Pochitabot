# importing the required module
import matplotlib.pyplot as plt
import math  
import numpy

def fwk(q1,q2):

    #leg lengths
    a11=25
    a12=50
    a21=50
    a22=25
    d=56.2

    q1=math.radians(q1)
    q2=math.radians(q2)

    E=2*a12*(d+a11*(math.cos(q2)-math.cos(q1)));
    F=2*a11*a12*(math.sin(q2)-math.sin(q1));
    G=d**2+2*a11**2+2*d*a11*math.cos(q2)-2*d*a11*math.cos(q1)-2*a11**2*math.cos(q2-q1);

    x=d+a11*math.cos(q2)+a12*math.cos(2*math.atan2((-F+math.sqrt(E**2+F**2-G**2)),(G-E)));
    y=a11*math.sin(q2)+a12*math.sin(2*math.atan2((-F-math.sqrt(E**2+F**2-G**2)),(G-E)));

    return [x,y]

def ivk(x,y):

    a11 = 25.0
    a12 = 50.0
    a21 = 50.0
    a22 = 25.0
    d = 56.2

    E1=-2*a11*x
    F1=-2*a11*y
    G1=a11**2-a12**2+x**2+y**2

    E2=2*a11*(-x+d)
    F2=-2*a11*y
    G2=d**2+a11**2-a12**2+x**2+y**2-2*d*x

    l1=E1**2+F1**2-G1**2

    q1=2*math.atan2(-F1+math.sqrt(abs(l1)),G1-E1)

    l2=E2**2+F2**2-G2**2

    q2=2*math.atan2(-F2-math.sqrt(abs(l2)),G2-E2)

    return [math.degrees(q1),math.degrees(q2)]

def elliptical(q1,a,b):
    
    #x y coordinates in an ellipse for ang q1

    r = a*b/(math.sqrt((b*math.cos(q1))**2+(a*math.sin(q1))**2))

    x = 28.1+r*math.cos(q1)
    y = 61+r*math.sin(q1)

    return [x,y]

q1 = numpy.linspace(30,150,50)
q2 = q1

rads = numpy.linspace(0,2*math.pi,200)

#draw task space

for i in range(50):
    for k in range(50):
       xy=fwk(q1[i],q2[k])
       plt.scatter(xy[0],xy[1],color='blue')

#draw ellipse

xcoord=numpy.zeros(200)
ycoord=numpy.zeros(200)

for i in range(200):
    xy=elliptical(rads[i],10,3)
    xcoord[i]=xy[0]
    ycoord[i]=xy[1]
    plt.scatter(xy[0],xy[1],color='red',s=20)

plt.xlabel('x[mm]')
plt.ylabel('y[mm]')
plt.title('Leg task space')
plt.show()

for i in range(200):
    xy=ivk(xcoord[i],ycoord[i])
    xcoord[i]=xy[0]
    ycoord[i]=xy[1]

plt.plot(xcoord,ycoord)
plt.xlabel('q1[rad]')
plt.ylabel('q2[rad]')
plt.title('Joint positions')
plt.show()




