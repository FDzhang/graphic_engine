     uniform sampler2D sampler2d; 
     varying mediump vec2 varCoord; 

     void main (void) 
     { 
     	 int i =0; 
     	 int j = 0; 
     	 mediump float CoordW =-0.22917; 
     	 mediump float CoordH =-0.104167; 
     	 mediump vec4 temp=vec4(0,0,0,0); 
     	for(i=0;i<10;i++) 
     	 { 
     	   for(j=0;j<30;j++) 
     		{	  
     		   temp +=texture2D(sampler2d,varCoord+vec2(CoordW,CoordH)); 
     		  CoordW += 0.015625; 

     		} 
     	   CoordH +=0.02083; 
     		CoordW =-0.22917; 
     	 } 

			  if(temp.r >=1.0&&(temp.g >=1.0)&&(temp.b >=1.0))
    			  {
    				 gl_FragColor = temp/300.0;
   
    			  }
    			  else
    			  {
    				 gl_FragColor = temp;
    			  }

     			 // gl_FragColor = temp/300.0;
     } 
    