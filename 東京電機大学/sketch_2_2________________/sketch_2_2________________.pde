// VectorSigmaの宣言
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
PVector eyePos        = new PVector(0.0f,0.0f,-5.0f);      // 視点位置
PVector spherePos     = new PVector(0.0f,0.0f,5.0f);       // 球の中心位置
float   sphereR       = 1.0;                               // 球の半径

PVector lightPos      = new PVector(-5.0f,5.0f,-5.0f);     //光源位置
float lightIntensity  = 1.0;                                  //光源の強度
float ambientIntensity= 0.1;                                  //環境光の強度

float Kamb            = 0.01;                              //環境反射係数
float kDif            = 0.69;                              //拡散反射係数
float kSpe            = 0.3;                               //鏡面反射係数
float shininess       = 8;                                 //光沢度
 
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
       
      PVector eyeDir = vectorSigma(1.0,pw,-1.0,eyePos);           // 視線方向 視線ベクトル
      PVector tmp    = vectorSigma(1.0,eyePos,-1.0,spherePos);     // 視点 - 球の中心
       
      // 二次方程式の係数(At^2 + Bt + C = 0)
      float A = eyeDir.magSq();
      float B = 2.0 * eyeDir.dot(tmp);
      float C = tmp.magSq() - sphereR*sphereR;
       
      float D = B*B - 4*A*C; // 判別式
      
      float t = -1;
      if(D==0)
      {
        t = -B / (2*A);
      }//if
      else if (D > 0)
      {
        float t1 = (-B - sqrt(D))/(2*A);
        float t2 = (-B + sqrt(D))/(2*A);
        
        t= t1 > 0 && t2 > 0 ? min(t1,t2) : max(t1,t2);
      }//else if
      
      stroke(color(100,149,237)); //背景色
      if(t > 0)
      {
        //環境光の反射光の放射輝度を計算する(Ra)
         float radianceAmb = Kamb * ambientIntensity;
        PVector intPos = vectorSigma(1,eyePos,t,eyeDir);      //交点位置
        PVector lightDir = PVector.sub(lightPos, intPos);    //入射ベクトル
        lightDir.normalize();
        PVector sphereN = PVector.sub(intPos,spherePos);     //法線ベクトル 
        sphereN.normalize();
      
      
      //法線ベクトルと入射ベクトルの内積を計算して、値の範囲を[0,1]に制限する。
      float nlDot = constrain(sphereN.dot(lightDir), 0, 1);
      
      //拡散反射光の放射輝度を計算する (Rd)
      float radianceDif    = kDif * lightIntensity * nlDot;
      
      float radianceSpe    = 0.0f;                           //鏡面反射光の放射輝度
      if(nlDot > 0)
      {
        PVector refDir     = vectorSigma(2*nlDot,sphereN,-1,lightDir);                               //正反射ベクトル
        PVector invEyeDir  = vectorSigma(-1,eyeDir.copy());  //視線ベクトルの逆ベクトル
        invEyeDir.normalize();
        
        //視線ベクトルの逆ベクトルと正反射ベクトルの内積を計算して、値の範囲を[0,1]に制限する
        float vrDot        = constrain(invEyeDir.dot(refDir),0,1);
        
        //鏡面反射光の放射輝度を計算する (Rs)
        radianceSpe        = kSpe * lightIntensity * pow(vrDot,shininess); 
      }//if
      
      //反射光の放射輝度を計算して、値の範囲を[0,1]に制限する
      float radiance = constrain(radianceAmb + radianceDif +radianceSpe, 0, 1);
      int gray = (int)(255 * radiance);
      stroke(color(gray,gray,gray));
      } //if
      
      point(x,y);
    }//for
  }//for
}// void draw()
