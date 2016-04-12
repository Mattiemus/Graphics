#include "Engine/Core/Engine.hpp"
#include "Engine/Graphics/Material.hpp"
#include "Implementation/Input/CameraController.hpp"
#include "Implementation/Graphics/FlickeringLight.hpp"
#include "Implementation/Scene/Terrain.hpp"
#include "Implementation/Scene/Tree.hpp"
#include "Implementation/Scene/Bench.hpp"
#include "Implementation/Scene/PlanetSpinner.hpp"
#include "Implementation/Scene/FirePit.hpp"
#include "Implementation/Scene/Grass.hpp"
#include "Implementation/Scene/Skybox.hpp"

#include <cstring>
#include <ctime>
#include <cstdlib>

#define PI 3.14159f

using namespace std;

int main(int argc, char* argv[])
{
    // Initialise the engine
    Engine::getInstance().init(1024, 768);
        
    // Create and attach the camera controller
    CameraController* camController = new CameraController();
    Engine::getInstance().addInputHandler(camController);
    Engine::getInstance().addUpdatable(camController);

    // Load materials
    Material* floorMaterial = Material::createLitParallaxMaterial("./Assets/Textures/tilefloor_diffuse.bmp",
        "./Assets/Textures/tilefloor_normal.bmp",
        "./Assets/Textures/tilefloor_specular.bmp",
        "./Assets/Textures/tilefloor_height.bmp");
    Material* pebbleMaterial = Material::createLitParallaxMaterial("./Assets/Textures/pebbles_diffuse.bmp",
        "./Assets/Textures/pebbles_normal.bmp",
        "./Assets/Textures/pebbles_specular.bmp",
        "./Assets/Textures/pebbles_height.bmp");
    Material* dirtMaterial = Material::createLitMaterial("./Assets/Textures/dirt_diffuse.bmp",
        "./Assets/Textures/dirt_normal.bmp",
        "./Assets/Textures/dirt_specular.bmp");
    dirtMaterial->connectParameter("textureRepeat", Vector2(15.0f, 15.0f));
    Material* woodMaterial = Material::createLitMaterial("./Assets/Textures/wood_diffuse.bmp",
        "./Assets/Textures/wood_normal.bmp",
        "./Assets/Textures/wood_specular.bmp");
    woodMaterial->connectParameter("textureRepeat", Vector2(0.5f, 1.0f));
    Material* barkMaterial = Material::createLitMaterial("./Assets/Textures/bark_diffuse.bmp",
        "./Assets/Textures/bark_normal.bmp",
        "./Assets/Textures/bark_specular.bmp");
    Material* rockMaterial = Material::createLitMaterial("./Assets/Textures/rock_diffuse.bmp",
        "./Assets/Textures/rock_normal.bmp",
        "./Assets/Textures/rock_specular.bmp");
    Material* leavesMaterial = Material::createLeavesMaterial("./Assets/Textures/leaves_diffuse.bmp");
    Material* grassMaterial = Material::createGrassMaterial("./Assets/Textures/grass_blades_diffuse.bmp");
    Material* fireMaterial = Material::createFireMaterial("./Assets/Textures/fire_diffuse.bmp");
    Material* frontSkyboxMaterial = Material::createSkyboxMaterial("./Assets/Textures/nightsky_north.bmp");
    Material* backSkyboxMaterial = Material::createSkyboxMaterial("./Assets/Textures/nightsky_south.bmp");
    Material* leftSkyboxMaterial = Material::createSkyboxMaterial("./Assets/Textures/nightsky_east.bmp");
    Material* rightSkyboxMaterial = Material::createSkyboxMaterial("./Assets/Textures/nightsky_west.bmp");
    Material* topSkyboxMaterial = Material::createSkyboxMaterial("./Assets/Textures/nightsky_up.bmp");

    // Add the skybox
    Skybox* sky = new Skybox(frontSkyboxMaterial, backSkyboxMaterial, topSkyboxMaterial, leftSkyboxMaterial, rightSkyboxMaterial);
    sky->getLocalTransform().setScale(Vector3(150000.0f, 150000.0f, 150000.0f));
    Engine::getInstance().getSceneRoot()->addChild(sky);
        
    // Add the planets
    PlanetSpinner* spinner = new PlanetSpinner(rockMaterial, rockMaterial);
    spinner->getLocalTransform().setScale(Vector3(1000.0f, 1000.0f, 1000.0f));
    spinner->getLocalTransform().setTranslation(Vector3(2500.0f, 0.0f, 2500.0f));
    Engine::getInstance().getSceneRoot()->addChild(spinner);

    // Generate terrain from heightmap
    Terrain* terrain = new Terrain("./Assets/Textures/terrain_height.bmp", dirtMaterial);
    terrain->getLocalTransform().setScale(Vector3(50000.0f, 1000.0f, 50000.0f));
    Engine::getInstance().getSceneRoot()->addChild(terrain);

    // Create the forest with a circle in the middle
    auto randFloat = []() { return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); };
    Tree* tree = new Tree(95u, barkMaterial, leavesMaterial);
    for (size_t x = 0; x < 8; x++) {
        for (size_t y = 0; y < 8; y++) {
            if ((x < 2 || x > 5) || (y < 2 || y > 5)) {
                Tree* treeCopy = Tree::cloneTree(tree);

                treeCopy->getLocalTransform().setScale(Vector3(600.0f + (randFloat() * 250.0f),
                    500.0f + (randFloat() * 100.0f),
                    600.0f + (randFloat() * 250.0f)));

                treeCopy->getLocalTransform().setTranslation(Vector3(6000.0f * x - 22000.0f, 
                    -440.0f + (220.0f * randFloat()),
                    6000.0f * y - 22000.0f));

                treeCopy->getLocalTransform().setRotation(Quaternion::fromAngleAxis(PI * 2.0f * randFloat(), 
                    Vector3(0.0f, 1.0f, 0.0f)));

                Engine::getInstance().getSceneRoot()->addChild(treeCopy);
            }
        }
    }

    // Create the grass patches
    Grass* grass = new Grass(terrain, grassMaterial, 236, 236, 0.3f, 0.3f);
    grass->getLocalTransform().setScale(Vector3(700.0f, 700.0f, 700.0f));
    grass->getLocalTransform().setTranslation(Vector3(-24500.0f, -440.0f, -24500.0f));
    Engine::getInstance().getSceneRoot()->addChild(grass);

    // Create some benches
    Bench* benchA = new Bench(barkMaterial, woodMaterial);
    benchA->getLocalTransform().setTranslation(Vector3(3.0f, -0.8f, -3.0f));
    benchA->getLocalTransform().setRotation(Quaternion::fromAngleAxis(PI / 4.0f, Vector3(0.0f, 1.0f, 0.0f)));
    Bench* benchB = new Bench(barkMaterial, woodMaterial);
    benchB->getLocalTransform().setTranslation(Vector3(-3.0f, -0.8f, -3.0f));
    benchB->getLocalTransform().setRotation(Quaternion::fromAngleAxis(-(PI / 4.0f), Vector3(0.0f, 1.0f, 0.0f)));
    Bench* benchC = new Bench(barkMaterial, woodMaterial);
    benchC->getLocalTransform().setTranslation(Vector3(3.0f, -0.8f, 3.0f));
    benchC->getLocalTransform().setRotation(Quaternion::fromAngleAxis(PI - (PI / 4.0f), Vector3(0.0f, 1.0f, 0.0f)));
    Bench* benchD = new Bench(barkMaterial, woodMaterial);
    benchD->getLocalTransform().setTranslation(Vector3(-3.0f, -0.8f, 3.0f));
    benchD->getLocalTransform().setRotation(Quaternion::fromAngleAxis(PI + (PI / 4.0f), Vector3(0.0f, 1.0f, 0.0f)));

    // Create the firepit
    FirePit* firepit = new FirePit(pebbleMaterial, floorMaterial, fireMaterial, barkMaterial);
    firepit->getLocalTransform().setTranslation(Vector3(0.0f, -0.8f, 0.0f));

    // Create the camping site group
    SceneObject* campSite = new SceneObject();
    campSite->getLocalTransform().setScale(Vector3(1000.0f, 1000.0f, 1000.0f));
    campSite->getLocalTransform().setTranslation(Vector3(-7000.0f, 0.0f, -7000.0f));
    campSite->addChild(benchA);
    campSite->addChild(benchB);
    campSite->addChild(benchC);
    campSite->addChild(benchD);
    campSite->addChild(firepit);
    Engine::getInstance().getSceneRoot()->addChild(campSite);

    // Add the light to the firepit
    FlickeringLight* firePitLight = new FlickeringLight(Vector4(0.9f, 0.5f, 0.0f, 1.0f), Vector4(0.8f, 0.4f, 0.0f, 0.0f));
    firePitLight->setPosition(firepit->getWorldTransform().getTranslation() + Vector3(0.0f, 2000.0f, 0.0f));
    firePitLight->setAmbientColor(Vector4(0.2f, 0.2f, 0.2f, 1.0f));
    firePitLight->setPower(2500000.0f);
    Engine::getInstance().addLight(firePitLight);
    Engine::getInstance().addUpdatable(firePitLight);

    // Start the scene!
    Engine::getInstance().run();

    // Cleanup
    return 1;
}
