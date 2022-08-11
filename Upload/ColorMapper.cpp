//#pragma source_character_set("utf-8")
//#pragma execution_character_set("utf-8")
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
			Engine2::ENGINE::WINDOW::measure._dump();
			GetClientRect(window, &rect);
			state.w = rect.right - rect.left;
			state.h = rect.bottom - rect.top;
			Engine2::ENGINE::WINDOW::measure.w = state.w;
			Engine2::ENGINE::WINDOW::measure.h = state.h;
			Engine2::ENGINE::WINDOW::measure.x = rect.top;
			Engine2::ENGINE::WINDOW::measure.y = rect.left;
			//Engine2::ENGINE::WINDOW::measure._dump();
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
					for (DINT c = engine.previous.h; c > 0; c--) {
						engine.previous.colors[c].color = engine.previous.colors[c - 1].color;
					}
					engine.previous.colors[0].color = engine.selected;
					break;
				}
			}

			for (DINT p = 0; p < engine.previous.colors.length; p++) {
				BLOCK b = engine.previous.colors[p];
				if (b.measure._within(m->x, m->y)) {
					engine.selected = b.color;
					break;
				}
			}

			for (DINT b = 0; b < engine.blocks.colors.length; b++) {
				BLOCK* blk = &engine.blocks.colors[b];
				if (blk->measure._within(m->x, m->y)) {
					if (Engine2::keyer.ctrl) {
						if (blk->color.exist) {
							COLOR c = blk->color;
							engine.selected = c;
							break;
						}
					}
					else {
						blk->color = engine.selected;
						break;
					}
				}
			}

			if (engine.save.measure._within(m->x, m->y) && Engine2::input.open == 0) {
				/*
				char save[32];
				HWND con = GetConsoleWindow();
				SetWindowPos(con, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
				std::cout << "\nSave as: ";
				std::cin >> save;
				STRING s = save;
				s._append(".drx");
				std::fstream file;
				//system("cls");
				DINT c = 0, col = 0, r = 0, row = 0, f = 0, w = 0, h = 0;
				SINT fr = -1, fc = -1;
				COLOR color = X;
				for (DINT x = 0; x < engine.blocks.w; x++) {
					for (DINT y = 0; y < engine.blocks.h; y++) {
						BLOCK blk = engine.blocks._get(x, y);
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
						if (blk.color != color) {
							col = c;
							if (fc == -1) fc = col;
						}
					}
					c++;
				}
				std::cout << "\nColor isn't X @ col: " << fc << " - " << col;

				if (fc != -1 && fr != -1) {
					file.open(s.text, std::fstream::out);
					if (file.is_open()) {
						DINT b = 0, l = (row - fr + 1) * (col - fc + 1);
						std::cout << "\nSaving " << s.text;
						file << "{{";
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
								//std::cout << "\nSaving: " << color.text;
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
				}
				else {
					std::cout << "\nEmpty map.";
				}

				*/
				Engine2::input = { "File: ", 2 };
				//engine.bg = R;
			}

			if (engine.load.measure._within(m->x, m->y) && Engine2::input.open == 0) {
				Engine2::input = { "File: " };
				/*
				SetWindowPos(Engine2::console, HWND_TOP, 250, 25, 0, 0, SWP_NOSIZE);
				std::cout << "\nFile to load: ";
				char name[32];
				std::cin >> name;
				Engine2::ENGINE::name._write(name);
				Engine2::ENGINE::name._append(".drx");
				std::cout << "\nLoading " << Engine2::ENGINE::name.text;
				engine.blocks = { Engine2::ENGINE::name.text };
				Engine2::ENGINE::preview.y = 325;
				if (engine.blocks.w == 32) {
					Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 32 - 2;
				}
				if (engine.blocks.w == 24) {
					Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 24 - 2;
				}
				if (engine.blocks.w == 16) {
					Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 16 - 2;
				}
				SetWindowPos(Engine2::window, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				*/
			}

			if (engine.clear.measure._within(m->x, m->y)) {
				for (DINT b = 0; b < engine.blocks.colors.length; b++) {
					engine.blocks.colors[b].color = X;
				}
			}

			if (engine.s.measure._within(m->x, m->y)) {
				/*
				engine.window._position(600, 480, engine.window.x, engine.window.y);
				engine.save._pos(Engine2::ENGINE::WINDOW::measure.w - 10, Engine2::ENGINE::WINDOW::measure.h - 10);
				engine.clear._pos(Engine2::ENGINE::WINDOW::measure.w - 60, Engine2::ENGINE::WINDOW::measure.h - 10);
				engine.s._pos(Engine2::ENGINE::WINDOW::measure.w - 110, Engine2::ENGINE::WINDOW::measure.h - 10);
				engine.m._pos(Engine2::ENGINE::WINDOW::measure.w - 160, Engine2::ENGINE::WINDOW::measure.h - 10);
				*/
				engine.blocks._form(16, 16, X);
				Engine2::ENGINE::preview.y = ENGINE_PREVIEW_Y;
				Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 16 - 2;
			}
			if (engine.m.measure._within(m->x, m->y)) {
				//engine.window._position(800, 600, engine.window.x, engine.window.y);
				//engine.save._pos(Engine2::ENGINE::WINDOW::measure.w - 10, Engine2::ENGINE::WINDOW::measure.h - 10);
				//engine.clear._pos(Engine2::ENGINE::WINDOW::measure.w - 60, Engine2::ENGINE::WINDOW::measure.h - 10);
				//engine.s._pos(Engine2::ENGINE::WINDOW::measure.w - 110, Engine2::ENGINE::WINDOW::measure.h - 10);
				//engine.m._pos(Engine2::ENGINE::WINDOW::measure.w - 160, Engine2::ENGINE::WINDOW::measure.h - 10);
				engine.blocks._form(24, 24, X, 14, 14);
				Engine2::ENGINE::preview.y = ENGINE_PREVIEW_Y;
				Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 24 - 2;
			}

			if (engine.l.measure._within(m->x, m->y)) {
				engine.blocks._form(32, 32, X, 12, 12);
				Engine2::ENGINE::preview.y = ENGINE_PREVIEW_Y;
				Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 32 - 2;
			}

			if (engine.test.block.measure._within(m->x, m->y)) {
				Engine2::input = { "File:" };
			}
			if (engine.test.measure._within(m->x, m->y)) {

				if (engine.test.c == 1) {
					Engine2::keyer.line = 1;
					engine.test.current = engine.test.active;
					engine.test.c = 2;
				}
				else {
					if (engine.test.c == 2) {
						Engine2::keyer.line = 0;
						engine.test.current = engine.test.hover;
						engine.test.c = 1;

					}
				}
			}
			Engine2::keyer.lclick = 0;
			delete m;
		} break;
		case WM_LBUTTONDOWN: {
			if(Engine2::keyer.ctrl == 0) Engine2::keyer.lclick = 1;
		} break;
		case WM_RBUTTONUP: {

			POINT* m = new POINT;
			if (GetCursorPos(m)) {
				if (ScreenToClient(engine.window.handle, m)) {
					m->x = (m->x < 0) ? (0) : (m->x);
					m->y = (m->y < 0) ? (0) : (m->y);
				}
			}

			for (DINT b = 0; b < engine.blocks.colors.length; b++) {
				BLOCK* blk = &engine.blocks.colors[b];
				if (blk->measure._within(m->x, m->y)) {
					blk->color = X;
					break;
				}
			}
			Engine2::keyer.rclick = 0;
			delete m;
		} break;
		case WM_RBUTTONDOWN: {
			Engine2::keyer.rclick = 1;
		} break;
		case WM_KEYUP: {
			if (Engine2::keyer.ctrl && w == 17) Engine2::keyer.ctrl = 0;
			if (Engine2::input.open) {
				if (w == 27) {
					Engine2::input.open = 0;
					break;
				}
				if (w != 13) {
					char c = WRITER::_valid(w);
					if (w == 8) {
						Engine2::input.cin._prev();
					}
					else {
						if (c != '?') {
							if (Engine2::input.cin.length < 32) {
								Engine2::input.cin._app(c);
							}
						}
					}
				}
				else {
					switch (Engine2::input.open) {
					default:
						case 1: {
							std::cout << "\nLoading " << Engine2::input.cin.text;
							engine.blocks = { Engine2::input.cin.text };
							DINT m = 0, f = 0;
							CHART <BLOCK> blks;
							for (DINT c = 0; c < engine.blocks.colors.length; c++) {
								BLOCK blk = engine.blocks.colors[c];
								f = 0;
								if (blk.color.exist) {
									for (DINT b = 0; b < blks.length; b++) {
										if (blks[b].color == blk.color) {
											f = 1;
											break;
										}

									}
									if (f == 0 && blks.length < 11) blks << blk;
								}
							}
							for (DINT b = 0; b < blks.length; b++) engine.previous.colors[b].color = blks[b].color;
							blks._close();
							Engine2::ENGINE::preview.y = ENGINE_PREVIEW_Y;
							if (engine.blocks.w == 32) {
								Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 32 - 2;
							}
							if (engine.blocks.w == 24) {
								Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 24 - 2;
							}
							if (engine.blocks.w == 16) {
								Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 16 - 2;
							}
						} break;
						case 2: {
							std::fstream file;
							//system("cls");
							DINT c = 0, col = 0, r = 0, row = 0, f = 0, w = 0, h = 0;
							SINT fr = -1, fc = -1;
							COLOR marker = MARKER;
							for (DINT x = 0; x < engine.blocks.w; x++) {
								for (DINT y = 0; y < engine.blocks.h; y++) {
									BLOCK blk = engine.blocks._get(x, y);
									if (blk.color.exist || blk.color == marker) {
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
									if (blk.color.exist || blk.color == marker) {
										col = c;
										if (fc == -1) fc = col;
									}
								}
								c++;
							}
							std::cout << "\nColor isn't X @ col: " << fc << " - " << col;

							if (fc != -1 && fr != -1) {
								Engine2::input.cin._append(".drx");
								file.open(Engine2::input.cin.text, std::fstream::out);
								if (file.is_open()) {
									DINT b = 0, l = (row - fr + 1) * (col - fc + 1);
									std::cout << "\nSaving " << Engine2::input.cin.text;
									file << "{{";
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
											//std::cout << "\nSaving: " << color.text;
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
							}
							else {
								std::cout << "\nEmpty map.";
							}
						} break;
					}
					Engine2::input.open = 0;
				}
			}
		} break;
		case WM_KEYDOWN: {
			if (w == 17) Engine2::keyer.ctrl = 1;

		};
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
		Engine2::window = engine.window.handle;
		GetClientRect(engine.window.handle, &rect);
		state.w = rect.right - rect.left;
		state.h = rect.bottom - rect.top;
		state._config(0, 0);
		Engine2::ENGINE::WINDOW::measure.w = state.w;
		Engine2::ENGINE::WINDOW::measure.h = state.h;
		Engine2::ENGINE::WINDOW::measure.x = rect.top;
		Engine2::ENGINE::WINDOW::measure.y = rect.left;
		engine._config();
		Engine2::console = GetConsoleWindow();
		//SetWindowPos(Engine2::console, HWND_TOP, 250, 25, 0, 0, SWP_NOSIZE);
	}

	//std::cout << "\nFile to load: ";
	//char name[32];
	//std::cin >> name;
	//Engine2::ENGINE::name._write(name);
	/*
	if (Engine2::ENGINE::name.length > 0) {
		Engine2::ENGINE::name._append(".drx");
		std::cout << "\nLoading " << Engine2::ENGINE::name.text;
		engine.blocks = { Engine2::ENGINE::name.text };
		Engine2::ENGINE::preview.y = 325;
		if (engine.blocks.w == 32) {		
			Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 32 - 2;
		}
		if (engine.blocks.w == 24) {
			Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 24 - 2;
		}
		if (engine.blocks.w == 16) {
			Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 16 - 2;
		}
		SetWindowPos(Engine2::window, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
	*/
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
