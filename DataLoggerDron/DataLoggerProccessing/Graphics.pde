
float separation = 20;
color colorPerData[] = {color(180,0,0), color(0,180,0), color(0,0,180)};

void drawGraphs(float Xpos, float Ypos, float w, float h,ArrayList<Float[]> data) {

  noFill();
  stroke(200);
  strokeWeight(3);
  rect(Xpos,Ypos,w,h);
  
  float x = 0;
  float lastY[] = new float[dataLength];
  for (int i = 0;i < dataLength;i++) {
      lastY[i] = Ypos;
    }
  boolean erase = false;

  for (Float segment[] : data) {
    for (int i = 0;i < dataLength;i++) {
      float y = map(segment[i],0,1023.0,0,h) + Ypos;
      stroke(colorPerData[i]);
      line(x + Xpos,height - lastY[i],x + separation + Xpos,height - y);
      lastY[i] = y;
    }
    x += separation;
    if (x > w) {
      x = 0;
      erase = true;
      break;
    }
  }
  if (erase) {
    data.clear();}
}