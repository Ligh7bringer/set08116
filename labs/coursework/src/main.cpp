#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

geometry geom;
effect eff;
effect shadow_eff;
free_camera cam;

//cursor position for camera
double cursor_x = 0.0;
double cursor_y = 0.0;

//textures
array<texture, 9> texs;

//map for meshes
map<string, mesh> meshes;

//light
spot_light spot;

//shadow map
shadow_map shadow;

bool initialiase() {
	// hide the pointer
	glfwSetInputMode(renderer::get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// get initial mouse x and y
	glfwGetCursorPos(renderer::get_window(), &cursor_x, &cursor_y);

	return true;
}

bool load_content() {
	// Create shadow map with screen dimensions
	shadow = shadow_map(renderer::get_screen_width(), renderer::get_screen_height());

	//plane
	meshes["plane"] = mesh(geometry_builder::create_plane());

	//meshes for the scene
	meshes["house"].set_geometry(geometry("models/house.obj"));
	meshes["tree"].set_geometry(geometry("models/DeadTree.obj"));
	meshes["axe"].set_geometry(geometry("models/axe.obj"));
	meshes["path"] = mesh(geometry_builder::create_box(vec3(60, 1, 15)));
	meshes["barrel"] = mesh(geometry_builder::create_cylinder(20, 20));
	meshes["tree2"] = meshes["tree"];
	meshes["chair"].set_geometry(geometry("models/chair4.obj"));
	meshes["mill"].set_geometry(geometry("models/windmill.obj"));

	//set materials
	//house
	meshes["house"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["house"].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes["house"].get_material().set_specular(vec4(0.5f, 0.35f, 0.05f, 1.0f));
	meshes["house"].get_material().set_shininess(5.0f);
	//tree
	meshes["tree"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["tree"].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes["tree"].get_material().set_specular(vec4(0.827f, 0.827f, 0.827f, 1.0f));
	meshes["tree"].get_material().set_shininess(10.0f);
	//axe
	meshes["axe"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["axe"].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes["axe"].get_material().set_specular(vec4(0.5f, 0.35f, 0.05f, 1.0f));
	meshes["axe"].get_material().set_shininess(10.0f);
	//path
	meshes["path"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["path"].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes["path"].get_material().set_specular(vec4(0.5f, 0.5f, 0.5f, 1.0f));
	meshes["path"].get_material().set_shininess(10.0f);
	//barrel
	meshes["barrel"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["barrel"].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes["barrel"].get_material().set_specular(vec4(0.545f, 0.271f, 0.075f, 1.0f));
	meshes["barrel"].get_material().set_shininess(10.0f);
	//tree2
	meshes["tree2"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["tree2"].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes["tree2"].get_material().set_specular(vec4(0.663f, 0.663f, 0.663f, 1.0f));
	meshes["tree2"].get_material().set_shininess(10.0f);
	//chair
	meshes["chair"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["chair"].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes["chair"].get_material().set_specular(vec4(0.545f, 0.271f, 0.075f, 1.0f));
	meshes["chair"].get_material().set_shininess(10.0f);
	//mill
	meshes["mill"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["mill"].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes["mill"].get_material().set_specular(vec4(0.871f, 0.722f, 0.529f, 1.0f));
	meshes["mill"].get_material().set_shininess(10.0f);

	//mesh transformations
	//house
	meshes["house"].get_transform().position = vec3(20.0f, 0.0f, 10.0f);
	meshes["house"].get_transform().orientation = vec3(0.0f, half_pi<float>(), 0.0f);
	//tree
	meshes["tree"].get_transform().position = vec3(10, 0, 40);
	meshes["tree"].get_transform().scale = vec3(1.5f, 1.5f, 1.5f);
	//axe
	meshes["axe"].get_transform().position = vec3(11.5f, 4.0f, 37);
	meshes["axe"].get_transform().scale = vec3(8.0f, 8.0f, 8.0f);
	meshes["axe"].get_transform().orientation = vec3(half_pi<float>(), 2 * pi<float>() / 45.0f, half_pi<float>());
	//path
	meshes["path"].get_transform().position.x -= 20;
	meshes["path"].get_transform().position.z += 10;
	//barrel
	meshes["barrel"].get_transform().scale = vec3(3.0f, 4.0f, 3.0f);
	meshes["barrel"].get_transform().position = vec3(15, 2, -2);
	//another tree
	meshes["tree2"].get_transform().position = vec3(29, 0, -25);
	meshes["tree2"].get_transform().scale = vec3(2.0f, 2.0f, 2.0f);
	//chair
	meshes["chair"].get_transform().position = vec3(9.0f, 1.0f, 7.0f);
	meshes["chair"].get_transform().orientation = vec3(0.0f, pi<float>(), 0.0f);
	//mill
	meshes["mill"].get_transform().position = vec3(-20, 0, -20);
	meshes["mill"].get_transform().scale = vec3(3.0f, 4.0f, 3.0f);

	//textures
	texs[0] = texture("textures/axe.png");
	texs[1] = texture("textures/barrel2.jpg");
	texs[2] = texture("textures/wood3.JPG");
	texs[3] = texture("textures/house.jpg");
	texs[4] = texture("textures/rust.jpg");
	texs[5] = texture("textures/pavement.jpg");
	texs[6] = texture("textures/grass2.jpg");
	texs[7] = texture("textures/bark2.jpg");
	texs[8] = texture("textures/bark.jpg");

	//set light properties
	spot.set_position(vec3(vec3(-50, 40, 50)));
	spot.set_light_colour(vec4(0.416f, 0.353f, 0.804f, 1.0f));
	spot.set_direction(normalize(-spot.get_position()));
	spot.set_range(500.0f);
	spot.set_power(10.0f);

	// Load shaders
	eff.add_shader("shaders/shadow.vert", GL_VERTEX_SHADER);
	vector<string> frag_shaders{ "shaders/shadow.frag", "shaders/part_s.frag", "shaders/part_shd.frag" };
	eff.add_shader(frag_shaders, GL_FRAGMENT_SHADER);

	shadow_eff.add_shader("shaders/spot.vert", GL_VERTEX_SHADER);
	shadow_eff.add_shader("shaders/spot.frag", GL_FRAGMENT_SHADER);

	// Build effect
	eff.build();
	shadow_eff.build();

	// Set camera properties
	cam.set_position(vec3(-50.0f, 10.0f, 0.0f));
	cam.set_target(vec3(20.0f, 0.0f, 10.0f));
	cam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);

	return true;
}


bool update(float delta_time) {
	// The ratio of pixels to rotation
	static double ratio_width = quarter_pi<float>() / static_cast<float>(renderer::get_screen_width());
	static double ratio_height =
		(quarter_pi<float>() *
		(static_cast<float>(renderer::get_screen_height()) / static_cast<float>(renderer::get_screen_width()))) /
		static_cast<float>(renderer::get_screen_height());

	//variable where mouse position will be stored
	double current_x;
	double current_y;

	// Get the current cursor position
	glfwGetCursorPos(renderer::get_window(), &current_x, &current_y);
	// Calculate delta of cursor positions
	double delta_x = current_x - cursor_x;
	double delta_y = current_y - cursor_y;

	// Multiply deltas by ratios
	delta_x = delta_x*ratio_width;
	delta_y = delta_y*ratio_height;

	// Rotate camera
	cam.rotate(delta_x, delta_y);

	// keyboard controls for camera
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_W))
	{
		cam.move(vec3(0.0f, 0.0f, 1.0f));
	}
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_S))
	{
		cam.move(vec3(0.0f, 0.0f, -1.0f));
	}
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_A))
	{
		cam.move(vec3(-1.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_D))
	{
		cam.move(vec3(1.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_SPACE))
	{
		cam.move(vec3(0.0f, 1.0f, 0.0f));
	}
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_LEFT_SHIFT))
	{
		cam.move(vec3(0.0f, -1.0f, 0.0f));
	}

	//go to the 4 corners of the plane
	if (glfwGetKey(renderer::get_window(), '1')) {
		cam.set_position(vec3(50, 10, 50));
	}
	if (glfwGetKey(renderer::get_window(), '2')) {
		cam.set_position(vec3(-50, 10, 50));
	}
	if (glfwGetKey(renderer::get_window(), '3')) {
		cam.set_position(vec3(-50, 10, -50));
	}
	if (glfwGetKey(renderer::get_window(), '4')) {
		cam.set_position(vec3(50, 10, -50));
	}

	// old cursor position becomes current
	cursor_x = current_x;
	cursor_y = current_y;

	// update light position
	shadow.light_position = spot.get_position();
	// update light dir
	shadow.light_dir = spot.get_direction();

	// Update the camera
	cam.update(delta_time);

	return true;
}

bool render() {
	renderer::set_render_target(shadow);
	// Clear depth buffer bit
	glClear(GL_DEPTH_BUFFER_BIT);
	// Set face cull mode to front
	glCullFace(GL_FRONT);

	//calcuate light projection matrix
	mat4 LightProjectionMat = perspective<float>(90.f, renderer::get_screen_aspect(), 0.1f, 1000.f);

	//bind shadow effect
	renderer::bind(shadow_eff);

	for (auto &e : meshes) {
		auto m = e.second;
		// Create MVP matrix
		auto M = m.get_transform().get_transform_matrix();
		// View matrix taken from shadow map
		auto V = shadow.get_view();
		// calculate mvp
		auto MVP = LightProjectionMat * V * M;
		// Set MVP matrix uniform
		glUniformMatrix4fv(shadow_eff.get_uniform_location("MVP"), // Location of uniform
			1,                                      // Number of values - 1 mat4
			GL_FALSE,                               // Transpose the matrix?
			value_ptr(MVP));                        // Pointer to matrix data
													// Render mesh
		renderer::render(m);
	}

	//set render target to screen
	renderer::set_render_target();
	// Set face cull mode to back
	glCullFace(GL_BACK);

	// Bind shader
	renderer::bind(eff);

	// accumulator to take care of textures and their ids when passing to the shader
	int i = 0;
	//for-each loop to take care of all meshes
	for (auto &e : meshes) {
		//get mesh
		auto m = e.second;
		// Bind effect
		renderer::bind(eff);

		// Create MVP matrix
		mat4 M = m.get_transform().get_transform_matrix();
		auto V = cam.get_view();
		auto P = cam.get_projection();
		auto MVP = P * V * M;

		// Set MVP uniform
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));
		// set M uniform
		glUniformMatrix4fv(eff.get_uniform_location("M"), 1, GL_FALSE, value_ptr(M));
		// Set N uniform
		glUniformMatrix3fv(eff.get_uniform_location("N"), 1, GL_FALSE, value_ptr(m.get_transform().get_normal_matrix()));

		// Set lightMVP uniform, using:
		//Model matrix from m
		auto light_model = M;
		// viewmatrix from the shadow map
		auto shadow_view = shadow.get_view();
		// Multiply together with LightProjectionMat
		auto lightMVP = LightProjectionMat * shadow_view * light_model;
		// Set uniform
		glUniformMatrix4fv(eff.get_uniform_location("lightMVP"), 1, GL_FALSE, value_ptr(lightMVP));

		// bind material
		renderer::bind(m.get_material(), "mat");
		// bind light
		renderer::bind(spot, "spot");
		//bind texture
		renderer::bind(texs[i], i);
		//set tex uniform
		glUniform1i(eff.get_uniform_location("tex"), i);
		// set eye position
		glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(cam.get_position()));

		//bind shadow texture and set uniform
		renderer::bind(texs[i], i + 20);
		glUniform1i(eff.get_uniform_location("shadow_map"), i + 20);

		// render mesh
		renderer::render(m);

		//dont forget to increment i
		i++;
	}
	return true;
}

void main() {
	// Create application
	app application("Graphics Coursework");
	// Set load content, update and render methods
	application.set_load_content(load_content);
	application.set_initialise(initialiase);
	application.set_update(update);
	application.set_render(render);
	// Run application
	application.run();
}
