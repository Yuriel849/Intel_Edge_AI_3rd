import turtle

## 전역 변수 선언 부분 ##
swidth, sheight = 500, 500


## 메인 코드 부분 ##
turtle.title('Drawing Android Bugdroid with Python Turtle')
turtle.shape('turtle')
turtle.setup(width = swidth + 50, height = sheight + 50)
turtle.screensize(swidth, sheight)

## 선과 채우기 색 설정
turtle.pencolor('#3DDC84')
turtle.fillcolor('#3DDC84')

## 몸통 그리기 ##
turtle.penup()
turtle.goto(-swidth / 5, sheight / 5)
turtle.begin_fill()
turtle.pendown()
turtle.goto(swidth / 5, sheight / 5)
turtle.goto(swidth / 5, -sheight / 5)
turtle.goto(-swidth / 5, -sheight / 5)
turtle.goto(-swidth / 5, sheight / 5)
turtle.end_fill()

## 오른팔 그리기 ##
turtle.penup()
turtle.goto(swidth / 5 + 60, -sheight / 5 + 50)
turtle.begin_fill()
turtle.pendown()
turtle.left(90)
turtle.forward(120)
turtle.circle(25, 180)
turtle.forward(120)
turtle.circle(25, 180)
turtle.end_fill()

## 왼팔 그리기 ##
turtle.penup()
turtle.goto(-swidth / 5 - 10, -sheight / 5 + 50)
turtle.begin_fill()
turtle.pendown()
turtle.forward(120)
turtle.circle(25, 180)
turtle.forward(120)
turtle.circle(25, 180)
turtle.end_fill()

## 머리 그리기 ##
turtle.penup()
turtle.goto(-swidth / 5, sheight / 5 + 10)
turtle.begin_fill()
turtle.pendown()
turtle.right(90)
turtle.forward(200)
turtle.left(90)
turtle.circle(100, 180)
turtle.end_fill()

## 눈 그리기 ##
turtle.penup()
turtle.goto(swidth / 5 - 60, sheight / 5 + 40)
turtle.left(90)
turtle.pencolor('white')
turtle.fillcolor('white')
turtle.begin_fill()
turtle.pendown()
turtle.circle(10)
turtle.end_fill()
turtle.penup()
turtle.goto(-swidth / 5 + 60, sheight / 5 + 40)
turtle.begin_fill()
turtle.pendown()
turtle.circle(10)
turtle.end_fill()
turtle.pencolor('#3DDC84')
turtle.fillcolor('#3DDC84')

## 안테나 그리기 ##
turtle.penup()
turtle.goto(0, sheight / 5 + 10)
turtle.left(60)
turtle.forward(100)
turtle.begin_fill()
turtle.pendown()
turtle.forward(30)
turtle.circle(5, 180)
turtle.forward(30)
turtle.end_fill()
turtle.penup()
turtle.goto(0, sheight / 5 + 10)
turtle.setheading(115)
turtle.forward(100)
turtle.begin_fill()
turtle.pendown()
turtle.forward(30)
turtle.circle(5, 180)
turtle.forward(30)
turtle.end_fill()

## 오른 다리 그리기 ##
turtle.penup()
turtle.goto(swidth / 5 - 30, -sheight / 5)
turtle.begin_fill()
turtle.pendown()
turtle.setheading(270)
turtle.forward(100)
turtle.circle(-25, 180)
turtle.forward(100)
turtle.end_fill()

## 왼 다리 그리기 ##
turtle.penup()
turtle.goto(-swidth / 5 + 80, -sheight / 5)
turtle.begin_fill()
turtle.pendown()
turtle.setheading(270)
turtle.forward(100)
turtle.circle(-25, 180)
turtle.forward(100)
turtle.end_fill()

turtle.hideturtle()
turtle.done()
