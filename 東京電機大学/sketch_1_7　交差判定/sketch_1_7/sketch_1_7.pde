
PVector vectorSigma(Object ... params)
{
  PVector result = new PVector(0,0,0);
  for(int i = 0; i < params.length;)
  {
    if ( params[i] instanceof Number )
    {
      if ( i+1 > params.length-1 || !(params[i+1] instanceof PVector) )
        throw new IllegalArgumentException();
      
      float k = ((Number)params[i]).floatValue();
      PVector v = (PVector)params[i+1];
      
      result.add(PVector.mult(v, k));
      i += 2;
    }
    else if ( params[i] instanceof PVector )
    {
      PVector v = (PVector)params[i];
      result.add(v);
      ++i;
    } 
  }//for
  return result;
}

// 定数の初期化
PVector eyePos    = new PVector(0.0f,0.0f,-5.0f); /* 穴埋め1 */; // 視点位置
PVector spherePos = new PVector(0.0f,0.0f,5.0f); /* 穴埋め2 */; // 球の中心位置
float   sphereR   = 1.0;/* 穴埋め3 */; // 球の半径
 
void setup()
{
  size(512, 512);
  background(color(0,0,0));
   
  noSmooth();
  noLoop();
}// void setup()
 
void draw()
{
  PVector pw = new PVector();
  pw.z = 0;
   
  for(int y = 0; y < height; ++y)
  {
    pw.y = map(y, 0, height-1, 1, -1);
    for(int x = 0; x < width; ++x)
    {
      pw.x = map(x, 0, width-1, -1,  1);
       
      PVector eyeDir = vectorSigma(1.0,eyePos, -1.0,pw);/* 穴埋め6 */; // 視線方向 視線ベクトル
      PVector tmp    = vectorSigma(1.0,eyePos,-1.0,spherePos);/* 穴埋め7 */; // 視点 - 球の中心
       
      // 二次方程式の係数(At^2 + Bt + C = 0)
      float A = abs(eyeDir.dot(eyeDir));
      float B = 2*eyeDir.dot(tmp);
      float C = abs(tmp.dot(tmp)) - sphereR*sphereR;
       
      float D = B*B - 4*A*C; // 判別式
       
      if(D>0)
        stroke(color(255,0,0));
      else
        stroke(color(0,0,255));
         
      point(x, y);
    }//for
  }//for
}// void draw()
