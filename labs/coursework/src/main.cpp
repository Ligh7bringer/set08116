#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

geometry geom;

//effects
effect eff, sky_eff, normal_map_eff;

free_camera cam;

//cursor position for camera
double cursor_x = 0.0;
double cursor_y = 0.0;

//textures
array<texture, 20> texs;
texture bark, house, bark_normal_map, wood_normal_map;

//map for meshes
map<string, mesh> meshes;
map<string, mesh> nmapobj;

//light
spot_light spot;
vector<point_light> points(2);
//cubemap for the skybox
cubemap cube_map;
mesh skybox;

bool initialiase() {
	// hide the pointer
	glfwSetInputMode(renderer::get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// get initial mouse x and y
	glfwGetCursorPos(renderer::get_window(), &cursor_x, &cursor_y);

	return true;
}

bool load_content() {

	//skybox
	skybox = mesh(geometry_builder::create_box());
	skybox.get_transform().scale = vec3(100, 100, 100);

	//plane
	meshes["plane"] = mesh(geometry_builder::create_plane());

	//meshes for the scene
	meshes["axe"].set_geometry(geometry("models/axe.obj"));
	meshes["path"] = mesh(geometry_builder::create_box(vec3(60, 1, 15)));
	meshes["barrel"] = mesh(geometry_builder::create_cylinder(20, 20));
	meshes["chair"].set_geometry(geometry("models/chair4.obj"));
	meshes["mill"].set_geometry(geometry("models/windmill.obj"));
	meshes["lamp"] = mesh(geometry("models/lamp.obj"));
	meshes["lamp2"] = mesh(geometry("models/lamp.obj"));
	nmapobj["tree1"].set_geometry(geometry("models/DeadTree.obj"));
	nmapobj["tree2"].set_geometry(geometry("models/DeadTree.obj"));
	nmapobj["house"].set_geometry(geometry("models/house.obj"));

	//set materials
	//house
	nmapobj["house"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	nmapobj["house"].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	nmapobj["house"].get_material().set_specular(vec4(0.5f, 0.35f, 0.05f, 1.0f));
	nmapobj["house"].get_material().set_shininess(5.0f);
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
	//lamp
	meshes["lamp"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["lamp"].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes["lamp"].get_material().set_specular(vec4(0.827f, 0.827f, 0.827f, 1.0f));
	meshes["lamp"].get_material().set_shininess(20.0f);
	//tree
	nmapobj["tree1"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	nmapobj["tree1"].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	nmapobj["tree1"].get_material().set_specular(vec4(0.827f, 0.827f, 0.827f, 1.0f));
	nmapobj["tree1"].get_material().set_shininess(10.0f);
	//tree2
	nmapobj["tree2"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	nmapobj["tree2"].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	nmapobj["tree2"].get_material().set_specular(vec4(0.663f, 0.663f, 0.663f, 1.0f));
	nmapobj["tree2"].get_material().set_shininess(10.0f);
	
	//mesh transformations
	//house
	nmapobj["house"].get_transform().position = vec3(20.0f, 0.0f, 10.0f);
	nmapobj["house"].get_transform().orientation = vec3(0.0f, half_pi<float>(), 0.0f);
	//tree
	nmapobj["tree1"].get_transform().position = vec3(10, 0, 40);
	nmapobj["tree1"].get_transform().scale = vec3(1.5f, 1.5f, 1.5f);
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
	nmapobj["tree2"].get_transform().position = vec3(29, 0, -25);
	nmapobj["tree2"].get_transform().scale = vec3(2.0f, 2.0f, 2.0f);
	//chair
	meshes["chair"].get_transform().position = vec3(9.0f, 1.0f, 7.0f);
	meshes["chair"].get_transform().orientation = vec3(0.0f, pi<float>(), 0.0f);
	//mill
	meshes["mill"].get_transform().position = vec3(-20, 0, -20);
	meshes["mill"].get_transform().scale = vec3(3.0f, 4.0f, 3.0f);
	//lamp2
	meshes["lamp2"].get_transform().position += vec3(0.0f, 0.0f, 20.0f);

	//textures
	bark = texture("textures/bark.jpg");
	house = texture("textures/house.jpg");
	bark_normal_map = texture("textures/treenormalmap.jpg");
	wood_normal_map = texture("textures/woodnormalmap.jpg");

	texs[0] = texture("textures/axe.png");
	texs[1] = texture("textures/barrel2.jpg");
	texs[2] = texture("textures/wood3.JPG");
	texs[3] = texture("textures/metal.jpg");
	texs[4] = texture("textures/metal.jpg");
	texs[5] = texture("textures/rust.jpg");
	texs[6] = texture("textures/pavement.jpg");
	texs[7] = texture("textures/grass2.jpg");

	//load skybox textures
	array<string, 6> filenames
	{
		"textures/cubemap/rt.tga", "textures/cubemap/lf.tga", "textures/cubemap/up2.jpg",
		"textures/cubemap/dn.tga", "textures/cubemap/bk.tga", "textures/cubemap/ft.tga"
	};

	//create cubemap
	cube_map = cubemap(filenames);

	//set light properties
	spot.set_position(vec3(vec3(50, 40, -50)));
	spot.set_light_colour(vec4(0.416f, 0.353f, 0.804f, 1.0f));
	spot.set_direction(normalize(-spot.get_position()));
	spot.set_range(500.0f);
	spot.set_power(10.0f);

	points[0].set_position(meshes["lamp"].get_transform().position + vec3(0, 10.0f, 0));
	points[0].set_light_colour(vec4(1.0f, 0.843f, 0.0f, 1.0f));
	points[0].set_range(20.0f);
	
	points[1].set_position(meshes["lamp2"].get_transform().position + vec3(0, 10.0f, 0));
	points[1].set_light_colour(points[0].get_light_colour());
	points[1].set_range(20.0f);

	// Load shaders
	//main effect
	eff.add_shader("shaders/main.vert", GL_VERTEX_SHADER);
	eff.add_shader("shaders/main.frag", GL_FRAGMENT_SHADER);
	//normal map effect
	normal_map_eff.add_shader("shaders/lights.frag", GL_FRAGMENT_SHADER);
	normal_map_eff.add_shader("shaders/part_normal_map.frag", GL_FRAGMENT_SHADER);
	normal_map_eff.add_shader("shaders/shader.frag", GL_FRAGMENT_SHADER);
	normal_map_eff.add_shader("shaders/shader.vert", GL_VERTEX_SHADER);
	//skybox effect
	sky_eff.add_shader("shaders/skybox.vert", GL_VERTEX_SHADER);
	sky_eff.add_shader("shaders/skybox.frag", GL_FRAGMENT_SHADER);

	// Build effects
	eff.build();
	normal_map_eff.build();
	sky_eff.build();

	// Set camera properties
	cam.set_position(vec3(-50.0f, 10.0f, 0.0f));
	cam.set_target(vec3(20.0f, 0.0f, 10.0f));
	cam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);

	return true;
}


bool update(float delta_time) {

	// Set skybox position to camera position
	skybox.get_transform().position = cam.get_position();

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
	cam.rotate(delta_x, -delta_y);

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

	// Update the camera
	cam.update(delta_time);

	return true;
}

bool render() {
	// Disable depth test,depth mask,face culling
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);
	
	// Bind skybox effect
	renderer::bind(sky_eff);
	
	// Calculate MVP for the skybox
	auto M = skybox.get_transform().get_transform_matrix();
	auto V = cam.get_view();
	auto P = cam.get_projection();
	auto MVP = P  * V * M;
	
	// Set MVP matrix uniform
	glUniformMatrix4fv(sky_eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));
	
	// Set cubemap uniform
	renderer::bind(cube_map, 0);
	glUniform1i(sky_eff.get_uniform_location("cubemap"), 0);
	
	// Render skybox
	renderer::render(skybox);
	
	// Enable depth test,depth mask,face culling
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);

	// Bind effect
	renderer::bind(normal_map_eff);
	
	int j = 0;

	for (auto &e : nmapobj) {
		auto m = e.second;

		mat4 M = m.get_transform().get_transform_matrix();
		auto V = cam.get_view();
		auto P = cam.get_projection();
		auto MVP = P * V * M;

		// Set MVP matrix uniform
		glUniformMatrix4fv(normal_map_eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));
		// Set M matrix uniform
		glUniformMatrix4fv(normal_map_eff.get_uniform_location("M"), 1, GL_FALSE, value_ptr(M));
		// Set N matrix uniform
		glUniformMatrix3fv(normal_map_eff.get_uniform_location("N"), 1, GL_FALSE,
			value_ptr(m.get_transform().get_normal_matrix()));

		// Bind material
		renderer::bind(m.get_material(), "mat");
		// Bind light
		renderer::bind(spot, "spot");
		renderer::bind(points, "points");

		if (j == 0) {
			// Bind texture
			renderer::bind(house, 0);
			// Set tex uniform
			glUniform1i(normal_map_eff.get_uniform_location("tex"), 0);
			// Bind normal_map
			renderer::bind(wood_normal_map, 1);
			// Set normal_map uniform
			glUniform1i(normal_map_eff.get_uniform_location("normal_map"), 1);
		}
		else {
			// Bind texture
			renderer::bind(bark, 0);
			// Set tex uniform
			glUniform1i(normal_map_eff.get_uniform_location("tex"), 0);
			// Bind normal_map
			renderer::bind(bark_normal_map, 1);
			// Set normal_map uniform
			glUniform1i(normal_map_eff.get_uniform_location("normal_map"), 1);
		}
		// Set eye position
		glUniform3fv(normal_map_eff.get_uniform_location("eye_pos"), 1, value_ptr(cam.get_position()));
		// Render mesh
		renderer::render(m);
		j++;
	}

	renderer::bind(eff);
	
	// accumulator to take care of textures and their ids when passing to the shader
	int i = 0;
	//for-each loop to take care of all meshes
	for (auto &e : meshes) {
		//get mesh
		auto m = e.second;

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

		// bind material
		renderer::bind(m.get_material(), "mat");
		// bind light
		renderer::bind(spot, "spot");
		renderer::bind(points, "points");
		//bind texture
		renderer::bind(texs[i], i);
		//set tex uniform
		glUniform1i(eff.get_uniform_location("tex"), i);
		// set eye position
		glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(cam.get_position()));

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
