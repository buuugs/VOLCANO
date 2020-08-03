#pragma once
#include <cstdint>
#include <d3d9.h>

struct color {
	int a, r, g, b;
	color() = default;
	color(int r, int g, int b, int a = 255) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	color(uint32_t color) {
		this->a = (color >> 24) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->g = (color >> 8) & 0xff;
		this->b = (color & 0xff);
	}
	color from_uint(uint32_t uint) {
		return color(uint);
	}
	D3DCOLOR from_color(color col) {
		return D3DCOLOR_ARGB(col.a, col.r, col.g, col.b);
	}

	static color black(int a = 255) { return { 0, 0, 0, a }; }
	static color white(int a = 255) { return { 255, 255, 255, a }; }
	static color red(int   a = 255) { return { 255, 0, 0, a }; }
	static color green(int a = 255) { return { 0, 255, 0, a }; }
	static color blue(int  a = 255) { return { 0, 0, 255, a }; }
	static color from_float(float* clr, int a = 255) { return { int(clr[0] * 255.f), int(clr[1] * 255.f), int(clr[2] * 255.f), a }; }
};

struct color2 {
	int a, r, g, b;
	color2() = default;
	color2(int r, int g, int b, int a = 255) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	color2(uint32_t color) {
		this->a = (color >> 24) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->g = (color >> 8) & 0xff;
		this->b = (color & 0xff);
	}
	color2 from_uint(uint32_t uint) {
		return color2(uint);
	}
	D3DCOLOR from_color(color2 col) {
		return D3DCOLOR_ARGB(col.a, col.r, col.g, col.b);
	}

	static color2 black(int a = 255) { return { 0, 0, 0, a }; }
	static color2 white(int a = 255) { return { 255, 255, 255, a }; }
	static color2 red(int   a = 255) { return { 255, 0, 0, a }; }
	static color2 green(int a = 255) { return { 0, 255, 0, a }; }
	static color2 blue(int  a = 255) { return { 0, 0, 255, a }; }
	static color2 from_float(float* clr, int a = 255) { return { int(clr[0] * 255.f), int(clr[1] * 255.f), int(clr[2] * 255.f), a }; }
};