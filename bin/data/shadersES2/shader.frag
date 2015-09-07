precision highp float;


void main()
{
    float windowWidth = 1024.0;
    float windowHeight = 768.0;
    
    float r = gl_FragCoord.x / windowWidth;
    float g = gl_FragCoord.y / windowHeight;
    float b = 1.0;
    float a = 1.0;
	gl_FragColor = mouseColor;
}
