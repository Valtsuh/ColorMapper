
namespace Engine2 {
	struct GET {
		GET(const char title[], DINT type = 1, DINT spacing = 1) {
			this->title = title;
			this->open = type;
			this->spacing = spacing;
			this->bg = { 25, 25, 100, 30 };
		};
		GET() {
			this->open = 0;
		};

		DINT open, spacing;
		STRING title, cin;
		DIMENSION bg;


	};
	static KEYER keyer;
	static GET input;

	struct VERSION {
		VERSION(DINT h, DINT l, DINT s, DINT m) {
			huge = h;
			large = l;
			lesser = s;
			minor = m;
		}
		VERSION() {};
		static DINT minor, lesser, large, huge;

		static STRING _text() {
			STRING st;
			st._append(WRITER::_itc(huge));
			st._app('.');
			st._append(WRITER::_itc(large));
			st._app('.');
			st._append(WRITER::_itc(lesser));
			st._app('.');
			st._append(WRITER::_itc(minor));
			return st;
		}

	};

	struct ENGINE {
		ENGINE() {
			this->on = 0;
			this->configured = 0;
			WRITER(ENGINE_TYPOGRAPH);
			Engine2::ENGINE::version = { ENGINE_HUGE, ENGINE_LARGE, ENGINE_SMALL, ENGINE_MINOR };
			//std::cout << "\nVersion: " << Engine2::ENGINE::version._text().text;

		};
		using frames = std::chrono::duration<int64_t, std::ratio<1, 10>>;
		struct STATISTICS {
			STATISTICS() {
				this->fps = 0;
				Engine2::ENGINE::STATISTICS::nf = std::chrono::system_clock::now();
				//Engine2::ENGINE::STATISTICS::lf = nf - frames{ 1 };
				Engine2::ENGINE::STATISTICS::lf = std::chrono::system_clock::now();
			};

			DINT fps;
			COUNTER loops;
			TIME elapsed;
			static std::chrono::system_clock::time_point nf, lf;


			void _loop() {
				this->loops.current += 1;
				this->elapsed._increment(this->elapsed);
				if (this->loops.current > 0 && this->elapsed._since() > 0) this->fps = this->loops.current / this->elapsed._since();
			}

			void _sleep(SINT target = 60) {				
				if (target != -1 && target < 60) {
					target = 1000 / (target + target / 2);
					/*
					std::cout << "\nTime: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - Engine2::ENGINE::STATISTICS::lf).count() << " ms";
					std::this_thread::sleep_until(Engine2::ENGINE::STATISTICS::nf);
					Engine2::ENGINE::STATISTICS::lf = Engine2::ENGINE::STATISTICS::nf;
					Engine2::ENGINE::STATISTICS::nf += frames {1};
					*/

					Engine2::ENGINE::STATISTICS::lf = std::chrono::system_clock::now();
					std::chrono::duration<double, std::milli> work = Engine2::ENGINE::STATISTICS::lf - Engine2::ENGINE::STATISTICS::nf;
					if (work.count() < target) {
						std::chrono::duration<double, std::milli> delta_ms(target - work.count());
						auto delta_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
						std::this_thread::sleep_for(std::chrono::milliseconds(delta_duration.count()));
					}
					Engine2::ENGINE::STATISTICS::nf = std::chrono::system_clock::now();
					std::chrono::duration<double, std::milli> sleep = Engine2::ENGINE::STATISTICS::nf - Engine2::ENGINE::STATISTICS::lf;
					
					//std::cout << "\nSleep: " << (work.count() + sleep.count()) << " ms";

				}
			}

		};
		struct WINDOW {
			WINDOW() {
				this->handle = 0;
				this->info = {};
				this->msg = { 0 };
				this->x = 0;
				this->y = 0;
				this->width = 0;
				this->heigth = 0;
				this->window = {};
				this->client = {};
				this->result = -1;
				this->m = ENGINE_MOUSE;
			};
			~WINDOW() {
				this->handle = 0;
				this->info = {};
				this->msg = { 0 };
				this->x = 0;
				this->y = 0;
				this->width = 0;
				this->heigth = 0;
				this->window = {};
				this->client = {};
			};
			HWND handle;
			WNDCLASS info;
			RECT client, window;
			DINT width, heigth, x, y;
			MSG msg;
			DIMENSION mouse;
			SPRITE m;
			BOOL result;
			static DIMENSION measure;
			//TRACKMOUSEEVENT me;

			CHART<DISPLAY_DEVICE> dd;
			CHART<DEVMODE> dm;

			void _register(WNDPROC proc, HINSTANCE i, const wchar_t name[]) {
				this->info = {};
				this->info.lpfnWndProc = proc;
				this->info.hInstance = i;
				this->info.lpszClassName = name;
				this->info.hbrBackground = 0; // Note to self handle WM_ERASEBKGND [white stuck]
				this->info.hCursor = 0;
				this->info.style = 0;
				RegisterClass(&this->info);
				std::cout << "\nWindow registered. (" << GetCurrentThreadId() << ", " << GetLastError() << ")";

			};

			void _device() {

				DINT device = 0;
				BOOL devi = 0;
				DISPLAY_DEVICE dd = {};
				std::cout << "\nChecking devices.";
				do {
					devi = EnumDisplayDevicesW(NULL, device, &dd, EDD_GET_DEVICE_INTERFACE_NAME);
					device++;
					if (devi != 0)this->dd << dd;

				} while (devi != 0);

				std::cout << "\n Devices found: ";

				for (DINT i = 0; i < this->dd.length; i++) {
					if (this->dd.exist[i]) {
						dd = this->dd[i];
						std::cout << "\n> " << dd.DeviceName;
						std::cout << " - " << dd.DeviceString;
						std::cout << " - " << dd.DeviceID;
						std::cout << " : " << *reinterpret_cast<DWORD64*>(dd.DeviceName);
						std::cout << "\n Graphics modes: ";
						BOOL got = 0;
						DINT j = 0;
						DEVMODE dev = {};
						do {
							got = EnumDisplaySettings(dd.DeviceName, j, &dev);
							std::cout << "\n>> " << dev.dmDeviceName;
							std::cout << " - " << dev.dmDriverVersion;
							std::cout << " - " << dev.dmDriverExtra;
							std::cout << " - " << dev.dmDisplayFrequency;
							if (got != 0) this->dm << dev;
						} while (got != 0);

					}
				}

			}

			HWND _set(unsigned int w, unsigned int h, unsigned int x, unsigned int y) {
				this->x = x;
				this->y = y;
				this->width = w;
				this->heigth = h;
				this->handle = CreateWindow(this->info.lpszClassName, L"Title", WS_OVERLAPPEDWINDOW, this->x, this->y, this->width, this->heigth, NULL, NULL, this->info.hInstance, NULL);
				//SetWindowLong(this->handle, GWL_STYLE, WS_BORDER);
				if (this->handle == NULL) {
					system("pause");
				}
				else {
					/*
					this->me.cbSize = sizeof(this->me);
					this->me.dwFlags = TME_HOVER;
					this->me.hwndTrack = this->handle;
					this->me.dwHoverTime = 500;
					TrackMouseEvent(&this->me);
					*/
					std::cout << "\nWindow created. (" << this->handle << ", " << GetLastError() << ")";
					this->_position(w, h, x, y);
				}
				return this->handle;
			};

			HWND _position(SINT w, SINT h, SINT x, SINT y) {
				this->x = x;
				this->y = y;
				this->width = w;
				this->heigth = h;
				SetWindowPos(this->handle, HWND_TOP, this->x, this->y, this->width, this->heigth, SWP_SHOWWINDOW);
				SendMessage(this->handle, WM_SIZE, 0, 0);
				this->_client();
				this->_window();
				//ShowWindow(this->handle, SW_SHOW);
				//UpdateWindow(this->handle);
				std::cout << "\nWindow positioned. (" << this->handle << ", " << GetLastError() << "), " << w << ", " << h;
				return this->handle;
			}

			void _client() {
				GetClientRect(this->handle, &this->client);
			}

			void _window() {
				GetWindowRect(this->handle, &this->window);
			}

		};

		struct BUTTON {
			BUTTON(SPRITE sprite, DINT scale = 2) {
				//this->row = row;
				//this->col = col;
				this->scale = scale;
				this->sprite = sprite;
				this->sprite.scale = this->scale;
				this->current = this->sprite;

			};
			BUTTON() {};
			DINT mode, c, p, scale, row, col;

			STRING text;
			BLOCK block;
			SPRITE sprite, hover, active, current;
			DIMENSION measure;

			void _pos(DINT x, DINT y) {
				if(this->mode == 0) x = x - this->measure.w + this->p;
				if(this->mode == 0) y = y - this->p * 2;
				this->measure = { x, y, this->measure.w, this->measure.h };
				if(this->mode == 0) this->block._mea(this->measure.x, this->measure.y, this->measure.w, this->measure.h);
			}

			void _draw(SINT x = -1, SINT y = -1) {
				x = (x == -1) ? (this->measure.x) : (x);
				y = (y == -1) ? (this->measure.y) : (y);
				/*
				this->text.width += this->text.length * 1;
				state._set(this->block.measure.x, this->block.measure.y, LGR, this->block.measure.w, this->block.measure.h);
				WRITER::_type(this->text, x + this->p, y + this->p, this->scale, 1, B);
				*/
				this->current._draw(this->scale, x, y);

			}


		};

		struct TOOLBAR {
			TOOLBAR(DINT x, DINT y) {
				this->measure.x = x;
				this->measure.y = y;
				this->spacing = 3;
			};
			TOOLBAR() {
				this->spacing = 3;
			};

			CHART<BUTTON> button;
			CHART<DIMENSION> row;
			DIMENSION measure;
			DINT spacing;

			void _add(BUTTON button, DINT row) {
				DINT w = button.current.size.w * button.scale + this->spacing;
				DINT h = button.current.size.h * button.scale + this->spacing;
				if (this->row.length < row + 1) {
					this->measure.h += h;
					DIMENSION d = { this->measure.w, this->measure.h, w, h };
					this->row << d;
				}
				else {
					this->row[row].w += w;
				}
				button.measure = { this->measure.x - this->row[row].w, this->measure.y - this->row[row].y, w, h};
				this->button << button;
				this->measure.w += w;
			}

			void _pos(DINT x, DINT y) {
				this->measure.x = x;
				this->measure.y = y;
			}

			void _draw() {
				for (DINT b = 0; b < this->button.length; b++) {
					BUTTON button = this->button[b];
					button._draw();
				}
			}

		};

		void _update() {
			POINT* m = new POINT;
			if (GetCursorPos(m)) {
				if (ScreenToClient(this->window.handle, m)) {
					m->x = (m->x < 0) ? (0) : (m->x);
					m->y = (m->y < 0) ? (0) : (m->y);
					if (this->window.mouse.x != (DINT)m->x || this->window.mouse.y != (DINT)m->y) {
						this->window.mouse.x = (DINT)m->x;
						this->window.mouse.y = (DINT)m->y;
					}
				}
			}

			if (this->test.measure._within(m->x, m->y) && this->test.c == 0) {
				this->test.current = this->test.hover;
				this->test.c = 1;
			}
			if (this->test.c == 1 && this->test.measure._within(m->x, m->y) != 1) {
				this->test.current = this->test.sprite;
				this->test.c = 0;
			}

			if (Engine2::keyer.lclick) {
				for (DINT b = 0; b < this->blocks.colors.length; b++) {
					BLOCK* blk = &this->blocks.colors[b];
					if (blk->measure._within(m->x, m->y)) {
						blk->color = this->selected;
					}
				}
			}
			if (Engine2::keyer.rclick) {
				for (DINT b = 0; b < this->blocks.colors.length; b++) {
					BLOCK* blk = &this->blocks.colors[b];
					if (blk->measure._within(m->x, m->y)) {
						blk->color = X;
					}
				}
			}
			STRING title;
			title._append("ColorMapper");
			title._space("v");
			title._append(Engine2::ENGINE::version._text().text);
			title._space(WRITER::_itc(this->stats.fps));

			delete m;
			SetWindowText(this->window.handle, title.wtext);

		}

		void _config() {
			this->configured = 1;
			this->on = 1;
			this->clrs._generate(COLORLIST);
			//this->clrs = CLRS;
			DINT padding = 2;
			this->clrs._set(0, 0, 22, 0, 0, 16, 8, padding);
			this->clrs._offset(Engine2::ENGINE::WINDOW::measure.w - (this->clrs.r + 1) * (16 + padding));
			this->previous._form(1, 11, W, 16, 8, padding);
			this->previous._offset(Engine2::ENGINE::WINDOW::measure.w - (this->clrs.r + 1) * (16 + padding));
			this->bg = BG;
			this->selected = X;
			this->blocks._form(16, 16, X);

			DINT y = Engine2::ENGINE::WINDOW::measure.h - 22, p = 3;
			DIMENSION e = Engine2::ENGINE::WINDOW::measure;
			this->toolbar._pos(e.w, e.h);
			this->toolbar._add({ ENGINE_BUTTON_SAVE }, 0);
			this->toolbar._add({ ENGINE_BUTTON_LOAD }, 1);
			this->toolbar._add({ ENGINE_BUTTON_DARKEN }, 0);
			this->toolbar._add({ ENGINE_BUTTON_LIGHTEN }, 0);
			this->toolbar._add({ ENGINE_BUTTON_CLEAR }, 0);
			this->toolbar._add({ ENGINE_BUTTON_SMALL }, 0);
			this->toolbar._add({ ENGINE_BUTTON_MEDIUM }, 0);
			this->toolbar._add({ ENGINE_BUTTON_LARGE }, 0);
			Engine2::ENGINE::x = X;
			Engine2::ENGINE::marker = MARKER;


			Engine2::ENGINE::preview.size = 2;
			Engine2::ENGINE::preview.y = ENGINE_PREVIEW_Y;
			Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 16 - 2;
		}


		void _painter() {

			for (DINT b = 0; b < this->blocks.colors.length; b++) {
				BLOCK blk = this->blocks.colors[b];
				state._set(blk.measure.x, blk.measure.y, blk.color, blk.measure.w, blk.measure.h);
				state._set(Engine2::ENGINE::preview.x + blk.pos.x * Engine2::ENGINE::preview.size, Engine2::ENGINE::preview.y + blk.pos.y * Engine2::ENGINE::preview.size, blk.color, Engine2::ENGINE::preview.size, Engine2::ENGINE::preview.size);				
				state._set(Engine2::ENGINE::preview.x + blk.pos.x + this->blocks.w, Engine2::ENGINE::preview.y + blk.pos.y - this->blocks.h - 2, blk.color);
			}

			DINT spacing = 2;
		
			for (DINT c = 0; c < this->clrs.colors.length; c++){
				BLOCK blk = this->clrs.colors[c];
				if (blk.color == this->selected) {
					state._set(blk.measure.x - spacing, blk.measure.y - spacing, blk.color, blk.measure.w + spacing * 2, blk.measure.h + spacing * 2, 1, W);
				}
				else {
					if (blk.color == Engine2::ENGINE::x || blk.color == Engine2::ENGINE::marker) {
						state._set(blk.measure.x - spacing / 2, blk.measure.y - spacing / 2, blk.color, blk.measure.w + spacing, blk.measure.h + spacing, 1, {255, 200, 100});
					}
					else {
						state._set(blk.measure.x, blk.measure.y, blk.color, blk.measure.w, blk.measure.h);
					}
				}
			}

			for (DINT p = 0; p < this->previous.colors.length; p++) {
				BLOCK blk = this->previous.colors[p];
				state._set(blk.measure.x, blk.measure.y, blk.color, blk.measure.w, blk.measure.h);
			}

			for (DINT t = 0; t < this->tools.colors.length; t++) {
				BLOCK blk = this->tools.colors[t];
				state._set(blk.measure.x, blk.measure.y, blk.color, blk.measure.w, blk.measure.h);
			}

			DIMENSION d = Engine2::ENGINE::WINDOW::measure;
			state._set(d.w - (this->clrs.r + 3) * (this->clrs.colors[0].measure.w) - spacing, spacing, this->selected, 16, 16, 1, LGR);

			this->toolbar._draw();
			if (Engine2::input.open != 0) {
				DIMENSION i = Engine2::input.bg;
				DINT scale = 1;
				DINT l = (Engine2::input.cin.length > Engine2::input.title.length) ? (Engine2::input.cin.length) : (Engine2::input.title.length);
				state._set(i.x, i.y, LGR, 200, 30);
				WRITER::_type(Engine2::input.title, i.x + 5, i.y + 5, scale, 1, B);
				WRITER::_type(Engine2::input.cin, i.x + 5, i.y + 17, scale, 1, B);
			}

			//state._set(this->window.mouse.x - 1, this->window.mouse.y - 1, PNK, 2, 2);
			this->window.m._draw(-1, this->window.mouse.x - this->window.m.size.w / 2, this->window.mouse.y - this->window.m.size.h / 2);
		}
		static DIMENSION preview;
		static COLOR x, marker;
		static VERSION version;
		TOOLBAR toolbar;
		BUTTON save, load, clear, s, m, l, test, darken, lighten;
		COLOR bg;
		COLORS blocks, clrs, previous, tools;
		STATISTICS stats;
		WINDOW window;
		DINT on, configured;
		COLOR selected;
		SPRITE tst;

	};
	static HWND console;
	static HWND window;
}
DINT Engine2::VERSION::huge;
DINT Engine2::VERSION::large;
DINT Engine2::VERSION::lesser;
DINT Engine2::VERSION::minor;
Engine2::VERSION Engine2::ENGINE::version;
COLOR Engine2::ENGINE::x;
COLOR Engine2::ENGINE::marker;
DIMENSION Engine2::ENGINE::preview;
DIMENSION Engine2::ENGINE::WINDOW::measure;
std::chrono::system_clock::time_point Engine2::ENGINE::STATISTICS::nf;
std::chrono::system_clock::time_point Engine2::ENGINE::STATISTICS::lf;