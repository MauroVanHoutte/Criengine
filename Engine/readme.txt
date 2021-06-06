https://github.com/MauroVanHoutte/Criengine


The engine uses a time singleton instead of dependency injection
The engine only renders and updates the currently active scene, scenes can be cycled through or open at will
GameObjects can be deactivated and activated which disables and enables rendering and updating of their components
Components in turn can also be activated or deactivated
Commands are linked to input for a specific scene, the same command can be added multiple times for use in multiple scenes

