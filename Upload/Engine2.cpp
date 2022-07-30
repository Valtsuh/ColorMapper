#include <Windows.h>
#include <iostream>

#include "engine.literary.h"
#include "engine.database.h"
#include "engine.utils.h"
#include "engine.math.h"
#include "engine.drawer.h"
#include "engine.writer.h"
#include "engine.game.h"
#include "engine.runner.h"

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
				BLOCK *blk = &engine.blocks.colors[b];
				if (blk->measure._within(m->x, m->y)) {
					blk->color = engine.selected;
				}
			}

			if (engine.save.block.measure._within(m->x, m->y)) {
				std::fstream file;
				file.open("colormap.drx", std::fstream::out);
				if (file.is_open()) {
					std::cout << "\nSaving bitmap.drx";
					for (DINT b = 0; b < engine.blocks.colors.length; b++) {
						STRING color;
						BLOCK blk = engine.blocks.colors[b];
						color._append("{");
						color._append(WRITER::_itc(blk.color.r));
						color._append(",");
						color._append(WRITER::_itc(blk.color.g));
						color._append(",");
						color._append(WRITER::_itc(blk.color.b));
						if (blk.color.exist == 0) {
							color._append(",0 ");
						}
						color._append("}");
						if (b < engine.blocks.colors.length - 1) {
							color._append(",");
						}
						file << color.text;
					}
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
		//engine.game._play();
		while (PeekMessage(&engine.window.msg, engine.window.handle, 0, 0, PM_REMOVE)) {
			TranslateMessage(&engine.window.msg);
			DispatchMessage(&engine.window.msg);
		}
		state._clear(engine.bg);
		//engine._paint();
		engine._painter();
		state._draw(engine.window.handle);
		engine.stats._loop();
		engine.stats._sleep(5);
	} while (engine.on && engine.game.played);
	return 0;
}
