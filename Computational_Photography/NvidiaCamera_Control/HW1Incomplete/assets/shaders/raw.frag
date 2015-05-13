precision mediump float;
uniform sampler2D  rawTex;     // The Y texture sampler.

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
   vec3 col;
   vec2 lookupCoord = vec2(vTexCoord.x, vTexCoord.y);
   col.r = texture2D( rawTex, lookupCoord );
   col.b = texture2D( rawTex, lookupCoord );
   col.g = texture2D( rawTex, lookupCoord );

   gl_FragColor.b = col;//1.164 * ( col.r - 0.0625)                          + 2.018 * ( col.g - 0.5);
   gl_FragColor.g = col;// 1.164 * ( col.r - 0.0625) - 0.813 * ( col.b - 0.5) - 0.391 * ( col.g - 0.5);
   gl_FragColor.r = col;// 1.164 * ( col.r - 0.0625) + 1.596 * ( col.b - 0.5);
   gl_FragColor.a = 1.0;
}