precision mediump float;
uniform sampler2D  uYTex;     // The Y texture sampler.
uniform sampler2D  uUTex;     // The U texture sampler.
uniform sampler2D  uVTex;     // The V texture sampler.
varying vec2       vTexCoord; // Texture coordinates.

/*
 * This shader just shows the texture on the screen, without performing any
 * processing to it. Therefore, just set the color of the fragment to the
 * same as in the texture.
 */
void main()
{
   // Look up the texture and set the fragment color
   // to the same value of the texture at the same location
   vec3 yuv;
   vec2 lookupCoord = vec2(vTexCoord.x, vTexCoord.y);
   yuv.r = texture2D( uYTex, lookupCoord );
   yuv.b = texture2D( uVTex, lookupCoord );
   yuv.g = texture2D( uUTex, lookupCoord );

   gl_FragColor.b = 1.164 * ( yuv.r - 0.0625)                          + 2.018 * ( yuv.g - 0.5);
   gl_FragColor.g = 1.164 * ( yuv.r - 0.0625) - 0.813 * ( yuv.b - 0.5) - 0.391 * ( yuv.g - 0.5);
   gl_FragColor.r = 1.164 * ( yuv.r - 0.0625) + 1.596 * ( yuv.b - 0.5);
   gl_FragColor.a = 1.0;
}