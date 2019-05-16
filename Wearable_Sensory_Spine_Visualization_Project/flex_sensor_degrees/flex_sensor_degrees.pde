import processing.serial.*;

Serial myPort;   
float xMid=500.0,yMid=500.0;
float x,y;
   float flexArray[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0};

void setup() {
  size(1000, 1000);
  
  println(Serial.list());  // print the serial port

  myPort = new Serial(this, Serial.list()[3], 9600);

  background(0);

}

void draw() {
serialEvent(myPort);
}

void serialEvent (Serial myPort) 
 {
     // println("serialevent");
   int count=0;
   float angle=0.0;
String inString = myPort.readStringUntil('\n');

 if (inString != null) 
 {
 String[] parts =inString.split("-");
 count = int(trim(parts[0]));
 inString = parts[1];
 // trim off any whitespace:
 inString = trim(inString);
 // convert to an int and map to the screen height:
 angle= float(inString);
 angle = radians(angle);
 flexArray[count]=angle;
  println(inString);

  for(int i=0;i<6;i++){
   drawVertex(i,flexArray[i],flexArray[0]);
   
 }
 //drawVertices(flexArray);
 }else{
    println(count + inString);

     background(0);
 }// END InString is not Null


 }// END SerialEvent 
 
 void drawVertex(int count, float angle,float rotation){
  float radius=75.0;
  x=500.0+sin(angle)*radius;
  y=(825.0-((radius*2)*count))-cos(angle)*radius;
  smooth();
  noFill();
  stroke(255);
  strokeWeight(4);
  beginShape();
  curveVertex(500, 900-((radius*2)*count)); // the first control point
  curveVertex(500, 900-((radius*2)*count)); // is also the start point of curve
  curveVertex(500, 825-((radius*2)*count));
  curveVertex(x, y); // the last point of curve
  curveVertex(x, y); // is also the last control point
  endShape(); 
 }
 void drawVertices(float[] arr){
  float radius=75.0;
  float x=500.0;
  float y=900.0;
  for(int i=1;i<7;i++){
  smooth();
  noFill();
  stroke(51);
  strokeWeight(4);
  //rotate(arr[i-1]);
  beginShape();
  curveVertex(x, y); // the first control point
  curveVertex(x, y); // is also the start point of curve
  x=500.0+sin(arr[i])*radius;
  y=(825.0-((radius*2)*(i-1)))-cos(arr[i])*radius;
  curveVertex(500, 825-((radius*2)*(i-1)));
  curveVertex(x, y); // the last point of curve
  curveVertex(x, y); // is also the last control point
  endShape(); 
   
 }
   
 }
