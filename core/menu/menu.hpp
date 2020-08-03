#pragma once
#include "zgui.hpp"
#include "../../dependencies/utilities/renderer/renderer.hpp"
#include "config.hpp"

namespace menu {
	void initialize();
	void draw();
	void GetConfigMassive();
}

extern std::vector<std::string> configs;