uniform sampler2D texture;

void main(){
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

	gl_FragColor = vec4(vec3(pixel.r + pixel.g + pixel.b)/3.0, pixel.a);
}