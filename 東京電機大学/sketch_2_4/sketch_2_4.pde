PVector eyePos;
Shape shape;

LightSource lightSource;
FColor      ambientIntensity;

FColor kAmb;
FColor kDif;
FColor kSpe;
float shininess;

void setup()
{
  size(512,512);
  background(color(0,0,0));
  
  noSmooth();
  noLoop();
  
  //定数の初期化
  eyePos = new PVector(0,0,-5); //視点位置
  
  Sphere sph = new Sphere(); //球オブジェクトを生成
  sph.center.set(0,0,5);//球の中心位置
  sph.radius = 1.0f; //球の半径
  shape = sph;
  
  PointLightSource pls = new PointLightSource();//点光源オブジェクトを生成
  pls.position.set(-5,5,-5); //点光源の位置
  pls.intensity.set(1.00,1.00,1.00); //点光源の強度
  lightSource = pls;
  
  ambientIntensity = new FColor(1.0); //環境光の強度
  
  kAmb = new FColor(0.01);//環境光反射係数
  kDif = new FColor(0.60,0.00,0.00); //拡散反射係数
  kSpe = new FColor(0.30); //鏡面反射係数
  shininess = 8;//光沢度
}// void setup()

void draw()
{
  PVector pw = new PVector(); //スクリーン上の点
  pw.z = 0;
  
  for(int y = 0;y < height; ++y)
  {
    pw.y = y;
    for(int x = 0; x < width; ++x)
    {
      pw.x = x;
      
      PVector eyeDir = PVector.sub(pw, eyePos); // 視線ベクトル
      Ray eyeRay = new Ray(eyePos,eyeDir); //視線レイ
      
      stroke(color(100,149,237)); //背景色
      
      //交差判定を試みる
      IntersectionPoint res = shape.testIntersection(eyeRay);
      if( res != null) //交点が存在する場合
      {
        //放射輝度を保存するためのFVolorのインスタンスを生成
        FColor col = new FColor(0,0,0);
        
        //環境光の反射光の放射輝度を計算する
        col.add(colorPi(kAmb, ambientIntensity));
        
        //交点におけるライティングを計算する
        Lighting ltg = new Lighting(res.distance,,res.normal);
        
        //法線ベクトルと入射ベクトルの内積を計算して、値の範囲を[0.1]に制限する
        float nlDot = constrain(sphereN.dot(lightDir),0,1);
        
        //拡散反射光の放射輝度を計算する
        col.add(kDif * lightIntensity * nlDot);
        
        if(nlDot > 0)
        {
          PVector refDir = vectorSigma(2*nlDot,sphereN,-1,lightDir); //正反射ベクトル
          PVector invEyeDir = vectorSigma(-1,eyeDir.copy()); //視線ベクトルの逆ベクトル
          invEyeDir.normalize();
          
          //法線ベクトルの逆ベクトルと正反射ベクトルの内積を計算して、値を[0,1]に制限する
          float nlDot = constrain(invEyeDir.dot(refDir),0,1);
          
          //鏡面反射光の放射輝度を計算する
          col.add(kSpe * lightIntensity * pow(vrDot,shininess));
        }//if
        
        stroke(col.toColor());//colをcolorに変換して描画色に設定する
      } //if
      
      point(x,y);
    }//for
  }//for
  
}//void draw()
