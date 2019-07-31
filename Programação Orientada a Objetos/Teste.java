import java . util . Scanner ;
class Main {
public static void main ( String [] args ) {
int a , b ;
Scanner sc = new Scanner ( System . in ) ;
a = sc . nextInt () ;
b = sc . nextInt () ;
Operator sum = new Operator ('+', a , b ) ;
Operator sub = new Operator ('-', a , b ) ;
System . out . println ( sum . getAnsw () ) ;
System . out . println ( sub . getAnsw () ) ;
}
}
class Operator {
private int answ ;
public Operator ( char operation , int a , int b ) {
if( operation == '+') {
this . answ = a + b ;
} else if( operation == '-') {
this . answ = a - b ;
}
}
public int getAnsw () {
return this . answ ;
}
}