// TODO: CONVERT THIS TO ARRAY!
uniform sampler2D u_sampler;

varying float v_textureID;

void main()
{
    //gl_FragColor = texture2D(u_sampler, v_texCoord);
    gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
