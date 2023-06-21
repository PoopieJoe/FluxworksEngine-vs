# Engine Features

## Graphics Engine:
- DirectX11
- models
    - obj
    - fbx
- textures
    - 2D
    - 3D 
    - physically based
    - precedural
- rendering
    - forward (easy-ish) (if deffered is picked this could still be used for planar reflections or live cubmap reflections)
    - deffered (harder but probably prefered)
        - allow for more lights
    - ray tracing (probably a no no)
- animations
    - animation manager?
    - skeletal animations
        - seperate zones for animation?
    - morph meshes
- anti-aliasing
    - msaa (easy)
    - taa (medium)
    - dlss/fsr (??? nvidia or amd sdk required?? + motion vectors required!)
- shadows
    - shadow maps (hard but required)
    - screen space shadows (? probably hard-ish, useful on top of shadow maps for small details)
    - screen space ambient occlusion (medium and required)
- lighting extras
    - volumetrics
    - frustrum aligned voxel Volumetric fog
    - sparse voxel octree global illumination
    - other gi?
- other
    - tesselation 

## Audio Engine
- XAudio2
- Things?

## Network
- Later

## Resource Management & Monitoring
- Basic asset (un)loading and saving

## Physics Engine
- Rigid body dynamics
- Soft body dynamics?
- Fluid dynamics?
- Collision
- Constraint/Impulse-based

## Input
- KB+M
- Controller

## Event loop/Handler
- Messaging system between objects through Subject-Observer (subscription)

## Game Data
- Worlds/Scenes/Levels
- Camera view
- Entities/Objects/Components

## Scripting

## UI

## Accesibility

## AI
- Later