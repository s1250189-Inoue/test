
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


void setup()
{
  PVector v1 = new PVector(3, 4, 5);
  PVector v2 = new PVector(6, 7, 8);
  PVector v3 = new PVector(9, 10, 11);
  
  println("1. "  + v1 );
  println("2. "  + v2 );
  println("3. "  + v3 );
  
  println("4. "  + vectorSigma(v1,v2));
  println("5. "  + vectorSigma(3,v1,4,v2));
  v1 = v3.copy();
  println("1. "  + v1 );
  v1.y = 0;
  println("1. "  + v1 );
  println("1. "  + vectorSigma(2,v1,-5,v2,10,v3) );
  v2.dot(v3);
  println("1. "  + v2.dot(v3) );
  println(v2.cross(v3));
  vectorSigma(v1,v2);

}
