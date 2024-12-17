add_library(gfx
	gfx.c
)

include_directories(gfx
	../ili9341
)

target_link_libraries(gfx
	pico_stdlib
	ili9341
)