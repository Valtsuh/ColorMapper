#include <Windows.h>
#include <iostream>

#include "engine.literary.h"
#include "engine.utils.h"
#include "engine.math.h"
#include "engine.drawer.h"
#include "engine.writer.h"
#include "cm.runner.h"

Engine2::ENGINE engine = {};
LRESULT CALLBACK _caller(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK _caller(HWND window, UINT msg, WPARAM w, LPARAM l)
{
	LRESULT result = 0;
	switch (msg) {
	case WM_CLOSE:
	case WM_QUIT:
	case WM_DESTROY: {
		engine.on = 0;
	} break;
	case WM_SIZE: {
		RECT rect;
		GetClientRect(window, &rect);
		state.w = rect.right - rect.left;
		state.h = rect.bottom - rect.top;
		Engine2::ENGINE::WINDOW::measure.w = state.w;
		Engine2::ENGINE::WINDOW::measure.h = state.h;
		Engine2::ENGINE::WINDOW::measure.x = rect.top;
		Engine2::ENGINE::WINDOW::measure.y = rect.left;
		state._config();
	} break;
	case WM_LBUTTONUP: {
		POINT* m = new POINT;
		if (GetCursorPos(m)) {
			if (ScreenToClient(engine.window.handle, m)) {
				m->x = (m->x < 0) ? (0) : (m->x);
				m->y = (m->y < 0) ? (0) : (m->y);
			}
		}
		for (DINT c = 0; c < engine.clrs.colors.length; c++) {
			BLOCK b = engine.clrs.colors[c];
			if (b.measure._within(m->x, m->y)) {
				engine.selected = b.color;
			}
		}
		for (DINT b = 0; b < engine.blocks.colors.length; b++) {
			BLOCK* blk = &engine.blocks.colors[b];
			if (blk->measure._within(m->x, m->y)) {
				blk->color = engine.selected;
			}
		}

		if (engine.save.block.measure._within(m->x, m->y)) {
			std::fstream file;
			file.open("colormap.drx", std::fstream::out);
			if (file.is_open()) {
				//system("cls");
				std::cout << "\nSaving colormap.drx";
				file << "{{";
				DINT c = 0, col = 0, r = 0, row = 0, f = 0, w = 0, h = 0;
				SINT fr = -1, fc = -1;
				for (DINT x = 0; x < engine.blocks.w; x++) {
					for (DINT y = 0; y < engine.blocks.h; y++) {
						BLOCK blk = engine.blocks._get(x, y);
						COLOR color = X;
						if (blk.color != color) {
							row = r;
							if (fr == -1) fr = row;
						}
					}
					r++;
				}
				f = 0;
				std::cout << "\nColor isn't X @ row: " << fr << " - " << row;
				for (DINT y = 0; y < engine.blocks.h; y++) {
					f = 0;
					for (DINT x = 0; x < engine.blocks.w; x++) {
						BLOCK blk = engine.blocks._get(x, y);
						COLOR color = X;
						if (blk.color != color) {
							col = c;
							if (fc == -1) fc = col;
						}
					}
					c++;
				}
				std::cout << "\nColor isn't X @ col: " << fc << " - " << col;
				DINT b = 0, l = (row - fr + 1) * (col - fc + 1);
				c = 0;
				r = 0;
				for (DINT x = fr; x <= row; x++) {
					c = 0;
					for (DINT y = fc; y <= col; y++) {
						STRING color;
						BLOCK blk = engine.blocks._get(x, y);
						color._append("{");
						color._append(WRITER::_itc(blk.color.r));
						color._append(",");
						color._append(WRITER::_itc(blk.color.g));
						color._append(",");
						color._append(WRITER::_itc(blk.color.b));
						if (blk.color.exist == 0) {
							color._append(",0");
						}
						color._append("}");
						if (b != l - 1) {
							color._append(",");
						}
						std::cout << "\nSaving: " << color.text;
						file << color.text;
						b++;
						c++;
					}
					r++;
				}
				for (DINT b = 0; b < engine.blocks.colors.length; b++) {
					BLOCK blk = engine.blocks.colors[b];
				}
				file << "},";
				file << r;
				file << ", ";
				file << c;
				file << "}";
				std::cout << "\n R: " << r << ", C: " << c << ", L: " << l;
			}
			else {
				std::cout << "\nUnable to open.";
			}
			//engine.bg = R;
		}

		delete m;
	} break;
	default: {
		result = DefWindowProc(window, msg, w, l);
	}
	}
	return result;
}

int main(HINSTANCE inst)
{
	if (engine.configured != 1) {
		engine.window._register(_caller, inst, L"Title");
		engine.window._set(600, 480, 25, 25);
		//engine.window._device();
		engine.stats.elapsed._clock(0);
		RECT rect;
		GetClientRect(engine.window.handle, &rect);
		state.w = rect.right - rect.left;
		state.h = rect.bottom - rect.top;
		state._config(0, 0);
		Engine2::ENGINE::WINDOW::measure.w = state.w;
		Engine2::ENGINE::WINDOW::measure.h = state.h;
		Engine2::ENGINE::WINDOW::measure.x = rect.top;
		Engine2::ENGINE::WINDOW::measure.y = rect.left;
		engine._config();
	}

	do {
		engine._update();
		while (PeekMessage(&engine.window.msg, engine.window.handle, 0, 0, PM_REMOVE)) {
			TranslateMessage(&engine.window.msg);
			DispatchMessage(&engine.window.msg);
		}
		state._clear(engine.bg);
		engine._painter();
		state._draw(engine.window.handle);
		engine.stats._loop();
		engine.stats._sleep(30);
	} while (engine.on);
	return 0;
}
