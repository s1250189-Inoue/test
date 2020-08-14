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

class FColor
{
  public float red, green, blue;
  public FColor(){ this(0,0,0); }
  public FColor(float v){ this(v,v,v); }
  public FColor(float r, float g, float b)
  {
    red = r; green = g; blue = b;
  } 
  public color toColor()
  {
      return toColor(1.0);
  }
  public color toColor(float k)
  {
    return toColor(k,k,k);
  }
  public color toColor(float kr, float kg, float kb)
  {
    int r = (int)(255 * constrain(red,   0, kr));
    int g = (int)(255 * constrain(green, 0, kg));
    int b = (int)(255 * constrain(blue,  0, kb));
    return color(r, g, b);
  }
  public FColor copy()
  {
    return new FColor(red, green, blue);
  }
  /** 
   * @deprecated FColor#get() is deprected.
   * @see FColor#copy() 
   */
  public FColor get()
  {
    return copy();
  }
  public void set(float r, float g, float b)
  {
    red = r;
    green = g;
    blue = b;
  }  
  public void add(FColor fc)
  {
    red += fc.red;
    green += fc.green;
    blue += fc.blue;
  }
  public void mult(FColor fc)
  {
    red *= fc.red;
    green *= fc.green;
    blue *= fc.blue;    
  }
  public String toString()
  {
    return "[ " + red + ", " + green + ", " + blue + " ]";
  }
}
FColor colorPi(FColor ... params)
{
  FColor res = new FColor(1,1,1);
  for(FColor fc : params)
    res.mult(fc);
  return res;
}

class Ray
{
  public PVector start, direction;
  public Ray(){ this(new PVector(), new PVector()); }
  public Ray(PVector s, PVector d)
  {
    start = s.copy();
    direction = d.copy();
  }
  public PVector getPoint(float t)
  {
    return vectorSigma(start, t, direction);
  }
}
class IntersectionPoint 
{
  public float distance;
  public PVector position;
  public PVector normal; 
}

abstract class Shape
{
  public abstract IntersectionPoint testIntersection(Ray ray);
}

class Lighting
{
  public float distance; 
  public FColor intensity;
  public PVector direction;
}

abstract class LightSource
{
  public abstract Lighting lightingAt(PVector pos);  
}

/////////////////////////////////////////////////////////////////////

class Sphere extends Shape 
{
  public PVector center;
  public float radius;
  
  public Sphere(){ this(new PVector(), 1); }
  public Sphere(PVector c, float r)
  {
    center = c.copy();
    radius = r;
  }
  
  public IntersectionPoint testIntersection(Ray ray)
  {
    // TODO: Implement this method!
    PVector tmp = vectorSigma(1.0,ray.start,-1.0,center); //レイの始点-球の中心
    
    //二次方程式の係数(At~2 + Bt + C = 0)
    float A = ray.direction.magSq();
    float B = 2.0*ray.direction.dot(tmp);
    float C = tmp.magSq() - radius*radius;
    
    float D = B*B - 4*A*C; //判別式
    float t = -1;
    
    if(D == 0)
    {
      t = -B / (2*A);
    }//if
    else if(D > 0)
    {
      float t1 = (-B - sqrt(D)) / (2*A);
      float t2 = (-B + sqrt(D)) / (2*A);
      
      t = t1 > 0 && t2 > 0 ? min(t1,t2) : max(t1,t2);
    }//else if
  
  if(t > 0)//交点がある場合
  {
    IntersectionPoint res = new IntersectionPoint(); //交点情報を生成
    res.distance = t*ray.direction.mag(); //交点までの距離
    res.position = vectorSigma(1,ray.start,t,ray.direction); //交点位置
    res.normal = PVector.sub(res.position,center); //交点における法線方向
    res.normal.normalize();
    return res;
  }//if
  else
  {
    return null;
  }//else
  }
}

class Plane extends Shape
{
  public PVector normal;
  public PVector position;
  
  public Plane(){ this(new PVector(0,1,0), new PVector(0,0,0)); }
  public Plane(PVector n, PVector p)
  {
    normal = n.copy();
    normal.normalize();
    position = p.copy();
  }
  public IntersectionPoint testIntersection(Ray ray)
  {
    float dn_dot = ray.direction.dot(normal);
    if ( dn_dot != 0 )
    {
      float t = (position.dot(normal) - ray.start.dot(normal)) / dn_dot;
      if ( t > 0 )
      {
        IntersectionPoint res = new IntersectionPoint();
        res.distance = t * ray.direction.mag();
        res.position = ray.getPoint(t);
        res.normal = normal.copy();
        return res;
      }//if
    }//if
    return null;    
  }
}


class PointLightSource extends LightSource
{
  public PVector position;
  public FColor intensity;
  
  public PointLightSource(){ this(new PVector(0,0,0), new FColor(1,1,1)); }
  public PointLightSource(PVector pos, FColor fc)
  {
    position = pos.copy();
    intensity = fc.copy();   
  }
  
  public Lighting lightingAt(PVector pos)
  {  
    Lighting res = new Lighting();
    res.direction = PVector.sub(position, pos);
    res.distance = res.direction.mag();
    res.direction.normalize();
    res.intensity = intensity.copy();
    return res;
  }
}

class DirectionalLightSource extends LightSource
{
  public PVector direction;
  public FColor intensity;

  public DirectionalLightSource(){ this(new PVector(0,-1,0), new FColor(1,1,1)); }
  public DirectionalLightSource(PVector dir, FColor fc)
  {
    direction = dir.copy();
    direction.normalize();
    intensity = fc.copy();      
  }  
  public Lighting lightingAt(PVector pos)
  {
    Lighting res = new Lighting();
    res.direction = PVector.mult(direction, -1);
    res.intensity = intensity.copy();
    res.distance = Float.MAX_VALUE;
    return res;
  }  
}
