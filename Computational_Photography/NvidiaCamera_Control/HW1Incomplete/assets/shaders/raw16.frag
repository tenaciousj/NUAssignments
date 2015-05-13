precision mediump float;
uniform sampler2D  uRAWTex;   // The RAW texture sampler.
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
   vec3 raw;
   vec2 lookupCoord = vec2(vTexCoord.x, vTexCoord.y);
   raw.r = texture2D( uRAWTex, lookupCoord );

   gl_FragColor.b = raw.r * 16.0f;
   gl_FragColor.g = raw.r * 16.0f;
   gl_FragColor.r = raw.r * 16.0f;
   gl_FragColor.a = 1.0;
}