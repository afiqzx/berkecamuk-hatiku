project('berkecamuk-hatiku', 'cpp', default_options: 'default_library=static')


subdir('src')
subdir('src/Physics')

sdl2_dep = dependency('sdl2')
sdl2_gfx_dep = dependency('SDL2_gfx')

executable('game', sources, dependencies: [sdl2_dep, sdl2_gfx_dep])
