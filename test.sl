﻿package org.my

// import sl.String
// import sl

int a = 10
printf("Hello world!")

//var c="Ni hao"
//println(c)
/*
class Base {
	int a
}

class MyClass : Base {
	int b
}

interface Itf {
	int b
}

Base xd = MyClass()

Itf ix = xd

func world(){
	var h = "hello"
	println(h)
}

// var data = "Data"
// println("Hello")
// world()

*/
/*
go { 
	println("Hello world:" + c)
}

world()

var nice = "Nice"
var strs=String[10]
//strs[0] = nice

// println(strs[0])
var x = strs[0]

func test(int v) {
	printf("%d", v)
}

func test(String v){
	printf(v)
}

test(15)
*/
/*
class Base {
	int a = 10
}

class MyFirst<T> : Base {
	int data
	T d2

	init(T d){
		d2=d
	}

	func show() : int {
		return data
	}

	var world=func(){
		println("Hello world:" + d2 )
	}


	operator -> ( func() what ){
		what()
	}

	//func world(){
	//	var s = "Hello:" + d2 + a
	//	println( s )	
	//}
}

var out="Out of "
var b=out

MyFirst<int> x(77)
x.world()
x-> {
	println("Array!")
}



*/

/*
func lu(int a){
	var str="hello"
	str = str + a
	println (str)
	println("Hello world"+a)
}

lu(12)


String v="Hi My World"
String n=v[3:2]
println(n)
*/
// =int

// enum MyEnum{ Red=1, Blue=2 }

// printf( "red=%d, data=%d\r\n", MyEnum.Red, MyFirst.data )

// String str = "Hello world!"
// println(str)

/*
int c=str.at(0)
printf( "c=%d\r\n", c )

var b = (c==0) ? 11 : 12
printf( "b=%d\r\n", b )

var tuple1 = ( 10, 20 )
var tuple2 = ( 20, 30 )


func mul( int a, int b ) : int x, int y {
	return a, b
}

var d, e := mul(10, 20)
printf("%d %d", d, e)
*/ 
// int x

// int[5] a=[1,2,3,4,5]
// printf( "o" + "a1=%d\r\n", a[0] )

/*
func myFirstFunc( int a, int b ) : int returnValue{
	var x=a/4
	int my=a

	if (a>2) x=5 else x=6

	a = a + 2

	printf( "a=%d b=%d x=%f my=%d\r\n", a,b,x, my )
	return my
}

var v= myFirstFunc( 10, 20 )
printf("%d", v)
*/

 /*
const y=16;
switch(y){
	case 16:
		printf("y=16\r\n")
}

// int[] arr = [10, 20]

	for( var i=0; i<10; i++ )
	{
		var a = i
		if( i < 5 ) a = 10+i
		printf("%d ", a)
	}



func add( int a, var b ) : var c{
	c = a + b
}

var x = add( 10, 5 )
printf("x=%d", x)


class MyFirst{
	int a
	var b

	init(var i){
		b = i
	}

	func inc() {
		a++
		b++
	}
}

const pi=3.1415
var my=MyFirst(5)
my.a = 10				
printf("pi=%f my.a=%d my.b=%d\r\n", pi, my.a, my.b)

enum MyEnum { red, blue=2, green }


my{
	inc()
}
my.inc()
printf("enum red:%d blue=%d green=%d\r\n", MyEnum.red, MyEnum.blue, MyEnum.green)

y=y+1

// var o=add( y, 10 )		// Call c function

//int b=sl.math.addii( 3, 4 )
//printf( "b %d\r\n", b )
//var str = "I want a keyboard."

printf( "Hello world\r\n" )

func myFirstFunc( int a, int b ) : int returnValue{
	var x=a/4
	int my=a

	if (a>2) x=5 else x=6

	a = a + 2

	printf( "a=%d b=%d x=%f\r\n", a,b,x );

	printf( "hello world: %f\r\n", a+b+x );

	while( my < 6 ){
		printf( "while: %d\r\n", my ) 		
		var zz = 1 
		my = my + zz
	}
	
	printf( " num %x\r\n", 4 | 1 );

	for( var i=0; i<5; i++ ){
		printf("for %d \r\n", i)
	}

	printf( "  inc %d\r\n", my++ );
	printf( "  inc %d\r\n", my );
	return my;
}

func second( int a ) : (int b, int c){
	b=a
	c=10
}

func tmp( var a ){
	if( a is int )		
		printf("int")
	else		
		printf("other")
}

var u;

tmp(10);

u=myFirstFunc( a=3, 4 )
printf( "return %d\r\n", u )

switch u {
	case 1:
		printf("1")
	case 2,3:
		printf("2 or 3")
	default:
		printf("default")
}



*/
			/*
// var bb, cc:=second( 15 )
// printf( "bb %d, cc %d\r\n", bb, cc )
class FirstClass<T, R> {
	int a
	int c
	T b
	R r

	protected:
	func inc(){
		a++
	}

	init{	// 构造函数
		printf("\r\n INIT %d\r\n", r)
	}		

	finalize{
	}	// 析构函数
}

FirstClass<int> cls

FirstClass cls={ b=10; r=20 }

int x = cls.b = 10

cls.inc()

printf("b %d\r\n", cls.b);

cls{
	c = 20
	printf("c %d %d\r\n", c, x);
}

												   */