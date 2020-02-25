#include <Game.h>

static bool flip;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube Texturing")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
	float texel[2];
} Vertex;

const int VERTEX_NUM{ 24 };

Vertex vertex[VERTEX_NUM];

/*Index of Poly / Triangle to Draw */
GLubyte triangles[36]
{
	// front
		0, 1, 2,
		2, 3, 0,
	// top
		6, 5, 4,
		4, 7, 6,
	// back
		8, 9, 10,
		10, 11, 8,

	// bottom
		14, 13, 12,
		12, 15, 14,

	// right
		16, 17, 18,
		18, 19, 16,

	// left
		20, 21, 22,
		22, 23, 20
};

/* Variable to hold the VBO identifier and shader data */
GLuint	index,		//Index to draw
		vsid,		//Vertex Shader ID
		fsid,		//Fragment Shader ID
		progID,		//Program ID
		vao = 0,	//Vertex Array ID
		vbo[1],		// Vertex Buffer ID
		positionID, //Position ID
		colorID,	// Color ID
		to,			// Texture ID 1 to 32
		textureID,	//Texture ID
		texelID;	// Texel ID
	
//const string filename = "texture.tga";
//const string filename = "cube.tga";

const string filename = "cube.tga";

int width; //width of texture
int height; //height of texture
int comp_count; //Component of texture
const int number = 4; //4 = RGBA

unsigned char* img_data;

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	/* Vertices counter-clockwise winding */
	vertex[0].coordinate[0] = -1.0f;
	vertex[0].coordinate[1] = -1.0f;
	vertex[0].coordinate[2] = 1.0f;

	vertex[1].coordinate[0] = 1.0f;
	vertex[1].coordinate[1] = -1.0f;
	vertex[1].coordinate[2] = 1.0f;

	vertex[2].coordinate[0] = 1.0f;
	vertex[2].coordinate[1] = 1.0f;
	vertex[2].coordinate[2] = 1.0f;

	vertex[3].coordinate[0] = -1.0f;
	vertex[3].coordinate[1] = 1.0f;
	vertex[3].coordinate[2] = 1.0f;

	// top
	vertex[4].coordinate[0] = 1.0f;
	vertex[4].coordinate[1] = 1.0f;
	vertex[4].coordinate[2] = 1.0f;

	vertex[5].coordinate[0] = -1.0f;
	vertex[5].coordinate[1] = 1.0f;
	vertex[5].coordinate[2] = 1.0f;


	vertex[6].coordinate[0] = -1.0f;
	vertex[6].coordinate[1] = 1.0f;
	vertex[6].coordinate[2] = -1.0f;

	vertex[7].coordinate[0] = 1.0f;
	vertex[7].coordinate[1] = 1.0f;
	vertex[7].coordinate[2] = -1.0f;

	

	//

	vertex[8].coordinate[0] = -1.0f;
	vertex[8].coordinate[1] = 1.0f;
	vertex[8].coordinate[2] = -1.0f;

	vertex[9].coordinate[0] = 1.0f;
	vertex[9].coordinate[1] = 1.0f;
	vertex[9].coordinate[2] = -1.0f;

	vertex[10].coordinate[0] = 1.0f;
	vertex[10].coordinate[1] = -1.0f;
	vertex[10].coordinate[2] = -1.0f;

	vertex[11].coordinate[0] = -1.0f;
	vertex[11].coordinate[1] = -1.0f;
	vertex[11].coordinate[2] = -1.0f;

	vertex[12].coordinate[0] = -1.0f;
	vertex[12].coordinate[1] = -1.0f;
	vertex[12].coordinate[2] = 1.0f;

	vertex[13].coordinate[0] = 1.0f;
	vertex[13].coordinate[1] = -1.0f;
	vertex[13].coordinate[2] = 1.0f;

	vertex[14].coordinate[0] = 1.0f;
	vertex[14].coordinate[1] = -1.0f;
	vertex[14].coordinate[2] = -1.0f;

	vertex[15].coordinate[0] = -1.0f;
	vertex[15].coordinate[1] = -1.0f;
	vertex[15].coordinate[2] = -1.0f;

	vertex[16].coordinate[0] = 1.0f;
	vertex[16].coordinate[1] = -1.0f;
	vertex[16].coordinate[2] = 1.0f;

	vertex[17].coordinate[0] = 1.0f;
	vertex[17].coordinate[1] = -1.0f;
	vertex[17].coordinate[2] = -1.0f;

	vertex[18].coordinate[0] = 1.0f;
	vertex[18].coordinate[1] = 1.0f;
	vertex[18].coordinate[2] = -1.0f;

	vertex[19].coordinate[0] = 1.0f;
	vertex[19].coordinate[1] = 1.0f;
	vertex[19].coordinate[2] = 1.0f;

	vertex[20].coordinate[0] = -1.0f;
	vertex[20].coordinate[1] = -1.0f;
	vertex[20].coordinate[2] = -1.0f;

	vertex[21].coordinate[0] = -1.0f;
	vertex[21].coordinate[1] = -1.0f;
	vertex[21].coordinate[2] = 1.0f;

	vertex[22].coordinate[0] = -1.0f;
	vertex[22].coordinate[1] = 1.0f;
	vertex[22].coordinate[2] = 1.0f;

	vertex[23].coordinate[0] = -1.0f;
	vertex[23].coordinate[1] = 1.0f;
	vertex[23].coordinate[2] = -1.0f;

	// ------------------------------------------------------------------------

	vertex[0].color[0] = 0.0f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 0.0f;

	vertex[1].color[0] = 0.0f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;

	vertex[2].color[0] = 0.0f;
	vertex[2].color[1] = 1.0f;
	vertex[2].color[2] = 0.0f;

	vertex[3].color[0] = 0.0f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;

	vertex[4].color[0] = 0.0f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 0.0f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;

	vertex[6].color[0] = 0.0f;
	vertex[6].color[1] = 1.0f;
	vertex[6].color[2] = 0.0f;

	vertex[7].color[0] = 0.0f;
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 0.0f;

	// top

	vertex[8].color[0] = 0.0f;
	vertex[8].color[1] = 1.0f;
	vertex[8].color[2] = 0.0f;

	vertex[9].color[0] = 0.0f;
	vertex[9].color[1] = 1.0f;
	vertex[9].color[2] = 0.0f;

	vertex[10].color[0] = 0.0f;
	vertex[10].color[1] = 1.0f;
	vertex[10].color[2] = 0.0f;

	vertex[11].color[0] = 0.0f;
	vertex[11].color[1] = 1.0f;
	vertex[11].color[2] = 0.0f;

	// bottom
	vertex[12].color[0] = 0.0f;
	vertex[12].color[1] = 1.0f;
	vertex[12].color[2] = 0.0f;

	vertex[13].color[0] = 0.0f;
	vertex[13].color[1] = 1.0f;
	vertex[13].color[2] = 0.0f;

	vertex[14].color[0] = 0.0f;
	vertex[14].color[1] = 1.0f;
	vertex[14].color[2] = 0.0f;

	vertex[15].color[0] = 0.0f;
	vertex[15].color[1] = 1.0f;
	vertex[15].color[2] = 0.0f;

	//left
	vertex[16].color[0] = 0.0f;
	vertex[16].color[1] = 1.0f;
	vertex[16].color[2] = 0.0f;

	vertex[17].color[0] = 0.0f;
	vertex[17].color[1] = 1.0f;
	vertex[17].color[2] = 0.0f;

	vertex[18].color[0] = 0.0f;
	vertex[18].color[1] = 1.0f;
	vertex[18].color[2] = 0.0f;

	vertex[19].color[0] = 0.0f;
	vertex[19].color[1] = 1.0f;
	vertex[19].color[2] = 0.0f;

	// right
	vertex[20].color[0] = 0.0f;
	vertex[20].color[1] = 1.0f;
	vertex[20].color[2] = 0.0f;

	vertex[21].color[0] = 0.0f;
	vertex[21].color[1] = 1.0f;
	vertex[21].color[2] = 0.0f;

	vertex[22].color[0] = 0.0f;
	vertex[22].color[1] = 1.0f;
	vertex[22].color[2] = 0.0f;

	vertex[23].color[0] = 0.0f;
	vertex[23].color[1] = 1.0f;
	vertex[23].color[2] = 0.0f;

	// ------------------------------------------------------------------------

	// front
	vertex[0].texel[0] = 0.5f;
	vertex[0].texel[1] = 0.5f;

	vertex[1].texel[0] = 0.25f;
	vertex[1].texel[1] = 0.5f;

	vertex[2].texel[0] = 0.25f;
	vertex[2].texel[1] = 0.25f;

	vertex[3].texel[0] = 0.5f;
	vertex[3].texel[1] = 0.25f;

	// top

	vertex[4].texel[0] = 0.25f;
	vertex[4].texel[1] = 0.0f;

	vertex[5].texel[0] = 0.5f;
	vertex[5].texel[1] = 0.0f;

	vertex[6].texel[0] = 0.5f;
	vertex[6].texel[1] = 0.25f;

	vertex[7].texel[0] = 0.25f;
	vertex[7].texel[1] = 0.25f;

	// back
	vertex[8].texel[0] = 1.0f;
	vertex[8].texel[1] = 0.5f;

	vertex[9].texel[0] = 0.75f;
	vertex[9].texel[1] = 0.5f;

	vertex[10].texel[0] = 0.75f;
	vertex[10].texel[1] = 0.25f;

	vertex[11].texel[0] = 1.0f;
	vertex[11].texel[1] = 0.25f;


	// bottom
	vertex[12].texel[0] = 0.5f;
	vertex[12].texel[1] = 0.75f;

	vertex[13].texel[0] = 0.25f;
	vertex[13].texel[1] = 0.75f;

	vertex[14].texel[0] = 0.25f;
	vertex[14].texel[1] = 0.5f;

	vertex[15].texel[0] = 0.5f;
	vertex[15].texel[1] = 0.5f;

	// left

	vertex[16].texel[0] = 0.75f;
	vertex[16].texel[1] = 0.5f;

	vertex[17].texel[0] = 0.5f;
	vertex[17].texel[1] = 0.5f;

	vertex[18].texel[0] = 0.5f;
	vertex[18].texel[1] = 0.25f;

	vertex[19].texel[0] = 0.75f;
	vertex[19].texel[1] = 0.25f;

	// right
	
	vertex[20].texel[0] = 0.25f;
	vertex[20].texel[1] = 0.5f;

	vertex[21].texel[0] = 0.0f;
	vertex[21].texel[1] = 0.5f;

	vertex[22].texel[0] = 0.0f;
	vertex[22].texel[1] = 0.25f;

	vertex[23].texel[0] = 0.25f;
	vertex[23].texel[1] = 0.25f;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 24, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader which would normally be loaded from an external file */
	std::string vsshader = readShader(std::string("vsshader.txt"));
	const char* vs_src = &vsshader[0]; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	std::string fsshader = readShader(std::string("fsshader.txt"));
	const char* fs_src = &fsshader[0]; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(GL_TEXTURE_2D, //2D Texture Image
		0, //Mipmapping Level 
		GL_RGBA, //GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width, //Width
		height, //Height
		0, //Border
		GL_RGBA, //Bitmap
		GL_UNSIGNED_BYTE, img_data);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	texelID = glGetAttribLocation(progID, "sv_texel");
	textureID = glGetUniformLocation(progID, "f_texture");

	glEnable(GL_CULL_FACE);
}

void Game::update()
{
	if (clock.getElapsedTime().asSeconds() > 1.0 / 60.0f)
	{
		glTranslatef(0.0f, 0.0f, 10.0f);
		// update game

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{

			for (int index = 0; index < VERTEX_NUM; index++)
			{
				Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], vertex[index].coordinate[2] };
				p = Matrix3().RotationZ(0.0703125) * p;

				vertex[index].coordinate[0] = p.getX();
				vertex[index].coordinate[1] = p.getY();
				vertex[index].coordinate[2] = p.getZ();
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			for (int index = 0; index < VERTEX_NUM; index++)
			{
				Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], vertex[index].coordinate[2] };
				p = Matrix3().RotationX(0.0703125) * p;

				vertex[index].coordinate[0] = p.getX();
				vertex[index].coordinate[1] = p.getY();
				vertex[index].coordinate[2] = p.getZ();
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{

			for (int index = 0; index < VERTEX_NUM; index++)
			{
				Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], vertex[index].coordinate[2] };
				p = Matrix3().RotationY(0.0703125) * p;

				vertex[index].coordinate[0] = p.getX();
				vertex[index].coordinate[1] = p.getY();
				vertex[index].coordinate[2] = p.getZ();
			}

		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{

		for (int index = 0; index < VERTEX_NUM; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], vertex[index].coordinate[2] };
			p = Matrix3().Scale3D(100.1) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
			vertex[index].coordinate[2] = p.getZ();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{

		for (int index = 0; index < VERTEX_NUM; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], vertex[index].coordinate[2] };
			p = Matrix3().Scale3D(99.9) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
			vertex[index].coordinate[2] = p.getZ();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		for (int index = 0; index < VERTEX_NUM; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], 1 };
			p = Matrix3().Translate(0, 0.02) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int index = 0; index < VERTEX_NUM; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], 1 };
			p = Matrix3().Translate(0, -0.02) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int index = 0; index < VERTEX_NUM; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], 1 };
			p = Matrix3().Translate(-0.02, 0) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int index = 0; index < VERTEX_NUM; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], 1 };
			p = Matrix3().Translate(0.02, 0) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
		}

	}

#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 24, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(texelID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
	stbi_image_free(img_data); //Free image
}

std::string Game::readShader(std::string t_fileName)
{
	std::string line;
	std::ifstream readFromFile(t_fileName);
	std::string fileContents;

	if (readFromFile.is_open())
	{
		while (std::getline(readFromFile, line)) // while there's lines to go through
		{
			fileContents += line;
		}
		}

	readFromFile.close();
	return fileContents;
	}